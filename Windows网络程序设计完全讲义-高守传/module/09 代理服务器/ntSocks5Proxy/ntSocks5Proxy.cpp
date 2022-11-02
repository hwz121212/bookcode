// ntSocks5Proxy.cpp : Defines the entry point for the console application.
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

#define SOCKV5		5

#define SOCKV5_CONNECT		1
#define SOCKV5_BIND			2	
#define SOCKV5_UDP_ASS		3
#define AUTHEN_FAILURE		0

char username[256]="\0";
char password[256]="\0";

struct Socks5Req
{
    BYTE Ver;
    BYTE nMethods;
    BYTE Methods[255];
};

struct AuthReq
{
    BYTE Ver;
    BYTE Ulen;
    BYTE UserPass[1024];
};

typedef struct
{
	BYTE Ver;      // Version Number
	BYTE CMD;      // 0x01==TCP CONNECT,0x02==TCP BIND,0x03==UDP ASSOCIATE
	BYTE RSV;
	BYTE ATYP;
	BYTE IP_LEN;
	BYTE szIP;
}Socks5Info;

typedef struct
{
	DWORD dwIP;
	WORD wPort;
}IPandPort;

typedef struct
{
	BYTE Ver;
	BYTE REP;
	BYTE RSV;
	BYTE ATYP;
	IPandPort IPandPort;
}Socks5AnsConn;

typedef struct
{
	BYTE RSV[2];
	BYTE FRAG;
	BYTE ATYP;
	IPandPort IPandPort;
//	BYTE DATA;
}Socks5UDPHead;

struct SocketInfo
{
	SOCKET socks;
	IPandPort IPandPort;
};
typedef struct
{
	SocketInfo Local;
	SocketInfo Client;
	SocketInfo servaddr;
}Socks5Para;
// End Of Structure

static CRITICAL_SECTION cs; 

void TcpExchange(SOCKET* sockets);
void UDPExchange(Socks5Para *sPara);
BOOL RelayConnect(SOCKET *serSocket,char *hostName,const WORD servPort);
/////////////////////////////////////////////////////


/////////////////////////////////////////////////////
int Authentication(SOCKET* sockets, char *recvBuf,int dataLen)
{
/*	
		+----+----------+----------+
		|VER | NMETHODS | METHODS  |
		+----+----------+----------+
		| 1  |    1     | 1 to 255 |
		+----+----------+----------+
*/	
	Socks5Req *sq;
/*		+----+--------+
		|VER | METHOD |
		+----+--------+
		| 1  |   1    |
		+----+--------+
*/
	char Method[2]={0x05,0};
	sq=(Socks5Req *)recvBuf;
	//若不是socks5则将其版本号返回
	if(sq->Ver!=SOCKV5)
		return sq->Ver;
/*
  o  X'00' NO AUTHENTICATION REQUIRED
  o  X'01' GSSAPI   rfc1961
  o  X'02' USERNAME/PASSWORD  rfc1929
  o  X'03' to X'7F' IANA ASSIGNED
  o  X'80' to X'FE' RESERVED FOR PRIVATE METHODS
  o  X'FF' NO ACCEPTABLE METHODS
	*/	
	//00，无需认证；01，GSSAPI；02，需要用户名和PASSWORD
	if((sq->Methods[0]==0)||(sq->Methods[0]==2))
	{
		//用户名为空时，不需认证，将其设置为0
		if(strlen(username)==0)
			Method[1]=0x00;
		else//用户名非空时，需认证，将其设置为2
			Method[1]=0x02;
		//然后将选中的方法返回给客户端
		if(send(sockets[0],Method,2,0) == SOCKET_ERROR)
			return 0;
	}else//若不是0或者2（即不需认证或者使用用户名密码认证）则返回认证失败
		return 0;

	//若需要使用用户名/密码认证协议 rfc1929
/*		+----+------+----------+------+----------+
		|VER | ULEN |  UNAME   | PLEN |  PASSWD  |
		+----+------+----------+------+----------+
		| 1  |  1   | 1 to 255 |  1   | 1 to 255 |
		+----+------+----------+------+----------+
*/
	if(Method[1]==0x02)
	{
		char USER[256];
		char PASS[256];
		memset(USER,0,sizeof(USER));
		memset(PASS,0,sizeof(PASS));
		//接收密码
		dataLen = recv(sockets[0],recvBuf,MAXBUFSIZE,0);
		if(dataLen == SOCKET_ERROR || dataLen == 0)
			return 0;
		AuthReq *aq=(AuthReq *)recvBuf;
		//USERNAME/PASSWORD协议版本号必须为1
		if(aq->Ver!=1)
			return 0;
		//用户名一字节大小
		if((aq->Ulen!=0)&&(aq->Ulen<=256))
			memcpy(USER,recvBuf+2,aq->Ulen);
		//密码也是一字节大小
		int PLen=recvBuf[2+aq->Ulen];
		if((PLen!=0)&&(PLen<=256))
			memcpy(PASS,recvBuf+3+aq->Ulen,PLen);
		printf("USER %s\nPASS %s\n",USER,PASS);
		//0=login successfully,0xFF=failure;
		if(!strcmp(username,USER) && !strcmp(password,PASS))
		{
			recvBuf[1]=0x00;
			printf("Socks5 Authentication Passed\n");
		}
		else
		{
			recvBuf[1]=(char)0xFF;
			printf("Invalid password\n");
		}
/*			+----+--------+
			|VER | STATUS |
			+----+--------+
			| 1  |   1    |
			+----+--------+
*/
		//认证结果返回客户端，两字节大小
		if(send(sockets[0],recvBuf,2,0) == SOCKET_ERROR)
			return 0;
	}

	//可以看出，认证返回的结果要么是失败0，成功1
	//或者非socks5时返回socks版本号
	return 1;
}

char *GetInetIP(char *outIP)
{
	// Get host adresses
	char addr[16];
	struct hostent * pHost;
	pHost = gethostbyname("");
	for( int i = 0; pHost!= NULL && pHost->h_addr_list[i]!= NULL; i++ )
	{
		outIP[0]=0;
		for( int j = 0; j < pHost->h_length; j++ )
		{
			if( j > 0 ) strcat(outIP,".");
			sprintf(addr,"%u", (unsigned int)((unsigned char*)pHost->h_addr_list[i])[j]);
			strcat(outIP,addr);
		}
	}
	return outIP;
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

int GetAddrPortAndData(char *recvBuf, int dataLen, int ATYP, char *hostName, WORD *servPort)
{
	Socks5Info *Socks5Request=(Socks5Info *)recvBuf;
	struct sockaddr_in in;
	//ATYP=0x01代表IP V4地址
	if((Socks5Request->Ver==SOCKV5)&&(ATYP==1))
	{
		IPandPort *IPP=(IPandPort *)&Socks5Request->IP_LEN;
		in.sin_addr.S_un.S_addr = IPP->dwIP;
		memcpy(hostName, inet_ntoa(in.sin_addr),strlen(inet_ntoa(in.sin_addr)));
		*servPort = ntohs(IPP->wPort);
	}
	//ATYP=0x03代表域名
	else if((Socks5Request->Ver==SOCKV5)&&(ATYP==3))
	{
		memcpy(hostName, &Socks5Request->szIP, Socks5Request->IP_LEN);
		memcpy(servPort, &Socks5Request->szIP+Socks5Request->IP_LEN, 2);
		*servPort=ntohs(*servPort);
	}//对于IPV4和域名以外的（实际上需要剥离请求头而获取UDP数据部分）
	else if((Socks5Request->Ver==0)&&(Socks5Request->CMD==0)&&(ATYP==1))
	{
		IPandPort *IPP=(IPandPort *)&Socks5Request->IP_LEN;
		in.sin_addr.S_un.S_addr = IPP->dwIP;
		memcpy(hostName, inet_ntoa(in.sin_addr),strlen(inet_ntoa(in.sin_addr)));
		*servPort = ntohs(IPP->wPort);
		return 10; //return Data Enter point
	}
	else if((Socks5Request->Ver==0)&&(Socks5Request->CMD==0)&&(ATYP==3))
	{
		memcpy(hostName, &Socks5Request->szIP, Socks5Request->IP_LEN);
		memcpy(servPort, &Socks5Request->szIP+Socks5Request->IP_LEN, 2);
		*servPort=ntohs(*servPort);
		return 7+Socks5Request->IP_LEN; //return Data Enter point
	}
	else
		return 0;

	return 1;

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
int SocksProcess(SOCKET *sockets, char *recvBuf, int dataLen, char *hostName, WORD *servPort)
{
	//sockets[0] cliSocket
	//sockets[1] serSocket
	int flag=AUTHEN_FAILURE;
	//账户认证
	flag = Authentication(sockets, recvBuf, dataLen);
	if(flag==0) return AUTHEN_FAILURE;
	//处理Socks v5请求......
	dataLen = recv(sockets[0],recvBuf,MAXBUFSIZE,0);

	if(dataLen == SOCKET_ERROR || dataLen == 0)
		return 0;
	Socks5Info *Socks5Request=(Socks5Info *)recvBuf;

	//无效的Socks5 请求
	if (Socks5Request->Ver != SOCKV5) 
	{
		printf("Invalid Socks 5 Request\n");
		return 0;
	}
	//判断IP类型：0x01==IP V4地址 0x03代表域名;0x04代表IP V6地址;not Support
	if((Socks5Request->ATYP==1)||(Socks5Request->ATYP==3))
	{
		if(!GetAddrPortAndData(recvBuf, dataLen, Socks5Request->ATYP, hostName, servPort))
			return 0;
	}
	else 
	{
		printf("Dosen't support this ip type currently!\n");
		return 0;
	}

	//获取并返回代理模式：1:TCP CONNECT 2:BIND  3:UDP ASSOCIATE 
	if((Socks5Request->CMD ==SOCKV5_CONNECT)||
		(Socks5Request->CMD==SOCKV5_UDP_ASS)||
		(Socks5Request->CMD ==SOCKV5_BIND))
		return Socks5Request->CMD;

	//SocksProcess返回几种结果：代理模式或者失败0
	return 0;
}

BOOL CreateUDPSocket(Socks5AnsConn *SAC, SOCKET *socks)
{
	char szIP[256];
	struct sockaddr_in 	UDPServer;
	struct sockaddr_in  in;
	memset(&in,0,sizeof(sockaddr_in));
	int structsize=sizeof(sockaddr_in);
	//注意目标端是任意地址任意端口，换句话说，由系统具体选择
	UDPServer.sin_family=AF_INET;
	UDPServer.sin_addr.s_addr= INADDR_ANY;
	UDPServer.sin_port=INADDR_ANY;
	//创建数据报类型套接字
	SOCKET Locals = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(Locals == SOCKET_ERROR)
	{
		printf("UDP socket create failed.\n");
		return FALSE;
	}
	//绑定套接字Locals与UDPServer，即代理服务器
	if(bind(Locals,(SOCKADDR*)&UDPServer, sizeof(UDPServer)) == SOCKET_ERROR)
	{
		printf("UDP socket bind failed.\n");
		return FALSE;
	}
	UINT timeOut = TIMEOUT;
	//setsockopt(Locals,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeOut,sizeof(timeOut));
	*socks = Locals;
	//获取本地套接字名：地址、端口等
	getsockname(Locals,(struct sockaddr *)&in,&structsize);
	SAC->IPandPort.dwIP = inet_addr(GetInetIP(szIP));
	SAC->IPandPort.wPort = in.sin_port;
	printf("UDP Bound to %s:%d\r\n", szIP, ntohs(in.sin_port));
	return TRUE;
}

DWORD WINAPI ntProxyThread(SOCKET* sockets)
{
	DWORD  dwThreadID;
	static int t=0;
	EnterCriticalSection(&cs);
	int n=++t;
	LeaveCriticalSection(&cs);
	WORD   servPort = 0;
	//为套接字创建工作环境
	char *hostName = (char*)malloc(sizeof(char)*MAX_HOSTNAME);
	char *recvBuf = (char*)malloc(sizeof(char)*MAXBUFSIZE);
	char *sendBuf  = (char*)malloc(sizeof(char)*MAXBUFSIZE);

	Socks5AnsConn SAC;
	memset(hostName,0,MAX_HOSTNAME);
	memset(recvBuf,0,MAXBUFSIZE);
	memset( sendBuf,0,MAXBUFSIZE);
	memset(&SAC,0,sizeof(SAC));
	//UDP variable
	Socks5Para sPara;
	struct sockaddr_in in;
	memset(&sPara,0,sizeof(Socks5Para));
	memset(&in,0,sizeof(sockaddr_in));
	int structsize=sizeof(sockaddr_in);
	//线程启动后，开始接收数据
	int dataLen = 0,flag = 0,protocolVer=0;
	//sockets[0]为代理服务器刚刚接受返回的套接字，本线程即为其服务
	dataLen = recv(sockets[0],recvBuf,MAXBUFSIZE,0);
	if(dataLen == SOCKET_ERROR || dataLen == 0)
		goto exit;	
	
	//SOCKS代理，SocksProcess返回代理模式或者失败0
	flag=SocksProcess(sockets, recvBuf, dataLen, hostName, &servPort);
	//返回0则表示失败
	if(!flag)
	{
		goto exit;
	}
	else if(flag==SOCKV5_CONNECT)  //TCP CONNECT
	{
		protocolVer=SOCKV5;
		//连接目标服务器，套接字存储在sockets[1]中
		if(!RelayConnect(&sockets[1],hostName,servPort))
			SAC.REP=0x01;//general SOCKS server failure
		SAC.Ver=0x05;
		SAC.ATYP=0x01;
		//由于创建套接字失败，向客户端返回出错信息
		if(send(sockets[0], (char *)&SAC, 10, 0) == SOCKET_ERROR)
			goto exit;
		if(SAC.REP==0x01) // general SOCKS server failure
			goto exit;//已初始化0x00 succeeded
		//对于TCP连接：TCP CONNECT，使用TcpExchange线程转发数据
		printf("Socks%d TCP Session-> %s:%d\n",protocolVer,hostName,servPort);
		HANDLE ThreadHandle = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)TcpExchange,(LPVOID)sockets,0,&dwThreadID);
		if (ThreadHandle != NULL)
		{
			WaitForSingleObject(ThreadHandle, INFINITE);
		}

	}
	else if(flag==SOCKV5_UDP_ASS)  //UDP ASSOCIATE
	{	//UDP会话
		protocolVer=SOCKV5;
		//存储客户端连接信息，包括地址与端口
		getpeername(sockets[0],(struct sockaddr *)&in,&structsize);
		//获取客户端IP地址
		if(inet_addr(hostName)==0)
			sPara.Client.IPandPort.dwIP = in.sin_addr.s_addr;
		else
			sPara.Client.IPandPort.dwIP = inet_addr(HostToIp(hostName));

		printf("Accept ip:%s\n",inet_ntoa(in.sin_addr));
		//客户端端口
		sPara.Client.IPandPort.wPort= htons(servPort);
		//设置与客户端对应的套接字
		sPara.Client.socks=sockets[0];
		//创建本地UDP套接字，也即与目标端对应的套接字
		if(!CreateUDPSocket(&SAC,&sPara.Local.socks)) 
			SAC.REP=0x01;
		SAC.Ver=SOCKV5;
		SAC.ATYP=1;
		//由于创建套接字失败，向客户端返回出错信息
		if(send(sockets[0], (char *)&SAC, 10, 0) == SOCKET_ERROR)
			goto exit;
		if(SAC.REP==0x01) // general SOCKS server failure
			goto exit;
		//Copy local UDPsocket data structure to sPara.Local
		sPara.Local.IPandPort=SAC.IPandPort; 
		//创建UDPExchange线程
		HANDLE ThreadHandle = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)UDPExchange,(LPVOID)&sPara,0,&dwThreadID);
		if (ThreadHandle != NULL)
		{
			printf("Socks%d UDP Session-> %s:%d\n",protocolVer,inet_ntoa(in.sin_addr),ntohs(sPara.Client.IPandPort.wPort));
			WaitForSingleObject(ThreadHandle, INFINITE);
			printf("UDPExchange Thread %d Exit.\n",n);
		}
		else
		{
			goto exit;
		}
		//UDPExchange线程结束之后，代理线程ntProxyThread也就返回了
		return 1;
	}
	else if(flag==SOCKV5_BIND)  //TCP BIND
	{
		printf("BIND unimplemented yet.\n");
		goto exit;
	}
		
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
	//用于认证时使用的用户名和密码，手工输入
	if(argc==4)
	{
		strcpy(username,argv[2]);
		strcpy(password,argv[3]);
	}

	printf("SOCKSv5 Proxy.\r\nUsage:\n%s ProxyPort (Default port 1080)\n%s ProxyPort username password\n",argv[0],argv[0]);

	InitializeCriticalSection(&cs);

	SOCKET AcceptSocket = INVALID_SOCKET;
	SOCKET *sockets;
	DWORD  dwThreadID;
	struct sockaddr_in servaddr={0};
	SOCKET ProxyServer;
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PROXYPORT);
	servaddr.sin_addr.S_un.S_addr = INADDR_ANY;

	//套接字准备:WSAStartup,socket,bind,listen
	WSADATA WSAData;
	if(WSAStartup(MAKEWORD(2,2), &WSAData))
		goto exit;
	
	//创建套接字
	ProxyServer= socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(ProxyServer == SOCKET_ERROR)
		goto exit;
	
	
	//绑定到本地ip地址
	if(bind(ProxyServer, (LPSOCKADDR)&servaddr, sizeof(servaddr)) == SOCKET_ERROR)
		goto exit;
	
	//监听在1080端口
	if(listen(ProxyServer, DEFLISNUM) == SOCKET_ERROR)
		goto exit;
	
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
		//对于每个单独的客户，使用单独的线程提供服务
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
		
	}

exit:
	
	WSACleanup();
	DeleteCriticalSection(&cs);
}
////////////////////////////////
int UDPSend(SOCKET s, char *buff, int nBufSize, struct sockaddr_in *to,int tolen)
{
	int nBytesLeft = nBufSize;
	int idx = 0, nBytes = 0;
	while(nBytesLeft > 0)
	{
		nBytes = sendto(s, &buff[idx], nBytesLeft, 0, (SOCKADDR *)to, tolen);
		if(nBytes == SOCKET_ERROR)
		{
			printf("Failed to send buffer to socket %d.\r\n", WSAGetLastError());
			return SOCKET_ERROR;
		}
		nBytesLeft -= nBytes;
		idx += nBytes;
	}
	return idx;
}

//UDP代理线程
void UDPExchange(Socks5Para *sPara)
{
	struct	sockaddr_in SenderAddr;
	int		SenderAddrSize=sizeof(SenderAddr),DataLength=0,result;
	char	RecvBuf[MAXBUFSIZE];

	struct sockaddr_in UDPClient,UDPServer;
	memset(&UDPClient,0,sizeof(sockaddr_in));
	memset(&UDPServer,0,sizeof(sockaddr_in));

	//客户端信息
	UDPClient.sin_family = AF_INET;
	UDPClient.sin_addr.s_addr = sPara->Client.IPandPort.dwIP;
	UDPClient.sin_port = sPara->Client.IPandPort.wPort;
	printf("UDPExchange thread start......\n");

	fd_set readfd;
	while(TRUE)
	{
		FD_ZERO(&readfd);
		//将两个套接字均置入读套接字集合
		FD_SET((UINT)sPara->Local.socks, &readfd);
		FD_SET((UINT)sPara->Client.socks, &readfd);
		result=select(sPara->Local.socks+1,&readfd,NULL,NULL,NULL);
		if((result<0) && (errno!=EINTR))
		{
			printf("Select error.\r\n");
			break;
		}
		//无论UDP代理还是TCP代理，客户端与代理服务器均有TCP连接建立，
		//所以二者之间的通信总是使用TCP通信。
		
		//sPara->Client.socks表示已建立连接的SOCKS5 TCP套接字
		if(FD_ISSET(sPara->Client.socks, &readfd))
			break;
		//若与目标端相对应的套接字上有数据可读
		if(FD_ISSET(sPara->Local.socks, &readfd))
		{
			memset(RecvBuf,0,MAXBUFSIZE);
			//从目标端读取数据
			DataLength=recvfrom(sPara->Local.socks,
			RecvBuf+10, MAXBUFSIZE-10, 0, (struct sockaddr FAR *)&SenderAddr, &SenderAddrSize);
			if(DataLength==SOCKET_ERROR)
			{
				printf("UDPExchange recvfrom error.\n");
				break;
			}
			//若数据来自已建立关联的客户端，需要将数据转发至目标端
			if(SenderAddr.sin_port==sPara->Client.IPandPort.wPort)
			{
				//首先要移除UDP请求头，见“SOCKS5 UDP代理”一节
				WORD	servPort = 0;
				char	hostName[MAX_HOSTNAME];
				memset(hostName,0,MAX_HOSTNAME);
				
				//获取地址、端口及UDP数据位置
				int DataPoint=GetAddrPortAndData(RecvBuf+10, DataLength, RecvBuf[13], 
					hostName, &servPort);
				if(DataPoint)
				{
					//将数据转发至目标端
					UDPServer.sin_family=AF_INET;
					UDPServer.sin_addr.s_addr= inet_addr(HostToIp(hostName));
					UDPServer.sin_port=htons(servPort);
					result=UDPSend(sPara->Local.socks,RecvBuf+10+DataPoint, 
						DataLength-DataPoint,&UDPServer,sizeof(UDPServer));
					if(result == SOCKET_ERROR)
					{
						printf("sendto server error\n");
						break;
					}
					printf("Data(%d) sent to server succeed.|| Bytes: %d\n",
						DataLength-DataPoint,result);
				}else break;
				
			}//数据来自服务端
			else if(SenderAddr.sin_port==UDPServer.sin_port)
			{
				//将数据转发至客户端
				Socks5UDPHead *UDPHead = (Socks5UDPHead*)RecvBuf;
				memset(UDPHead,0,10);
				UDPHead->ATYP=0x01;
				UDPHead->IPandPort=sPara->Client.IPandPort;
				result=UDPSend(sPara->Local.socks,RecvBuf,DataLength+10,
					&UDPClient,sizeof(UDPClient));
				if(result == SOCKET_ERROR)
				{
					printf("sendto client error\n");
					break;
				}
				printf("Data(%d) sent to client succeed.|| Bytes: %d\n",DataLength+10,result);
			}else
			{
				printf("!!!!!The data are not from client or server.drop it.%s\n",
					inet_ntoa(SenderAddr.sin_addr));
			}
		}
		Sleep(5);
	}
	closesocket(sPara->Local.socks);
	closesocket(sPara->Client.socks);
}

void TcpExchange(SOCKET* sockets)
{
	SOCKET cliSocket = sockets[0];
	SOCKET serSocket = sockets[1];
	struct timeval timeset;
	//读写集合
	fd_set readfd,writefd;
	int result,i=0;
	char read_in1[MAXBUFSIZE],send_out1[MAXBUFSIZE];
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

