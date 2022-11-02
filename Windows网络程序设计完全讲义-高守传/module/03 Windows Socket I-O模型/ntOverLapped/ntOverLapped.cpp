// ntOverLapped.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "winsock2.h"

//winsock 2.2 library
#pragma comment(lib,"ws2_32.lib")

#define PORT 8888
#define BUFFERSIZE 100
//�׽��ֻ���
//�׽��ֻ���
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
	
	//��ʼ��Winsock 2.2
	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2,2),&wsaData) != 0)
	{
		fprintf(stderr,"WSAStartup() failed %d\n, WSAGetLastError()");
		exit(0); 
	}
	printf("Initialised successfully.\n");
	//��������socket
	printf("\nCreating TCP socket...\n");
	if((listensocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0,
	  WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET) 
	{
		printf("Creation of socket failed %d\n", WSAGetLastError());
		WSACleanup();
		return 0;
	}
	
	//����SOCKADDR_IN��ַ�ṹ
	serAddr.sin_family = AF_INET;
	serAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//  serAddr.sin_addr.s_addr = inet_addr(ADDR);
	serAddr.sin_port = htons(PORT);
	//���׽���
	if (bind(listensocket, (SOCKADDR *) &serAddr, sizeof(serAddr))
		== SOCKET_ERROR)
	{
		printf("bind failed with error %d\n", WSAGetLastError());
		closesocket(listensocket);
		WSACleanup();
		return 0;
	}
	
	//��������
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


//ÿ���̷߳���һ������
DWORD WINAPI ClientThread(LPVOID sock_thread_data)
{

	SOCKET csocket=(SOCKET &)sock_thread_data;
	
	LPSOCKET_INFO sockinfo;
	//�Ӷ��Ϸ����ڴ�
	if ((sockinfo = (LPSOCKET_INFO) GlobalAlloc(GPTR,
		sizeof(SOCKET_INFO))) == NULL)
	{
		printf("GlobalAlloc() failed\n");
		return FALSE;
	}
	//����һ���¼��Թ���OVERLAPPED
	WSAEVENT EventArray[1];
	EventArray[0]=WSACreateEvent();

	sockinfo->socket=csocket;
	sockinfo->overlap.hEvent=EventArray[0];
	sockinfo->wsaBuf.buf=sockinfo->buf;
	sockinfo->wsaBuf.len=BUFFERSIZE;
	sockinfo->flags=0;

	// Ͷ�ݵ�һ��WSARecv�����Ա㿪ʼ���׽����Ͻ�������
	if(WSARecv(sockinfo->socket,&sockinfo->wsaBuf,1,&sockinfo->bytesrecv,&sockinfo->flags,
		&sockinfo->overlap,NULL) == SOCKET_ERROR)
	{
		if(WSAGetLastError() != WSA_IO_PENDING)
		{
			// ����WSA_IO_PENDING�������������ʾIO�������ڽ��У������������
			// �������WSA_IO_PENDING���󣬾ͱ�ʾ����ʧ����
			printf("The first WSARecv failed with error %d\n",WSAGetLastError());
			closesocket(csocket);
			GlobalFree(sockinfo);
			ExitThread(0);
		}
	}

	while(TRUE)
	{
		//���׽����ϵȴ������¼���ÿ�̴߳���һ���׽��֣�Ҳֻ��һ���¼�	
		DWORD dwIndex = WSAWaitForMultipleEvents(1,EventArray,
			FALSE, WSA_INFINITE, TRUE);
		//
		if ((dwIndex == WSA_WAIT_FAILED)||(dwIndex == WSA_WAIT_TIMEOUT))
			continue;
			
		//Ȼ��ȷ��SOCKET���ص�����״̬	
		WSAGetOverlappedResult(sockinfo->socket,&sockinfo->overlap,
			&sockinfo->bytesend,FALSE,&sockinfo->flags);
		//������exit���˳�����ѭ��
		if(strncmp(sockinfo->buf,"exit",sizeof("exit"))==0)
		{
			printf("Client someone log off!\n");
			closesocket(csocket);
			GlobalFree(sockinfo);
			ExitThread(0);
		}	
		
		//���յ���������ʾ����Ļ��
		printf("%s \n",sockinfo->buf);


		//���յ������ݷ������ͻ���
		WSASend(sockinfo->socket,&(sockinfo->wsaBuf),
			1, &sockinfo->bytesend, 0,NULL, NULL);
		printf("Waiting to receive data...\n");
		ZeroMemory(sockinfo->wsaBuf.buf,BUFFERSIZE);

		// Ͷ�ݵڶ���WSARecv�����Ա㿪ʼ���׽����Ͻ�������
		if(WSARecv(sockinfo->socket,&sockinfo->wsaBuf,1,&sockinfo->bytesrecv,&sockinfo->flags,
			&sockinfo->overlap,NULL) == SOCKET_ERROR)
		{
			if(WSAGetLastError() != WSA_IO_PENDING)
			{
				// ����WSA_IO_PENDING�������������ʾIO�������ڽ��У������������
				// �������WSA_IO_PENDING���󣬾ͱ�ʾ����ʧ����
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
	//�����������׽���
	SOCKET listensocket,acceptsocket;
	//�ͻ��˵�ַ
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

		//�����ͻ������߳�
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


