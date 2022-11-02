// ntCompletionPort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "winsock2.h"

//winsock 2.2 library
#pragma comment(lib,"ws2_32.lib")

#define PORT 8888
#define BUFFERSIZE 100

//完成键-与套接字相关
typedef struct _tagCOMPLETION_KEY {
	SOCKET socket;
	DWORD other_needed;
} COMPLETION_KEY, * LPCOMPLETION_KEY;

//套接字环境
typedef struct _tagSOCKET_INFO {
	OVERLAPPED overlap;
	WSABUF wsaBuf;
	char buf[BUFFERSIZE];
	DWORD bytesend;
	DWORD bytesrecv;
	DWORD flags;
	COMPLETION_KEY 	key;
} SOCKET_INFO, * LPSOCKET_INFO;

DWORD WINAPI ServerThread(LPVOID comportID);


DWORD datasend,datarecv;

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	//客户端,服务端地址
	SOCKADDR_IN serAddr,cliAddr;
	int cliAddrLen;
	SOCKET listensocket,acceptsocket;
	HANDLE threadhandle,comport;
	DWORD dwThreadId;
	SYSTEM_INFO sysinfo;
	LPSOCKET_INFO sockinfo;
	
	//初始化Winsock 2.2
	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2,2),&wsaData) != 0)
	{
		fprintf(stderr,"WSAStartup() failed %d\n, WSAGetLastError()");
		exit(0); 
	}
	printf("Initialised successfully.\n");
	//创建监听socket
	printf("\nCreating TCP socket...\n");
	if((listensocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0,
		WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET) 
	{
		printf("Creation of socket failed %d\n", WSAGetLastError());
		WSACleanup();
		return 0;
	}
	
	//设置SOCKADDR_IN地址结构
	serAddr.sin_family = AF_INET;
	serAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//  serAddr.sin_addr.s_addr = inet_addr(ADDR);
	serAddr.sin_port = htons(PORT);
	//绑定套接字
	if (bind(listensocket, (SOCKADDR *) &serAddr, sizeof(serAddr))
		== SOCKET_ERROR)
	{
		printf("bind failed with error %d\n", WSAGetLastError());
		closesocket(listensocket);
		WSACleanup();
		return 0;
	}
	
	//监听到来的连接请求
	if (listen(listensocket, 5))
	{
		printf("listen failed with error %d\n", WSAGetLastError());
		closesocket(listensocket);
		WSACleanup();
		return 0;
	}

	printf("Listening on the %s:%d...\n",
		inet_ntoa(serAddr.sin_addr), htons(serAddr.sin_port));
	//首先创建完成端口
	if ((comport = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0)) == NULL)
	{
		printf( "CreateIoCompletionPort failed with error: %d\n", GetLastError());
		return 0;
	}

	GetSystemInfo(&sysinfo);
	//创建工作线程
	for(DWORD dwThread = 0; dwThread< sysinfo.dwNumberOfProcessors * 2;dwThread++)
	{
		//为完成端口指定工作线程，线程都是在完成端口上读写数据     
		if ((threadhandle = CreateThread(NULL, 0, &ServerThread, (LPVOID)comport,
			0, &dwThreadId)) == NULL)
		{
			printf("CreateThread() failed with error %d\n", GetLastError());
			return 0;
		}     
		CloseHandle(threadhandle);
	}

	while(TRUE)
	{
		//接受连接
		//cliAddrLen必须初始化为cliAddr的大小
		cliAddrLen=sizeof(cliAddr);
		if ((acceptsocket = accept(listensocket,
			(sockaddr*)&cliAddr,&cliAddrLen))== INVALID_SOCKET)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				printf("accept() failed with error %d\n",WSAGetLastError());
			}
			return 0;
		}
		
		printf("successfully got a connection from %s:%d.\n",
			inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));
		
		printf("Socket %d connected.\n", acceptsocket);


		if ((sockinfo= (LPSOCKET_INFO) GlobalAlloc(GPTR, sizeof(SOCKET_INFO))) == NULL)
		{
			printf("GlobalAlloc() failed with error %d\n", GetLastError());
			return 0;
		} 
		
		ZeroMemory(sockinfo, sizeof(SOCKET_INFO));
		sockinfo->wsaBuf.buf=sockinfo->buf;
		sockinfo->wsaBuf.len=BUFFERSIZE;
		sockinfo->flags=0;
		LPCOMPLETION_KEY completionkey=&sockinfo->key;

		completionkey->socket=acceptsocket;
		//将套接字、完成端口以及完成键关联起来
		if (CreateIoCompletionPort((HANDLE) acceptsocket, comport, (DWORD) completionkey,
			0) == NULL)
		{
			printf("CreateIoCompletionPort failed with error %d\n", GetLastError());
			return 0;
		}
		//接收数据
		if (WSARecv(acceptsocket,&sockinfo->wsaBuf,1,&sockinfo->bytesrecv,&sockinfo->flags,
		&sockinfo->overlap,NULL) == SOCKET_ERROR)
		{
			if (WSAGetLastError() != ERROR_IO_PENDING)
			{
				printf("WSARecv() failed with error %d\n", WSAGetLastError());
				return 0;
			}
		}
	}

	return 0;
}

DWORD WINAPI ServerThread(LPVOID comportID)
{
	HANDLE comport = (HANDLE)comportID;
	
	DWORD transdata;
	LPSOCKET_INFO sockinfo;
	LPCOMPLETION_KEY pkey;
	
	while(TRUE)
	{
		//使用GetQueuedCompletionStatus完成端口上的数据情况
		if (!GetQueuedCompletionStatus(comport, &transdata,
			(PULONG_PTR)&pkey, (LPOVERLAPPED *)&sockinfo, INFINITE))
		{
			printf("GetQueuedCompletionStatus failed with error %d\n", GetLastError());
			return 0;
		}
		
		//对方已关闭连接
		if (transdata == 0)
		{
			printf("Closing socket %d\n", sockinfo->key.socket);
			
			if (closesocket(sockinfo->key.socket) == SOCKET_ERROR)
			{
				printf("closesocket failed with error %d\n", WSAGetLastError());
				return 0;
			}
			
			GlobalFree(pkey);
			GlobalFree(sockinfo);
			continue;
		}    

		//检查是初次收到数据还是再次接收同一批数据的后续部分
		if (sockinfo->bytesrecv == 0)
		{
			sockinfo->bytesrecv = transdata;
			sockinfo->bytesend = 0;
		}
		else
		{
			sockinfo->bytesend += transdata;
		}
		
		//检查数据是否发完，若没有发完则接着上次发送的尾部继续发送
		if (sockinfo->bytesrecv > sockinfo->bytesend)
		{
			
			ZeroMemory(&sockinfo->overlap, sizeof(OVERLAPPED)); 
			sockinfo->wsaBuf.buf = sockinfo->buf + sockinfo->bytesend;
			sockinfo->wsaBuf.len = sockinfo->bytesrecv - sockinfo->bytesend;
			
			//发送数据
			if (WSASend(sockinfo->key.socket, &(sockinfo->wsaBuf), 1, &datasend, 0,
				&(sockinfo->overlap), NULL) == SOCKET_ERROR)
			{
				if (WSAGetLastError() != ERROR_IO_PENDING)
				{
					printf("WSASend() failed with error %d\n", WSAGetLastError());
					return 0;
				}
			}
		}
		else
		{
			//若发现exit则退出处理循环
			if(strncmp(sockinfo->buf,"exit",sizeof("exit"))==0)
			{
				printf("Client someone log off!\n");
				closesocket(sockinfo->key.socket);
				GlobalFree(pkey);
				GlobalFree(sockinfo);
				ExitThread(0);
			}	
			
			//将收到的数据显示在屏幕上
			printf("%s \n",sockinfo->buf);
			printf("Waiting to receive data...\n");
			
			sockinfo->bytesrecv=0;	
			sockinfo->flags=0;
			ZeroMemory(&(sockinfo->overlap), sizeof(OVERLAPPED)+BUFFERSIZE);
			
			sockinfo->wsaBuf.len = BUFFERSIZE;
			sockinfo->wsaBuf.buf = sockinfo->buf;
			
			if (WSARecv(sockinfo->key.socket, &sockinfo->wsaBuf, 1, &datarecv, &sockinfo->flags,
				&sockinfo->overlap, NULL) == SOCKET_ERROR)
			{
				if (WSAGetLastError() != ERROR_IO_PENDING)
				{
					printf("WSARecv() failed with error %d\n", WSAGetLastError());
					return 0;
				}
			}
		}
   }
	return 0;
}