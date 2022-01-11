#include <stdio.h>
#include <Winsock2.h>

#define PORT 8888

void main()
{
	WSADATA wsa_data;
	WSAStartup(MAKEWORD(2, 2), &wsa_data);

	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(PORT);
	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	send(sockClient, "hello", strlen("hello") + 1, 0);
	//char recvBuf[50];
	//memset(recvBuf, 0, sizeof(recvBuf));
	//if (recv(sockClient, recvBuf, 50, 0) != SOCKET_ERROR)
	//{
	//	printf("%s\n", recvBuf);
	//}
	//else
	//{
	//	printf("recv error");
	//}

	getchar();

	shutdown(sockClient, SD_BOTH);

	closesocket(sockClient);

	WSACleanup();
}