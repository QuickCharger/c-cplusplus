#include "sys/types.h"
#include "sys/socket.h"
#include "stdio.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "unistd.h"
#include "string.h"
#include "stdlib.h"
#include "fcntl.h"
#include "sys/shm.h"

#define MYPORT 8887
#define QUEUE 20
#define BUFFER_SIZE 1024

int main()
{
	int server_sockfd = socket( AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_sockaddr;
	server_sockaddr.sin_family = AF_INET;
	server_sockaddr.sin_port = htons(MYPORT);
	server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if( bind( server_sockfd, (struct sockaddr*)&server_sockaddr, sizeof(server_sockaddr)) == -1)
	{
		perror("bind");
		exit(1);
	}

	if(listen(server_sockfd, QUEUE) == -1)
	{
		perror("listen");
		exit(1);
	}

	char buffer[BUFFER_SIZE];
	struct sockaddr_in client_addr;
	socklen_t length = sizeof(client_addr);

	int conn = accept( server_sockfd, (struct sockaddr*)&client_addr, &length);
	if( conn < 0)
	{
		perror("connect");
		exit(1);
	}

	printf("new connect\n");

	char *ok_buffer = "recv\n";

	while(1)
	{
		memset(buffer, 0, sizeof(buffer));
		int len = recv( conn, buffer, sizeof(buffer), 0);
		if( strcmp(buffer, "exiit\n") == 0)
			break;
		printf("recv: ");
		fputs(buffer, stdout);
		send(conn, ok_buffer, strlen(ok_buffer), 0);
	}
	close(conn);
	close(server_sockfd);

	return 0;
}
