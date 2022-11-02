// ntOverLapCR.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "winsock2.h"

//winsock 2.2 library
#pragma comment(lib,"ws2_32.lib")

#define PORT 8888
#define BUFFERSIZE 100
//�׽��ֻ���
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
	sockinfo->socket=csocket;
	sockinfo->wsaBuf.buf=sockinfo->buf;
	sockinfo->wsaBuf.len=BUFFERSIZE;
	sockinfo->flags=0;
	ZeroMemory(&sockinfo->overlap,sizeof(OVERLAPPED));

	// Ͷ�ݵ�һ��WSARecv�����Ա㿪ʼ���׽����Ͻ�������
	if(WSARecv(csocket,&sockinfo->wsaBuf,1,&sockinfo->bytesrecv,&sockinfo->flags,
		&sockinfo->overlap,CompletionROUTINE) == SOCKET_ERROR)
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

	WSAEVENT temEvent=WSACreateEvent();

	while(TRUE)
	{
		//���׽����ϵȴ����¼���Ҳ����ֱ��ʹ��SleepEx
		DWORD dwIndex = WSAWaitForMultipleEvents(1,&temEvent,
			FALSE, WSA_INFINITE, TRUE);
//		DWORD  dwIndex = SleepEx(INFINITE,TRUE);
		if(dwIndex==WAIT_IO_COMPLETION)
		{

			//ĳ���ص���������������ִ����ϣ�����Ϊ�����
            //������̷��� 
			continue;
		}
		else
		{
			// ����WSA_IO_PENDING�������������ʾIO�������ڽ��У������������
			// �������WSA_IO_PENDING���󣬾ͱ�ʾ����ʧ����
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

		//�����ͻ������߳�
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
	
	//SOCKET_INFO�ṹ�ĵ�һ��Ԫ�ؾ�
	//��OVERLAPPED�ṹ����˿���ת������
	LPSOCKET_INFO sockinfo=(SOCKET_INFO* )Overlapped;

	if (Error != 0||BytesTransferred == 0)
    {
        printf("The CompletionROUTINE failed with error %d\n",WSAGetLastError());
		closesocket(sockinfo->socket);
		GlobalFree(sockinfo);
		return;
    }
	//���ˣ��ص�I/O�����������ɣ����ݱ������ص�I/O����
	//ָ���Ļ������С����ݴ���󣬿���ֱ�������������
	//����Ͷ���ص�I/O����

	//������exit���˳�����ѭ��
	if(strncmp(sockinfo->wsaBuf.buf,"exit",sizeof("exit"))==0)
	{
		printf("Client someone log off!\n");
		closesocket(sockinfo->socket);
		GlobalFree(sockinfo);
		ExitThread(0);
	}
	//������ݵĽ������
	if (sockinfo->bytesrecv == 0)
	{
		sockinfo->bytesrecv = BytesTransferred;
		sockinfo->bytesend = 0;
	}
	else
	{
		sockinfo->bytesend += BytesTransferred;
	}
	//��if��������˵����δ���յ������ݷ�����ϣ�
	//��˽�����һ�η��ͽ����ĵط��������ͺ���������
	if (sockinfo->bytesrecv > sockinfo->bytesend)
	{
		//���յ������ݷ������ͻ��ˡ�һ��δ���ܹ������꣬��˷���ѭ����
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
		//�ٴν�������֮ǰ�����ϴν��յ�������ʾ����Ļ��
		printf("%s\n",sockinfo->wsaBuf.buf);
		//�����ѷ�����ϣ�׼��������һ������
		printf("Waiting to receive data...\n");
		sockinfo->bytesrecv = 0;	
		sockinfo->flags = 0;
		ZeroMemory(&(sockinfo->overlap), sizeof(WSAOVERLAPPED));
		
		sockinfo->wsaBuf.len = BUFFERSIZE;
		sockinfo->wsaBuf.buf = sockinfo->buf;
		ZeroMemory(sockinfo->wsaBuf.buf,BUFFERSIZE);
		// Ͷ�ݵڶ���WSARecv�����Ա����׽����ϼ�����������
		if (WSARecv(sockinfo->socket, &(sockinfo->wsaBuf), 1,
			&sockinfo->bytesrecv, &sockinfo->flags,
			&(sockinfo->overlap), CompletionROUTINE) == SOCKET_ERROR)
		{
			// ����WSA_IO_PENDING�������������ʾIO�������ڽ��У������������
			// �������WSA_IO_PENDING���󣬾ͱ�ʾ����ʧ����
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

