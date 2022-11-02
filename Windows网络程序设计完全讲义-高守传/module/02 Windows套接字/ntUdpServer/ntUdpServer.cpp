// ntUdpServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "winsock2.h"

//winsock 2.2 library
#pragma comment(lib,"ws2_32.lib")

#define PORT  8888
#define ADDR  "127.0.0.1"

int main(int argc, char* argv[])
{
	WSADATA	wsock;
	SOCKET sersocket;
	SOCKADDR_IN  serAddr;
	int   serAddrsize=sizeof(serAddr);
	int   nRet=0;
	char  buf[1024];

	//��ʼ��Winsock 2.2
	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2,2),&wsock) != 0)
	{
		fprintf(stderr,"WSAStartup() failed %d\n, WSAGetLastError()");
        exit(0); 
	} 
	printf("Initialised successfully.\n");
	
	//����socket
	printf("\nCreating UDP Socket...\n");
	if ((sersocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) 
		== INVALID_SOCKET)
	{
		printf("Creation of socket failed %d\n", WSAGetLastError());
		WSACleanup();
		return 0;
	}

	printf("UDP Socket Created successfully.\n");

	//����SOCKADDR_IN��ַ�ṹ
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(PORT);    
	//   serAddr.sin_addr.s_addr = INADDR_ANY;
	serAddr.sin_addr.s_addr = inet_addr(ADDR);
	//���׽���
	if (bind(sersocket, (SOCKADDR *)&serAddr,
		sizeof(serAddr))== SOCKET_ERROR)
	{
		printf("bind failed with error %d\n", WSAGetLastError());
		closesocket(sersocket);
		WSACleanup();
		return 0;
	}

	printf("Waiting to receive data...\n");

	for(int i=0;;i++)
	{
		if ((nRet = recvfrom(sersocket, buf, sizeof(buf), 0,
			(SOCKADDR *)&serAddr, &serAddrsize)) == SOCKET_ERROR)
		{
			printf("ERROR: recvfrom failed with error %d\n", WSAGetLastError());
			closesocket(sersocket);
			WSACleanup();
			return 0;
		}
		//��ʾ���յ�������
		printf(buf);
		printf("\n");
		if ((nRet = sendto(sersocket, buf, strlen(buf), 0, 
			(SOCKADDR *)&serAddr, sizeof(serAddr))) == SOCKET_ERROR)
		{
			printf("ERROR: sendto failed with error %d\n", WSAGetLastError());
			closesocket(sersocket);
			WSACleanup();
			return 0;
		}

		//������exit���˳�����ѭ��
		if(strncmp(buf,"exit",sizeof("exit"))==0)
		{
			printf("exit the receiving loop\n");
			break;
		}
	}

	//�ر��׽���
	closesocket(sersocket);
	
	WSACleanup();
	return 0;
}

