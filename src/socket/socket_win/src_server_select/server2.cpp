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

	//add
	bool bReuseAddr = true;
	if (setsockopt(sockSrv, SOL_SOCKET, SO_REUSEADDR, (char*)&bReuseAddr, sizeof(bReuseAddr) == SOCKET_ERROR))
	{
		printf("Failed to set Resueaddr socket\n");
		getchar();
		WSACleanup();
		return -1;
	}

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

	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(sockSrv, &readfds);

	printf("Start server...\n");

	while (1)
	{
		fd_set oldfds = readfds;
		int iSelectResult = select(FD_SETSIZE, &oldfds, (fd_set*)0, (fd_set*)0, (struct timeval*)0);
		//int iSelectResult = select(0, &oldfds, nullptr, nullptr, nullptr);

		if (iSelectResult < 1)
		{
			perror("server failed\n");
			getchar();
			exit(1);
		}

		for (unsigned int i = 0; i < readfds.fd_count; ++i)
		{
			if (FD_ISSET(readfds.fd_array[i], &oldfds))
			{
				//if (i == sockSrv)
				if (readfds.fd_array[i] == sockSrv)
				{
					struct sockaddr_in client_address;
					int iClientLen = sizeof(client_address);
					unsigned int sockConn = accept(sockSrv, (struct sockaddr *)&client_address, &iClientLen);
					if (sockConn != INVALID_SOCKET)
					{
						FD_SET(sockConn, &readfds);		//add sockConn into readfds
						printf("adding client on fd %d, addr:%s, port:%d\n", sockConn, inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
					}
				}
				else
				{
					char dataBuf[100];
					memset(dataBuf, 0, sizeof(dataBuf));
					unsigned long ulReadLen = recv(readfds.fd_array[i], dataBuf, sizeof(dataBuf), 0);
					
					if (ulReadLen == SOCKET_ERROR)
					{
						closesocket(readfds.fd_array[i]);
						FD_CLR(readfds.fd_array[i], &readfds);
						printf("Failed to recv data, client: %d\n", readfds.fd_array[i]);
						i--;
					}
					else if (ulReadLen == 0)
					{
						printf("close client: %d\n", readfds.fd_array[i]);
						closesocket(readfds.fd_array[i]);
						FD_CLR(readfds.fd_array[i], &readfds);
						i--;
					}
					else if (ulReadLen > 0)
					{
						printf("recv: %s\n", dataBuf);
						char sendBuf[100] = "send from server";
						send(readfds.fd_array[i], sendBuf, sizeof(sendBuf), 0);
					}
				}
			}
		}
	}

	closesocket(sockSrv);
	WSACleanup();
}
