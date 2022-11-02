// ntTcpServer.cpp : Defines the entry point for the console application.
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
	SOCKET listensocket,newconnection;
	SOCKADDR_IN          serAddr,cliAddr;
	int                  cliAddrLen=sizeof(cliAddr);
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
	if ((listensocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) 
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
	//   serAddr.sin_addr.s_addr = INADDR_ANY;
	serAddr.sin_addr.s_addr = inet_addr(ADDR);
	//绑定套接字
	if (bind(listensocket, (SOCKADDR *)&serAddr,
	   sizeof(serAddr))== SOCKET_ERROR)
	{
		printf("bind failed with error %d\n", WSAGetLastError());
		closesocket(listensocket);
		WSACleanup();
		return 0;
	}
	
	//监听连接
	if (listen(listensocket, 5) == SOCKET_ERROR)
	{
		printf("listen failed with error %d\n", WSAGetLastError());
		closesocket(listensocket);
		WSACleanup();
		return 0;
	} 
	
	printf("Waiting for a connection on port %d.\n", PORT);

	//接受连接
	if ((newconnection = accept(listensocket, (SOCKADDR *) &cliAddr,
		&cliAddrLen)) == INVALID_SOCKET)
	{
		printf("accept failed with error %d\n", WSAGetLastError());
		closesocket(listensocket);
		WSACleanup();
		return 0;
	}
	
	printf("successfully got a connection from %s:%d.\n",
		inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));

	//此时可以继续监听新的连接，或者停止监听进行数据收发
	closesocket(listensocket);
	
	printf("Waiting to receive data...\n");
	
	memset(buf,0,sizeof(buf));
	for(int i=0;;i++)
	{
		if ((nRet = recv(newconnection, buf, sizeof(buf), 0)) 
			== SOCKET_ERROR)
		{
			printf("recv failed with error %d\n", WSAGetLastError());
			closesocket(newconnection);
			WSACleanup();
			return 0;
		}
		//显示接收到的数据
		printf(buf);
		printf("\n");
		//若发现exit则退出处理循环
		if(strncmp(buf,"exit",sizeof("exit"))==0)
		{
			printf("exit the receiving loop\n");
			break;
		}
		if((nRet = send(newconnection,buf,strlen(buf),0))
			==SOCKET_ERROR)
		{
			printf("send failed with error %d\n", WSAGetLastError());
		}
	} 
	//关闭已连接套接字
	closesocket(newconnection);
	
	WSACleanup();
	return 0;
}

