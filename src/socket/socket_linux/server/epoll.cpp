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
	epfd = epoll_create(1);	//����epoll���,�������ͣ�Ӧ�����Դ�linux2.6.8֮��size�����Ǳ����Եģ�ֻҪ����0��Ϳ��ԡ�
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
		int nfds = epoll_wait(epfd, events, 20, 500);	//�ȴ�500ms, ȡ���20��socket��������events��
		for(int i = 0; i < nfds; ++i)
		{
			if(events[i].data.fd == listenfd)	//�µ�����
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
				epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev);	//����������ӵ�epoll����������
			}
			else if(events[i].events & EPOLLIN)	//�յ�����, ��socket
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
			else if(events[i].events & EPOLLOUT)	//�����ݴ�����,дsocket
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
����һ��epoll�ľ����size���������ں������������Ŀһ���ж�����������ͬ��select()�еĵ�һ��������������������fd+1��ֵ����Ҫע����ǣ���������epoll����������ǻ�ռ��һ��fdֵ����linux������鿴/proc/����id/fd/�����ܹ��������fd�ģ�������ʹ����epoll�󣬱������close()�رգ�������ܵ���fd���ľ���


2. int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
epoll���¼�ע�ắ��������ͬ��select()���ڼ����¼�ʱ�����ں�Ҫ����ʲô���͵��¼���������������ע��Ҫ�������¼����͡���һ��������epoll_create()�ķ���ֵ���ڶ���������ʾ������������������ʾ��
EPOLL_CTL_ADD��ע���µ�fd��epfd�У�
EPOLL_CTL_MOD���޸��Ѿ�ע���fd�ļ����¼���
EPOLL_CTL_DEL����epfd��ɾ��һ��fd��
��������������Ҫ������fd�����ĸ������Ǹ����ں���Ҫ����ʲô�£�struct epoll_event�ṹ���£�

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

events���������¼�����ļ��ϣ�
EPOLLIN ����ʾ��Ӧ���ļ����������Զ��������Զ�SOCKET�����رգ���
EPOLLOUT����ʾ��Ӧ���ļ�����������д��
EPOLLPRI����ʾ��Ӧ���ļ��������н��������ݿɶ�������Ӧ�ñ�ʾ�д������ݵ�������
EPOLLERR����ʾ��Ӧ���ļ���������������
EPOLLHUP����ʾ��Ӧ���ļ����������Ҷϣ�
EPOLLET�� ��EPOLL��Ϊ��Ե����(Edge Triggered)ģʽ�����������ˮƽ����(Level Triggered)��˵�ġ�
EPOLLONESHOT��ֻ����һ���¼���������������¼�֮���������Ҫ�����������socket�Ļ�����Ҫ�ٴΰ����socket���뵽EPOLL������


3. int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);
�ȴ��¼��Ĳ�����������select()���á�����events�������ں˵õ��¼��ļ��ϣ�maxevents��֮�ں����events�ж����� maxevents��ֵ���ܴ��ڴ���epoll_create()ʱ��size������timeout�ǳ�ʱʱ�䣨���룬0���������أ�-1����ȷ����Ҳ��˵��˵���������������ú���������Ҫ������¼���Ŀ���緵��0��ʾ�ѳ�ʱ��


4������ET��LT���ֹ���ģʽ��
���Եó������Ľ���:
ETģʽ����״̬�����仯��ʱ��Ż��֪ͨ,������ν��״̬�ı仯���������������л���δ���������,Ҳ����˵,���Ҫ����ETģʽ,��Ҫһֱread/writeֱ������Ϊֹ,�ܶ��˷�ӳΪʲô����ETģʽֻ������һ�������ݾ���Ҳ�ò���֪ͨ��,�����Ϊ����;��LTģʽ��ֻҪ������û�д���ͻ�һֱ֪ͨ��ȥ��.

���̣�
����ͨ��create_epoll(int maxfds)������һ��epoll�ľ��������maxfdsΪ��epoll��֧�ֵ������������������᷵��һ���µ�epoll�����֮������в�����ͨ�������������в�����������֮�󣬼ǵ���close()���ر��������������epoll�����

֮�������������ѭ�����棬ÿһ֡�ĵ���epoll_wait(int epfd, epoll_event events, int max events, int timeout)����ѯ���е�����ӿڣ�����һ�����Զ�����һ������д�ˡ��������﷨Ϊ��
nfds = epoll_wait(kdpfd, events, maxevents, -1);
����kdpfdΪ��epoll_create����֮��ľ����events��һ��epoll_event*��ָ�룬��epoll_wait������������ɹ�֮��epoll_events���潫�������еĶ�д�¼���max_events�ǵ�ǰ��Ҫ����������socket����������һ��timeout�� epoll_wait�ĳ�ʱ��Ϊ0��ʱ���ʾ���Ϸ��أ�Ϊ-1��ʱ���ʾһֱ����ȥ��ֱ�����¼���Χ��Ϊ������������ʱ���ʾ����ô����ʱ�䣬���һֱû���¼�����Χ��һ�����������ѭ���ǵ������̵߳Ļ���������-1���ȣ��������Ա�֤һЩЧ�ʣ�����Ǻ����߼���ͬһ���̵߳Ļ����������0����֤��ѭ����Ч�ʡ�

epoll_wait��Χ֮��Ӧ����һ��ѭ�����������е��¼���

�ο����£�http://blog.csdn.net/ljx0305/article/details/4065058

������ӵ�����ʾ��δ��
http://www.cppblog.com/API/archive/2013/07/01/201424.html
*/
