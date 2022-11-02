// ntEthereal.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <windows.h>
#include  <stdlib.h>      
#include <winsock2.h>
#include <mstcpip.h>


//winsock 2.2 library
#pragma comment(lib,"ws2_32.lib")

void StartSniffing   (SOCKET Sock);             //This will sniff here and there
void PacketProcess   (unsigned char* , int);    //This will decide how to digest
void ProcessIpHeader   (unsigned char* , int);    
void ProcessIcmpPacket (unsigned char* , int);
void ProcessUdpPacket  (unsigned char* , int);
void ProcessTcpPacket  (unsigned char* , int);
void ConvertToHex    (unsigned char* , unsigned int);

//IP头部
typedef struct ip_hdr
{
    unsigned char  ip_header_len:4;  // IPv4头部长度，4位，以4字节为单位定义头部长度
    unsigned char  ip_version   :4;  // IPv4版本，4位
    unsigned char  ip_tos;           // IP服务类型
    unsigned short ip_total_length;  // 数据报总长度
    unsigned short ip_id;            // 标识，16位 
    
	unsigned char  ip_frag_offset   :5;// 分段偏移
	
	unsigned char  ip_more_fragment :1;//标记位，更多分段
	unsigned char  ip_dont_fragment :1;//标记位，不分段
	unsigned char  ip_reserved_zero :1;//保留位
	
    unsigned char  ip_frag_offset1;    //分段偏移
	
	unsigned char  ip_ttl;           // TTL，生存时间
    unsigned char  ip_protocol;      // 上（传输）层协议类型
    unsigned short ip_checksum;      // IP校验和
    unsigned int   ip_srcaddr;       //源IP地址
    unsigned int   ip_destaddr;      //目的IP地址
}   IPV4_HDR, *PIPV4_HDR;


// TCP header
typedef struct tcp_header 
{ 
	unsigned short source_port;  // 源端口 
	unsigned short dest_port;    // 目的端口 
	unsigned int   sequence;     // 序列号32位 
	unsigned int   acknowledge;  //响应序列号32位 
	
	unsigned char  ns   :1;          //参见RFC 3540.
	unsigned char  reserved_part1:3; //参见rfc
	unsigned char  data_offset:4;    //数据偏移，TCP头部长度总是4字节的倍数 
	
	unsigned char  fin  :1;      //终止连接标志
	unsigned char  syn  :1;      //同步序列号标志
	unsigned char  rst  :1;      //连接复位标志
	unsigned char  psh  :1;      //请求紧急标志 
	unsigned char  ack  :1;      //确认有效标志 
	unsigned char  urg  :1;      //紧急指针标志
	
	unsigned char  ecn  :1;      //ECN-Echo标志
	unsigned char  cwr  :1;      //紧缩拥塞窗口标志
	
	unsigned short window;  // 窗口大小 
	unsigned short checksum;  // 校验和 
	unsigned short urgent_pointer;  //紧急指针 
}   TCP_HDR , *PTCP_HDR;

typedef struct udp_hdr
{
    unsigned short source_port;     //源端口
    unsigned short dest_port;       // 目的端口
    unsigned short udp_length;      //UDP包长度
    unsigned short udp_checksum;    //UDP校验和（可选）
}   UDP_HDR;

typedef struct icmp_hdr    
{
    BYTE type;          // ICMP错误类型
    BYTE code;          // 错误代码
    USHORT checksum;	//校验和
    USHORT id;			//其余部分，不同的错误有不同的内容
    USHORT seq;
}   ICMP_HDR;


int ntcp=0,nudp=0,nicmp=0,nothers=0,nigmp=0,ntotal=0,i,j;
struct sockaddr_in source,dest;
char hex[2];

//协议头部指针
IPV4_HDR *iphdr;
TCP_HDR  *tcpheader;
UDP_HDR  *udpheader;
ICMP_HDR *icmpheader;

int main(int argc, char* argv[])
{
	SOCKET sniffer;
	struct in_addr addr;
	int in;	
	
	char hostname[100];
	struct hostent *local;
	WSADATA wsa;	

	//初始化Winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2), &wsa) != 0)
	{
		printf("WSAStartup() failed.\n");
		return 1;
	}
    printf("Initialised");
		
	//创建RAW Socket
	printf("\nCreating RAW Socket...");
	sniffer = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
    if (sniffer == INVALID_SOCKET)
	{
		printf("Failed to create raw socket.\n");
		return 1;
	}
    printf("Created.");
		
	//本机名
	if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR) 
	{
        printf("Error : %d",WSAGetLastError());
		return 1;
    }
	printf("\nHost name : %s \n",hostname);
	
	//本机可用IP
	local = gethostbyname(hostname);
    printf("\nAvailable Network Interfaces : \n");
	if (local == NULL) 
	{
        printf("Error : %d.\n",WSAGetLastError());
        return 1;
    }

    for (i = 0; local->h_addr_list[i] != 0; ++i) 
	{
		memcpy(&addr, local->h_addr_list[i], sizeof(struct in_addr));
        printf("Interface Number : %d Address : %s\n",i,inet_ntoa(addr));
    }

	printf("Enter the interface number you would like to sniff : ");
	scanf("%d",&in);
	
	memset(&dest, 0, sizeof(dest));
	memcpy(&dest.sin_addr.s_addr,local->h_addr_list[in],sizeof(dest.sin_addr.s_addr));
	dest.sin_family      = AF_INET;
	dest.sin_port        = 0;
    //绑定地址
	printf("\nBinding socket to local system and port 0 ...");
	if (bind(sniffer,(struct sockaddr *)&dest,sizeof(dest)) == SOCKET_ERROR)
	{
		printf("bind(%s) failed.\n", inet_ntoa(addr));
		return 1;
	}
    printf("Binding successful"); 
		
	//开启嗅探功能，SIO_RCVALL将接收所有IP数据包
	j=1;
	printf("\nSetting socket to sniff...");
	if (WSAIoctl(sniffer, SIO_RCVALL, &j, sizeof(j), 
		0, 0, (unsigned long *)&in,0, 0) == SOCKET_ERROR)
	{
		int dwError;
		printf("WSAIoctl() failed.\n");

		dwError =WSAGetLastError();
		printf("Error sending Packet : %d\n",dwError);
		//指向用于接收错误信息的缓冲区
		HLOCAL hlocal = NULL;
		//错误代码的文字描述
		BOOL fOk = FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, 
			NULL, dwError, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), (PTSTR) &hlocal, 0, NULL);
		if (hlocal != NULL)
		{
			printf ("Error Reason: %s\n",(PCSTR) LocalLock(hlocal));
			LocalFree(hlocal);
		}

		return 1;
	}
    printf("Socket set.");
	
	//开始嗅探
	printf("\nStarted Sniffing\n");
	printf("Packet Capture Statistics...\n");
	StartSniffing(sniffer);
	
	closesocket(sniffer);
	WSACleanup();

	return 0;
}

void StartSniffing(SOCKET sniffer)
{
	//分配一个较大的缓冲区，16位所能表示的最大值
	unsigned char *Buffer = (unsigned char *)malloc(65536); 
	int  nResult;
	
	if (Buffer == NULL)
	{
		printf("malloc() failed.\n");
		return;
	}

	do
	{
		//接收 
		nResult = recv(sniffer,(char *)Buffer,65536,0); 
		if(nResult > 0)
			PacketProcess(Buffer, nResult);
		else 
			printf( "recvfrom() failed.\n");
	} 
	while (nResult > 0);

	free(Buffer);
}

void PacketProcess(unsigned char* Buffer, int Size)
{
	iphdr = (IPV4_HDR *)Buffer;
	++ntotal;
	//检测协议类型
	switch (iphdr->ip_protocol) 
	{
		case 1:  //ICMP协议
			++nicmp;
			ProcessIcmpPacket(Buffer,Size);
			break;
		
		case 2:  //IGMP协议
			++nigmp;
			break;
		
		case 6:  //TCP协议
			++ntcp;
			ProcessTcpPacket(Buffer,Size);
			break;
		
		case 17: //UDP协议
			++nudp;
			ProcessUdpPacket(Buffer,Size);
			break;
		
		default: //其他协议类型
			++nothers;
			break;
	}
	printf("TCP : %d   UDP : %d   ICMP : %d   IGMP : %d   Others : %d   Total : %d\r",
		ntcp,nudp,nicmp,nigmp,nothers,ntotal);
}


void ProcessIpHeader (unsigned char* Buffer, int Size)
{
	unsigned short iphdrlen;
		
	iphdr = (IPV4_HDR *)Buffer;
	iphdrlen = iphdr->ip_header_len*4;
	
	memset(&source, 0, sizeof(source));
	source.sin_addr.s_addr = iphdr->ip_srcaddr;
	
	memset(&dest, 0, sizeof(dest));
	dest.sin_addr.s_addr = iphdr->ip_destaddr;
}

void ProcessTcpPacket(unsigned char* Buffer, int Size)
{
	unsigned short iphdrlen;
	
	iphdr = (IPV4_HDR *)Buffer;
	iphdrlen = iphdr->ip_header_len*4;
	
	tcpheader=(TCP_HDR*)(Buffer+iphdrlen);
}

void ProcessUdpPacket(unsigned char *Buffer,int Size)
{
	unsigned short iphdrlen;
		
	iphdr = (IPV4_HDR *)Buffer;
	iphdrlen = iphdr->ip_header_len*4;
	
	udpheader = (UDP_HDR *)(Buffer + iphdrlen);
	
}

void ProcessIcmpPacket(unsigned char* Buffer , int Size)
{
	unsigned short iphdrlen;
		
	iphdr = (IPV4_HDR *)Buffer;
	iphdrlen = iphdr->ip_header_len*4;
	
	icmpheader=(ICMP_HDR*)(Buffer+iphdrlen);
}

void ConvertToHex(unsigned char *hex , unsigned int decimal)
{
	int rem,k=0,p;
	p=decimal;
	while(decimal!=0)
	{
		rem=decimal%16;
		decimal=decimal/16;
		if(rem>=10)
		{
			//65表示A
			hex[k++]=65 + rem - 10;  
		}
		else if(rem<=9)	
		{
			//48表示0
			hex[k++]=rem+48; 
		}
	}
	hex[k++]='\0';
	if(p==0)      strcpy((char *)hex,"00");
	else if(p<16) strcat((char *)hex,"0");
	_strrev((char *)hex);
}

