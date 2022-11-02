// ntHttpProxy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <errno.h>
#pragma comment(lib,"ws2_32.lib")

#define MAX_HOSTNAME	256
#define DEFAULTPORT		80
#define PROXYPORT		1080
#define DEFLISNUM		50
#define MAXBUFSIZE		20480
#define TIMEOUT			10000

#define GET_METHOD			1
#define HEAD_METHOD			2
#define POST_METHOD			3
#define CONNECT_METHOD		4
#define OTHER_METHOD		0


#define HEADLEN			7 //"http://"�ĳ���
char errorTip[]="Http/1.1 403 Forbidden\r\n\r\n<body><h1>403 Forbidden</h1></body>";
char connectedTip[]="HTTP/1.0 200 OK\r\n\r\n";

static CRITICAL_SECTION cs; 

void TcpExchange(SOCKET* sockets);
BOOL RelayConnect(SOCKET *serSocket,char *hostName,const WORD servPort);
/////////////////////////////////////////////////////
//---------------------------------------------------------------------------
void GetHostNameAndPort(char *recvBuf,int datalen,char *hostName,UINT *servPort)
{
	char *fp = recvBuf;
	for(int i = 0;i < datalen && *fp != ':' && *fp != '\0' && *fp != '\r' && *fp != '/';i++)
	{
		hostName[i]=*fp++;
		if(*fp == ':')
			*servPort=atoi(fp+1);
		else *servPort=DEFAULTPORT;
	}
}
//---------------------------------------------------------------------------
char * GetURLRootPoint(char * recvBuf,int dataLen,int *hostNameLen)
{
	for(int i = 0;i < dataLen; i++)
	{
		if(recvBuf[i] == '/')
		{
			*hostNameLen = i;
			return &recvBuf[i];
		}
	}
	return NULL;
}
//���ͻ����ύ����������
int ParseRequest(char *recvBuf,int *methodLen)
{
	//GET�����1
	if(!strnicmp(recvBuf,"GET ",4))
	{
		*methodLen = 4;
		return GET_METHOD;
	}
	//HEAD�����2����GET����
	else if(!strnicmp(recvBuf,"HEAD ",5)) 
	{
		*methodLen = 5;
		return HEAD_METHOD;
	}
	//POST�����3
	else if(!strnicmp(recvBuf,"POST ",5))
	{
		*methodLen = 5;
		return POST_METHOD;
	}
	//CONNECT�����4
	else if(!strnicmp(recvBuf,"CONNECT ",8))
	{
		*methodLen = 8;
		return CONNECT_METHOD;
	}
	//�����򷵻�0
	else
	{
		return OTHER_METHOD;
	}
}
int EditRequest(char *sendBuf,char *recvBuf,int dataLen,int methodLen)
{
	printf("The connetcion request is:\n\n%s\n",recvBuf);
	//��������ȡ
	strncpy(sendBuf,recvBuf,methodLen);
	
	int hedLen = 0;
	//ȷ���Ƿ�Ϊ"http://"Э��
	if(strncmp(recvBuf+methodLen,"http://",HEADLEN))
		return 0;

	//��ȡ��ȥ�����������Ĳ��֣���recvBufΪ"GET http://www.126.com/ HTTP/1.1..."
	//��getRootfpΪ"/ HTTP/1.1 ..."
	char * getRootfp = GetURLRootPoint(recvBuf+methodLen+HEADLEN,dataLen-methodLen-HEADLEN,&hedLen);
	if(getRootfp == NULL)
		return 0;

	memcpy(sendBuf+methodLen,getRootfp,dataLen-methodLen-HEADLEN-hedLen);
	//������������ʵ�����ǽ�"http://www.126.com"�����������Ƴ�
//	printf("The Edited request is:\n\n%s\n",sendBuf);
	return dataLen-HEADLEN-hedLen;
}
BOOL SendReqRes(SOCKET* sockets, char *sendBuf, char *recvBuf, int dataLen)
{
	//sockets[0] cliSocket
	//sockets[1] serSocket
	DWORD  dwThreadID;
	char   hostName[MAX_HOSTNAME] = {0};
	UINT   servPort = 0;
	static int t=0;
	EnterCriticalSection(&cs);
	int n=++t;
	LeaveCriticalSection(&cs);
	int flag=0, methodLen=0, sendLen=0;
	//���ͻ����ύ���������ͣ�����ȡ����ĳ����Ա���ȡ����
	flag = ParseRequest(recvBuf,&methodLen);
	if(flag==OTHER_METHOD)
		return FALSE;

	//����GET_METHOD��HEAD_METHOD��POST_METHOD��ΪHTTP����
	if(flag==GET_METHOD|| flag==HEAD_METHOD|| flag==POST_METHOD)
	{
		//�޸����󣬼��Ƴ������������֣���������sendBuf��
		sendLen=EditRequest(sendBuf,recvBuf,dataLen,methodLen);
		if(!sendLen)
			return 0;
		//��recvBuf�л�ȡĿ�����������˿��Ա���������
		GetHostNameAndPort(recvBuf+methodLen+HEADLEN,dataLen-methodLen-HEADLEN,hostName,&servPort);
		if(!RelayConnect(&sockets[1],hostName,servPort))
			return 0;
		//����Ŀ�����������ӽ����ɹ��Ժ󣬽��޸ĺ�Ŀͻ��������͸�Ŀ��������
		//��ʱ��������������ת���ͻ���HTTP������������Ժ��ʵ���ʱ��Ŀ������Ҳ����
		//HTTP����������Ӧת�����ͻ��˼���
		if(send(sockets[1],sendBuf,sendLen,0) == SOCKET_ERROR)
			return 0;
	}//����CONNECT_METHOD��Ϊ������
	else if(flag==CONNECT_METHOD)
	{
		GetHostNameAndPort(recvBuf+methodLen,dataLen-methodLen,hostName,&servPort);
		if(!RelayConnect(&sockets[1],hostName,servPort))
			return 0;
		//��ͻ��˷������ӳɹ���������Ϣ
		send(sockets[0], connectedTip, strlen(connectedTip)+1,0);
	}
	//�������ѳɹ���ʼ�ṩ���񣬼��������Ӿ��ѽ���
	if(sockets[0] && sockets[1])
	{
		printf("HTTP Proxy request %d OK.\n",n);
		//����TCP�����̣߳�ת�����ݣ�ֱ�������߳̽���Ϊֹ
		HANDLE ThreadHandle = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)TcpExchange,(LPVOID)sockets,0,&dwThreadID);
		if (ThreadHandle != NULL)
		{
			WaitForSingleObject(ThreadHandle, INFINITE);
			printf("HTTP Proxy request %d Exit.\n",n);
		}
	}else
		return 0;
	return 1;

}

//��������
char *HostToIp(char *hostName)
{
	HOSTENT *hostent = NULL;
	IN_ADDR iaddr;
	hostent = gethostbyname(hostName);
	if (hostent == NULL)
	{
		return NULL;
	}
	iaddr = *((LPIN_ADDR)*hostent->h_addr_list);
	return inet_ntoa(iaddr);
}


BOOL RelayConnect(SOCKET *serSocket,char *hostName,const WORD servPort)
{
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(servPort);

	if (inet_addr(hostName) != INADDR_NONE)
		servaddr.sin_addr.s_addr = inet_addr(hostName);
	else
	{
		//���������Ի�ȡIP��ַ
		if (HostToIp(hostName) != NULL)
			servaddr.sin_addr.s_addr = inet_addr(HostToIp(hostName));
		else
			return FALSE;
	}
	//������������Ŀ���������׽��֣��洢��sockets[1]�з���
	*serSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (*serSocket == INVALID_SOCKET)
		return FALSE;
	UINT timeOut = TIMEOUT;
	//���ó�ʱֵ������Ŀ��������������
	setsockopt(*serSocket,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeOut,sizeof(timeOut));
	if (connect(*serSocket, (const SOCKADDR *)&servaddr,sizeof(servaddr)) == SOCKET_ERROR)
	{
		printf("Fail To Connect To Remote Host\n");
		closesocket(*serSocket);
		return FALSE;
	}

	return TRUE;
}

DWORD WINAPI ntProxyThread(SOCKET* sockets)
{
	static int t=0;
	EnterCriticalSection(&cs);
	int n=++t;
	LeaveCriticalSection(&cs);
	WORD   servPort = 0;
	//Ϊ�׽��ִ�����������
	char *hostName = (char*)malloc(sizeof(char)*MAX_HOSTNAME);
	char *recvBuf = (char*)malloc(sizeof(char)*MAXBUFSIZE);
	char *sendBuf  = (char*)malloc(sizeof(char)*MAXBUFSIZE);

	memset(hostName,0,MAX_HOSTNAME);
	memset(recvBuf,0,MAXBUFSIZE);
	memset(sendBuf,0,MAXBUFSIZE);

	struct sockaddr_in in;
	memset(&in,0,sizeof(sockaddr_in));
	int structsize=sizeof(sockaddr_in);
	//�߳������󣬿�ʼ��������
	int dataLen = 0,flag = 0;
	//sockets[0]Ϊ����������ոս��ܷ��ص��׽��֣����̼߳�Ϊ�����
	dataLen = recv(sockets[0],recvBuf,MAXBUFSIZE,0);
	if(dataLen == SOCKET_ERROR || dataLen == 0)
		goto exit;
	//��������HTTP����
	if(SendReqRes(sockets, sendBuf, recvBuf, dataLen))
		goto exit;
exit:
	closesocket(sockets[0]);
	closesocket(sockets[1]);
	free(sockets);
	free(hostName);
	free(sendBuf);
	free(recvBuf);
	return 0;
}


void main(int argc, char* argv[])
{

	printf("Http Proxy.\r\nUsage:\n%s ProxyPort (Default port 1080)\n%s ProxyPort \n",argv[0],argv[0]);

	InitializeCriticalSection(&cs);

	//�׽���׼��:WSAStartup,socket,bind,listen
	WSADATA WSAData;
	if(WSAStartup(MAKEWORD(2,2), &WSAData))
		return;
	
	//�����׽���
	SOCKET ProxyServer= socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(ProxyServer == SOCKET_ERROR)
		return;
	
	struct sockaddr_in servaddr={0};
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PROXYPORT);
	servaddr.sin_addr.S_un.S_addr = INADDR_ANY;
	
	//�󶨵�����ip��ַ
	if(bind(ProxyServer, (LPSOCKADDR)&servaddr, sizeof(servaddr)) == SOCKET_ERROR)
		return;
	
	//������1080�˿�
	if(listen(ProxyServer, DEFLISNUM) == SOCKET_ERROR)
		return;
	
	SOCKET AcceptSocket = INVALID_SOCKET;
	SOCKET *sockets;
	DWORD  dwThreadID;
	
	printf("Now listening on port: %d\r\n",PROXYPORT);
	while(TRUE)
	{
		//���ܿͻ��˵���������
		AcceptSocket = accept(ProxyServer, NULL, NULL);
		printf("Accepting New Requests\n");
		//�����׽��ִ洢�ռ䣬�����鷽ʽ�洢�����׽��֣�
		//���ܵ��׽����Լ�����Ŀ�꣨Զ�̣������׽���
		sockets = (SOCKET*)malloc(sizeof(SOCKET)*2);
		if (sockets == NULL)
		{
			printf("Fail To Allocate Ram\n");
			continue;
		}
		sockets[0] = AcceptSocket;
		//���ڿͻ�����ʹ�ö������߳��ṩ����
		HANDLE hThread = CreateThread (NULL,0, (LPTHREAD_START_ROUTINE)ntProxyThread,sockets,0, &dwThreadID);        // Create Thread To Handle Request
		if (hThread == NULL)
		{
			printf("Fail To Create Thread.Probably Too Many Threads Have Been Created\n");
			Sleep(1000);
		}
		else
		{
			CloseHandle(hThread);
		}
		WaitForSingleObject(hThread,INFINITE);
	}

	WSACleanup();
	DeleteCriticalSection(&cs);
}


void TcpExchange(SOCKET* sockets)
{
	SOCKET cliSocket = sockets[0];
	SOCKET serSocket = sockets[1];
	struct timeval timeset;
	//��д����
	fd_set readfd,writefd;
	int result,i=0;
	char read_in1[MAXBUFSIZE],send_out1[MAXBUFSIZE],sendBuf[MAXBUFSIZE];
	char read_in2[MAXBUFSIZE],send_out2[MAXBUFSIZE];
	int read1=0,totalread1=0,send1=0;
	int read2=0,totalread2=0,send2=0;
	int sendcount1,sendcount2;
	int maxfd;

	maxfd=max(cliSocket,serSocket)+1;
	memset(read_in1,0,MAXBUFSIZE);
	memset(read_in2,0,MAXBUFSIZE);
	memset(send_out1,0,MAXBUFSIZE);
	memset(send_out2,0,MAXBUFSIZE);

	timeset.tv_sec=TIMEOUT;
	timeset.tv_usec=0;
	while(TRUE)
	{
		FD_ZERO(&readfd);
		FD_ZERO(&writefd);
		//�������׽��־����뵽��д������
		FD_SET((UINT)cliSocket, &readfd);
		FD_SET((UINT)cliSocket, &writefd);
		FD_SET((UINT)serSocket, &writefd);
		FD_SET((UINT)serSocket, &readfd);

		result=select(maxfd,&readfd,&writefd,NULL,&timeset);
		if((result<0) && (errno!=EINTR))
		{
			printf("Select error.\r\n");
			break;
		}
		else if(result==0)
		{
			printf("Socket time out.\r\n");
			break;
		}
		//serSocketΪ��Ŀ���������ӵ��׽��֣��������Ƿ������ݷ���
		if(FD_ISSET(serSocket, &readfd))
		{
			if(totalread2<MAXBUFSIZE)
			{
				read2=recv(serSocket,read_in2,MAXBUFSIZE-totalread2, 0);
				if(read2==0)break;
				if((read2<0) && (errno!=EINTR))
				{
					printf("Read serSocket data error,maybe close?\r\n\r\n");
					break;
				}

				memcpy(send_out2+totalread2,read_in2,read2);

          		totalread2+=read2;
          		memset(read_in2,0,MAXBUFSIZE);

			}
        }
		//cliSocketΪ��ͻ����������ӵ��׽��֣��Ƿ���Խ����ݷ��ظ��ͻ���
		if(FD_ISSET(cliSocket, &writefd))
     	{
			int err2=0;
     	   	sendcount2=0;
     	   	while(totalread2>0)
     	   	{
     	   	 	send2=send(cliSocket, send_out2+sendcount2, totalread2, 0);
     	   		if(send2==0)break;
     	   		if((send2<0) && (errno!=EINTR))
     	   		{
     	   			printf("Send to cliSocket unknow error.\r\n");
					err2=1;
     	   			break;
     	   		}
     	   		if((send2<0) && (errno==ENOSPC)) break;
     	   		sendcount2+=send2;
     	   		totalread2-=send2;

     	   	}
			if(err2==1) break;
     	  	if((totalread2>0) && (sendcount2 > 0))
			{
				/* move not sended data to start addr */
				memcpy(send_out2, send_out2+sendcount2, totalread2);
				memset(send_out2+totalread2, 0, MAXBUFSIZE-totalread2);
			}
			else
				memset(send_out2,0,MAXBUFSIZE);
		}

		//cliSocketΪ��ͻ����������ӵ��׽��֣��Ƿ�������ӿͻ��˵���
		if(FD_ISSET(cliSocket, &readfd))
		{
			if(totalread1<MAXBUFSIZE)
      	 	{
				read1=recv(cliSocket, read_in1, MAXBUFSIZE-totalread1, 0);
				if((read1==SOCKET_ERROR) || (read1==0))
		  		{
		  			break;
		  		}

				memcpy(send_out1+totalread1,read_in1,read1);

				totalread1+=read1;
				memset(read_in1,0,MAXBUFSIZE);
			}
			//ת�����Կͻ��˵�����
			if(SendReqRes(sockets,sendBuf,send_out1,totalread1))
				totalread1=0;
		}
		//serSocketΪ��Ŀ���������ӵ��׽��֣�������Ƿ������������ύ����
		if(FD_ISSET(serSocket, &writefd))
		{
			int err=0;
			sendcount1=0;
			while(totalread1>0)
			{
				send1=send(serSocket, send_out1+sendcount1, totalread1, 0);
				if(send1==0)break;
				if((send1<0) && (errno!=EINTR))
				{
					err=1;
					break;
				}

				if((send1<0) && (errno==ENOSPC)) break;
				sendcount1+=send1;
				totalread1-=send1;

			}

			if(err==1) break;
			if((totalread1>0) && (sendcount1>0))
			{
				memcpy(send_out1,send_out1+sendcount1,totalread1);
				memset(send_out1+totalread1,0,MAXBUFSIZE-totalread1);
			}
			else
			memset(send_out1,0,MAXBUFSIZE);
		}
		Sleep(5);
	}

	closesocket(cliSocket);
	closesocket(serSocket);
}

