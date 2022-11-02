// ntEventSelect.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "winsock2.h"

//winsock 2.2 library
#pragma comment(lib,"ws2_32.lib")

#define PORT 8888
#define BUFFERSIZE 100
#define BASE0 WSA_WAIT_EVENT_0
//套接字环境
typedef struct _tagSOCKET_INFO {
	OVERLAPPED overlap;
	WSABUF wsaBuf;
	char buf[BUFFERSIZE];
	SOCKET socket;
	DWORD bytesend;
	DWORD bytesrecv;
	DWORD flags;
	WSAEVENT sockevent;
} SOCKET_INFO, * LPSOCKET_INFO;

BOOL CreateSocketInfo(SOCKET s,long Noti=-1);
void FreeSocketInfo(DWORD Index);

WSAEVENT EventArray [WSA_MAXIMUM_WAIT_EVENTS];
DWORD totalsocks = 0;

//接收发送数据计数
LPSOCKET_INFO socklist[WSA_MAXIMUM_WAIT_EVENTS];

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	WSANETWORKEVENTS NetworkEvents;
	SOCKADDR_IN cliAddr,serAddr;
	//cliAddrLen必须初始化为cliAddr的大小
	int cliAddrLen=sizeof(cliAddr);
	SOCKET acceptsocket, listensocket;	
	DWORD Index;
	
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
	
	//为监听套接字创建工作环境
	if (CreateSocketInfo(listensocket,FD_ACCEPT | FD_CLOSE) == FALSE)
		return 0;
	//监听连接
	if (listen(listensocket, 5))
	{
		printf("listen failed with error %d\n", WSAGetLastError());
		closesocket(listensocket);
		WSACleanup();
		return 0;
	}
	printf("Listening on the %s:%d...\n",
		inet_ntoa(serAddr.sin_addr), htons(serAddr.sin_port));

	EventArray[totalsocks-1] = socklist[totalsocks-1]->sockevent;
	
	while(TRUE)
	{
		//在所有套接字上等待网络事件
		Index = WSAWaitForMultipleEvents(totalsocks,EventArray, 
			FALSE, WSA_INFINITE, FALSE);	
		//
		if ((Index == WSA_WAIT_FAILED)||(Index == WSA_WAIT_TIMEOUT))
			continue;
		else
		{
			Index = Index - BASE0;
			WSAEnumNetworkEvents(socklist[Index]->socket,EventArray[Index], &NetworkEvents);
			//FD_ACCEPT			
			if (NetworkEvents.lNetworkEvents & FD_ACCEPT)
			{ 
				if (NetworkEvents.iErrorCode[FD_ACCEPT_BIT] != 0)
				{
					printf("FD_ACCEPT failed with error %d\n", 
						NetworkEvents.iErrorCode[FD_ACCEPT_BIT]);
					continue;
				}
				
				acceptsocket = accept(socklist[Index]->socket,(sockaddr*)&cliAddr,&cliAddrLen);		
				//为新套接字创建工作环境
				if (CreateSocketInfo(acceptsocket,FD_READ|FD_WRITE|FD_CLOSE) == FALSE)
					return 0;
				printf("successfully got a connection from %s:%d.\n",
					inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));
				
				//最多处理WSA_MAXIMUM_WAIT_EVENTS 
				if (totalsocks > WSA_MAXIMUM_WAIT_EVENTS)//
				{
					printf("Too many connections");
					//把新接受的连接环境释放
					FreeSocketInfo(totalsocks-1);
					continue;
				}
				
				EventArray[totalsocks-1] = socklist[totalsocks-1]->sockevent;

				printf("Socket %d connected\n", acceptsocket);
			}
			//FD_WRITE
			if (NetworkEvents.lNetworkEvents & FD_WRITE)
			{
				if (NetworkEvents.iErrorCode[FD_WRITE_BIT] != 0)
				{
					printf("FD_WRITE failed with error %d\n", 
						NetworkEvents.iErrorCode[FD_WRITE_BIT]);
					continue;
				}
			}
			//FD_READ
			if (NetworkEvents.lNetworkEvents & FD_READ)
			{
				if (NetworkEvents.iErrorCode[FD_READ_BIT] != 0)
				{
					printf("FD_READ failed with error %d\n", 
						NetworkEvents.iErrorCode[FD_READ_BIT]);
					continue;
				}
				//接收数据
				socklist[Index - BASE0]->flags = 0;
				if (WSARecv(socklist[Index - BASE0]->socket, 
					&(socklist[Index - BASE0]->wsaBuf), 1, 
					&socklist[Index - BASE0]->bytesrecv,
					&socklist[Index - BASE0]->flags, NULL, NULL) == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK)
					{
						printf("Receive failed with error\n");
						FreeSocketInfo(Index - BASE0);
					}
				} 
				else
				{
					//获取客户端地址信息
					if(getpeername(socklist[Index - BASE0]->socket,
						(sockaddr*)&cliAddr,&cliAddrLen))
					{
						printf("getpeername failed with error %d\n", WSAGetLastError());
					}
					
					printf( "The following data comes from %s:%d\n",
						inet_ntoa(cliAddr.sin_addr),htons(cliAddr.sin_port)); 
					//显示接收到的数据
					printf("%s\n",socklist[Index - BASE0]->wsaBuf.buf);

					WSASend(socklist[Index - BASE0]->socket, 
						&(socklist[Index - BASE0]->wsaBuf), 1, 
						&socklist[Index - BASE0]->bytesend, 0,NULL, NULL);
					ZeroMemory(socklist[Index - BASE0]->wsaBuf.buf,BUFFERSIZE);
					printf("Waiting to receive data...\n");
					//若发现exit则退出处理循环
					if(strncmp(socklist[Index - BASE0]->wsaBuf.buf,"exit",sizeof("exit"))==0)
					{
						printf("exit the receiving loop\n");
						exit(0);
					}	
					//连接关闭，则接收到0字节
					if (socklist[Index - BASE0]->bytesrecv== 0)
					{
						FreeSocketInfo(Index - BASE0);
					}
				}
			}
			if (NetworkEvents.lNetworkEvents & FD_CLOSE)
			{
				if (NetworkEvents.iErrorCode[FD_CLOSE_BIT] != 0)
				{
					printf("FD_CLOSE failed with error %d\n", 
						NetworkEvents.iErrorCode[FD_CLOSE_BIT]);
					continue;
				}
				FreeSocketInfo(Index);
			}
			//复位事件
			WSAResetEvent(EventArray[Index]);
		}
	}
	
	return 0;
}


void FreeSocketInfo(DWORD Index)
{
	
	LPSOCKET_INFO sockinfo = socklist[Index];
	DWORD loop;
	
	closesocket(sockinfo->socket);
	
	WSACloseEvent(EventArray[Index]);
	printf("Closing socket.....\n");
	
	GlobalFree(sockinfo);
	
	//从数组中移除，注意数组下边界
	for (loop = Index; loop < totalsocks-1; loop++)
	{
		socklist[loop] = socklist[loop + 1];
		//事件与套接字对应
		EventArray[loop]=EventArray[loop+1];
	}
	//递减已关闭连接套接字的计数
	totalsocks--;
}


BOOL CreateSocketInfo(SOCKET s,long noti)
{
	LPSOCKET_INFO sockinfo;
	
	printf("Accepted socket!\n");
	//从堆上分配内存
	if ((sockinfo = (LPSOCKET_INFO) GlobalAlloc(GPTR,
		sizeof(SOCKET_INFO))) == NULL)
	{
		printf("GlobalAlloc() failed\n");
		return FALSE;
	}
	
	//套接字相关
	sockinfo->socket=s;
	sockinfo->bytesend=sockinfo->bytesrecv=0;

	WSAEVENT NewEvent = WSACreateEvent(); 
	WSAEventSelect(s, NewEvent,noti);
	sockinfo->sockevent=NewEvent;
	sockinfo->wsaBuf.buf=sockinfo->buf;
	sockinfo->wsaBuf.len=sizeof(sockinfo->buf);
	
	socklist[totalsocks]=sockinfo;
	//递增已接受连接套接字的计数
	totalsocks++;
	
	return TRUE;
}


