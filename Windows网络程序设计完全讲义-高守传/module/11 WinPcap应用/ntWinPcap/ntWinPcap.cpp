// ntWinPcap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <winsock2.h>
#include <stdio.h>
#include  <mbstring.h>
#include "pcap.h"
#include "remote-ext.h"

#pragma comment(lib,"Ws2_32")
#pragma comment(lib,"Wpcap")

// *** Defines and Typedefs

#define LS_HI_PART(x)  ((x>>4) & 0x0F)
#define LS_LO_PART(x)  ((x) & 0x0F)

#define LS_MAX_PACKET_SIZE 65535

//protocol type
#define IP_ICMP 1 
#define IP_IGMP 2
#define IP_TCP 6
#define IP_UDP 17

#define WriteLog fprintf 

#ifndef SIO_RCVALL
#  define SIO_RCVALL    _WSAIOW(IOC_VENDOR,1)
#endif

typedef struct _IPV4_HDR_
{
	BYTE  ver_ihl;        // Version (4 bits) and Internet Header Length (4 bits)
	BYTE  type;           // Type of Service (8 bits)
	WORD  length;         // Total size of packet (header + data)(16 bits)
	WORD  packet_id;      // (16 bits)
	WORD  flags_foff;     // Flags (3 bits) and Fragment Offset (13 bits)
	BYTE  time_to_live;   // (8 bits)
	BYTE  protocol;       // (8 bits)
	WORD  hdr_chksum;     // Header check sum (16 bits)
	DWORD source_ip;      // Source Address (32 bits)
	DWORD dest_ip; // Destination Address (32 bits)
} IPV4HDR,*LPIPV4HDR;

typedef struct _TCP_HDR_
{
	WORD  source_port;       // (16 bits)
	WORD  dest_port;  // (16 bits)
	DWORD seq_number;        // Sequence Number (32 bits)
	DWORD ack_number;        // Acknowledgment Number (32 bits)
	WORD  info_ctrl;         // Data Offset (4 bits), Reserved (6 bits), Control bits (6 bits)
	WORD  window;            // (16 bits)
	WORD  checksum;          // (16 bits)
	WORD  urgent_pointer;    // (16 bits)
} TCPHDR,*LPTCPHDR;

typedef struct _ICMP_HDR_
{
	BYTE type;               // (8 bits)  
	BYTE code;               // (8 bits)  
	WORD checksum;           // (16 bits) 
	WORD id;
    WORD seq;
} ICMPHDR,*LPICMPHDR;

typedef struct _UDP_HDR_
{
    WORD source_port;     // Source port no.
    WORD dest_port;       // Dest. port no.
    WORD udp_length;      // Udp packet length
    WORD udp_checksum;    // Udp checksum (optional)
}UDPHDR,*LPUDPHDR;


/* 4�ֽڵ�mac��ַ */
typedef struct _MAC_ADDRESS_{
    BYTE byte1;
    BYTE byte2;
    BYTE byte3;
    BYTE byte4;
	BYTE byte5;
    BYTE byte6;
}MACADDRESS;

/* 14�ֽڵ�MACͷ�� */
typedef struct _MAC_HDR_{
    MACADDRESS dest;
	MACADDRESS sour;
	BYTE   type1;
	BYTE   type2;
}MACHDR,*LPMACHDR;

// *** Prototypes
////////////////////////////////////
void PacketIO   (u_char* , int);  
void WriteMacHeader  (u_char* , int); 
void WriteIpHeader   (u_char* , int);    
void WriteIcmpPacket (u_char* , int);
void WriteUdpPacket  (u_char* , int);
void WriteTcpPacket  (u_char* , int);
void ConvertToHex    (u_char* , unsigned int);
void WriteData       (u_char* , int);
/////////////////////////////////////////////
/* �ص�����ԭ�� */
void packet_handler(u_char *param, 
					const struct pcap_pkthdr *header,
					const u_char *pkt_data);

FILE *logfile;
int iTcp=0,iUdp=0,iIcmp=0,iOthers=0,iGgmp=0,iTotal=0,iTem,jTem;
struct sockaddr_in source,dest;
u_char hex[2];

LPIPV4HDR iphdr;
LPICMPHDR icmph;
LPMACHDR mach;
LPTCPHDR tcph;
LPUDPHDR udph;

int main(int argc, char* argv[])
{
	pcap_if_t *alldevs=NULL;
	pcap_if_t *dev=NULL;
	pcap_dumper_t *dumpfile=NULL;

	int iInterfaceNum=0;
	int iDevIndex=0;
	pcap_t *adhandle=NULL;
	char errbuf[PCAP_ERRBUF_SIZE];
	u_int netmask=0;
	char packet_filter[] = "ip";//������:���� ip���ݰ�
	struct bpf_program fcode;


	// �������������
    if(argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return -1;
    }
	
	logfile=fopen("log.txt","w");
	if(logfile==NULL)
		printf("Unable to create file.");

    // ����豸�б�
    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
		printf("pcap_findalldevs(..) failed!\n");
		return 0;
	}
    
    // ��ӡ�б�
    for(dev=alldevs; dev; dev=dev->next)
    {
        printf("%d. %s", ++iDevIndex, dev->name);
        if (dev->description)
            printf(" (%s)\n", dev->description);
        else
            printf(" (No description available)\n");
    }

    if(iDevIndex==0)
    {
        printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
        return -1;
    }
    
    printf("Enter the interface number (1-%d):",iDevIndex);
    scanf("%d", &iInterfaceNum);
    
    if(iInterfaceNum < 1 || iInterfaceNum >iDevIndex)
    {
        printf("\nInterface number out of range.\n");
        // �ͷ��豸�б�
        pcap_freealldevs(alldevs);
        return -1;
    }

    //��ת����ѡ�豸
    for(dev=alldevs, iDevIndex=0; iDevIndex< iInterfaceNum-1 ;dev=dev->next,iDevIndex++);
    
    // ��������
    if ( (adhandle= pcap_open(dev->name,  // �豸��
                             65535,     // Ҫ��׽�����ݰ��Ĳ��� 
                                        // 65535��֤�ܲ��񵽲�ͬ
										//������·���ϵ�ÿ�����ݰ���ȫ������
                             PCAP_OPENFLAG_PROMISCUOUS,         // ����ģʽ
                             1000,      // ��ȡ��ʱʱ��
                             NULL,      // Զ�̻�����֤
                             errbuf     // ���󻺳��
                             ) ) == NULL)
    {
        WriteLog(stderr,"\nUnable to open the adapter. %s is not supported by WinPcap\n");
        //�ͷ��豸�б�
        pcap_freealldevs(alldevs);
        return -1;
    }
    
    // ���������·�㣬Ϊ�˼򵥣�ֻ������̫�� 
    if(pcap_datalink(adhandle) != DLT_EN10MB)
    {
        WriteLog(stderr,"\nThis program works only on Ethernet networks.\n");
        //�ͷ��豸�б�
        pcap_freealldevs(alldevs);
        return -1;
    }
    
    if(dev->addresses != NULL)
        //��ýӿڵ�һ����ַ������
        netmask=((struct sockaddr_in *)(dev->addresses->netmask))->sin_addr.S_un.S_addr;
    else
        //����ӿ�û�е�ַ������һ��C�������
        netmask=0xffffff; 


    //���������
    if (pcap_compile(adhandle, &fcode, packet_filter, 1, netmask) <0 )
    {
        WriteLog(stderr,"\nUnable to compile the packet filter. Check the syntax.\n");
        //�ͷ��豸�б�
        pcap_freealldevs(alldevs);
        return -1;
    }
    
    //���ù�����
    if (pcap_setfilter(adhandle, &fcode)<0)
    {
        WriteLog(stderr,"\nError setting the filter.\n");
        //�ͷ��豸�б�
        pcap_freealldevs(alldevs);
        return -1;
    }
    
    printf("\nlistening on %s...\n", dev->description);
    
    //�ͷ��豸�б�
    pcap_freealldevs(alldevs);
    
    // �򿪶��ļ�
    dumpfile = pcap_dump_open(adhandle, argv[1]);	
    if(dumpfile==NULL)
    {
        fprintf(stderr,"\nError opening output file\n");
        return -1;
    }

	//��ʼ��׽
    pcap_loop(adhandle, 0, packet_handler, (unsigned char *)dumpfile);
//	pcap_dispatch(adhandle, 0, packet_handler, NULL); 
    
    return 0;
}

//�ص����������յ�ÿһ�����ݰ�ʱ�ᱻWinPcap/libpcap������
void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	//�����ݰ����浽���ļ����ļ���ʽ��
	//��׼��WinPcap/libpcap�Ķ��ļ�����ʹ��Ethereal�ȴ����
    pcap_dump(param, header, pkt_data);

	//����ʵ�ʵ����ݣ�����Э��ͷ���Լ����ݲ���
	WriteMacHeader((u_char *)pkt_data,0);
	//���IP���ݰ�ͷ����λ��
	LPIPV4HDR iphdr0 = (IPV4HDR *)(pkt_data +sizeof(MACHDR));//��̫��ͷ������14
	
	PacketIO((u_char *)iphdr0,ntohs(iphdr0->length));
	
}


void PacketIO(u_char* pkt_data, int pkt_size)
{
	iphdr = (IPV4HDR *)pkt_data;
	++iTotal;
	switch (iphdr->protocol)
	{
		case IP_ICMP:  //ICMP Protocol
			++iIcmp;
			WriteIcmpPacket(pkt_data,pkt_size);
			break;
		
		case IP_IGMP:  //IGMP Protocol
			++iGgmp;
			break;
		
		case IP_TCP:  //TCP Protocol
			++iTcp;
			WriteTcpPacket(pkt_data,pkt_size);
			break;
		
		case IP_UDP: //UDP Protocol
			++iUdp;
			WriteUdpPacket(pkt_data,pkt_size);
			break;
		
		default: //����Э��
			++iOthers;
			break;
	}
	printf("TCP :%d UDP : %d ICMP :%d IGMP :%d  Others :%d Total :%d\r",
		iTcp,iUdp,iIcmp,iGgmp,iOthers,iTotal);
}


void WriteMacHeader  (u_char* pkt_data, int pkt_size)
{
	MACHDR* machdr = (MACHDR *)pkt_data;
	WriteLog(logfile,"\n=========================MAC Header===========================\n");
	WriteLog(logfile,"   |-Dest MAC   :%X:%X:%X:%X:%X:%X\n",
		machdr->dest.byte1,machdr->dest.byte2,machdr->dest.byte3,
		machdr->dest.byte4,machdr->dest.byte5,machdr->dest.byte6);
	WriteLog(logfile,"   |-Source MAC :%X:%X:%X:%X:%X:%X\n",
		machdr->sour.byte1,machdr->sour.byte2,machdr->sour.byte3,
		machdr->sour.byte4,machdr->sour.byte5,machdr->sour.byte6);
	WriteLog(logfile,"   |-Type:%02d%02d",machdr->type1,machdr->type2);
}


void WriteIpHeader (u_char* pkt_data, int pkt_size)
{
	unsigned short iphdrlen;
		
	iphdr = (IPV4HDR *)pkt_data;
	iphdrlen = LS_LO_PART(iphdr->ver_ihl)*4;// size in 32 bits words
	
	memset(&source, 0, sizeof(source));
	source.sin_addr.s_addr = iphdr->source_ip;
	
	memset(&dest, 0, sizeof(dest));
	dest.sin_addr.s_addr = iphdr->dest_ip;
	
	WriteLog(logfile,"\n");
	WriteLog(logfile,"IP Header\n");
	WriteLog(logfile,"   |-IP Ver    : %d\n",(unsigned int)LS_HI_PART(iphdr->ver_ihl));
	WriteLog(logfile,"   |-IP Hdr Len: %d Bytes\n",(unsigned int)iphdrlen);
	WriteLog(logfile,"   |-TOS		 : %d\n",(unsigned int)iphdr->type);
	WriteLog(logfile,"   |-IP Total Len: %d  Bytes(Size of Packet)\n",ntohs(iphdr->length));
	//�����λ��־λ1110 0000 0000 0000
	BYTE flags = (ntohs(iphdr->flags_foff)>>8&0xE0);
	WriteLog(logfile,"   |-Res	ZERO : %d\n",(unsigned int)(flags & 0x80)>>7);
	WriteLog(logfile,"   |-Dont Frag : %d\n",(unsigned int)(flags & 0x40)>>6);
	WriteLog(logfile,"   |-More Frag : %d\n",(unsigned int)(flags & 0x20)>>5);
	
	WriteLog(logfile,"   |-Id	    : %d\n",ntohs(iphdr->packet_id));
	WriteLog(logfile,"   |-TTL      : %d\n",(unsigned int)iphdr->time_to_live);
	WriteLog(logfile,"   |-Protocol : %d\n",(unsigned int)iphdr->protocol);
	WriteLog(logfile,"   |-Checksum : %d\n",ntohs(iphdr->hdr_chksum));
	WriteLog(logfile,"   |-Source IP: %s\n",inet_ntoa(source.sin_addr));
	WriteLog(logfile,"   |-Dest IP  : %s\n",inet_ntoa(dest.sin_addr));
}

void WriteTcpPacket(u_char* pkt_data, int pkt_size)
{
	unsigned short iphdrlen;
	
	iphdr = (IPV4HDR *)pkt_data;
	iphdrlen = LS_LO_PART(iphdr->ver_ihl)*4;// size in 32 bits words
	
	tcph=(TCPHDR*)(pkt_data+iphdrlen);
			
	WriteLog(logfile,"\n\n======================TCP Packet==========================\n");	
		
	WriteIpHeader(pkt_data,pkt_size);
		
	WriteLog(logfile,"\n");
	WriteLog(logfile,"TCP Header\n");
	WriteLog(logfile,"   |-Source Port      : %u\n",ntohs(tcph->source_port));
	WriteLog(logfile,"   |-Dest Port : %u\n",ntohs(tcph->dest_port));
	WriteLog(logfile,"   |-Sequence Number : %u\n",ntohl(tcph->seq_number));
	WriteLog(logfile,"   |-Ack Number : %u\n",ntohl(tcph->ack_number));
	WriteLog(logfile,"   |-Hdr Len    : %d BYTES\n",
		(unsigned int)LS_LO_PART(tcph->info_ctrl)*4);

	//���6λ��־ 0000 0000 0011 1111
	BYTE flags = ( ntohs(tcph->info_ctrl) & 0x3F); 

	WriteLog(logfile,"   |-Urg Flag  : %d\n",(unsigned int)(flags & 0x20)>>5);
	WriteLog(logfile,"   |-Ack Flag  : %d\n",(unsigned int)(flags & 0x10)>>4);
	WriteLog(logfile,"   |-Push Flag : %d\n",(unsigned int)(flags & 0x08)>>3);
	WriteLog(logfile,"   |-Reset Flag: %d\n",(unsigned int)(flags & 0x04)>>2);
	WriteLog(logfile,"   |-Syn Flag  : %d\n",(unsigned int)(flags & 0x02)>>1);
	WriteLog(logfile,"   |-Fin Flag  : %d\n",(unsigned int)(flags & 0x01)>>0);
	WriteLog(logfile,"   |-Window    : %d\n",ntohs(tcph->window));
	WriteLog(logfile,"   |-Checksum  : %d\n",ntohs(tcph->checksum));
	WriteLog(logfile,"   |-Urg Pointer: %d\n",tcph->urgent_pointer);
	WriteLog(logfile,"\n");
	WriteLog(logfile,"                        DATA Dump                         ");
	WriteLog(logfile,"\n");
		
	WriteLog(logfile,"IP Header\n");
	WriteData(pkt_data,iphdrlen);
		
	WriteLog(logfile,"TCP Header\n");
	WriteData(pkt_data+iphdrlen,LS_LO_PART(tcph->info_ctrl)*4);
		
	WriteLog(logfile,"Data Payload\n");	
	WriteData(pkt_data+iphdrlen+LS_LO_PART(tcph->info_ctrl)*4
		,(pkt_size-LS_LO_PART(tcph->info_ctrl)*4-iphdrlen));
						
	WriteLog(logfile,"\n=======================================");
}

void WriteUdpPacket(u_char *pkt_data,int pkt_size)
{
	unsigned short iphdrlen;
		
	iphdr = (IPV4HDR *)pkt_data;
	iphdrlen = LS_LO_PART(iphdr->ver_ihl)*4;// size in 32 bits words
	
	udph= (UDPHDR *)(pkt_data + iphdrlen);
	
	WriteLog(logfile,"\n\n====================UDP Packet=============================\n");
	
	WriteIpHeader(pkt_data,pkt_size);			
	
	WriteLog(logfile,"\nUDP Header\n");
	WriteLog(logfile,"   |-Source Port : %d\n",ntohs(udph->source_port));
	WriteLog(logfile,"   |-Dest Port   : %d\n",ntohs(udph->dest_port));
	WriteLog(logfile,"   |-UDP Len     : %d\n",ntohs(udph->udp_length));
	WriteLog(logfile,"   |-UDP Checksum: %d\n",ntohs(udph->udp_checksum));
	
	WriteLog(logfile,"\n");
	WriteLog(logfile,"IP Header\n");
	WriteData(pkt_data,iphdrlen);
		
	WriteLog(logfile,"UDP Header\n");
	WriteData(pkt_data+iphdrlen,sizeof(UDPHDR));
		
	WriteLog(logfile,"Data Payload\n");	
	WriteData(pkt_data+iphdrlen+sizeof(UDPHDR)
		,(pkt_size - sizeof(UDPHDR) - iphdrlen));
	
	WriteLog(logfile,"\n==========================================");
}

void WriteIcmpPacket(u_char* pkt_data , int pkt_size)
{
	unsigned short iphdrlen;
		
	iphdr = (IPV4HDR *)pkt_data;
	iphdrlen = LS_LO_PART(iphdr->ver_ihl)*4;// size in 32 bits words
	
	icmph=(ICMPHDR*)(pkt_data+iphdrlen);
		
	WriteLog(logfile,"\n\n=========================ICMP Packet============================\n");	
	WriteIpHeader(pkt_data,pkt_size);
			
	WriteLog(logfile,"\n");
		
	WriteLog(logfile,"ICMP Header\n");
	WriteLog(logfile,"   |-Type : %d",(unsigned int)(icmph->type));
			
	if((unsigned int)(icmph->type)==11)	
		WriteLog(logfile,"  (TTL Expired)\n");
	else if((unsigned int)(icmph->type)==0)
		WriteLog(logfile,"  (ICMP Echo Reply)\n");
	else if((unsigned int)(icmph->type)==8)
		WriteLog(logfile,"  (ICMP Echo Request)\n");
			
	
	WriteLog(logfile,"   |-Code		: %d\n",(unsigned int)(icmph->code));
	WriteLog(logfile,"   |-Checksum : %d\n",ntohs(icmph->checksum));
	WriteLog(logfile,"   |-ID       : %d\n",ntohs(icmph->id));
	WriteLog(logfile,"   |-Sequence : %d\n",ntohs(icmph->seq));
	WriteLog(logfile,"\n");

	WriteLog(logfile,"IP Header\n");
	WriteData(pkt_data,iphdrlen);
		
	WriteLog(logfile,"UDP Header\n");
	WriteData(pkt_data+iphdrlen,sizeof(ICMPHDR));
		
	WriteLog(logfile,"Data Payload\n");	
	WriteData(pkt_data+iphdrlen+sizeof(ICMPHDR)
		,(pkt_size - sizeof(ICMPHDR) - iphdrlen));
	
	WriteLog(logfile,"\n======================================================");
}

void WriteData (u_char* data , int pkt_size)
{
	
	for(iTem=0 ; iTem < pkt_size ; iTem++)
	{
		//ÿ����ʾ16�ֽ�
		if( iTem!=0 && iTem%16==0)
		{
			WriteLog(logfile,"         ");
			for(jTem=iTem-16 ; jTem<iTem ; jTem++)
			{
				//�ո��ASCII��ֵΪ32��~��ASCII��ֵΪ126
				if(data[jTem]>=32 && data[jTem]<=126)
					WriteLog(logfile,"%c",(u_char)data[jTem]); 
				//����ֵ��ʾΪ"."
				else WriteLog(logfile,"."); 
			}
			WriteLog(logfile,"\n");
		} 
		
		if(iTem%16==0)
			WriteLog(logfile,"   ");
		//��16������ʾ����		
		ConvertToHex(hex,(unsigned int)data[iTem]);
		WriteLog(logfile," %s",hex);
				
		if( iTem==pkt_size-1)  //��ӡ���Ŀո�
		{
			for(jTem=0;jTem<15-iTem%16;jTem++)
				WriteLog(logfile,"   "); //����Ŀո�
			
			WriteLog(logfile,"         ");
			
			for(jTem=iTem-iTem%16 ; jTem<=iTem ; jTem++)
			{
				if(data[jTem]>=32 && data[jTem]<=128)
					WriteLog(logfile,"%c",(u_char)data[jTem]);
				else WriteLog(logfile,".");
			}
			WriteLog(logfile,"\n");
		}
	}
}


void ConvertToHex(u_char *hex , unsigned int decimal)
{
	int rem,k=0,p;
	p=decimal;
	while(decimal!=0)
	{
		rem=decimal%16;
		decimal=decimal/16;
		if(rem>=10)
			hex[k++]=65 + rem - 10;  //65 means A
		else if(rem<=9)
			hex[k++]=rem+48;     //48 means 0
	}
	
	hex[k++]='\0';
	if(p==0)
		_mbscpy(hex,(const u_char *)"00");
	else if(p<16) 
		_mbscat(hex,(const u_char *)"0");
	*_mbsrev(hex);
}