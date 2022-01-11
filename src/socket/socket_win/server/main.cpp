#include <stdio.h>
#include <winsock2.h>

#define PORT 8888

int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv;
	memset(&addrSrv, 0, sizeof(SOCKADDR_IN));
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_port = htons(PORT);

	if (bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		perror("Failed to bind adress\n");
		getchar();
		WSACleanup();
		return -1;
	}

	if (listen(sockSrv, 5) != 0)
	{
		perror("Failed to listen adress\n");
		getchar();
		WSACleanup();
		return -1;
	}

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	while (1)
	{
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);
		char sendBuf[50] = {};
		sprintf(sendBuf, "Welcome %s to here!", inet_ntoa(addrClient.sin_addr));
		send(sockConn, sendBuf, strlen(sendBuf) + 1, 0);
		char recvBuf[50] = {};
		recv(sockConn, recvBuf, 50, 0);
		printf("%s\n", recvBuf);
		closesocket(sockConn);
	}

	closesocket(sockSrv);
	WSACleanup();
}