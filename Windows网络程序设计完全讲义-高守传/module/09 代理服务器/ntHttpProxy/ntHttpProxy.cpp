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


#define HEADLEN			7 //"http://"的长度
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
//检查客户端提交的请求类型
int ParseRequest(char *recvBuf,int *methodLen)
{
	//GET命令返回1
	if(!strnicmp(recvBuf,"GET ",4))
	{
		*methodLen = 4;
		return GET_METHOD;
	}
	//HEAD命令返回2，与GET类似
	else if(!strnicmp(recvBuf,"HEAD ",5)) 
	{
		*methodLen = 5;
		return HEAD_METHOD;
	}
	//POST命令返回3
	else if(!strnicmp(recvBuf,"POST ",5))
	{
		*methodLen = 5;
		return POST_METHOD;
	}
	//CONNECT命令返回4
	else if(!strnicmp(recvBuf,"CONNECT ",8))
	{
		*methodLen = 8;
		return CONNECT_METHOD;
	}
	//其他则返回0
	else
	{
		return OTHER_METHOD;
	}
}
int EditRequest(char *sendBuf,char *recvBuf,int dataLen,int methodLen)
{
	printf("The connetcion request is:\n\n%s\n",recvBuf);
	//将命令提取
	strncpy(sendBuf,recvBuf,methodLen);
	
	int hedLen = 0;
	//确定是否为"http://"协议
	if(strncmp(recvBuf+methodLen,"http://",HEADLEN))
		return 0;

	//获取除去命令及域名以外的部分，如recvBuf为"GET http://www.126.com/ HTTP/1.1..."
	//则getRootfp为"/ HTTP/1.1 ..."
	char * getRootfp = GetURLRootPoint(recvBuf+methodLen+HEADLEN,dataLen-methodLen-HEADLEN,&hedLen);
	if(getRootfp == NULL)
		return 0;

	memcpy(sendBuf+methodLen,getRootfp,dataLen-methodLen-HEADLEN-hedLen);
	//经过上述处理，实际上是将"http://www.126.com"即域名部分移除
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
	//检查客户端提交的请求类型，并获取命令的长度以便提取命令
	flag = ParseRequest(recvBuf,&methodLen);
	if(flag==OTHER_METHOD)
		return FALSE;

	//对于GET_METHOD、HEAD_METHOD及POST_METHOD则为HTTP代理
	if(flag==GET_METHOD|| flag==HEAD_METHOD|| flag==POST_METHOD)
	{
		//修改请求，即移除主机域名部分，将其置于sendBuf中
		sendLen=EditRequest(sendBuf,recvBuf,dataLen,methodLen);
		if(!sendLen)
			return 0;
		//从recvBuf中获取目标主机名及端口以便向其连接
		GetHostNameAndPort(recvBuf+methodLen+HEADLEN,dataLen-methodLen-HEADLEN,hostName,&servPort);
		if(!RelayConnect(&sockets[1],hostName,servPort))
			return 0;
		//在与目标主机的连接建立成功以后，将修改后的客户端请求发送给目标主机，
		//此时代理服务器已完成转发客户端HTTP请求的任务，在稍后适当的时候将目标主机也即是
		//HTTP服务器的响应转发给客户端即可
		if(send(sockets[1],sendBuf,sendLen,0) == SOCKET_ERROR)
			return 0;
	}//对于CONNECT_METHOD则为代理保留
	else if(flag==CONNECT_METHOD)
	{
		GetHostNameAndPort(recvBuf+methodLen,dataLen-methodLen,hostName,&servPort);
		if(!RelayConnect(&sockets[1],hostName,servPort))
			return 0;
		//向客户端发送连接成功建立的消息
		send(sockets[0], connectedTip, strlen(connectedTip)+1,0);
	}
	//若代理已成功开始提供服务，即两个连接均已建立
	if(sockets[0] && sockets[1])
	{
		printf("HTTP Proxy request %d OK.\n",n);
		//创建TCP传输线程，转发数据，直至传输线程结束为止
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

//域名解析
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
		//解析域名以获取IP地址
		if (HostToIp(hostName) != NULL)
			servaddr.sin_addr.s_addr = inet_addr(HostToIp(hostName));
		else
			return FALSE;
	}
	//创建用于连接目标主机的套接字，存储在sockets[1]中返回
	*serSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (*serSocket == INVALID_SOCKET)
		return FALSE;
	UINT timeOut = TIMEOUT;
	//设置超时值，并向目标主机发起连接
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
	//为套接字创建工作环境
	char *hostName = (char*)malloc(sizeof(char)*MAX_HOSTNAME);
	char *recvBuf = (char*)malloc(sizeof(char)*MAXBUFSIZE);
	char *sendBuf  = (char*)malloc(sizeof(char)*MAXBUFSIZE);

	memset(hostName,0,MAX_HOSTNAME);
	memset(recvBuf,0,MAXBUFSIZE);
	memset(sendBuf,0,MAXBUFSIZE);

	struct sockaddr_in in;
	memset(&in,0,sizeof(sockaddr_in));
	int structsize=sizeof(sockaddr_in);
	//线程启动后，开始接收数据
	int dataLen = 0,flag = 0;
	//sockets[0]为代理服务器刚刚接受返回的套接字，本线程即为其服务
	dataLen = recv(sockets[0],recvBuf,MAXBUFSIZE,0);
	if(dataLen == SOCKET_ERROR || dataLen == 0)
		goto exit;
	//发送请求，HTTP代理
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

	//套接字准备:WSAStartup,socket,bind,listen
	WSADATA WSAData;
	if(WSAStartup(MAKEWORD(2,2), &WSAData))
		return;
	
	//创建套接字
	SOCKET ProxyServer= socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(ProxyServer == SOCKET_ERROR)
		return;
	
	struct sockaddr_in servaddr={0};
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PROXYPORT);
	servaddr.sin_addr.S_un.S_addr = INADDR_ANY;
	
	//绑定到本地ip地址
	if(bind(ProxyServer, (LPSOCKADDR)&servaddr, sizeof(servaddr)) == SOCKET_ERROR)
		return;
	
	//监听在1080端口
	if(listen(ProxyServer, DEFLISNUM) == SOCKET_ERROR)
		return;
	
	SOCKET AcceptSocket = INVALID_SOCKET;
	SOCKET *sockets;
	DWORD  dwThreadID;
	
	printf("Now listening on port: %d\r\n",PROXYPORT);
	while(TRUE)
	{
		//接受客户端的连接请求
		AcceptSocket = accept(ProxyServer, NULL, NULL);
		printf("Accepting New Requests\n");
		//分配套接字存储空间，以数组方式存储两个套接字：
		//接受的套接字以及连接目标（远程）机的套接字
		sockets = (SOCKET*)malloc(sizeof(SOCKET)*2);
		if (sockets == NULL)
		{
			printf("Fail To Allocate Ram\n");
			continue;
		}
		sockets[0] = AcceptSocket;
		//对于客户请求，使用独立的线程提供服务
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
	//读写集合
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
		//将两个套接字均加入到读写集合中
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
		//serSocket为与目标主机连接的套接字：服务器是否有数据返回
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
		//cliSocket为与客户端主机连接的套接字：是否可以将数据返回给客户端
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

		//cliSocket为与客户端主机连接的套接字：是否有请求从客户端到来
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
			//转发来自客户端的请求
			if(SendReqRes(sockets,sendBuf,send_out1,totalread1))
				totalread1=0;
		}
		//serSocket为与目标主机连接的套接字：代理端是否可以向服务器提交数据
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

