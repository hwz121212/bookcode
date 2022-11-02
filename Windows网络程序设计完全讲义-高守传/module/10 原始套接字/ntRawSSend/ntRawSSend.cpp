// ntRawSSend.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "winsock2.h"
#include "ws2tcpip.h" 
#include <stdlib.h>

//winsock 2.2 library
#pragma comment(lib,"ws2_32.lib")  


//IPͷ��
typedef struct ip_hdr
{
    unsigned char  ip_header_len:4;  // IPv4ͷ�����ȣ�4λ����4�ֽ�Ϊ��λ����ͷ������
    unsigned char  ip_version   :4;  // IPv4�汾��4λ
    unsigned char  ip_tos;           // IP��������
    unsigned short ip_total_length;  // ���ݱ��ܳ���
    unsigned short ip_id;            // ��ʶ��16λ 
    
	unsigned char  ip_frag_offset   :5;        // �ֶ�ƫ��
	
	unsigned char  ip_more_fragment :1;//���λ������ֶ�
	unsigned char  ip_dont_fragment :1;//���λ�����ֶ�
	unsigned char  ip_reserved_zero :1;//����λ
	
    unsigned char  ip_frag_offset1;    //�ֶ�ƫ��
	
	unsigned char  ip_ttl;           // TTL������ʱ��
    unsigned char  ip_protocol;      // �ϣ����䣩��Э������
    unsigned short ip_checksum;      // IPУ���
    unsigned int   ip_srcaddr;       //ԴIP��ַ
    unsigned int   ip_destaddr;      //Ŀ��IP��ַ
}IPV4_HDR, *PIPV4_HDR;


// TCP header
typedef struct tcp_header 
{ 
	unsigned short source_port;  // Դ�˿� 
	unsigned short dest_port;    // Ŀ�Ķ˿� 
	unsigned int   sequence;     // ���к�32λ 
	unsigned int   acknowledge;  //��Ӧ���к�32λ 
	
	unsigned char  ns   :1;          //�μ�RFC 3540.
	unsigned char  reserved_part1:3; //�μ�rfc
	unsigned char  data_offset:4;    //����ƫ�ƣ�TCPͷ����������4�ֽڵı��� 
																			 
	unsigned char  fin  :1;      //��ֹ���ӱ�־
	unsigned char  syn  :1;      //ͬ�����кű�־
	unsigned char  rst  :1;      //���Ӹ�λ��־
	unsigned char  psh  :1;      //���������־ 
	unsigned char  ack  :1;      //ȷ����Ч��־ 
	unsigned char  urg  :1;      //����ָ���־
									 
	unsigned char  ecn  :1;      //ECN-Echo��־
	unsigned char  cwr  :1;      //����ӵ�����ڱ�־
									 
	unsigned short window;  // ���ڴ�С 
	unsigned short checksum;  // У��� 
	unsigned short urgent_pointer;  //����ָ�� 
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
	//��ʼ��Winsock
	WSADATA wsock;
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsock) != 0)
	{
		fprintf(stderr,"WSAStartup() failed");
        exit(EXIT_FAILURE); 
	} 
	printf("Initialised successfully.");
		
	//����Raw Socket
	printf("\nCreating Raw TCP Socket...");
	if((s = socket(AF_INET, SOCK_RAW, IPPROTO_RAW))==SOCKET_ERROR)
	{
		printf("Creation of raw socket failed.");
		return 0;
	}
	printf("Raw TCP Socket Created successfully.");
		
	//����ͷ������Ա����IPv4ͷ��
	printf("\nSetting the socket in RAW mode...");
	if(setsockopt(s, IPPROTO_IP, IP_HDRINCL, (char *)&optval, sizeof(optval))==SOCKET_ERROR)
	{
		printf("failed to set socket in raw mode.");
		return 0;
	}
	printf("Successful.");
		
	//Ŀ������
	printf("\nEnter hostname : ");
	gets_s(host);
	printf("\nResolving Hostname...");
	if((server=gethostbyname(host))==0)
	{
		printf("Unable to resolve.");
		return 0;
	}
	dest.sin_family = AF_INET;
	//����Ŀ��˿ڣ�ע���������ֽ�˳��
	dest.sin_port   = htons(80);
	memcpy(&dest.sin_addr.s_addr,server->h_addr,server->h_length);
	printf("Resolved.");
	
	//����ԴIP��ַ
	printf("\nEnter Source IP : ");
	gets_s(source_ip);
	printf("The source IP is:%s.",source_ip);

	//������IPͷ��
	v4hdr = (IPV4_HDR *)buf_packet; 
	v4hdr->ip_version=4;
	v4hdr->ip_header_len=5;
	v4hdr->ip_tos    = 0;
	//ע���������ֽ�˳��
	v4hdr->ip_total_length = htons ( sizeof(IPV4_HDR) + sizeof(TCP_HDR) + PAYLOAD );
	v4hdr->ip_id     = htons(2);
	v4hdr->ip_frag_offset = 0;
	v4hdr->ip_frag_offset1 = 0;
	v4hdr->ip_reserved_zero = 0;
	v4hdr->ip_dont_fragment = 1;
	v4hdr->ip_more_fragment = 0;
	v4hdr->ip_ttl    = 8;
	//����Э������
	v4hdr->ip_protocol = IPPROTO_TCP;
	v4hdr->ip_srcaddr  = inet_addr(source_ip);
	v4hdr->ip_destaddr = inet_addr(inet_ntoa(dest.sin_addr));
	v4hdr->ip_checksum = 0;

	//��ȡ������TCPͷ��
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
	//У�����Э��ջ���
	tcphdr->checksum = 0;
         
	
	//���ݲ�������
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
			//ָ�����ڽ��մ�����Ϣ�Ļ�����
			HLOCAL hlocal = NULL;
			//����������������
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

