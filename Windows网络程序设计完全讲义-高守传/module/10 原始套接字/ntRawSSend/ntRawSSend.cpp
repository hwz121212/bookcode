// ntRawSSend.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "winsock2.h"
#include "ws2tcpip.h" 
#include <stdlib.h>

//winsock 2.2 library
#pragma comment(lib,"ws2_32.lib")  


//IP头部
typedef struct ip_hdr
{
    unsigned char  ip_header_len:4;  // IPv4头部长度，4位，以4字节为单位定义头部长度
    unsigned char  ip_version   :4;  // IPv4版本，4位
    unsigned char  ip_tos;           // IP服务类型
    unsigned short ip_total_length;  // 数据报总长度
    unsigned short ip_id;            // 标识，16位 
    
	unsigned char  ip_frag_offset   :5;        // 分段偏移
	
	unsigned char  ip_more_fragment :1;//标记位，更多分段
	unsigned char  ip_dont_fragment :1;//标记位，不分段
	unsigned char  ip_reserved_zero :1;//保留位
	
    unsigned char  ip_frag_offset1;    //分段偏移
	
	unsigned char  ip_ttl;           // TTL，生存时间
    unsigned char  ip_protocol;      // 上（传输）层协议类型
    unsigned short ip_checksum;      // IP校验和
    unsigned int   ip_srcaddr;       //源IP地址
    unsigned int   ip_destaddr;      //目的IP地址
}IPV4_HDR, *PIPV4_HDR;


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
}TCP_HDR , *PTCP_HDR;


#define PAYLOAD 60

int main(int argc, char* argv[])
{
	char host[100],buf_packet[1000],*data=NULL,source_ip[20]; 
	SOCKET s;
	int nSent=0,nTotalPacket=0;
	
	IPV4_HDR *v4hdr=NULL;
	TCP_HDR  *tcphdr=NULL;
	
	int optval;
	SOCKADDR_IN dest;
	hostent *server;
	if(argc!=2)
	{
		printf("Please input number of Packets to send.\n");

		return 0;
	}
	nTotalPacket=atoi(argv[1]);
	//初始化Winsock
	WSADATA wsock;
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsock) != 0)
	{
		fprintf(stderr,"WSAStartup() failed");
        exit(EXIT_FAILURE); 
	} 
	printf("Initialised successfully.");
		
	//创建Raw Socket
	printf("\nCreating Raw TCP Socket...");
	if((s = socket(AF_INET, SOCK_RAW, IPPROTO_RAW))==SOCKET_ERROR)
	{
		printf("Creation of raw socket failed.");
		return 0;
	}
	printf("Raw TCP Socket Created successfully.");
		
	//设置头包含项，以便控制IPv4头部
	printf("\nSetting the socket in RAW mode...");
	if(setsockopt(s, IPPROTO_IP, IP_HDRINCL, (char *)&optval, sizeof(optval))==SOCKET_ERROR)
	{
		printf("failed to set socket in raw mode.");
		return 0;
	}
	printf("Successful.");
		
	//目标主机
	printf("\nEnter hostname : ");
	gets_s(host);
	printf("\nResolving Hostname...");
	if((server=gethostbyname(host))==0)
	{
		printf("Unable to resolve.");
		return 0;
	}
	dest.sin_family = AF_INET;
	//设置目标端口，注意是网络字节顺序
	dest.sin_port   = htons(80);
	memcpy(&dest.sin_addr.s_addr,server->h_addr,server->h_length);
	printf("Resolved.");
	
	//设置源IP地址
	printf("\nEnter Source IP : ");
	gets_s(source_ip);
	printf("The source IP is:%s.",source_ip);

	//先设置IP头部
	v4hdr = (IPV4_HDR *)buf_packet; 
	v4hdr->ip_version=4;
	v4hdr->ip_header_len=5;
	v4hdr->ip_tos    = 0;
	//注意是网络字节顺序
	v4hdr->ip_total_length = htons ( sizeof(IPV4_HDR) + sizeof(TCP_HDR) + PAYLOAD );
	v4hdr->ip_id     = htons(2);
	v4hdr->ip_frag_offset = 0;
	v4hdr->ip_frag_offset1 = 0;
	v4hdr->ip_reserved_zero = 0;
	v4hdr->ip_dont_fragment = 1;
	v4hdr->ip_more_fragment = 0;
	v4hdr->ip_ttl    = 8;
	//设置协议类型
	v4hdr->ip_protocol = IPPROTO_TCP;
	v4hdr->ip_srcaddr  = inet_addr(source_ip);
	v4hdr->ip_destaddr = inet_addr(inet_ntoa(dest.sin_addr));
	v4hdr->ip_checksum = 0;

	//获取并设置TCP头部
	tcphdr = (TCP_HDR *)&buf_packet[sizeof(IPV4_HDR)]; 
	
	tcphdr->source_port = htons(1234);
	tcphdr->dest_port = htons(80);
	tcphdr->cwr=0;
	tcphdr->ecn=1;
	tcphdr->urg=0;
	tcphdr->ack=0;
	tcphdr->psh=0;
	tcphdr->rst=1;
	tcphdr->syn=0;
	tcphdr->fin=0;
	tcphdr->ns=1;
	//校验和让协议栈完成
	tcphdr->checksum = 0;
         
	
	//数据部分设置
	data = &buf_packet[sizeof(IPV4_HDR) + sizeof(TCP_HDR)];
	memset(data, 'A', PAYLOAD);

	
	printf("\nSending packet...\n");
	
	for(nSent=0;nSent<nTotalPacket;nSent++)
	{
		if((sendto(s , buf_packet , sizeof(IPV4_HDR)+sizeof(TCP_HDR) + PAYLOAD, 0,
			(SOCKADDR *)&dest, sizeof(dest)))==SOCKET_ERROR)
		{
			
			DWORD dwError =WSAGetLastError();
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
			
			break;
		}
		
		printf("  %d  packets sent\r",nSent);
	}

	printf("The %d of packets have been sent successfully!\r",nSent);

	return 0;
}

