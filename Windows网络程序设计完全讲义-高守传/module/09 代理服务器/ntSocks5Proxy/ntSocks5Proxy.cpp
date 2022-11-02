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
	//������socks5����汾�ŷ���
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
	//00��������֤��01��GSSAPI��02����Ҫ�û�����PASSWORD
	if((sq->Methods[0]==0)||(sq->Methods[0]==2))
	{
		//�û���Ϊ��ʱ��������֤����������Ϊ0
		if(strlen(username)==0)
			Method[1]=0x00;
		else//�û����ǿ�ʱ������֤����������Ϊ2
			Method[1]=0x02;
		//Ȼ��ѡ�еķ������ظ��ͻ���
		if(send(sockets[0],Method,2,0) == SOCKET_ERROR)
			return 0;
	}else//������0����2����������֤����ʹ���û���������֤���򷵻���֤ʧ��
		return 0;

	//����Ҫʹ���û���/������֤Э�� rfc1929
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
		//��������
		dataLen = recv(sockets[0],recvBuf,MAXBUFSIZE,0);
		if(dataLen == SOCKET_ERROR || dataLen == 0)
			return 0;
		AuthReq *aq=(AuthReq *)recvBuf;
		//USERNAME/PASSWORDЭ��汾�ű���Ϊ1
		if(aq->Ver!=1)
			return 0;
		//�û���һ�ֽڴ�С
		if((aq->Ulen!=0)&&(aq->Ulen<=256))
			memcpy(USER,recvBuf+2,aq->Ulen);
		//����Ҳ��һ�ֽڴ�С
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
		//��֤������ؿͻ��ˣ����ֽڴ�С
		if(send(sockets[0],recvBuf,2,0) == SOCKET_ERROR)
			return 0;
	}

	//���Կ�������֤���صĽ��Ҫô��ʧ��0���ɹ�1
	//���߷�socks5ʱ����socks�汾��
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

int GetAddrPortAndData(char *recvBuf, int dataLen, int ATYP, char *hostName, WORD *servPort)
{
	Socks5Info *Socks5Request=(Socks5Info *)recvBuf;
	struct sockaddr_in in;
	//ATYP=0x01����IP V4��ַ
	if((Socks5Request->Ver==SOCKV5)&&(ATYP==1))
	{
		IPandPort *IPP=(IPandPort *)&Socks5Request->IP_LEN;
		in.sin_addr.S_un.S_addr = IPP->dwIP;
		memcpy(hostName, inet_ntoa(in.sin_addr),strlen(inet_ntoa(in.sin_addr)));
		*servPort = ntohs(IPP->wPort);
	}
	//ATYP=0x03��������
	else if((Socks5Request->Ver==SOCKV5)&&(ATYP==3))
	{
		memcpy(hostName, &Socks5Request->szIP, Socks5Request->IP_LEN);
		memcpy(servPort, &Socks5Request->szIP+Socks5Request->IP_LEN, 2);
		*servPort=ntohs(*servPort);
	}//����IPV4����������ģ�ʵ������Ҫ��������ͷ����ȡUDP���ݲ��֣�
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
int SocksProcess(SOCKET *sockets, char *recvBuf, int dataLen, char *hostName, WORD *servPort)
{
	//sockets[0] cliSocket
	//sockets[1] serSocket
	int flag=AUTHEN_FAILURE;
	//�˻���֤
	flag = Authentication(sockets, recvBuf, dataLen);
	if(flag==0) return AUTHEN_FAILURE;
	//����Socks v5����......
	dataLen = recv(sockets[0],recvBuf,MAXBUFSIZE,0);

	if(dataLen == SOCKET_ERROR || dataLen == 0)
		return 0;
	Socks5Info *Socks5Request=(Socks5Info *)recvBuf;

	//��Ч��Socks5 ����
	if (Socks5Request->Ver != SOCKV5) 
	{
		printf("Invalid Socks 5 Request\n");
		return 0;
	}
	//�ж�IP���ͣ�0x01==IP V4��ַ 0x03��������;0x04����IP V6��ַ;not Support
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

	//��ȡ�����ش���ģʽ��1:TCP CONNECT 2:BIND  3:UDP ASSOCIATE 
	if((Socks5Request->CMD ==SOCKV5_CONNECT)||
		(Socks5Request->CMD==SOCKV5_UDP_ASS)||
		(Socks5Request->CMD ==SOCKV5_BIND))
		return Socks5Request->CMD;

	//SocksProcess���ؼ��ֽ��������ģʽ����ʧ��0
	return 0;
}

BOOL CreateUDPSocket(Socks5AnsConn *SAC, SOCKET *socks)
{
	char szIP[256];
	struct sockaddr_in 	UDPServer;
	struct sockaddr_in  in;
	memset(&in,0,sizeof(sockaddr_in));
	int structsize=sizeof(sockaddr_in);
	//ע��Ŀ����������ַ����˿ڣ����仰˵����ϵͳ����ѡ��
	UDPServer.sin_family=AF_INET;
	UDPServer.sin_addr.s_addr= INADDR_ANY;
	UDPServer.sin_port=INADDR_ANY;
	//�������ݱ������׽���
	SOCKET Locals = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(Locals == SOCKET_ERROR)
	{
		printf("UDP socket create failed.\n");
		return FALSE;
	}
	//���׽���Locals��UDPServer�������������
	if(bind(Locals,(SOCKADDR*)&UDPServer, sizeof(UDPServer)) == SOCKET_ERROR)
	{
		printf("UDP socket bind failed.\n");
		return FALSE;
	}
	UINT timeOut = TIMEOUT;
	//setsockopt(Locals,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeOut,sizeof(timeOut));
	*socks = Locals;
	//��ȡ�����׽���������ַ���˿ڵ�
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
	//Ϊ�׽��ִ�����������
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
	//�߳������󣬿�ʼ��������
	int dataLen = 0,flag = 0,protocolVer=0;
	//sockets[0]Ϊ����������ոս��ܷ��ص��׽��֣����̼߳�Ϊ�����
	dataLen = recv(sockets[0],recvBuf,MAXBUFSIZE,0);
	if(dataLen == SOCKET_ERROR || dataLen == 0)
		goto exit;	
	
	//SOCKS����SocksProcess���ش���ģʽ����ʧ��0
	flag=SocksProcess(sockets, recvBuf, dataLen, hostName, &servPort);
	//����0���ʾʧ��
	if(!flag)
	{
		goto exit;
	}
	else if(flag==SOCKV5_CONNECT)  //TCP CONNECT
	{
		protocolVer=SOCKV5;
		//����Ŀ����������׽��ִ洢��sockets[1]��
		if(!RelayConnect(&sockets[1],hostName,servPort))
			SAC.REP=0x01;//general SOCKS server failure
		SAC.Ver=0x05;
		SAC.ATYP=0x01;
		//���ڴ����׽���ʧ�ܣ���ͻ��˷��س�����Ϣ
		if(send(sockets[0], (char *)&SAC, 10, 0) == SOCKET_ERROR)
			goto exit;
		if(SAC.REP==0x01) // general SOCKS server failure
			goto exit;//�ѳ�ʼ��0x00 succeeded
		//����TCP���ӣ�TCP CONNECT��ʹ��TcpExchange�߳�ת������
		printf("Socks%d TCP Session-> %s:%d\n",protocolVer,hostName,servPort);
		HANDLE ThreadHandle = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)TcpExchange,(LPVOID)sockets,0,&dwThreadID);
		if (ThreadHandle != NULL)
		{
			WaitForSingleObject(ThreadHandle, INFINITE);
		}

	}
	else if(flag==SOCKV5_UDP_ASS)  //UDP ASSOCIATE
	{	//UDP�Ự
		protocolVer=SOCKV5;
		//�洢�ͻ���������Ϣ��������ַ��˿�
		getpeername(sockets[0],(struct sockaddr *)&in,&structsize);
		//��ȡ�ͻ���IP��ַ
		if(inet_addr(hostName)==0)
			sPara.Client.IPandPort.dwIP = in.sin_addr.s_addr;
		else
			sPara.Client.IPandPort.dwIP = inet_addr(HostToIp(hostName));

		printf("Accept ip:%s\n",inet_ntoa(in.sin_addr));
		//�ͻ��˶˿�
		sPara.Client.IPandPort.wPort= htons(servPort);
		//������ͻ��˶�Ӧ���׽���
		sPara.Client.socks=sockets[0];
		//��������UDP�׽��֣�Ҳ����Ŀ��˶�Ӧ���׽���
		if(!CreateUDPSocket(&SAC,&sPara.Local.socks)) 
			SAC.REP=0x01;
		SAC.Ver=SOCKV5;
		SAC.ATYP=1;
		//���ڴ����׽���ʧ�ܣ���ͻ��˷��س�����Ϣ
		if(send(sockets[0], (char *)&SAC, 10, 0) == SOCKET_ERROR)
			goto exit;
		if(SAC.REP==0x01) // general SOCKS server failure
			goto exit;
		//Copy local UDPsocket data structure to sPara.Local
		sPara.Local.IPandPort=SAC.IPandPort; 
		//����UDPExchange�߳�
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
		//UDPExchange�߳̽���֮�󣬴����߳�ntProxyThreadҲ�ͷ�����
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
	//������֤ʱʹ�õ��û��������룬�ֹ�����
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

	//�׽���׼��:WSAStartup,socket,bind,listen
	WSADATA WSAData;
	if(WSAStartup(MAKEWORD(2,2), &WSAData))
		goto exit;
	
	//�����׽���
	ProxyServer= socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(ProxyServer == SOCKET_ERROR)
		goto exit;
	
	
	//�󶨵�����ip��ַ
	if(bind(ProxyServer, (LPSOCKADDR)&servaddr, sizeof(servaddr)) == SOCKET_ERROR)
		goto exit;
	
	//������1080�˿�
	if(listen(ProxyServer, DEFLISNUM) == SOCKET_ERROR)
		goto exit;
	
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
		//����ÿ�������Ŀͻ���ʹ�õ������߳��ṩ����
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

//UDP�����߳�
void UDPExchange(Socks5Para *sPara)
{
	struct	sockaddr_in SenderAddr;
	int		SenderAddrSize=sizeof(SenderAddr),DataLength=0,result;
	char	RecvBuf[MAXBUFSIZE];

	struct sockaddr_in UDPClient,UDPServer;
	memset(&UDPClient,0,sizeof(sockaddr_in));
	memset(&UDPServer,0,sizeof(sockaddr_in));

	//�ͻ�����Ϣ
	UDPClient.sin_family = AF_INET;
	UDPClient.sin_addr.s_addr = sPara->Client.IPandPort.dwIP;
	UDPClient.sin_port = sPara->Client.IPandPort.wPort;
	printf("UDPExchange thread start......\n");

	fd_set readfd;
	while(TRUE)
	{
		FD_ZERO(&readfd);
		//�������׽��־�������׽��ּ���
		FD_SET((UINT)sPara->Local.socks, &readfd);
		FD_SET((UINT)sPara->Client.socks, &readfd);
		result=select(sPara->Local.socks+1,&readfd,NULL,NULL,NULL);
		if((result<0) && (errno!=EINTR))
		{
			printf("Select error.\r\n");
			break;
		}
		//����UDP������TCP�����ͻ�����������������TCP���ӽ�����
		//���Զ���֮���ͨ������ʹ��TCPͨ�š�
		
		//sPara->Client.socks��ʾ�ѽ������ӵ�SOCKS5 TCP�׽���
		if(FD_ISSET(sPara->Client.socks, &readfd))
			break;
		//����Ŀ������Ӧ���׽����������ݿɶ�
		if(FD_ISSET(sPara->Local.socks, &readfd))
		{
			memset(RecvBuf,0,MAXBUFSIZE);
			//��Ŀ��˶�ȡ����
			DataLength=recvfrom(sPara->Local.socks,
			RecvBuf+10, MAXBUFSIZE-10, 0, (struct sockaddr FAR *)&SenderAddr, &SenderAddrSize);
			if(DataLength==SOCKET_ERROR)
			{
				printf("UDPExchange recvfrom error.\n");
				break;
			}
			//�����������ѽ��������Ŀͻ��ˣ���Ҫ������ת����Ŀ���
			if(SenderAddr.sin_port==sPara->Client.IPandPort.wPort)
			{
				//����Ҫ�Ƴ�UDP����ͷ������SOCKS5 UDP����һ��
				WORD	servPort = 0;
				char	hostName[MAX_HOSTNAME];
				memset(hostName,0,MAX_HOSTNAME);
				
				//��ȡ��ַ���˿ڼ�UDP����λ��
				int DataPoint=GetAddrPortAndData(RecvBuf+10, DataLength, RecvBuf[13], 
					hostName, &servPort);
				if(DataPoint)
				{
					//������ת����Ŀ���
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
				
			}//�������Է����
			else if(SenderAddr.sin_port==UDPServer.sin_port)
			{
				//������ת�����ͻ���
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
	//��д����
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

