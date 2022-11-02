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


/* 4字节的mac地址 */
typedef struct _MAC_ADDRESS_{
    BYTE byte1;
    BYTE byte2;
    BYTE byte3;
    BYTE byte4;
	BYTE byte5;
    BYTE byte6;
}MACADDRESS;

/* 14字节的MAC头部 */
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
/* 回调函数原型 */
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
	char packet_filter[] = "ip";//过滤器:所有 ip数据包
	struct bpf_program fcode;


	// 检查程序输入参数
    if(argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return -1;
    }
	
	logfile=fopen("log.txt","w");
	if(logfile==NULL)
		printf("Unable to create file.");

    // 获得设备列表
    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
		printf("pcap_findalldevs(..) failed!\n");
		return 0;
	}
    
    // 打印列表
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
        // 释放设备列表
        pcap_freealldevs(alldevs);
        return -1;
    }

    //跳转到已选设备
    for(dev=alldevs, iDevIndex=0; iDevIndex< iInterfaceNum-1 ;dev=dev->next,iDevIndex++);
    
    // 打开适配器
    if ( (adhandle= pcap_open(dev->name,  // 设备名
                             65535,     // 要捕捉的数据包的部分 
                                        // 65535保证能捕获到不同
										//数据链路层上的每个数据包的全部内容
                             PCAP_OPENFLAG_PROMISCUOUS,         // 混杂模式
                             1000,      // 读取超时时间
                             NULL,      // 远程机器验证
                             errbuf     // 错误缓冲池
                             ) ) == NULL)
    {
        WriteLog(stderr,"\nUnable to open the adapter. %s is not supported by WinPcap\n");
        //释放设备列表
        pcap_freealldevs(alldevs);
        return -1;
    }
    
    // 检查数据链路层，为了简单，只考虑以太网 
    if(pcap_datalink(adhandle) != DLT_EN10MB)
    {
        WriteLog(stderr,"\nThis program works only on Ethernet networks.\n");
        //释放设备列表
        pcap_freealldevs(alldevs);
        return -1;
    }
    
    if(dev->addresses != NULL)
        //获得接口第一个地址的掩码
        netmask=((struct sockaddr_in *)(dev->addresses->netmask))->sin_addr.S_un.S_addr;
    else
        //如果接口没有地址，假设一个C类的掩码
        netmask=0xffffff; 


    //编译过滤器
    if (pcap_compile(adhandle, &fcode, packet_filter, 1, netmask) <0 )
    {
        WriteLog(stderr,"\nUnable to compile the packet filter. Check the syntax.\n");
        //释放设备列表
        pcap_freealldevs(alldevs);
        return -1;
    }
    
    //设置过滤器
    if (pcap_setfilter(adhandle, &fcode)<0)
    {
        WriteLog(stderr,"\nError setting the filter.\n");
        //释放设备列表
        pcap_freealldevs(alldevs);
        return -1;
    }
    
    printf("\nlistening on %s...\n", dev->description);
    
    //释放设备列表
    pcap_freealldevs(alldevs);
    
    // 打开堆文件
    dumpfile = pcap_dump_open(adhandle, argv[1]);	
    if(dumpfile==NULL)
    {
        fprintf(stderr,"\nError opening output file\n");
        return -1;
    }

	//开始捕捉
    pcap_loop(adhandle, 0, packet_handler, (unsigned char *)dumpfile);
//	pcap_dispatch(adhandle, 0, packet_handler, NULL); 
    
    return 0;
}

//回调函数，当收到每一个数据包时会被WinPcap/libpcap所调用
void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	//将数据包保存到堆文件，文件格式是
	//标准的WinPcap/libpcap的堆文件，可使用Ethereal等打开浏览
    pcap_dump(param, header, pkt_data);

	//分析实际的数据，包括协议头部以及数据部分
	WriteMacHeader((u_char *)pkt_data,0);
	//获得IP数据包头部的位置
	LPIPV4HDR iphdr0 = (IPV4HDR *)(pkt_data +sizeof(MACHDR));//以太网头部长度14
	
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
		
		default: //其他协议
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
	//最高三位标志位1110 0000 0000 0000
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

	//最低6位标志 0000 0000 0011 1111
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
		//每行显示16字节
		if( iTem!=0 && iTem%16==0)
		{
			WriteLog(logfile,"         ");
			for(jTem=iTem-16 ; jTem<iTem ; jTem++)
			{
				//空格的ASCII码值为32，~的ASCII码值为126
				if(data[jTem]>=32 && data[jTem]<=126)
					WriteLog(logfile,"%c",(u_char)data[jTem]); 
				//其他值显示为"."
				else WriteLog(logfile,"."); 
			}
			WriteLog(logfile,"\n");
		} 
		
		if(iTem%16==0)
			WriteLog(logfile,"   ");
		//以16进制显示数据		
		ConvertToHex(hex,(unsigned int)data[iTem]);
		WriteLog(logfile," %s",hex);
				
		if( iTem==pkt_size-1)  //打印最后的空格
		{
			for(jTem=0;jTem<15-iTem%16;jTem++)
				WriteLog(logfile,"   "); //额外的空格
			
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