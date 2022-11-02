// ntWebServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#pragma warning(disable:4786)

#include <winsock2.h>
#include <string>
#include <map>
#include <list>
#include <process.h>
#include <time.h>


#define THREADEXIT_SUCCESS	0x1234
#define THREADKILL_TO		1000
#define THREADWAIT_TO		30000
#define SERVERPORT			80
#define MAX_BUFFER			100000
#define SENDBLOCK			200000
#define MAX_MSG_SIZE	1024
#define LOGFILENAME			"ServerError.log"
#define ERROR404			"/fnf.html"
#define ERROR501			"/mna.html"

#define SERVERNAME			"ntWebServer/0.1b"

//winsock 2.2 library
#pragma comment(lib,"ws2_32.lib")

//ע�����ö��̰߳汾
//project settings->c/c++->category:code generation->
//user run-time library:debug multithread
using namespace std;

FILE *m_f;
char szLogFilePath[MAX_PATH];
char szMessage[MAX_MSG_SIZE];
char szDT[128];
struct tm *newtime;
time_t ltime;
CRITICAL_SECTION cs;

WSAEVENT ShutdownEvent;
HANDLE ThreadLaunchedEvent;

typedef struct _tagStatistics  
{
	long	nClientsConnected;
	long	nTotalHits;
	double	nTotalSent;
	double	nTotalRecv;
	double	nErrosCount;
	long	nVisitors;
}Statistics;
Statistics 	Stats;

string			szHomeDir;
string			szDefIndex;
typedef map<string, string> MIMETYPES;

MIMETYPES MimeTypes;
// Accept Thread
HANDLE	  ThreadA; 
unsigned int ThreadA_ID;	



BOOL ClearLog(const char*);
BOOL LogMessage(const char*, const char*, const char* = NULL, long = NULL);

BOOL IsComplete(string szRequest);
BOOL ParseRequest(string szRequest, string &szResponse, BOOL &bKeepAlive);
void InitMIMEType();

UINT __stdcall	AcceptThread(LPVOID);
UINT __stdcall 	ClientThread(LPVOID);
void  CleanupThread(WSAEVENT, WSAEVENT, SOCKET);
BOOL Shutdown();



int main(int argc, char* argv[])
{
	szHomeDir = ".";
	szDefIndex = "index.htm";
	
	if(szHomeDir.substr(szHomeDir.size() - 1, 1) != "\\")
		szHomeDir += "\\";

	InitMIMEType();
	InitializeCriticalSection(&cs);
	//��ʼ���Զ����á��ź�̬  
	ThreadLaunchedEvent	= CreateEvent(NULL, FALSE, TRUE, NULL);
	
	//���������߳�
	ResetEvent(ThreadLaunchedEvent);
	ThreadA = (HANDLE)_beginthreadex(NULL, 0, AcceptThread, NULL, 0, &ThreadA_ID);
	if(!ThreadA)
	{
		LogMessage(LOGFILENAME, "_beginthreadex(...) failure, for Launch Thread", "AcceptThread", errno);
		return FALSE;
	}	
	
	if(WaitForSingleObject(ThreadLaunchedEvent, INFINITE) != WAIT_OBJECT_0)
	{
		LogMessage(LOGFILENAME, "Unable to get response from Accept Thread withing specified Timeout ->", "ThreadLaunchedEvent", 0);
		CloseHandle(ThreadLaunchedEvent);
		return FALSE;
	}
	CloseHandle(ThreadLaunchedEvent);

	return 0;
}


UINT __stdcall AcceptThread(LPVOID pParam)
{
	SOCKET s;
	WORD wVersionRequested;
	WSADATA wsaData;
	sockaddr_in saLocal;
	WSAEVENT Handles[2];
	WSANETWORKEVENTS	NetworkEvents;
	sockaddr ClientAddr;
	INT addrlen = sizeof(ClientAddr);
	sockaddr_in sain;
	int result;
	
	saLocal.sin_family		= AF_INET;
	saLocal.sin_port		= htons(SERVERPORT);
	saLocal.sin_addr.s_addr = INADDR_ANY;
	
	wVersionRequested = MAKEWORD(2, 2);
	//��ʼ��Winsock 2.2
	printf("Initialising Winsock...\n");
	result = WSAStartup(wVersionRequested, &wsaData);
	if(result != 0)
	{
		LogMessage(LOGFILENAME, "WSAStartup(...) failure", "AcceptThread", result);
		return THREADEXIT_SUCCESS;
	}
	printf("Initialised successfully.\n");
	
	if(	LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2) 
	{
		LogMessage(LOGFILENAME, "Requested Socket version not exist", "AcceptThread");
		CleanupThread(NULL, NULL, NULL);
		return THREADEXIT_SUCCESS; 
	}
	//���������ص��׽���
	printf("\nCreating TCP socket...\n");
	s = WSASocket(AF_INET, SOCK_STREAM, 0, (LPWSAPROTOCOL_INFO)NULL, 0, WSA_FLAG_OVERLAPPED);
	if(s == INVALID_SOCKET)
	{
		LogMessage(LOGFILENAME, "WSASocket(...) failure", "AcceptThread", WSAGetLastError());
		CleanupThread(NULL, NULL, NULL);
		return THREADEXIT_SUCCESS;
	}

	//��
	result = bind(s, (struct sockaddr *)&saLocal, sizeof(saLocal));
	if(result == SOCKET_ERROR)
	{
		LogMessage(LOGFILENAME, "bind(...) failure", "AcceptThread", WSAGetLastError());
		CleanupThread(NULL, NULL, s);
		return THREADEXIT_SUCCESS;
	}	

	//����
	printf("ntWebserver listening on the %s:%d for HTTP service now!......\n",
		inet_ntoa(saLocal.sin_addr), htons(saLocal.sin_port));
	result = listen(s, SOMAXCONN);
	if(result == SOCKET_ERROR)
	{
		LogMessage(LOGFILENAME, "listen(...) failure", "AcceptThread", WSAGetLastError());
		CleanupThread(NULL, NULL, s);
		return THREADEXIT_SUCCESS;
	}	
	//�����¼����������߳�ͬ��
 	ShutdownEvent = WSACreateEvent();
	if(ShutdownEvent == WSA_INVALID_EVENT)
	{
		LogMessage(LOGFILENAME, "WSACreateEvent(...) failure for ShutdownEvent", "AcceptThread", WSAGetLastError());
		return THREADEXIT_SUCCESS;
	}		

	WSAEVENT Event = WSACreateEvent();
	if(Event == WSA_INVALID_EVENT)
	{
		LogMessage(LOGFILENAME, "WSACreateEvent(...) failure for Event", "AcceptThread", WSAGetLastError());
		CleanupThread(NULL, ShutdownEvent, s);
		return THREADEXIT_SUCCESS;
	}		
	//�¼�����
	Handles[0] = ShutdownEvent;
	Handles[1] = Event;

	//��ע�����¼�
	result = WSAEventSelect(s, Event, FD_ACCEPT);
	if(result == SOCKET_ERROR)
	{
		LogMessage(LOGFILENAME, "WSAEventSelect(...) failure", "AcceptThread", WSAGetLastError());
		CleanupThread(Event, ShutdownEvent, s);
		return THREADEXIT_SUCCESS;
	}

	//����ThreadLaunchedEvent�¼����˳����̣߳�������������
//	SetEvent(ThreadLaunchedEvent);
	//��������ѭ����
	for(;;)
	{
		//�ȴ������¼���һ����
		DWORD EventCaused = WSAWaitForMultipleEvents(
			2,
			Handles,  
			FALSE,                  
			WSA_INFINITE, 
			FALSE);

		if(EventCaused == WAIT_FAILED || EventCaused == WAIT_OBJECT_0)
		{
			if(EventCaused == WAIT_FAILED)
				LogMessage(LOGFILENAME, "WaitForMultipleObjects(...) failure", "AcceptThread", GetLastError());
			CleanupThread(Event, ShutdownEvent, s);
			return THREADEXIT_SUCCESS;
		}
		//�鿴�������¼�
		result = WSAEnumNetworkEvents(
			s,                           
			Event,              
			&NetworkEvents);
		
		if(result == SOCKET_ERROR)						 
		{
			LogMessage(LOGFILENAME, "WSAEnumNetworkEvents(...) failure", "AcceptThread", WSAGetLastError());
			CleanupThread(Event, ShutdownEvent, s);
			return THREADEXIT_SUCCESS;
		}

		//�����ӵ�����׼����������
		if(NetworkEvents.lNetworkEvents == FD_ACCEPT)
		{
			SOCKET ClientSocket = WSAAccept(s, &ClientAddr, &addrlen, NULL, NULL);	
			memcpy(&sain, &ClientAddr, addrlen);			
			//��ȡ�ͻ��˵�ַ��Ϣ
			printf("The client address is:%s:%d\n\n\n",
							inet_ntoa(sain.sin_addr),htons(sain.sin_port)); 

			if(INVALID_SOCKET == ClientSocket)
			{
				LogMessage(LOGFILENAME, "WSAAccept(...) failure", "AcceptThread", WSAGetLastError());
				//�����´�ѭ��
				continue; 
			}
			else
			{			
				//ÿ���ͻ�����ʹ�õ������߳�
				HANDLE			hThread;
				unsigned int	threadID;				
				EnterCriticalSection(&cs);
				hThread = 
					(HANDLE)_beginthreadex(NULL, 0, ClientThread, (LPVOID)ClientSocket, 0, &threadID);
				if(hThread)
				{
				}
				else
				{
					LogMessage(LOGFILENAME, "_beginthreadex(...) failure", "ClientThread", errno);
				}
				LeaveCriticalSection(&cs);
			}
		}
	}

	CleanupThread(Event, ShutdownEvent, s);
	return THREADEXIT_SUCCESS; 
}	

unsigned __stdcall ClientThread(LPVOID pParam)
{
	SOCKET s=(SOCKET)pParam;

	int					result;
	WSAEVENT			EventArray[2];
	WSANETWORKEVENTS	NetworkEvents;

	BOOL				bResend = FALSE;
	WSABUF				Buffer;
	DWORD				NumberOfBytesSent,dwBytesSent;
	BOOL				bKeepAlive = FALSE;
	string				szRequest,szResponse;
				
	WSAEVENT			Event = WSACreateEvent();

	if(Event == WSA_INVALID_EVENT)
	{
		LogMessage(LOGFILENAME, "WSACreateEvent(...) failure", "ClientThread", WSAGetLastError());
		return THREADEXIT_SUCCESS;
	}

	result = WSAEventSelect(s, Event, FD_READ | FD_WRITE | FD_CLOSE);
	if(result == SOCKET_ERROR)
	{
		LogMessage(LOGFILENAME, "WSAEventSelect(...) failure", "ClientThread", WSAGetLastError());
		return THREADEXIT_SUCCESS;
	}
	//�¼�����
	EventArray[0] = Event;
	EventArray[1] = ShutdownEvent;

	for(;;)
	{
		DWORD EventCaused = WSAWaitForMultipleEvents(
			2,
			EventArray,  
			FALSE,                  
			WSA_INFINITE, 
			FALSE);
		
		if(WSA_WAIT_FAILED == EventCaused)
		{
			LogMessage(LOGFILENAME, "WSAWaitForMultipleEvents(...) failure", "ClientThread", WSAGetLastError());
			return THREADEXIT_SUCCESS;
		}

		// ��ʱ��ر�
		if(EventCaused == 1 || EventCaused == WSA_WAIT_TIMEOUT)
		{
			return THREADEXIT_SUCCESS;
		}
		
		//�鿴�����������¼� 
		result = WSAEnumNetworkEvents(
			s,                           
			Event,              
			&NetworkEvents);

		if(result == SOCKET_ERROR)
		{
			LogMessage(LOGFILENAME, "WSAEnumNetworkEvents(...) failure", "ClientThread", WSAGetLastError());
			continue; 
		}

		//�¼�����
		if(NetworkEvents.lNetworkEvents & FD_READ)
		{
			//��������
			DWORD NumberOfBytesRecvd;
			WSABUF Buffers;
			DWORD dwBufferCount = 1;
			char szBuffer[MAX_BUFFER];
			DWORD Flags = 0;
			Buffers.buf = szBuffer;
			Buffers.len = MAX_BUFFER;
			
			result = WSARecv(
				s,
				&Buffers,
				dwBufferCount,
				&NumberOfBytesRecvd,
				&Flags,
				NULL,
				NULL);
			
			if(result != SOCKET_ERROR)
			{
				Stats.nTotalRecv += (double)NumberOfBytesRecvd / 1024;
				
				//���ͻ������Ƿ�������
				szRequest += string(szBuffer, NumberOfBytesRecvd);
				if(!IsComplete(szRequest))
					continue;
				
				//��������
				if(!ParseRequest(szRequest, szResponse, bKeepAlive))
				{
					return THREADEXIT_SUCCESS;
				}

				//���ͻ������ӡ����
				printf(szRequest.c_str());
				//�ڶ�ȡ����󣬸�������ֱ��������Ӧ�����͸��ͻ���
				NumberOfBytesSent = 0;
				dwBytesSent = 0;
				do
				{
					Buffer.len = (szResponse.size() - dwBytesSent) >= SENDBLOCK ? SENDBLOCK : szResponse.size() - dwBytesSent;	
					Buffer.buf = (char*)((DWORD)szResponse.c_str() + dwBytesSent);

					result = WSASend(
						s,                                                
						&Buffer,                                     
						1,                                    
						&NumberOfBytesSent,
						0,                                          
						0,                           
						NULL);
					
					if(SOCKET_ERROR != result)
						dwBytesSent += NumberOfBytesSent;
				}//ͨ��dowhileѭ��������Ӧ��ֱ��������ϻ���ִ���
				while((dwBytesSent < szResponse.size()) && SOCKET_ERROR != result);

				if(WSAGetLastError() == WSAEWOULDBLOCK)
				{
					//˵����Ӧ��Ϣ��δ��ȫ���ͣ���Ҫ�ٴη���
					bResend = TRUE;
					continue;
				}

				if(SOCKET_ERROR != result)
				{
					Stats.nTotalSent += (double)dwBytesSent / 1024;
				}
				else
				{
					LogMessage(LOGFILENAME, "WSASend(...) failure", "ClientThread, Primary Send", WSAGetLastError());
					bKeepAlive = FALSE;
				}
				
				if(!bKeepAlive) 
				{
					return THREADEXIT_SUCCESS;
				}

				//������ϣ���������
				szRequest.erase(0, string::npos);
			}
			else
				LogMessage(LOGFILENAME, "WSARecv(...) failure", "ClientThread", WSAGetLastError());
		}
		
		//����Ƿ���Ҫ���ŷ����ϴ�δ�������Ӧ
		if((NetworkEvents.lNetworkEvents & FD_WRITE) && bResend)
		{
			
			do
			{
				Buffer.len = (szResponse.size() - dwBytesSent) >= SENDBLOCK ? SENDBLOCK : szResponse.size() - dwBytesSent;	
				Buffer.buf = (char*)((DWORD)szResponse.c_str() + dwBytesSent);
				
				result = WSASend(
					s,                                                
					&Buffer,                                     
					1,                                    
					&NumberOfBytesSent,
					0,                                          
					0,                           
					NULL);

				if(SOCKET_ERROR != result)				
					dwBytesSent += NumberOfBytesSent;
			}
			while((dwBytesSent < szResponse.size()) && SOCKET_ERROR != result);
			//��Ȼ��Ҫ�ٴη���ʣ�ಿ��
			if(WSAGetLastError() == WSAEWOULDBLOCK)
			{
				bResend = TRUE;
				continue;
			}
			//˵���ѷ������
			if(SOCKET_ERROR != result)
			{
				Stats.nTotalSent += (double)dwBytesSent / 1024;
			}
			else//���������������
			{
				LogMessage(LOGFILENAME, "WSASend(...) failure", "ClientThread, Primary Send", WSAGetLastError());
				bKeepAlive = FALSE;
			}
			//���������Ժ��˳�
			if(!bKeepAlive)
			{
				return THREADEXIT_SUCCESS;
			}
			//���ˣ�˵���ѷ�����ϣ�������ŷ���
			bResend = FALSE;
			szRequest.erase(0, string::npos);
		}	
		
		//�ر��¼�
		if(NetworkEvents.lNetworkEvents & FD_CLOSE)
		{
			return THREADEXIT_SUCCESS;
		}
	}

	//��Զ����ִ�е��˴�
	return THREADEXIT_SUCCESS;
}	

void CleanupThread(WSAEVENT Event, WSAEVENT ShutdownEvent, SOCKET s)
{
	if(Event)
		WSACloseEvent(Event);
	
	if(ShutdownEvent)
		WSACloseEvent(ShutdownEvent);
	
	if(s)
		closesocket(s);
	
	WSACleanup();
}



BOOL LogMessage(const char *szFolder, const char *szMsg, const char *szMsg1, long nNumber)
{
	EnterCriticalSection(&cs);
//	time(&ltime);
	
	if((!strlen(szFolder)) || (!strlen(szMsg)))
		return FALSE;
	
	if(!GetCurrentDirectory(MAX_PATH,szLogFilePath))
	{
		LeaveCriticalSection(&cs);
		return FALSE;
	}
	
	if(szLogFilePath[0] != '\\')
		strcat(szLogFilePath, "\\");
	strcat(szLogFilePath, szFolder);
	
	m_f = fopen(szLogFilePath, "a");
	if(m_f != NULL)				
	{
		newtime = localtime(&ltime);
		strftime(szDT, 128,
			"%a, %d %b %Y %H:%M:%S", newtime);
		
		if(szMsg1 != NULL)
			sprintf(szMessage, "%s - %s.\t[%s]\t[%d]\n", szDT, szMsg, szMsg1, nNumber);
		else
			sprintf(szMessage, "%s - %s.\t[%d]\n", szDT, szMsg, nNumber);
		
		int n = fwrite(szMessage, sizeof(char), strlen(szMessage), m_f);
		if(n != strlen(szMessage))
		{
			LeaveCriticalSection(&cs);
			fclose(m_f);
			return FALSE;
		}
		
		fclose(m_f);
		LeaveCriticalSection(&cs);
		return TRUE;
	}
	
	LeaveCriticalSection(&cs);
	return FALSE;
}



BOOL ClearLog(const char *szFolder)
{
	if(!strlen(szFolder))
		return FALSE;
	
	if(!GetWindowsDirectory(szLogFilePath, MAX_PATH))
		return FALSE;
	
	if(szLogFilePath[0] != '\\')
		strcat(szLogFilePath, "\\");
	strcat(szLogFilePath, szFolder);
	
	return 	DeleteFile(szLogFilePath);
}

BOOL ParseRequest(string szRequest, string &szResponse, BOOL &bKeepAlive)
{
	// �����ͻ�����
	string szMethod;
	string szFileName;
	string szFileExt;
	string szStatusCode("200 OK");
	string szContentType("text/html");
	string szConnectionType("close");
	string szNotFoundMessage;
	string szDateTime;
	char pResponseHeader[2048];
	fpos_t lengthActual = 0, length = 0;
	char *pBuf = NULL;
	int n;
				
	//������󷽷�
	n = szRequest.find(" ", 0);
	if(n != string::npos)
	{
		szMethod = szRequest.substr(0, n);
		//GET����������ֻʵ����GET����
		if(szMethod == "GET")
		{
			//������ļ���
			int n1 = szRequest.find(" ", n + 1);
			if(n != string::npos)
			{
				szFileName = szRequest.substr(n + 1, n1 - n - 1);
				if(szFileName == "/")
				{
					szFileName = szDefIndex;
				}
			}
			else
			{
				LogMessage(LOGFILENAME, "No 'space' found in Request String #1", "ParseRequest");
				return FALSE;
			}
		}
		else//����������δʵ��
		{
			szStatusCode = "501 Not Implemented";
			szFileName = ERROR501;
		}
	}
	else
	{
		LogMessage(LOGFILENAME, "No 'space' found in Request String #2", "ParseRequest");
		return FALSE;
	}

	//�ж���������
	n = szRequest.find("\nConnection: Keep-Alive", 0);
	if(n != string::npos)
		bKeepAlive = TRUE;

	//�ҳ���������
	int nPointPos = szFileName.rfind(".");
	if(nPointPos != string::npos)
	{
		szFileExt = szFileName.substr(nPointPos + 1, szFileName.size());
		strlwr((char*)szFileExt.c_str());
		MIMETYPES::iterator it;
		it = MimeTypes.find(szFileExt);
		if(it != MimeTypes.end())
			szContentType = (*it).second;
	}

	//��ȡ��ǰGMT����ʱ��
	char szDT[128];
	struct tm *newtime;
	time_t ltime;
	
	time(&ltime);
	newtime = gmtime(&ltime);
	strftime(szDT, 128,
		"%a, %d %b %Y %H:%M:%S GMT", newtime);

	//��ȡ�ļ�
	FILE *f;
	f = fopen((szHomeDir + szFileName).c_str(), "r+b");
	//���ɹ����ļ�
	if(f != NULL)				
	{
		//��ȡ�ļ���С
		fseek(f, 0, SEEK_END);
		fgetpos(f, &lengthActual);
		fseek(f, 0, SEEK_SET);
		
		pBuf = new char[lengthActual + 1];

		length = fread(pBuf, 1, lengthActual, f);
		fclose(f);
		//������Ӧ
		sprintf(pResponseHeader, "HTTP/1.0 %s\r\nDate: %s\r\nServer: %s\r\nAccept-Ranges: bytes\r\nContent-Length: %d\r\nConnection: %s\r\nContent-Type: %s\r\n\r\n",
			szStatusCode.c_str(), szDT, SERVERNAME, (int)length, bKeepAlive ? "Keep-Alive" : "close", szContentType.c_str());
	}
	//�����ļ�ʧ��
	else
	{
		//��û�����ļ�	�����ṩĬ�ϵ���ʾ   
		f = fopen((szHomeDir + ERROR404).c_str(), "r+b");
		if(f != NULL)				
		{
			//��ȡERROR404�ļ���С
			fseek(f, 0, SEEK_END);
			fgetpos(f, &lengthActual);
			fseek(f, 0, SEEK_SET);
			pBuf = new char[lengthActual + 1];
			length = fread(pBuf, 1, lengthActual, f);
			fclose(f);
			szNotFoundMessage = string(pBuf, length);
			delete pBuf;
			pBuf = NULL;
		}
		szStatusCode = "404 Resource not found";

		sprintf(pResponseHeader, "HTTP/1.0 %s\r\nContent-Length: %d\r\nContent-Type: text/html\r\nDate: %s\r\nServer: %s\r\n\r\n%s",
			szStatusCode.c_str(), szNotFoundMessage.size(), szDT, SERVERNAME, szNotFoundMessage.c_str());
		bKeepAlive = FALSE;  
	}

	//������Ӧ
	szResponse = string(pResponseHeader);
	if(pBuf)
		szResponse += string(pBuf, length);
	delete pBuf;
	pBuf = NULL;
	
	return TRUE;
}

//�ж������Ƿ����
BOOL IsComplete(string szRequest)
{
	//��Ҫ��ͨ���鿴����ĸ��ֽ��Ƿ�Ϊ���������Ļس����ж�
	if(szRequest.substr(szRequest.size()-4, 4) == "\r\n\r\n")
		return TRUE;
	else
		return FALSE;
}

void InitMIMEType()
{
	//��ʼ��MIMETypes
	MimeTypes["doc"]	= "application/msword";
	MimeTypes["bin"]	= "application/octet-stream";
	MimeTypes["dll"]	= "application/octet-stream";
	MimeTypes["exe"]	= "application/octet-stream";
	MimeTypes["pdf"]	= "application/pdf";
	MimeTypes["p7c"]	= "application/pkcs7-mime";
	MimeTypes["ai"]		= "application/postscript";
	MimeTypes["eps"]	= "application/postscript";
	MimeTypes["ps"]		= "application/postscript";
	MimeTypes["rtf"]	= "application/rtf";
	MimeTypes["fdf"]	= "application/vnd.fdf";
	MimeTypes["arj"]	= "application/x-arj";
	MimeTypes["gz"]		= "application/x-gzip";
	MimeTypes["class"]	= "application/x-java-class";
	MimeTypes["js"]		= "application/x-javascript";
	MimeTypes["lzh"]	= "application/x-lzh";
	MimeTypes["lnk"]	= "application/x-ms-shortcut";
	MimeTypes["tar"]	= "application/x-tar";
	MimeTypes["hlp"]	= "application/x-winhelp";
	MimeTypes["cert"]	= "application/x-x509-ca-cert";
	MimeTypes["zip"]	= "application/zip";
	MimeTypes["cab"]	= "application/x-compressed";
	MimeTypes["arj"]	= "application/x-compressed";
	MimeTypes["aif"]	= "audio/aiff";
	MimeTypes["aifc"]	= "audio/aiff";
	MimeTypes["aiff"]	= "audio/aiff";
	MimeTypes["au"]		= "audio/basic";
	MimeTypes["snd"]	= "audio/basic";
	MimeTypes["mid"]	= "audio/midi";
	MimeTypes["rmi"]	= "audio/midi";
	MimeTypes["mp3"]	= "audio/mpeg";
	MimeTypes["vox"]	= "audio/voxware";
	MimeTypes["wav"]	= "audio/wav";
	MimeTypes["ra"]		= "audio/x-pn-realaudio";
	MimeTypes["ram"]	= "audio/x-pn-realaudio";
	MimeTypes["bmp"]	= "image/bmp";
	MimeTypes["gif"]	= "image/gif";
	MimeTypes["jpeg"]	= "image/jpeg";
	MimeTypes["jpg"]	= "image/jpeg";
	MimeTypes["tif"]	= "image/tiff";
	MimeTypes["tiff"]	= "image/tiff";
	MimeTypes["xbm"]	= "image/xbm";
	MimeTypes["wrl"]	= "model/vrml";
	MimeTypes["htm"]	= "text/html";
	MimeTypes["html"]	= "text/html";
	MimeTypes["c"]		= "text/plain";
	MimeTypes["cpp"]	= "text/plain";
	MimeTypes["def"]	= "text/plain";
	MimeTypes["h"]		= "text/plain";
	MimeTypes["txt"]	= "text/plain";
	MimeTypes["rtx"]	= "text/richtext";
	MimeTypes["rtf"]	= "text/richtext";
	MimeTypes["java"]	= "text/x-java-source";
	MimeTypes["css"]	= "text/css";
	MimeTypes["mpeg"]	= "video/mpeg";
	MimeTypes["mpg"]	= "video/mpeg";
	MimeTypes["mpe"]	= "video/mpeg";
	MimeTypes["avi"]	= "video/msvideo";
	MimeTypes["mov"]	= "video/quicktime";
	MimeTypes["qt"]		= "video/quicktime";
	MimeTypes["shtml"]	= "wwwserver/html-ssi";
	MimeTypes["asa"]	= "wwwserver/isapi";
	MimeTypes["asp"]	= "wwwserver/isapi";
	MimeTypes["cfm"]	= "wwwserver/isapi";
	MimeTypes["dbm"]	= "wwwserver/isapi";
	MimeTypes["isa"]	= "wwwserver/isapi";
	MimeTypes["plx"]	= "wwwserver/isapi";
	MimeTypes["url"]	= "wwwserver/isapi";
	MimeTypes["cgi"]	= "wwwserver/isapi";
	MimeTypes["php"]	= "wwwserver/isapi";
	MimeTypes["wcgi"]	= "wwwserver/isapi";
}

BOOL Shutdown()
{	
	BOOL bResult = TRUE;
	HANDLE	hArray[1];
	
	hArray[0] = ThreadA;
	
	//����Acceptthread
	SetEvent(ShutdownEvent);
	DWORD n = WaitForMultipleObjects(1, hArray, TRUE, THREADKILL_TO);
	
	if(n == WAIT_TIMEOUT || n == WAIT_FAILED)
	{
		LogMessage(LOGFILENAME, "WaitForMultipleObjects(...) timed out", "Shutdown");
		if(!TerminateThread(ThreadA, THREADEXIT_SUCCESS))
			LogMessage(LOGFILENAME, "TerminateThread(.ThreadA.) failure, probably it is already terminated", "Shutdown", GetLastError());
		bResult = FALSE;
	}
	
	CloseHandle(ThreadA); 
	
	DeleteCriticalSection(&cs);
	
	return bResult;
}