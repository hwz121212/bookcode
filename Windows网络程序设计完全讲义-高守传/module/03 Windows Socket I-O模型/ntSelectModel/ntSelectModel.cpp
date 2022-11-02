// ntSelectModel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "winsock2.h"

//winsock 2.2 library
#pragma comment(lib,"ws2_32.lib")

#define PORT 8888
#define BUFFERSIZE 100
#define ADDR  "127.0.0.1"
#define ECHO   0xFE
#define REPLY  0xFF

//�׽��ֻ���
typedef struct _tagSOCKET_INFO {
	OVERLAPPED overlap;
	WSABUF wsaBuf;
	char buf[BUFFERSIZE];
	SOCKET socket;
	DWORD bytesend;
	DWORD bytesrecv;
} SOCKET_INFO, * LPSOCKET_INFO;

BOOL CreateSocketInfo(SOCKET s);
void FreeSocketInfo(DWORD Index);

DWORD totalsocks = 0;
LPSOCKET_INFO socklist[FD_SETSIZE];

int main(int argc, char* argv[])
{
	//�����������׽���
	SOCKET listensocket,acceptsocket;
	//����˵�ַ
	SOCKADDR_IN serAddr;
	WSADATA wsaData;
	//select����
	struct fd_set fdwrite,fdread;
	//������׼���õ��׽��ּ���
	DWORD index,sockok;
	//�׽��ֹ���ģʽ
	ULONG sockmode;
	DWORD flags;
	//���շ������ݼ���
	DWORD datasend,datarecv;
	//�ͻ��˵�ַ
	SOCKADDR_IN  cliAddr;
	int cliAddrLen;

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

	//���ļ����׽��ֹ���ģʽ��������ģʽ+select

	sockmode = 1;
	if (ioctlsocket(listensocket, FIONBIO, &sockmode) == SOCKET_ERROR)
	{
		printf("ioctlsocket() failed \n");
		return 0;
	}

	while(TRUE)
	{
		//��ʼ����д�׽��ּ���
		FD_ZERO(&fdread);
		FD_ZERO(&fdwrite);
		//�������׽�����ӵ������У��Ա�����������
		FD_SET(listensocket, &fdread);
		
		//���ݻ�������ǰ��״̬��Ϊ�׽������ÿɶ��Լ���д�Բ���
		//Ʃ�統�յ������Ժ���Ҫ���Ի������Ŀ�д��
		//����Ͳ�����ɶ���

		for (index = 0; index < totalsocks; index++)
			if (socklist[index]->bytesrecv > socklist[index]->bytesend)
				FD_SET(socklist[index]->socket, &fdwrite);
			else
				FD_SET(socklist[index]->socket, &fdread);
			//ѡ�����Ȥ���׽��ּ���
			if ((sockok = select(0, &fdread, &fdwrite, 
				NULL, NULL)) == SOCKET_ERROR)
			{
				fprintf(stderr, "select failed: %d\n", WSAGetLastError());
				return -1;
			}
			//��鵽������������
			if (FD_ISSET(listensocket, &fdread))
			{
				sockok--;
				//cliAddrLen�����ʼ��ΪcliAddr�Ĵ�С
				cliAddrLen=sizeof(cliAddr);
				if ((acceptsocket = accept(listensocket, 
					(sockaddr*)&cliAddr,&cliAddrLen)) != INVALID_SOCKET)
				{
					//�������Ӳ����µ��׽�������Ϊ������ģʽ
					sockmode = 1;
					if (ioctlsocket(acceptsocket, FIONBIO, &sockmode) == SOCKET_ERROR)
					{
						printf("ioctlsocket() failed with error %d\n", WSAGetLastError());
						return 0;
					}
					//Ϊ���׽��ִ�����������
					if (CreateSocketInfo(acceptsocket) == FALSE)
						return 0;
					printf("successfully got a connection from %s:%d.\n",
						inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));
				}
				else
				{		
					if (WSAGetLastError() != WSAEWOULDBLOCK)
					{
						printf("accept() failed with error %d\n", WSAGetLastError());
						return 0;
					}
					
				}
			}
			//Ϊ���е�sockok�׽��ּ���д֪ͨ
			for (index = 0; sockok > 0 && index < totalsocks; index++)
			{
				LPSOCKET_INFO sockinfo = socklist[index];
				
				//�������ɶ��Բ���
				if (FD_ISSET(sockinfo->socket, &fdread))
				{
					sockok--;
					
					sockinfo->wsaBuf.buf = sockinfo->buf;
					sockinfo->wsaBuf.len = BUFFERSIZE;
					flags = 0;
					if (WSARecv(sockinfo->socket, 
						&(sockinfo->wsaBuf), 1, &datarecv,
			   &flags, NULL, NULL) == SOCKET_ERROR)
					{
						if (WSAGetLastError() != WSAEWOULDBLOCK)
						{
							printf("Receive failed with error\n");
							FreeSocketInfo(index);
						}
						
						continue;
					} 
					else
					{
						//cliAddrLen�����ʼ��ΪcliAddr�Ĵ�С
						cliAddrLen=sizeof(cliAddr);
						
						//��ȡ�ͻ��˵�ַ��Ϣ
						if(getpeername(sockinfo->socket,(sockaddr*)&cliAddr,&cliAddrLen))
						{
							printf("getpeername failed with error %d\n", WSAGetLastError());
						}
						
						printf( "The following data comes from %s:%d\n",
							inet_ntoa(cliAddr.sin_addr),htons(cliAddr.sin_port)); 
						//���յ�������
						sockinfo->bytesrecv = datarecv;
						//��ʾ���յ�������
						printf("%s\n",sockinfo->wsaBuf.buf);
						printf("Waiting to receive data...\n");
						//������exit���˳�����ѭ��
						if(strncmp(sockinfo->wsaBuf.buf,"exit",sizeof("exit"))==0)
						{
							printf("exit the receiving loop\n");
							break;
						}	
						//���ӹرգ�����յ�0�ֽ�
						if (datarecv == 0)
						{
							FreeSocketInfo(index);
							continue;
						}
					}
				}
				//��������д�Բ���
				if (FD_ISSET(sockinfo->socket, &fdwrite))
				{
					sockok--;
					
					//��������ʣ�ಿ��
					sockinfo->wsaBuf.buf = sockinfo->buf + sockinfo->bytesend;
					sockinfo->wsaBuf.len = sockinfo->bytesrecv - sockinfo->bytesend;
					if (WSASend(sockinfo->socket, 
						&(sockinfo->wsaBuf), 1, &datasend, 0,
						NULL, NULL) == SOCKET_ERROR)
					{
						if (WSAGetLastError() != WSAEWOULDBLOCK)
						{
							printf("Send failed with error\n");
							FreeSocketInfo(index);
						}
						
						continue;
					}
					else
					{
						//�����ѷ������ݼ���
						sockinfo->bytesend += datasend;
						//�������ʱ˵�����������ѷ������
						if (sockinfo->bytesend == sockinfo->bytesrecv)
						{
							sockinfo->bytesend = 0;
							sockinfo->bytesrecv = 0;
							ZeroMemory(sockinfo->wsaBuf.buf,BUFFERSIZE);
						}
					}
				}
			}
	}

	WSACleanup();
}


void FreeSocketInfo(DWORD Index)
{
	
	LPSOCKET_INFO sockinfo = socklist[Index];
	DWORD loop;
	
	closesocket(sockinfo->socket);
	
	printf("Closing socket.....\n");
	
	GlobalFree(sockinfo);
	
	//���������Ƴ�
	for (loop = Index; loop < totalsocks-1; loop++)
	{
		socklist[loop] = socklist[loop + 1];
	}
	//�ݼ��ѹر������׽��ֵļ���
	totalsocks--;
}


BOOL CreateSocketInfo(SOCKET s)
{
	LPSOCKET_INFO sockinfo;
	
	printf("Accepted socket!\n");
	//�Ӷ��Ϸ����ڴ�
	if ((sockinfo = (LPSOCKET_INFO) GlobalAlloc(GPTR,
		sizeof(SOCKET_INFO))) == NULL)
	{
		printf("GlobalAlloc() failed\n");
		return FALSE;
	}
	
	//�׽������
	sockinfo->socket=s;
	sockinfo->bytesend=sockinfo->bytesrecv =0;
	
	socklist[totalsocks]=sockinfo;
	//�����ѽ��������׽��ֵļ���
	totalsocks++;

   return TRUE;
}



