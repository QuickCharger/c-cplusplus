#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

#define MAXLINE 5
#define OPEN_MAX 100
#define LISTENQ 20
#define SERV_PORT 5000
#define INFTIM 1000

int main()
{
	int maxi, listenfd, sockfd, epfd;
	size_t n;
	char line[MAXLINE];
	socklen_t clilen;
	
	struct epoll_event ev, events[20];
	epfd = epoll_create(1);	//创建epoll句柄,参数解释：应该是自从linux2.6.8之后，size参数是被忽略的，只要它比0大就可以。
	struct sockaddr_in clientaddr, serveraddr;
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	
	ev.data.fd = listenfd;
	ev.events = EPOLLIN | EPOLLET;
	
	epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);
	//bzero(&serveraddr, sizeof(serveraddr));
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	const char *local_addr = "127.0.0.1";
	inet_aton(local_addr, &(serveraddr.sin_addr));

	serveraddr.sin_port = htons(SERV_PORT);
	bind(listenfd, (sockaddr*)&serveraddr, sizeof(serveraddr));
	listen(listenfd, LISTENQ);
	maxi = 0;
	for(;;)
	{
		int nfds = epoll_wait(epfd, events, 20, 500);	//等待500ms, 取最多20个socket并放置在events中
		for(int i = 0; i < nfds; ++i)
		{
			if(events[i].data.fd == listenfd)	//新的链接
			{
				int connfd = accept(listenfd, (sockaddr*)&clientaddr, &clilen);
				if(connfd < 0)
				{
					perror("connfd < 0");
					exit(1);
				}
				char *str = inet_ntoa(clientaddr.sin_addr);
				cout << "accept a connection from " << str << endl;
				ev.data.fd = connfd;
				ev.events = EPOLLIN | EPOLLET;
				epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev);	//将新链接添加到epoll监听队列中
			}
			else if(events[i].events & EPOLLIN)	//收到数据, 读socket
			{
				cout << "EPOLLIN" << endl;
				if((sockfd = events[i].data.fd) < 0)
					continue;
				if((n = read(sockfd, line, MAXLINE)) < 0)
				{
					if(errno == ECONNRESET)
					{
						close(sockfd);
						events[i].data.fd = -1;
					}
					else
					{
						cout << "readline error" << endl;
					}
				}
				else if( n == 0)
				{
					close(sockfd);
					events[i].data.fd = -1;
				}
				line[n] = '\0';
				cout << "read" << line << endl;
				ev.data.fd = sockfd;
				ev.events = EPOLLOUT | EPOLLET;
			}
			else if(events[i].events & EPOLLOUT)	//有数据待发送,写socket
			{
				sockfd = events[i].data.fd;
				write(sockfd, line, n);
				ev.data.fd = sockfd;
				ev.events = EPOLLIN | EPOLLET;
				epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
			}
		}
	}
	return 0;
}

/*
1. int epoll_create(int size);
创建一个epoll的句柄，size用来告诉内核这个监听的数目一共有多大。这个参数不同于select()中的第一个参数，给出最大监听的fd+1的值。需要注意的是，当创建好epoll句柄后，它就是会占用一个fd值，在linux下如果查看/proc/进程id/fd/，是能够看到这个fd的，所以在使用完epoll后，必须调用close()关闭，否则可能导致fd被耗尽。


2. int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
epoll的事件注册函数，它不同与select()是在监听事件时告诉内核要监听什么类型的事件，而是在这里先注册要监听的事件类型。第一个参数是epoll_create()的返回值，第二个参数表示动作，用三个宏来表示：
EPOLL_CTL_ADD：注册新的fd到epfd中；
EPOLL_CTL_MOD：修改已经注册的fd的监听事件；
EPOLL_CTL_DEL：从epfd中删除一个fd；
第三个参数是需要监听的fd，第四个参数是告诉内核需要监听什么事，struct epoll_event结构如下：

typedef union epoll_data {
    void *ptr;
    int fd;
    __uint32_t u32;
    __uint64_t u64;
} epoll_data_t;

struct epoll_event {
    __uint32_t events; /* Epoll events /
    epoll_data_t data; /* User data variable /
};

events可以是以下几个宏的集合：
EPOLLIN ：表示对应的文件描述符可以读（包括对端SOCKET正常关闭）；
EPOLLOUT：表示对应的文件描述符可以写；
EPOLLPRI：表示对应的文件描述符有紧急的数据可读（这里应该表示有带外数据到来）；
EPOLLERR：表示对应的文件描述符发生错误；
EPOLLHUP：表示对应的文件描述符被挂断；
EPOLLET： 将EPOLL设为边缘触发(Edge Triggered)模式，这是相对于水平触发(Level Triggered)来说的。
EPOLLONESHOT：只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个socket的话，需要再次把这个socket加入到EPOLL队列里


3. int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);
等待事件的产生，类似于select()调用。参数events用来从内核得到事件的集合，maxevents告之内核这个events有多大，这个 maxevents的值不能大于创建epoll_create()时的size，参数timeout是超时时间（毫秒，0会立即返回，-1将不确定，也有说法说是永久阻塞）。该函数返回需要处理的事件数目，如返回0表示已超时。


4、关于ET、LT两种工作模式：
可以得出这样的结论:
ET模式仅当状态发生变化的时候才获得通知,这里所谓的状态的变化并不包括缓冲区中还有未处理的数据,也就是说,如果要采用ET模式,需要一直read/write直到出错为止,很多人反映为什么采用ET模式只接收了一部分数据就再也得不到通知了,大多因为这样;而LT模式是只要有数据没有处理就会一直通知下去的.

流程：
首先通过create_epoll(int maxfds)来创建一个epoll的句柄，其中maxfds为你epoll所支持的最大句柄数。这个函数会返回一个新的epoll句柄，之后的所有操作将通过这个句柄来进行操作。在用完之后，记得用close()来关闭这个创建出来的epoll句柄。

之后在你的网络主循环里面，每一帧的调用epoll_wait(int epfd, epoll_event events, int max events, int timeout)来查询所有的网络接口，看哪一个可以读，哪一个可以写了。基本的语法为：
nfds = epoll_wait(kdpfd, events, maxevents, -1);
其中kdpfd为用epoll_create创建之后的句柄，events是一个epoll_event*的指针，当epoll_wait这个函数操作成功之后，epoll_events里面将储存所有的读写事件。max_events是当前需要监听的所有socket句柄数。最后一个timeout是 epoll_wait的超时，为0的时候表示马上返回，为-1的时候表示一直等下去，直到有事件范围，为任意正整数的时候表示等这么长的时间，如果一直没有事件，则范围。一般如果网络主循环是单独的线程的话，可以用-1来等，这样可以保证一些效率，如果是和主逻辑在同一个线程的话，则可以用0来保证主循环的效率。

epoll_wait范围之后应该是一个循环，遍利所有的事件。

参考文章：http://blog.csdn.net/ljx0305/article/details/4065058

这个链接的完整示例未看
http://www.cppblog.com/API/archive/2013/07/01/201424.html
*/
