// ntNetService.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <tchar.h>
#include <windows.h>
#include "winsock2.h"

//winsock 2.2 library
#pragma comment(lib,"ws2_32.lib")

#define PORT 8888
#define BUFFERSIZE 100
#define ADDR  "127.0.0.1"
#define ECHO   0xFE
#define REPLY  0xFF

//�׽��ֻ���
typedef struct _tagSOCKET_INFO {
	OVERLAPPED overlap;
	WSABUF wsaBuf;
	char buf[BUFFERSIZE];
	SOCKET socket;
	DWORD bytesend;
	DWORD bytesrecv;
} SOCKET_INFO, * LPSOCKET_INFO;

BOOL CreateSocketInfo(SOCKET s);
void FreeSocketInfo(DWORD Index);

DWORD totalsocks = 0;
LPSOCKET_INFO socklist[FD_SETSIZE];


#define SERVICENAME  "NET SERVICE"
#define DISPLAYNAME  "NET SERVICE"
#define NEXT_ARG ((((*Argv)[2])==TEXT('\0'))?(--Argc,*++Argv):(*Argv)+2)

HANDLE hStopEvent=0;
DWORD dwCheckPoint=0;
SERVICE_STATUS srvStatus;	
SERVICE_STATUS_HANDLE sshStatusHandle=0;
HANDLE ServiceThread;


BOOL RegisterService(int argc, char ** argv);
// "StartDispatcher()" registers one service-procedure
// to the service control dispatcher (using the predefined
// "ServiceMain()" function below).
// Override this funtion, if you want to develop a
// multithreaded NT-Service.
BOOL StartDispatcher();

void WINAPI	ServiceMain(DWORD argc, LPTSTR * argv);
void WINAPI	ServiceCtrlHandler(DWORD CtrlCode);
unsigned __stdcall Daemon(void*);
BOOL ReportStatus(DWORD CurState,DWORD WaitHint = 3000,DWORD ErrExit = 0);

LPTSTR GetLastErrorText( LPTSTR lpszBuf, DWORD dwSize );
void Run(DWORD argc, LPTSTR * argv);
void Stop();
void Pause();
void Continue();
void Shutdown();

BOOL InstallService();
BOOL RemoveService();
BOOL StopService();
BOOL StartupService();

void WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv) {

	//ע�������ƴ�����
	sshStatusHandle =RegisterServiceCtrlHandler(SERVICENAME,ServiceCtrlHandler);

	if(sshStatusHandle)
		//��SCM���浱ǰ״̬
		if(ReportStatus(SERVICE_START_PENDING) )
		{
			Run( dwArgc, lpszArgv );
		}
	//��SCM����ֹͣ״̬
	if( sshStatusHandle )
		ReportStatus(SERVICE_STOPPED);
}


void WINAPI ServiceCtrlHandler(DWORD dwCtrlCode) 
{
	//����������ƴ���
	switch( dwCtrlCode ) 
	{
		case SERVICE_CONTROL_STOP:
			//ֹͣ����
			srvStatus.dwCurrentState = SERVICE_STOP_PENDING;
			Stop();
			break;

		case SERVICE_CONTROL_PAUSE:
			srvStatus.dwCurrentState = SERVICE_PAUSE_PENDING;
			Pause();
			break;

		case SERVICE_CONTROL_CONTINUE:
			srvStatus.dwCurrentState = SERVICE_CONTINUE_PENDING;			
			Continue();		
			break;

		case SERVICE_CONTROL_SHUTDOWN:			
			Shutdown();
			break;

		case SERVICE_CONTROL_INTERROGATE:
			//���·���״̬
			ReportStatus(srvStatus.dwCurrentState);
			break;

		default:
			break;
	}
}


BOOL ReportStatus(DWORD dwCurrentState,DWORD dwWaitHint,DWORD dwErrExit ) 
{
	BOOL fResult = TRUE;

    srvStatus.dwControlsAccepted =SERVICE_ACCEPT_STOP | 
		SERVICE_ACCEPT_PAUSE_CONTINUE | 
		SERVICE_ACCEPT_SHUTDOWN;
	
    srvStatus.dwCurrentState = dwCurrentState;
    srvStatus.dwWin32ExitCode = NO_ERROR;
    srvStatus.dwWaitHint = dwWaitHint;
	
	//���ô�����ش���
	srvStatus.dwServiceSpecificExitCode = dwErrExit;
	if (dwErrExit!=0)
		srvStatus.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR;
	
    if( dwCurrentState == SERVICE_RUNNING ||
        dwCurrentState == SERVICE_STOPPED )
        srvStatus.dwCheckPoint = 0;
    else
        srvStatus.dwCheckPoint = ++dwCheckPoint;
	
    //��SCM���浱ǰ״̬
    if (!(fResult = SetServiceStatus( sshStatusHandle, &srvStatus))) 
	{
        TCHAR szBuf[256];
		_tprintf(TEXT("\n%s failed to SetServiceStatus: %s\n"), DISPLAYNAME, GetLastErrorText(szBuf,256));
    }

    return fResult;
}


BOOL RegisterService( int argc, char ** argv ) {
	
	BOOL (* fnc)() = &StartDispatcher;
    DWORD Argc;
    LPTSTR * Argv;

    Argc = (DWORD) argc;
    Argv = argv;
	//SCM���ô˺���ʱû�����µĲ���
    while( ++Argv, --Argc ) 
	{
		if( Argv[0][0] == TEXT('-') )
		{
			switch( Argv[0][1] ) 
			{
				case TEXT('i'):	//��װ����
					fnc = &InstallService;
					break;
				case TEXT('u'):	//ж�ط���
					fnc = &RemoveService;
					break;
				case TEXT('s'):	//��������
					fnc = &StartupService;
					break;
				case TEXT('t'):	//terminateֹͣ����
					fnc = &StopService;
					break;
				default:
					break;
			}
		}
	}
	
	return (*fnc)();
}


BOOL StartDispatcher() 
{
    //ע�����������
	SERVICE_TABLE_ENTRY dispatchTable[] =
    {
        { LPTSTR(SERVICENAME), (LPSERVICE_MAIN_FUNCTION)ServiceMain },
        { 0, 0 }
    };
	
	BOOL bRet = StartServiceCtrlDispatcher(dispatchTable);
	if( ! bRet ) 
	{
		TCHAR szBuf[256];
		_tprintf(TEXT("\n%s failed to start: %s\n"), DISPLAYNAME, GetLastErrorText(szBuf,256));
	}
	
	return bRet;
}



LPTSTR GetLastErrorText( LPTSTR lpszBuf, DWORD dwSize ) 
{
    LPTSTR lpszTemp = 0;	
    DWORD dwRet =	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_ARGUMENT_ARRAY,
		0,
		GetLastError(),
		LANG_NEUTRAL,
		(LPTSTR)&lpszTemp,
		0,
		0);
	
	strcpy(lpszBuf,lpszTemp);
	if(lpszTemp)
        LocalFree(HLOCAL(lpszTemp));
	
    return lpszBuf;
}

BOOL InstallService() 
{
    TCHAR szPath[1024];

	if( GetModuleFileName( 0, szPath, 1023 ) == 0 ) 
	{
		TCHAR szErr[256];
		_tprintf(TEXT("Unable to install %s - %s\n"), DISPLAYNAME, GetLastErrorText(szErr, 256));
		return FALSE;
	}

	BOOL bRet = FALSE;
	//��SCM
	SC_HANDLE schSCManager =	OpenSCManager(
		0,						// machine (NULL == local)
		0,						// database (NULL == default)
		SC_MANAGER_ALL_ACCESS	// access required
		);
	if( schSCManager ) 
	{
		SC_HANDLE schService =CreateService(
			schSCManager,
			SERVICENAME,
			DISPLAYNAME,
			SERVICE_ALL_ACCESS,
			SERVICE_WIN32_OWN_PROCESS,
			SERVICE_AUTO_START,
			SERVICE_ERROR_NORMAL,
			szPath,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL
			);
		
		if( schService ) 
		{
			_tprintf(TEXT("%s installed.\n"), DISPLAYNAME );
			CloseServiceHandle(schService);
			bRet = TRUE;
		} 
		else 
		{
			TCHAR szErr[256];
			_tprintf(TEXT("CreateService failed - %s\n"), GetLastErrorText(szErr, 256));
		}
		
		CloseServiceHandle(schSCManager);
	} 
	else 
	{
		TCHAR szErr[256];
		_tprintf(TEXT("OpenSCManager failed - %s\n"), GetLastErrorText(szErr,256));
	}
	
	if( bRet ) 
	{
		// ��װ�ɹ�
	}

	return bRet;
}


BOOL RemoveService()
{
	BOOL bRet = FALSE;

	//��SCM
	SC_HANDLE schSCManager = OpenSCManager(
		0,						// machine (NULL == local)
		0,						// database (NULL == default)
		SC_MANAGER_ALL_ACCESS	// access required
								);
	if( schSCManager )
	{
		SC_HANDLE schService =	OpenService(
			schSCManager,
			SERVICENAME,
			SERVICE_ALL_ACCESS
			);
		
		if( schService ) 
		{
			//ֹͣ����
			if( ControlService(schService, SERVICE_CONTROL_STOP, &srvStatus) )
			{
				_tprintf(TEXT("Stopping %s."), DISPLAYNAME);
				Sleep(1000);
				
				while( QueryServiceStatus(schService, &srvStatus) )
				{
					if( srvStatus.dwCurrentState == SERVICE_STOP_PENDING ) 
					{
						_tprintf(TEXT("."));
						Sleep( 1000 );
					} else
						break;
				}
				
				if( srvStatus.dwCurrentState == SERVICE_STOPPED )
					_tprintf(TEXT("\n%s stopped.\n"), DISPLAYNAME);
				else
					_tprintf(TEXT("\n%s failed to stop.\n"), DISPLAYNAME);
			}
			
			//ɾ������
			if( DeleteService(schService) ) 
			{
				_tprintf(TEXT("%s removed.\n"), DISPLAYNAME);
				bRet = TRUE;
			} 
			else 
			{
				TCHAR szErr[256];
				_tprintf(TEXT("DeleteService failed - %s\n"), GetLastErrorText(szErr,256));
			}
			
			CloseServiceHandle(schService);
		} 
		else
		{
			TCHAR szErr[256];
			_tprintf(TEXT("OpenService failed - %s\n"), GetLastErrorText(szErr,256));
		}
		
		CloseServiceHandle(schSCManager);
	} 
	else 
	{
		TCHAR szErr[256];
		_tprintf(TEXT("OpenSCManager failed - %s\n"), GetLastErrorText(szErr,256));
	}

	return bRet;
}


BOOL StopService() 
{
	BOOL bRet = FALSE;

	SC_HANDLE schSCManager = OpenSCManager(
								0,						// machine (NULL == local)
								0,						// database (NULL == default)
								SC_MANAGER_ALL_ACCESS	// access required
							);
	if( schSCManager )
	{
		SC_HANDLE schService =	OpenService(
									schSCManager,
									SERVICENAME,
									SERVICE_ALL_ACCESS
								);

		if( schService )
		{
			//ֹͣ����
			if( ControlService(schService, SERVICE_CONTROL_STOP, &srvStatus) ) 
			{
				_tprintf(TEXT("Stopping %s."), DISPLAYNAME);
				Sleep(1000);

				while( QueryServiceStatus(schService, &srvStatus) ) 
				{
					if( srvStatus.dwCurrentState == SERVICE_STOP_PENDING ) 
					{
						_tprintf(TEXT("."));
						Sleep( 1000 );
					} else
						break;
				}

				if( srvStatus.dwCurrentState == SERVICE_STOPPED )
					bRet = TRUE, _tprintf(TEXT("\n%s stopped.\n"), DISPLAYNAME);
                else
                    _tprintf(TEXT("\n%s failed to stop.\n"), DISPLAYNAME);
			}

			CloseServiceHandle(schService);
		} 
		else 
		{
			TCHAR szErr[256];
			_tprintf(TEXT("OpenService failed - %s\n"), GetLastErrorText(szErr,256));
		}

        CloseServiceHandle(schSCManager);
    }
	else 
	{
		TCHAR szErr[256];
		_tprintf(TEXT("OpenSCManager failed - %s\n"), GetLastErrorText(szErr,256));
	}

	return bRet;
}


BOOL StartupService() 
{
	
	BOOL bRet = FALSE;
	SC_HANDLE schSCManager = OpenSCManager(
								0,						// machine (NULL == local)
								0,						// database (NULL == default)
								SC_MANAGER_ALL_ACCESS	// access required
							);
	if(schSCManager) 
	{
		SC_HANDLE schService =	OpenService(
									schSCManager,
									SERVICENAME,
									SERVICE_ALL_ACCESS
								);

		if(schService) 
		{
			//��������
			_tprintf(TEXT("Starting up %s."), DISPLAYNAME);
			if( StartService(schService, 0, 0) ) {
				Sleep(1000);

				while( QueryServiceStatus(schService, &srvStatus) ) 
				{
					if( srvStatus.dwCurrentState == SERVICE_START_PENDING ) 
					{
						_tprintf(TEXT("."));
						Sleep( 1000 );
					} 
					else
						break;
				}

				if( srvStatus.dwCurrentState == SERVICE_RUNNING )
					bRet = TRUE, _tprintf(TEXT("\n%s started.\n"), DISPLAYNAME);
                else
                    _tprintf(TEXT("\n%s failed to start.\n"), DISPLAYNAME);
			} 
			else 
			{
				//��������ʧ��
				TCHAR szErr[256];
				_tprintf(TEXT("\n%s failed to start: %s\n"), DISPLAYNAME, GetLastErrorText(szErr,256));
			}

			CloseServiceHandle(schService);
		} 
		else 
		{
			TCHAR szErr[256];
			_tprintf(TEXT("OpenService failed - %s\n"), GetLastErrorText(szErr,256));
		}

        CloseServiceHandle(schSCManager);
    } 
	else 
	{
		TCHAR szErr[256];
		_tprintf(TEXT("OpenSCManager failed - %s\n"), GetLastErrorText(szErr,256));
	}

	return bRet;
}

void Pause() 
{	
	ReportStatus(srvStatus.dwCurrentState);
	SuspendThread(ServiceThread);
	ReportStatus(SERVICE_PAUSED);		
}

void Continue() 
{
	ReportStatus(srvStatus.dwCurrentState);
	ResumeThread(ServiceThread);
	ReportStatus(SERVICE_RUNNING);
}


void Shutdown() 
{
}


//֪ͨ����
void Stop() 
{
	if( hStopEvent )
	{
		SetEvent(hStopEvent);
	}
	ReportStatus(SERVICE_STOPPED);
}

//��������ĺ���
void Run(DWORD argc, LPTSTR * argv) 
{
	
	ReportStatus(SERVICE_START_PENDING);
	hStopEvent = CreateEvent(0, TRUE, FALSE, 0);
	ReportStatus(SERVICE_RUNNING);
	
	DWORD thrid_daemon;
	//�����ػ��̣߳�Ҳ�����ṩʵ�ʷ�����߳�
	ServiceThread = CreateThread(0, 0,
		(LPTHREAD_START_ROUTINE) Daemon,
      0, 0, &thrid_daemon);
	
	WaitForSingleObject(hStopEvent,INFINITE);
	
	TerminateThread((void*)ServiceThread,0);
	CloseHandle(hStopEvent);
		
	ReportStatus(SERVICE_STOPPED);
}


unsigned __stdcall Daemon(void*)
{
	//�����������׽���
	SOCKET listensocket,acceptsocket;
	//����˵�ַ
	SOCKADDR_IN serAddr;
	WSADATA wsaData;
	//select����
	struct fd_set fdwrite,fdread;
	//������׼���õ��׽��ּ���
	DWORD index,sockok;
	//�׽��ֹ���ģʽ
	ULONG sockmode;
	DWORD flags;
	//���շ������ݼ���
	DWORD datasend,datarecv;
	//�ͻ��˵�ַ
	SOCKADDR_IN  cliAddr;
	int cliAddrLen;

	//��ʼ��Winsock 2.2
	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2,2),&wsaData) != 0)
	{
		fprintf(stderr,"WSAStartup() failed %d\n, WSAGetLastError()");
		return 0; 
	}
	printf("Initialised successfully.\n");

	//��������socket
	printf("\nCreating TCP socket...\n");
	if((listensocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0,
	  WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET) 
	{
		printf("Creation of socket failed %d\n", WSAGetLastError());
		WSACleanup();
		return 0;
	}

	//����SOCKADDR_IN��ַ�ṹ
	serAddr.sin_family = AF_INET;
	serAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//  serAddr.sin_addr.s_addr = inet_addr(ADDR);
	serAddr.sin_port = htons(PORT);

	//���׽���
	if (bind(listensocket, (SOCKADDR *) &serAddr, sizeof(serAddr))
	  == SOCKET_ERROR)
	{
		printf("bind failed with error %d\n", WSAGetLastError());
		closesocket(listensocket);
		WSACleanup();
		return 0;
	}

	//��������
	if (listen(listensocket, 5))
	{
		printf("listen failed with error %d\n", WSAGetLastError());
		closesocket(listensocket);
		WSACleanup();
		return 0;
	}

	printf("Listening on the %s:%d...\n",
		inet_ntoa(serAddr.sin_addr), htons(serAddr.sin_port));

	//���ļ����׽��ֹ���ģʽ��������ģʽ+select

	sockmode = 1;
	if (ioctlsocket(listensocket, FIONBIO, &sockmode) == SOCKET_ERROR)
	{
		printf("ioctlsocket() failed \n");
		return 0;
	}

	while(TRUE)
	{
		//��ʼ����д�׽��ּ���
		FD_ZERO(&fdread);
		FD_ZERO(&fdwrite);
		//�������׽�����ӵ������У��Ա�����������
		FD_SET(listensocket, &fdread);
		
		//���ݻ�������ǰ��״̬��Ϊ�׽������ÿɶ��Լ���д�Բ���
		//Ʃ�統�յ������Ժ���Ҫ���Ի������Ŀ�д��
		//����Ͳ�����ɶ���

		for (index = 0; index < totalsocks; index++)
			if (socklist[index]->bytesrecv > socklist[index]->bytesend)
				FD_SET(socklist[index]->socket, &fdwrite);
			else
				FD_SET(socklist[index]->socket, &fdread);
			//ѡ�����Ȥ���׽��ּ���
			if ((sockok = select(0, &fdread, &fdwrite, 
				NULL, NULL)) == SOCKET_ERROR)
			{
				fprintf(stderr, "select failed: %d\n", WSAGetLastError());
				return -1;
			}
			//��鵽������������
			if (FD_ISSET(listensocket, &fdread))
			{
				sockok--;
				//cliAddrLen�����ʼ��ΪcliAddr�Ĵ�С
				cliAddrLen=sizeof(cliAddr);
				if ((acceptsocket = accept(listensocket, 
					(sockaddr*)&cliAddr,&cliAddrLen)) != INVALID_SOCKET)
				{
					//�������Ӳ����µ��׽�������Ϊ������ģʽ
					sockmode = 1;
					if (ioctlsocket(acceptsocket, FIONBIO, &sockmode) == SOCKET_ERROR)
					{
						printf("ioctlsocket() failed with error %d\n", WSAGetLastError());
						return 0;
					}
					//Ϊ���׽��ִ�����������
					if (CreateSocketInfo(acceptsocket) == FALSE)
						return 0;
					printf("successfully got a connection from %s:%d.\n",
						inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));
				}
				else
				{		
					if (WSAGetLastError() != WSAEWOULDBLOCK)
					{
						printf("accept() failed with error %d\n", WSAGetLastError());
						return 0;
					}
					
				}
			}
			//Ϊ���е�sockok�׽��ּ���д֪ͨ
			for (index = 0; sockok > 0 && index < totalsocks; index++)
			{
				LPSOCKET_INFO sockinfo = socklist[index];
				
				//�������ɶ��Բ���
				if (FD_ISSET(sockinfo->socket, &fdread))
				{
					sockok--;
					
					sockinfo->wsaBuf.buf = sockinfo->buf;
					sockinfo->wsaBuf.len = BUFFERSIZE;
					flags = 0;
					if (WSARecv(sockinfo->socket, 
						&(sockinfo->wsaBuf), 1, &datarecv,
			   &flags, NULL, NULL) == SOCKET_ERROR)
					{
						if (WSAGetLastError() != WSAEWOULDBLOCK)
						{
							printf("Receive failed with error\n");
							FreeSocketInfo(index);
						}
						
						continue;
					} 
					else
					{
						//cliAddrLen�����ʼ��ΪcliAddr�Ĵ�С
						cliAddrLen=sizeof(cliAddr);
						
						//��ȡ�ͻ��˵�ַ��Ϣ
						if(getpeername(sockinfo->socket,(sockaddr*)&cliAddr,&cliAddrLen))
						{
							printf("getpeername failed with error %d\n", WSAGetLastError());
						}
						
						printf( "The following data comes from %s:%d\n",
							inet_ntoa(cliAddr.sin_addr),htons(cliAddr.sin_port)); 
						//���յ�������
						sockinfo->bytesrecv = datarecv;
						//��ʾ���յ�������
						printf("%s\n",sockinfo->wsaBuf.buf);
						printf("Waiting to receive data...\n");
						//������exit���˳�����ѭ��
						if(strncmp(sockinfo->wsaBuf.buf,"exit",sizeof("exit"))==0)
						{
							printf("exit the receiving loop\n");
							break;
						}	
						//���ӹرգ�����յ�0�ֽ�
						if (datarecv == 0)
						{
							FreeSocketInfo(index);
							continue;
						}
					}
				}
				//��������д�Բ���
				if (FD_ISSET(sockinfo->socket, &fdwrite))
				{
					sockok--;
					
					//��������ʣ�ಿ��
					sockinfo->wsaBuf.buf = sockinfo->buf + sockinfo->bytesend;
					sockinfo->wsaBuf.len = sockinfo->bytesrecv - sockinfo->bytesend;
					if (WSASend(sockinfo->socket, 
						&(sockinfo->wsaBuf), 1, &datasend, 0,
						NULL, NULL) == SOCKET_ERROR)
					{
						if (WSAGetLastError() != WSAEWOULDBLOCK)
						{
							printf("Send failed with error\n");
							FreeSocketInfo(index);
						}
						
						continue;
					}
					else
					{
						Beep(200,200);
						//�����ѷ������ݼ���
						sockinfo->bytesend += datasend;
						//�������ʱ˵�����������ѷ������
						if (sockinfo->bytesend == sockinfo->bytesrecv)
						{
							sockinfo->bytesend = 0;
							sockinfo->bytesrecv = 0;
							ZeroMemory(sockinfo->wsaBuf.buf,BUFFERSIZE);
						}
					}
				}
			}
	}

	WSACleanup();
	return 0;
}

void FreeSocketInfo(DWORD Index)
{
	
	LPSOCKET_INFO sockinfo = socklist[Index];
	DWORD loop;
	
	closesocket(sockinfo->socket);
	
	printf("Closing socket.....\n");
	
	GlobalFree(sockinfo);
	
	//���������Ƴ�
	for (loop = Index; loop < totalsocks-1; loop++)
	{
		socklist[loop] = socklist[loop + 1];
	}
	//�ݼ��ѹر������׽��ֵļ���
	totalsocks--;
}


BOOL CreateSocketInfo(SOCKET s)
{
	LPSOCKET_INFO sockinfo;
	
	printf("Accepted socket!\n");
	//�Ӷ��Ϸ����ڴ�
	if ((sockinfo = (LPSOCKET_INFO) GlobalAlloc(GPTR,
		sizeof(SOCKET_INFO))) == NULL)
	{
		printf("GlobalAlloc() failed\n");
		return FALSE;
	}
	
	//�׽������
	sockinfo->socket=s;
	sockinfo->bytesend=sockinfo->bytesrecv =0;
	
	socklist[totalsocks]=sockinfo;
	//�����ѽ��������׽��ֵļ���
	totalsocks++;
	
	return TRUE;
}


int main(int argc, char* argv[])
{
	srvStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	srvStatus.dwServiceSpecificExitCode = 0;
	RegisterService(argc, argv);
	return 0;
}

