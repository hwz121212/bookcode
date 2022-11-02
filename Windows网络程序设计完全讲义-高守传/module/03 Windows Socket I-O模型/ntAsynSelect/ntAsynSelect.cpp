// ntAsynSelect.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <stdlib.h>
#include "winsock2.h"

//winsock 2.2 library
#pragma comment(lib,"ws2_32.lib")

#define WM_SOCK  WM_USER + 100

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
	WSAEVENT sockevent;
	DWORD bytesend;
	DWORD bytesrecv;
	DWORD flags;
} SOCKET_INFO, * LPSOCKET_INFO;

BOOL Createsockinfo(SOCKET s);
void Freesockinfo(DWORD Index);

DWORD totalsocks = 0;
LPSOCKET_INFO socklist[FD_SETSIZE];
//���շ������ݼ���
DWORD datasend,datarecv;

///////////////////////////////////////////////////
MSG msg;
//�����������׽���
SOCKET listensocket,acceptsocket;
//����˵�ַ
SOCKADDR_IN serAddr;
WSADATA wsaData;
//select����
struct fd_set fdwrite,fdread;
//������׼���õ��׽��ּ���
DWORD index;
//�׽��ֹ���ģʽ
ULONG sockmode;
//�ͻ��˵�ַ
SOCKADDR_IN  cliAddr;
int cliAddrLen;
int   nRet;
HWND hWnd=NULL;


//���е��׽��ֲ�����ת�Ƶ����ڹ����У���Ϊ��ģ���ǻ���windows��Ϣ��ģ��
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_SOCK)
    {
        //���
        if (WSAGETSELECTERROR(lParam))
        {
            //��������ر�
            printf("Socket failed with error %d\n", WSAGETSELECTERROR(lParam));
            closesocket(wParam);
        }
        else
        {
			//��һ����鷢���������¼���wParamΪ�׽��־��
            switch (WSAGETSELECTEVENT(lParam))
            {
                case FD_ACCEPT:
                    printf("Waiting for a connection on port %d.\n", PORT);
					//��������
					//cliAddrLen�����ʼ��ΪcliAddr�Ĵ�С
					cliAddrLen=sizeof(cliAddr);
					if ((acceptsocket = accept(listensocket, 
						(sockaddr*)&cliAddr,&cliAddrLen)) != INVALID_SOCKET)
					{
						//Ϊ���׽��ִ�����������
						if (Createsockinfo(acceptsocket) == FALSE)
							return 0;
						printf("successfully got a connection from %s:%d.\n",
							inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));
						//Ϊ�������׽���ע�������¼�FD_READ|FD_WRITE|FD_CLOSE
						nRet = WSAAsyncSelect(acceptsocket,hwnd,WM_SOCK,
							FD_READ|FD_WRITE|FD_CLOSE);

						if (nRet == SOCKET_ERROR)
						{
							printf("WSAAsyncSelect failed: %d\n", WSAGetLastError());
							return -1;
						}
					}
					else
					{		
						if (WSAGetLastError() != WSAEWOULDBLOCK)
						{
							printf("accept failed with error %d\n",WSAGetLastError());
							return 0;
						}
						
					}
                    break;

                case FD_WRITE:
					//for���׽���������ѭ�����ҷ��������¼����׽���
					for (index = 0; index < totalsocks; index++)
					{
						LPSOCKET_INFO sockinfo = socklist[index];
						
						if(wParam==sockinfo->socket)
						{
							//��������ʣ�ಿ��
							sockinfo->wsaBuf.buf = sockinfo->buf + sockinfo->bytesend;
							sockinfo->wsaBuf.len = sockinfo->bytesrecv - sockinfo->bytesend;
							if (WSASend(sockinfo->socket, 
								&(sockinfo->wsaBuf), 1, &datasend, 0,
								NULL, NULL) == SOCKET_ERROR)
							{
								if (WSAGetLastError() != WSAEWOULDBLOCK)
								{
									printf("Send failed with error %d\n",WSAGetLastError());
									Freesockinfo(index);
								}
							}
							else
							{
								//�����ѷ������ݼ���
								sockinfo->bytesend +=datasend;
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
					
                    break;
				case FD_READ:
					//for���׽��������в��ҷ��������¼����׽���
					for (index = 0; index < totalsocks; index++)
					{
						LPSOCKET_INFO sockinfo = socklist[index];
						
						if(wParam==sockinfo->socket)
						{
							//��������
							sockinfo->wsaBuf.buf = sockinfo->buf;
							sockinfo->wsaBuf.len = BUFFERSIZE;
							sockinfo->flags = 0;
							if (WSARecv(sockinfo->socket, 
								&(sockinfo->wsaBuf), 1, &datarecv,
								&sockinfo->flags, NULL, NULL) == SOCKET_ERROR)
							{
								if (WSAGetLastError() != WSAEWOULDBLOCK)
								{
									printf("Receive failed with error %d\n",WSAGetLastError());
									Freesockinfo(index);
								}
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
								sockinfo->bytesrecv= datarecv;
								//��ʾ���յ�������
								printf("%s\n",sockinfo->wsaBuf.buf);
								printf("Waiting to receive data...\n");
								//������exit���˳�����ѭ��
								if(strncmp(sockinfo->wsaBuf.buf,"exit",sizeof("exit"))==0)
								{
									printf("exit the receiving loop\n");
								}	
								//���ղ������ݣ��Է��ر�����
								if (datarecv== 0)
								{
									Freesockinfo(index);
								}
							}
						}
					}
					break;
                case FD_CLOSE:
                    // ����FD_READ��Ϣ�Ա�ǿ���ٽ���һ�Σ�ȷ�����ݽ������
                    PostMessage(hwnd, WM_SOCK, wParam, FD_READ);
                    break;
                default:
                    printf("Unknown message received: %d\n", WSAGETSELECTEVENT(lParam));
                    break;
            }
        }
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


//����windows����
HWND CreateDummyWindow(void)
{
    WNDCLASS wndclass;
    CHAR *wclassname = "AsynSelect";
    HWND hTemWnd;
	
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = (WNDPROC)WndProc;
    wndclass.cbClsExtra=wndclass.cbWndExtra = 0;  
    wndclass.hInstance = NULL;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = wclassname;
	
    if (RegisterClass(&wndclass) == 0)
    {
        printf("RegisterClass failed with error %d\n", GetLastError());
        return NULL;
    }
	
    //��������	
    if ((hTemWnd = CreateWindow(wclassname,"",WS_TILED,
		0,0,0,0,NULL,NULL,NULL,NULL)) == NULL)
    {      
        printf("CreateWindow failed with error %d\n", GetLastError());
        return NULL;
    }
	
    return hTemWnd;
}

int main(int argc, char* argv[])
{
	

	//��ʼ��Winsock 2.2
	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2,2),&wsaData) != 0)
	{
		printf("WSAStartup failed %d\n, WSAGetLastError()");
		exit(0); 
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

	hWnd=CreateDummyWindow();
	//Ϊ�����׽���ע��FD_ACCEPT|FD_CLOSE�¼�֪ͨ
	nRet= WSAAsyncSelect(listensocket,hWnd,WM_SOCK,FD_ACCEPT|FD_CLOSE);
	if (nRet == SOCKET_ERROR)
	{
		printf("WSAAsyncSelect failed: %d\n", WSAGetLastError());
		return -1;
	}

	//��Ϣѭ����������ͣ����ѭ����
	while(nRet = GetMessage(&msg,NULL, 0, 0))
    {
        if (nRet == -1)
        {
            printf("GetMessage failed with error %d\n", GetLastError());
            return -1;
        }
		
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
	
	WSACleanup();

	return 0;
}

void Freesockinfo(DWORD Index)
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


BOOL Createsockinfo(SOCKET s)
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

