// ntTcpClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "winsock2.h"

//winsock 2.2 library
#pragma comment(lib,"ws2_32.lib")

#define PORT  8888
#define ADDR  "127.0.0.1"

int main(int argc, char* argv[])
{
	WSADATA	wsock;
	SOCKET sconnection;
	SOCKADDR_IN          serAddr;
	int                  nRet=0;
	char                 buf[100];
	
	//初始化Winsock 2.2
	
	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2,2),&wsock) != 0)
	{
		fprintf(stderr,"WSAStartup() failed %d\n, WSAGetLastError()");
        exit(0); 
	} 
	printf("Initialised successfully.\n");
	
	//创建监听socket
	printf("\nCreating TCP Socket...\n");
	if ((sconnection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) 
		== INVALID_SOCKET)
	{
		printf("Creation of socket failed %d\n", WSAGetLastError());
		WSACleanup();
		return 0;
	}
	printf("TCP Socket Created successfully.\n");
	//设置SOCKADDR_IN地址结构
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(PORT);    
	//serAddr.sin_addr.s_addr = INADDR_ANY;
	serAddr.sin_addr.s_addr = inet_addr(ADDR);
	//连接服务端
	printf("Connecting to %s:%d...\n",
		inet_ntoa(serAddr.sin_addr), htons(serAddr.sin_port));
	if (connect(sconnection, (SOCKADDR *) &serAddr, sizeof(serAddr)) 
		== SOCKET_ERROR)
	{
		printf("connection failed with error %d\n", WSAGetLastError());
		closesocket(sconnection);
		WSACleanup();
		return 0;
	} 
	printf("connection successfully.\n");
	printf("Trying to send  messages.\n");
	//收发处理
	for(int i=0;;i++)
	{
		memset(buf,0,sizeof(buf));
		printf("\nMessage to be sent:");
		gets_s(buf);
		if ((nRet = send(sconnection, buf, strlen(buf), 0)) == SOCKET_ERROR)
		{
			printf("send failed with error %d\n", WSAGetLastError());
			closesocket(sconnection);
			WSACleanup();
			return 0;
		}

		printf("The  data  was sent to %s successfully.\n",inet_ntoa(serAddr.sin_addr));
		if(strncmp(buf,"exit",sizeof("exit"))==0)
			break;
		memset(buf,0,sizeof(buf));

		if ((nRet = recv(sconnection, buf, sizeof(buf), 0)) 
			== SOCKET_ERROR)
		{
			printf("recv failed with error %d\n", WSAGetLastError());
		}
		printf("The following data  was received from %s successfully.\n",
			inet_ntoa(serAddr.sin_addr));
		printf(buf);
	}
	printf("Closing the connection.\n");

	closesocket(sconnection);
	WSACleanup();

	return 0;
}

