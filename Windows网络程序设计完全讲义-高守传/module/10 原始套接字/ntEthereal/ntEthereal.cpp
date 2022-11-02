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

//IPͷ��
typedef struct ip_hdr
{
    unsigned char  ip_header_len:4;  // IPv4ͷ�����ȣ�4λ����4�ֽ�Ϊ��λ����ͷ������
    unsigned char  ip_version   :4;  // IPv4�汾��4λ
    unsigned char  ip_tos;           // IP��������
    unsigned short ip_total_length;  // ���ݱ��ܳ���
    unsigned short ip_id;            // ��ʶ��16λ 
    
	unsigned char  ip_frag_offset   :5;// �ֶ�ƫ��
	
	unsigned char  ip_more_fragment :1;//���λ������ֶ�
	unsigned char  ip_dont_fragment :1;//���λ�����ֶ�
	unsigned char  ip_reserved_zero :1;//����λ
	
    unsigned char  ip_frag_offset1;    //�ֶ�ƫ��
	
	unsigned char  ip_ttl;           // TTL������ʱ��
    unsigned char  ip_protocol;      // �ϣ����䣩��Э������
    unsigned short ip_checksum;      // IPУ���
    unsigned int   ip_srcaddr;       //ԴIP��ַ
    unsigned int   ip_destaddr;      //Ŀ��IP��ַ
}   IPV4_HDR, *PIPV4_HDR;


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
}   TCP_HDR , *PTCP_HDR;

typedef struct udp_hdr
{
    unsigned short source_port;     //Դ�˿�
    unsigned short dest_port;       // Ŀ�Ķ˿�
    unsigned short udp_length;      //UDP������
    unsigned short udp_checksum;    //UDPУ��ͣ���ѡ��
}   UDP_HDR;

typedef struct icmp_hdr    
{
    BYTE type;          // ICMP��������
    BYTE code;          // �������
    USHORT checksum;	//У���
    USHORT id;			//���ಿ�֣���ͬ�Ĵ����в�ͬ������
    USHORT seq;
}   ICMP_HDR;


int ntcp=0,nudp=0,nicmp=0,nothers=0,nigmp=0,ntotal=0,i,j;
struct sockaddr_in source,dest;
char hex[2];

//Э��ͷ��ָ��
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

	//��ʼ��Winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2), &wsa) != 0)
	{
		printf("WSAStartup() failed.\n");
		return 1;
	}
    printf("Initialised");
		
	//����RAW Socket
	printf("\nCreating RAW Socket...");
	sniffer = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
    if (sniffer == INVALID_SOCKET)
	{
		printf("Failed to create raw socket.\n");
		return 1;
	}
    printf("Created.");
		
	//������
	if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR) 
	{
        printf("Error : %d",WSAGetLastError());
		return 1;
    }
	printf("\nHost name : %s \n",hostname);
	
	//��������IP
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
    //�󶨵�ַ
	printf("\nBinding socket to local system and port 0 ...");
	if (bind(sniffer,(struct sockaddr *)&dest,sizeof(dest)) == SOCKET_ERROR)
	{
		printf("bind(%s) failed.\n", inet_ntoa(addr));
		return 1;
	}
    printf("Binding successful"); 
		
	//������̽���ܣ�SIO_RCVALL����������IP���ݰ�
	j=1;
	printf("\nSetting socket to sniff...");
	if (WSAIoctl(sniffer, SIO_RCVALL, &j, sizeof(j), 
		0, 0, (unsigned long *)&in,0, 0) == SOCKET_ERROR)
	{
		int dwError;
		printf("WSAIoctl() failed.\n");

		dwError =WSAGetLastError();
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

		return 1;
	}
    printf("Socket set.");
	
	//��ʼ��̽
	printf("\nStarted Sniffing\n");
	printf("Packet Capture Statistics...\n");
	StartSniffing(sniffer);
	
	closesocket(sniffer);
	WSACleanup();

	return 0;
}

void StartSniffing(SOCKET sniffer)
{
	//����һ���ϴ�Ļ�������16λ���ܱ�ʾ�����ֵ
	unsigned char *Buffer = (unsigned char *)malloc(65536); 
	int  nResult;
	
	if (Buffer == NULL)
	{
		printf("malloc() failed.\n");
		return;
	}

	do
	{
		//���� 
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
	//���Э������
	switch (iphdr->ip_protocol) 
	{
		case 1:  //ICMPЭ��
			++nicmp;
			ProcessIcmpPacket(Buffer,Size);
			break;
		
		case 2:  //IGMPЭ��
			++nigmp;
			break;
		
		case 6:  //TCPЭ��
			++ntcp;
			ProcessTcpPacket(Buffer,Size);
			break;
		
		case 17: //UDPЭ��
			++nudp;
			ProcessUdpPacket(Buffer,Size);
			break;
		
		default: //����Э������
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
			//65��ʾA
			hex[k++]=65 + rem - 10;  
		}
		else if(rem<=9)	
		{
			//48��ʾ0
			hex[k++]=rem+48; 
		}
	}
	hex[k++]='\0';
	if(p==0)      strcpy((char *)hex,"00");
	else if(p<16) strcat((char *)hex,"0");
	_strrev((char *)hex);
}

