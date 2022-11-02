// ntOverLapped.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "winsock2.h"

//winsock 2.2 library
#pragma comment(lib,"ws2_32.lib")

#define PORT 8888
#define BUFFERSIZE 100
//套接字环境
//套接字环境
typedef struct _tagSOCKET_INFO {
	OVERLAPPED overlap;
	WSABUF wsaBuf;
	char buf[BUFFERSIZE];
	SOCKET socket;
	DWORD bytesend;
	DWORD bytesrecv;
	DWORD flags;
} SOCKET_INFO, * LPSOCKET_INFO;


HANDLE hStopEvent;
DWORD WINAPI ClientThread(LPVOID sock_thread_data);
DWORD WINAPI ServerThread(LPVOID thread_data);

HANDLE hServerThread;
HANDLE hClientThread;

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKADDR_IN serAddr;
	SOCKET listensocket;	
	DWORD dwThreadId;
	
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

	hStopEvent = CreateEvent(NULL,TRUE,FALSE,"OVERLAP");

	hServerThread = CreateThread(NULL,0,&ServerThread,(LPVOID)listensocket,0,&dwThreadId);
	
	if (hServerThread == NULL)
	{
        printf("CreateThread() failed: %d\n", GetLastError());
		return 1;
   }

	WaitForSingleObject(hStopEvent,INFINITE);

	WSACleanup();
	
	return 0;
}


//每个线程服务一个连接
DWORD WINAPI ClientThread(LPVOID sock_thread_data)
{

	SOCKET csocket=(SOCKET &)sock_thread_data;
	
	LPSOCKET_INFO sockinfo;
	//从堆上分配内存
	if ((sockinfo = (LPSOCKET_INFO) GlobalAlloc(GPTR,
		sizeof(SOCKET_INFO))) == NULL)
	{
		printf("GlobalAlloc() failed\n");
		return FALSE;
	}
	//创建一个事件以关联OVERLAPPED
	WSAEVENT EventArray[1];
	EventArray[0]=WSACreateEvent();

	sockinfo->socket=csocket;
	sockinfo->overlap.hEvent=EventArray[0];
	sockinfo->wsaBuf.buf=sockinfo->buf;
	sockinfo->wsaBuf.len=BUFFERSIZE;
	sockinfo->flags=0;

	// 投递第一个WSARecv请求，以便开始在套接字上接受数据
	if(WSARecv(sockinfo->socket,&sockinfo->wsaBuf,1,&sockinfo->bytesrecv,&sockinfo->flags,
		&sockinfo->overlap,NULL) == SOCKET_ERROR)
	{
		if(WSAGetLastError() != WSA_IO_PENDING)
		{
			// 返回WSA_IO_PENDING是正常情况，表示IO操作正在进行，不能立即完成
			// 如果不是WSA_IO_PENDING错误，就表示操作失败了
			printf("The first WSARecv failed with error %d\n",WSAGetLastError());
			closesocket(csocket);
			GlobalFree(sockinfo);
			ExitThread(0);
		}
	}

	while(TRUE)
	{
		//在套接字上等待网络事件，每线程处理一个套接字，也只有一个事件	
		DWORD dwIndex = WSAWaitForMultipleEvents(1,EventArray,
			FALSE, WSA_INFINITE, TRUE);
		//
		if ((dwIndex == WSA_WAIT_FAILED)||(dwIndex == WSA_WAIT_TIMEOUT))
			continue;
			
		//然后确定SOCKET的重叠请求状态	
		WSAGetOverlappedResult(sockinfo->socket,&sockinfo->overlap,
			&sockinfo->bytesend,FALSE,&sockinfo->flags);
		//若发现exit则退出处理循环
		if(strncmp(sockinfo->buf,"exit",sizeof("exit"))==0)
		{
			printf("Client someone log off!\n");
			closesocket(csocket);
			GlobalFree(sockinfo);
			ExitThread(0);
		}	
		
		//将收到的数据显示在屏幕上
		printf("%s \n",sockinfo->buf);


		//将收到的数据返还给客户端
		WSASend(sockinfo->socket,&(sockinfo->wsaBuf),
			1, &sockinfo->bytesend, 0,NULL, NULL);
		printf("Waiting to receive data...\n");
		ZeroMemory(sockinfo->wsaBuf.buf,BUFFERSIZE);

		// 投递第二个WSARecv请求，以便开始在套接字上接受数据
		if(WSARecv(sockinfo->socket,&sockinfo->wsaBuf,1,&sockinfo->bytesrecv,&sockinfo->flags,
			&sockinfo->overlap,NULL) == SOCKET_ERROR)
		{
			if(WSAGetLastError() != WSA_IO_PENDING)
			{
				// 返回WSA_IO_PENDING是正常情况，表示IO操作正在进行，不能立即完成
				// 如果不是WSA_IO_PENDING错误，就表示操作失败了
				printf("The second WSARecv failed with error %d\n",WSAGetLastError());
							
				closesocket(csocket);
				GlobalFree(sockinfo);
				ExitThread(0);
			}
		}
	}

	return 0;
}


DWORD WINAPI ServerThread(LPVOID sock_thread_data)
{
	//监听、连接套接字
	SOCKET listensocket,acceptsocket;
	//客户端地址
	SOCKADDR_IN  cliAddr;
	int cliAddrLen;
	DWORD dwThreadId;
	HANDLE hClientThread;

	listensocket = (SOCKET &)sock_thread_data;
    if (listen(listensocket, 5))
    {
       printf("listen() failed with error %d\n", WSAGetLastError());
	   WSAResetEvent(hStopEvent);
       return 0;
    }


    while (TRUE)
    {
        cliAddrLen = sizeof(cliAddr);
        acceptsocket = accept(listensocket, (struct sockaddr *)&cliAddr,
                        &cliAddrLen);        
        if (acceptsocket == INVALID_SOCKET)
        {        
            printf("accept() failed: %d\n", WSAGetLastError());
            break;
        }

		printf("successfully got a connection from %s:%d.\n",
			inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));

		printf("Socket %d connected.\n", acceptsocket);

		//创建客户服务线程
        hClientThread = CreateThread(NULL, 0, &ClientThread,
			(LPVOID)acceptsocket, 0, &dwThreadId);
        if (hClientThread == NULL)
        {
            printf("CreateThread() failed: %d\n", GetLastError());
            break;
        }

	}

	return 0;
}


