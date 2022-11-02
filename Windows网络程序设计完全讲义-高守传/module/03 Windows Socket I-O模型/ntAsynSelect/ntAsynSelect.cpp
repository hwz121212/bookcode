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

//套接字环境
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
//接收发送数据计数
DWORD datasend,datarecv;

///////////////////////////////////////////////////
MSG msg;
//监听、连接套接字
SOCKET listensocket,acceptsocket;
//服务端地址
SOCKADDR_IN serAddr;
WSADATA wsaData;
//select集合
struct fd_set fdwrite,fdread;
//缓冲区准备好的套接字计数
DWORD index;
//套接字工作模式
ULONG sockmode;
//客户端地址
SOCKADDR_IN  cliAddr;
int cliAddrLen;
int   nRet;
HWND hWnd=NULL;


//所有的套接字操作都转移到窗口过程中，因为该模型是基于windows消息的模型
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_SOCK)
    {
        //查错
        if (WSAGETSELECTERROR(lParam))
        {
            //发生错误关闭
            printf("Socket failed with error %d\n", WSAGETSELECTERROR(lParam));
            closesocket(wParam);
        }
        else
        {
			//进一步检查发生的网络事件，wParam为套接字句柄
            switch (WSAGETSELECTEVENT(lParam))
            {
                case FD_ACCEPT:
                    printf("Waiting for a connection on port %d.\n", PORT);
					//接受连接
					//cliAddrLen必须初始化为cliAddr的大小
					cliAddrLen=sizeof(cliAddr);
					if ((acceptsocket = accept(listensocket, 
						(sockaddr*)&cliAddr,&cliAddrLen)) != INVALID_SOCKET)
					{
						//为新套接字创建工作环境
						if (Createsockinfo(acceptsocket) == FALSE)
							return 0;
						printf("successfully got a connection from %s:%d.\n",
							inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));
						//为已连接套接字注册网络事件FD_READ|FD_WRITE|FD_CLOSE
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
					//for在套接字数组中循环查找发生网络事件的套接字
					for (index = 0; index < totalsocks; index++)
					{
						LPSOCKET_INFO sockinfo = socklist[index];
						
						if(wParam==sockinfo->socket)
						{
							//继续发送剩余部分
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
								//增加已发送数据计数
								sockinfo->bytesend +=datasend;
								//二者相等时说明接收数据已发送完毕
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
					//for在套接字数组中查找发生网络事件的套接字
					for (index = 0; index < totalsocks; index++)
					{
						LPSOCKET_INFO sockinfo = socklist[index];
						
						if(wParam==sockinfo->socket)
						{
							//接收数据
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
								//cliAddrLen必须初始化为cliAddr的大小
								cliAddrLen=sizeof(cliAddr);
								
								//获取客户端地址信息
								if(getpeername(sockinfo->socket,(sockaddr*)&cliAddr,&cliAddrLen))
								{
									printf("getpeername failed with error %d\n", WSAGetLastError());
								}
								
								printf( "The following data comes from %s:%d\n",
									inet_ntoa(cliAddr.sin_addr),htons(cliAddr.sin_port)); 
								//接收的数据量
								sockinfo->bytesrecv= datarecv;
								//显示接收到的数据
								printf("%s\n",sockinfo->wsaBuf.buf);
								printf("Waiting to receive data...\n");
								//若发现exit则退出处理循环
								if(strncmp(sockinfo->wsaBuf.buf,"exit",sizeof("exit"))==0)
								{
									printf("exit the receiving loop\n");
								}	
								//接收不到数据，对方关闭连接
								if (datarecv== 0)
								{
									Freesockinfo(index);
								}
							}
						}
					}
					break;
                case FD_CLOSE:
                    // 寄送FD_READ消息以便强制再接收一次，确保数据接收完毕
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


//创建windows窗口
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
	
    //创建窗口	
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
	

	//初始化Winsock 2.2
	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2,2),&wsaData) != 0)
	{
		printf("WSAStartup failed %d\n, WSAGetLastError()");
		exit(0); 
	}
	printf("Initialised successfully.\n");

	//创建监听socket
	printf("\nCreating TCP socket...\n");
	if((listensocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0,
	  WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET) 
	{
		printf("Creation of socket failed %d\n", WSAGetLastError());
		WSACleanup();
		return 0;
	}

	//设置SOCKADDR_IN地址结构
	serAddr.sin_family = AF_INET;
	serAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//  serAddr.sin_addr.s_addr = inet_addr(ADDR);
	serAddr.sin_port = htons(PORT);
	
	//绑定套接字
	if (bind(listensocket, (SOCKADDR *) &serAddr, sizeof(serAddr))
		== SOCKET_ERROR)
	{
		printf("bind failed with error %d\n", WSAGetLastError());
		closesocket(listensocket);
		WSACleanup();
		return 0;
	}
	
	//监听连接
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
	//为监听套接字注册FD_ACCEPT|FD_CLOSE事件通知
	nRet= WSAAsyncSelect(listensocket,hWnd,WM_SOCK,FD_ACCEPT|FD_CLOSE);
	if (nRet == SOCKET_ERROR)
	{
		printf("WSAAsyncSelect failed: %d\n", WSAGetLastError());
		return -1;
	}

	//消息循环，主程序停留在循环中
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
	
	//从数组中移除
	for (loop = Index; loop < totalsocks-1; loop++)
	{
		socklist[loop] = socklist[loop + 1];
	}
	//递减已关闭连接套接字的计数
	totalsocks--;
}


BOOL Createsockinfo(SOCKET s)
{
	LPSOCKET_INFO sockinfo;
	
	printf("Accepted socket!\n");
	//从堆上分配内存
	if ((sockinfo = (LPSOCKET_INFO) GlobalAlloc(GPTR,
		sizeof(SOCKET_INFO))) == NULL)
	{
		printf("GlobalAlloc() failed\n");
		return FALSE;
	}
	
	//套接字相关
	sockinfo->socket=s;
	sockinfo->bytesend=sockinfo->bytesrecv =0;
	
	socklist[totalsocks]=sockinfo;
	//递增已接受连接套接字的计数
	totalsocks++;
	
	return TRUE;
}

