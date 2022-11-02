// ntPing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <winsock2.h>
#include <windows.h>



//winsock 2.2 library
#pragma comment(lib,"ws2_32.lib")

struct icmp_hdr
{
	unsigned char	icmp_type;
	unsigned char	icmp_code;
	unsigned short	icmp_checksum;
	unsigned short	icmp_id;
	unsigned short	icmp_sequence;
};

struct ip_hdr
{
    unsigned char	ip_verlen;        
    unsigned char	ip_tos;       
    unsigned short	ip_total_length;   
    unsigned short	ip_id;            
    unsigned short	ip_frag_offset1;        
    unsigned char	ip_ttl;          
    unsigned char	ip_protocol;     
    unsigned short	ip_checkksum;      
    unsigned int	ip_srcaddr;       
    unsigned int	ip_destaddr;      
};

unsigned short CalcChecksum (char *pBuffer, int nLen);
bool ValidateChecksum (char *pBuffer, int nLen);
bool Initialize ();
bool UnInitialize ();
bool ResolveIP (char *pszRemoteHost, char **pszIPAddress);
void Usage ();

int main(int argc, char* argv[])
{
	
	Usage();

	if (Initialize () == false)
	{
		return -1;
	}

	int icmp_sequence = 0;
	//ȱʡ��������
	int nMessageSize = 32;	//ICMP���������Ĵ�С
	int nTimeOut = 1000;//����ʱ
	int nCount = 4;	//�������

	char *pszRemoteIP = NULL, *pSendBuffer = NULL, *pszRemoteHost = NULL;

	//����ָ����������һ������Ϊ����
	pszRemoteHost = argv [1];
	
	for (int i = 2; i < argc; ++i)
	{
		switch (i)
		{
		case 2:			
			nCount = atoi (argv [2]);
			break;
		case 3:
			nMessageSize = atoi (argv [3]);
			break;
		case 4:
			nTimeOut = atoi (argv [4]);
			break;
		}
	}

	//����Զ������IP
	//����ָ��pszRemoteHost�����������gethostname
	if (ResolveIP (pszRemoteHost, &pszRemoteIP) == false)
	{
		printf("Unable to resolve hostname");
		return -1;
	}

	printf("Pinging %s [%s] with %d bytes of data.\n\n",pszRemoteHost,pszRemoteIP,nMessageSize);
	icmp_hdr sendHdr;

	//����ԭʼ�׽���ICMP
	SOCKET sock;
	sock = socket (AF_INET, SOCK_RAW, IPPROTO_ICMP);	

	//Ŀ�ĵ�ַ
	SOCKADDR_IN dest;	
	dest.sin_addr.S_un.S_addr = inet_addr (pszRemoteIP);
	dest.sin_family = AF_INET;
	//�趨����˿�
	dest.sin_port = rand ();	

	int nResult = 0;

	fd_set fdRead;
	//��������
	SYSTEMTIME timeSend, timeRecv;
	int nTotalRoundTripTime = 0, nMaxRoundTripTime = 0, 
		nMinRoundTripTime = -1, nRoundTripTime = 0;
	int nPacketsSent = 0, nPacketsReceived = 0;

	timeval timeInterval = {0, 0};
	timeInterval.tv_usec = nTimeOut * 1000;
	
	//���ICMPͷ��
	sendHdr.icmp_id = htons (rand ());

	while (nPacketsSent < nCount)
	{
		//���䱨�Ļ������������ɱ���ͷ�ṹ�ͱ��ı���
		pSendBuffer = new char [sizeof (icmp_hdr) + nMessageSize];

		//����ICMP���Ժ�Ӧ���ģ�codeΪ0
		sendHdr.icmp_code = 0;	
		//���к�
		sendHdr.icmp_sequence = htons (icmp_sequence++);
		//ICMP���Ա�������Ϊ8
		sendHdr.icmp_type = 8;
		//�Ժ������У���
		sendHdr.icmp_checksum = 0;	

		//׼������
		memcpy (pSendBuffer, &sendHdr, sizeof (icmp_hdr));
		//�����������ַ����
		memset (pSendBuffer + sizeof (icmp_hdr), 'A', nMessageSize);

		//У��ͼ��㣺ICMPͷ���ͱ����壬����У���ת��Ϊ����˳��
		sendHdr.icmp_checksum = htons (CalcChecksum (pSendBuffer, 
			sizeof (icmp_hdr) + nMessageSize));	

		//��ICMPͷ�����ƻط��ͻ�������ע�⣬����ǰ�����ȷУ��͵�ͷ��
		memcpy (pSendBuffer, &sendHdr, sizeof (icmp_hdr));
		//���ͻ�������
		nResult = sendto (sock, pSendBuffer, sizeof (icmp_hdr) + nMessageSize,
			0, (SOCKADDR *)&dest, sizeof (SOCKADDR_IN));
		
		//��¼���ͻ��������ʱ�䣬�Ա��������ʱ��
		GetSystemTime (&timeSend);

		++nPacketsSent;

		if (nResult == SOCKET_ERROR)
		{
			printf("An error occured in sendto operation: %d" , WSAGetLastError());
			UnInitialize ();
			delete []pSendBuffer;
			return -1;
		}
		//ʹ��selectģ�����ж�Ӧ���ʱ����
		FD_ZERO (&fdRead);
		FD_SET (sock, &fdRead);

		if ((nResult = select (0, &fdRead, NULL, NULL, &timeInterval))
			== SOCKET_ERROR)
		{
			printf("An error occured in select operation: %d" ,WSAGetLastError ());
			delete []pSendBuffer;
			return -1;
		}

		//����������������Ӧ����
		if (nResult > 0 && FD_ISSET (sock, &fdRead))
		{
			//���仺�����Ա�洢Ӧ����Ϣ
			char *pRecvBuffer = new char [1500];
			//����Ӧ����Ϣ
			if ((nResult = recvfrom (sock, pRecvBuffer, 1500, 0, 0, 0)) 
				== SOCKET_ERROR)
			{
				printf("An error occured in recvfrom operation:%d",WSAGetLastError());
				UnInitialize ();
				delete []pSendBuffer;
				delete []pRecvBuffer;
				return -1;
			}
			
			//������յ�Ӧ���ʱ��
			GetSystemTime (&timeRecv);

			//ԭʼ�׽��ֽ��յ����ǰ���IPͷ�����ڵ��������ݱ�
			icmp_hdr recvHdr;
			char *pICMPbuffer = NULL;

			//��ȡָ��ICMPͷ����ָ��
			pICMPbuffer = pRecvBuffer + sizeof(ip_hdr);

			//ICMP���ĳ��ȣ���ICMPͷ�� 
			int nICMPMsgLen = nResult - sizeof(ip_hdr);

			//����ICMPͷ��
			memcpy (&recvHdr,  pICMPbuffer, sizeof (recvHdr));

			//����IPͷ��
			ip_hdr ipHdr;
			memcpy (&ipHdr,  pRecvBuffer, sizeof (ipHdr));
			//��У���ת��������˳��
			recvHdr.icmp_checksum = ntohs (recvHdr.icmp_checksum);

			//�����Ӧ�Ƿ�Ϊ����Ӧ������ID�Լ�
			//���к��Ƿ�������һ�£�У����Ƿ���ȷ
			if (recvHdr.icmp_type == 0 &&
				recvHdr.icmp_id == sendHdr.icmp_id &&
				recvHdr.icmp_sequence == sendHdr.icmp_sequence &&
				ValidateChecksum (pICMPbuffer, nICMPMsgLen)  && 
				memcmp (pSendBuffer + sizeof(icmp_hdr), pRecvBuffer + sizeof (icmp_hdr) + sizeof(ip_hdr), 
					nResult - sizeof (icmp_hdr) - sizeof(ip_hdr)) == 0)
			{
				//����������ⶼȷ�ϵĻ��������������Ӧ�𣬼�������ʱ��
				int nSec = timeRecv.wSecond - timeSend.wSecond;
				if (nSec < 0)
				{
					nSec = nSec + 60;
				}

				int nMilliSec = abs (timeRecv.wMilliseconds - timeSend.wMilliseconds);

				int nRoundTripTime = 0;
				nRoundTripTime = abs (nSec * 1000 - nMilliSec);

				//��ʾ״̬��Ϣ
				printf("Reply from %s : bytes = %d  time = %d ms TTL = %d\n",pszRemoteIP, 
					nResult -sizeof (icmp_hdr) - sizeof (ip_hdr),nRoundTripTime,(int)ipHdr.ip_ttl);
				nTotalRoundTripTime = nTotalRoundTripTime + nRoundTripTime;

				if (nMinRoundTripTime == -1)
				{
					nMinRoundTripTime = nRoundTripTime;
					nMaxRoundTripTime = nRoundTripTime;
				}
				else if (nRoundTripTime < nMinRoundTripTime)
				{
					nMinRoundTripTime = nRoundTripTime;
				}
				else if (nRoundTripTime > nMaxRoundTripTime)
				{
					nMaxRoundTripTime = nRoundTripTime;
				}

				++nPacketsReceived;
			}
			else
			{
				printf("The echo reply is not correct!");
			}

			delete []pRecvBuffer;
		}
		else
		{
			printf("Request timed out.\n");
		}

		delete []pSendBuffer;
	}

	//ͳ����Ϣ
	printf("Ping statistics for %s:\n\tPackets: Sent =%d, Received =%d,Lost=%d (%.1f%% loss)\n",
		pszRemoteIP,nPacketsSent,nPacketsReceived,nPacketsSent - nPacketsReceived,
		((nPacketsSent - nPacketsReceived)/(float)nPacketsSent)* 100);

	//ʱ����Ϣ
	if (nPacketsReceived > 0)
	{
		printf("Approximate round trip times in milli-seconds:\n\tMinimum =%d ms, "
			"Maximum = %d ms ,Average =%.4f ms\n",nMinRoundTripTime,nMaxRoundTripTime,
			nTotalRoundTripTime / (float)nPacketsReceived);
	}

	if (UnInitialize () == false)
	{
		return -1;
	}

	return 0;
}

unsigned short CalcChecksum (char *pBuffer, int nLen)
{
	//ICMPУ��ͼ��㣬���㷽ʽ�����IPͷ������
	unsigned short nWord;
	unsigned int nSum = 0;
	int i;
    
	//����������8λ�����16λ�ֲ����������
	for (i = 0; i < nLen; i = i + 2)
	{
		nWord =((pBuffer [i] << 8)& 0xFF00) + (pBuffer [i + 1] & 0xFF);
		nSum = nSum + (unsigned int)nWord;	
	}
	
	
	while (nSum >> 16)
	{
		nSum = (nSum & 0xFFFF) + (nSum >> 16);
	}

	//ȡ��
	nSum = ~nSum;
	
	return ((unsigned short) nSum);
}

bool ValidateChecksum (char *pBuffer, int nLen)
{
	unsigned short nWord;
	unsigned int nSum = 0;
	int i;
    
	//Make 16 bit words out of every two adjacent 8 bit words in the packet
	//and add them up
	for (i = 0; i < nLen; i = i + 2)
	{
		nWord =((pBuffer [i] << 8)& 0xFF00) + (pBuffer [i + 1] & 0xFF);
		nSum = nSum + (unsigned int)nWord;	
	}
	
	//Take only 16 bits out of the 32 bit sum and add up the carries
	while (nSum >> 16)
	{
		nSum = (nSum & 0xFFFF) + (nSum >> 16);
	}

	//To validate the checksum on the received message we don't complement the sum
	//of one's complement
	//One's complement the result
	//nSum = ~nSum;
	
	//The sum of one's complement should be 0xFFFF
	return ((unsigned short)nSum == 0xFFFF);
}

bool Initialize ()
{
	//Initialize WinSock
	WSADATA wsaData;

	if (WSAStartup (MAKEWORD (2, 2), &wsaData) == SOCKET_ERROR)
	{
		printf("An error occured in WSAStartup operation:%d ",WSAGetLastError ());
		return false;
	}

	SYSTEMTIME time;
	GetSystemTime (&time);

	//Seed the random number generator with current millisecond value
	srand (time.wMilliseconds);

	return true;
}

bool UnInitialize ()
{
	//Cleanup
	if (WSACleanup () == SOCKET_ERROR)
	{
		printf("An error occured in WSACleanup operation:%d",WSAGetLastError ());
		return false;
	}

	return true;
}

bool ResolveIP (char *pszRemoteHost, char **pszIPAddress)
{
	hostent *pHostent = gethostbyname (pszRemoteHost);
	if (pHostent == NULL)
	{
		printf("An error occured in gethostbyname operation: %d",WSAGetLastError ());
		return false;
	}

	in_addr in;
	memcpy (&in,  pHostent->h_addr_list [0], sizeof (in_addr));
	*pszIPAddress = inet_ntoa (in);

	return true;
}

void Usage()
{
	printf("Usage: ping r n b t\n");
	printf("  r - Remote host\n");
	printf("  n - Number of echo requests to send\n");
	printf("  b - Bytes to send\n");
	printf("  t - Timeout after these many milliseconds\n");
	printf("  (null)- If no parameter then ping localhost\n");

	printf("\nping google.com 4 32 1000\n");
}

