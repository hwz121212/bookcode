// ntOverLapCR.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "winsock2.h"

//winsock 2.2 library
#pragma comment(lib,"ws2_32.lib")

#define PORT 8888
#define BUFFERSIZE 100
//套接字环境
typedef struct _tagSOCKET_INFO {
	OVERLAPPED overlap;
	WSABUF wsaBuf;
	char buf[BUFFERSIZE];
	SOCKET socket;
	WSAEVENT sockevent;
	DWORD bytesend;
	DWORD bytesrecv;
	DWORD flags;
} SOCKET_INFO, * LPSOCKET_INFO;


void CALLBACK CompletionROUTINE(DWORD Error,DWORD BytesTransferred, 
                            LPWSAOVERLAPPED Overlapped,DWORD InFlags);
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

	hStopEvent = CreateEvent(NULL,TRUE,FALSE,"COMPLETIONROUTINE");

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
	sockinfo->socket=csocket;
	sockinfo->wsaBuf.buf=sockinfo->buf;
	sockinfo->wsaBuf.len=BUFFERSIZE;
	sockinfo->flags=0;
	ZeroMemory(&sockinfo->overlap,sizeof(OVERLAPPED));

	// 投递第一个WSARecv请求，以便开始在套接字上接受数据
	if(WSARecv(csocket,&sockinfo->wsaBuf,1,&sockinfo->bytesrecv,&sockinfo->flags,
		&sockinfo->overlap,CompletionROUTINE) == SOCKET_ERROR)
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

	WSAEVENT temEvent=WSACreateEvent();

	while(TRUE)
	{
		//在套接字上等待虚事件，也可以直接使用SleepEx
		DWORD dwIndex = WSAWaitForMultipleEvents(1,&temEvent,
			FALSE, WSA_INFINITE, TRUE);
//		DWORD  dwIndex = SleepEx(INFINITE,TRUE);
		if(dwIndex==WAIT_IO_COMPLETION)
		{

			//某个重叠请求的完成例程已执行完毕，继续为更多的
            //完成例程服务 
			continue;
		}
		else
		{
			// 返回WSA_IO_PENDING是正常情况，表示IO操作正在进行，不能立即完成
			// 如果不是WSA_IO_PENDING错误，就表示操作失败了
			printf("The Thread WSARecv failed with error %d\n",WSAGetLastError());
			closesocket(sockinfo->socket);
			GlobalFree(sockinfo);
			ExitThread(0);
		}
	}

	return 0;
}


DWORD WINAPI ServerThread(LPVOID sock_thread_data)
{
	SOCKET sServer,sClient;
	SOCKADDR_IN client;
	int iAddrSize;
	DWORD dwThreadId;
	HANDLE hClientThread;

	sServer = (SOCKET &)sock_thread_data;
    if (listen(sServer, 5))
    {
       printf("listen() failed with error %d\n", WSAGetLastError());
	   WSAResetEvent(hStopEvent);
       return 0;
    }


    while (TRUE)
    {
        iAddrSize = sizeof(client);
        sClient = accept(sServer, (struct sockaddr *)&client,
                        &iAddrSize);        
        if (sClient == INVALID_SOCKET)
        {        
            printf("accept() failed: %d\n", WSAGetLastError());
            continue;
        }

		printf("successfully got a connection from %s:%d.\n",
			inet_ntoa(client.sin_addr), ntohs(client.sin_port));

		printf("Socket %d connected.\n", sClient);

		//创建客户服务线程
        hClientThread = CreateThread(NULL, 0, &ClientThread,
			(LPVOID)sClient, 0, &dwThreadId);
        if (hClientThread == NULL)
        {
            printf("CreateThread() failed: %d\n", GetLastError());
            continue;
        }

	}

	return 0;
}


void CALLBACK CompletionROUTINE(DWORD Error,DWORD BytesTransferred,
							LPWSAOVERLAPPED Overlapped,DWORD InFlags)
{
	
	//SOCKET_INFO结构的第一个元素就
	//是OVERLAPPED结构，因此可以转换如下
	LPSOCKET_INFO sockinfo=(SOCKET_INFO* )Overlapped;

	if (Error != 0||BytesTransferred == 0)
    {
        printf("The CompletionROUTINE failed with error %d\n",WSAGetLastError());
		closesocket(sockinfo->socket);
		GlobalFree(sockinfo);
		return;
    }
	//至此，重叠I/O请求操作已完成，数据保存在重叠I/O请求
	//指定的缓冲区中。数据处理后，可以直接在完成例程中
	//继续投递重叠I/O请求

	//若发现exit则退出处理循环
	if(strncmp(sockinfo->wsaBuf.buf,"exit",sizeof("exit"))==0)
	{
		printf("Client someone log off!\n");
		closesocket(sockinfo->socket);
		GlobalFree(sockinfo);
		ExitThread(0);
	}
	//检查数据的接收情况
	if (sockinfo->bytesrecv == 0)
	{
		sockinfo->bytesrecv = BytesTransferred;
		sockinfo->bytesend = 0;
	}
	else
	{
		sockinfo->bytesend += BytesTransferred;
	}
	//若if成立，则说明尚未将收到的数据发送完毕，
	//因此接着上一次发送结束的地方继续发送后续的数据
	if (sockinfo->bytesrecv > sockinfo->bytesend)
	{
		//将收到的数据返还给客户端。一次未必能够发送完，因此放在循环中
		ZeroMemory(&sockinfo->overlap, sizeof(WSAOVERLAPPED));
		
		sockinfo->wsaBuf.buf = sockinfo->buf + sockinfo->bytesend;
		sockinfo->wsaBuf.len = sockinfo->bytesrecv - sockinfo->bytesend;
		
		if (WSASend(sockinfo->socket, &(sockinfo->wsaBuf), 1, &sockinfo->bytesend, 0,
			&(sockinfo->overlap), CompletionROUTINE) == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSA_IO_PENDING)
			{
				printf("WSASend() failed with error %d\n", WSAGetLastError());
				ExitThread(0);
			}
		}
		
	}
	else
	{
		//再次接收数据之前，将上次接收的数据显示在屏幕上
		printf("%s\n",sockinfo->wsaBuf.buf);
		//数据已发送完毕，准备接收下一批数据
		printf("Waiting to receive data...\n");
		sockinfo->bytesrecv = 0;	
		sockinfo->flags = 0;
		ZeroMemory(&(sockinfo->overlap), sizeof(WSAOVERLAPPED));
		
		sockinfo->wsaBuf.len = BUFFERSIZE;
		sockinfo->wsaBuf.buf = sockinfo->buf;
		ZeroMemory(sockinfo->wsaBuf.buf,BUFFERSIZE);
		// 投递第二个WSARecv请求，以便在套接字上继续接收数据
		if (WSARecv(sockinfo->socket, &(sockinfo->wsaBuf), 1,
			&sockinfo->bytesrecv, &sockinfo->flags,
			&(sockinfo->overlap), CompletionROUTINE) == SOCKET_ERROR)
		{
			// 返回WSA_IO_PENDING是正常情况，表示IO操作正在进行，不能立即完成
			// 如果不是WSA_IO_PENDING错误，就表示操作失败了
			if (WSAGetLastError() != WSA_IO_PENDING )
			{
				printf("The second WSARecv failed with error %d\n",WSAGetLastError());
				closesocket(sockinfo->socket);
				GlobalFree(sockinfo);
				ExitThread(0);
			}
		}
   }
}

