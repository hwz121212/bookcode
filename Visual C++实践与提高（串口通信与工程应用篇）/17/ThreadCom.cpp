// ThreadSerial.cpp : implementation file
//

#include "stdafx.h"

#include "ThreadCom.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThreadCom

IMPLEMENT_DYNCREATE(CThreadCom, CWinThread)

CThreadCom::CThreadCom(HANDLE hCom)
{
	m_hCom=hCom;
	m_bOpen=FALSE;	
	m_sError="成功";
	m_hThread=NULL;
	m_dwMsgToData=0;
	m_dwMsgToParent=0;
	m_pWndData=NULL;
	m_pWndParent=NULL;	
	memset((unsigned char*)&m_overRead,0,sizeof(OVERLAPPED));
	memset((unsigned char*)&m_overWrite,0,sizeof(OVERLAPPED));
	m_overRead.hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
	m_overWrite.hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
}

CThreadCom::~CThreadCom()
{
}

BOOL CThreadCom::InitInstance()
{
	// TODO:  perform and per-thread initialization here	
	m_bAutoDelete=FALSE;
	m_bDone=FALSE;
	return TRUE;
}

int CThreadCom::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	BOOL bFlag=CloseCom();	
	return CWinThread::ExitInstance();	
}

BEGIN_MESSAGE_MAP(CThreadCom, CWinThread)
	//{{AFX_MSG_MAP(CThreadCom)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThreadCom message handlers

///////////////////////////////////////////////////////////////////
// 函数名：	ReceiveData
// 功  能：	接收串口发来的数据
// 参  数：	LPCTSTR rBuf--接收数据的缓冲区
//			int nMaxLength--接收的字符最大长度
// 返回值：	BOOL--接收数据是否成功，成功返回TRUE，失败返回FALSE
// 备  注： 在检测到串口有数据来时，调用此函数接收数据
///////////////////////////////////////////////////////////////////
BOOL CThreadCom::ReceiveData(LPCTSTR rBuf, int nMaxLength)
{
	DWORD		dwLength;		// 接收的数据的长度
	DWORD		dwError;		// 错误代码
	DWORD		dwErrorFlags;	// 错误代码
	COMSTAT		ComStat;		// 串口状态值
	BOOL		fReadStat ;		// 从串口读数据的状态

	// 清除端口的错误信息
    ClearCommError( m_hCom, &dwErrorFlags, &ComStat ) ;
	// 取接受字符串中的字符数目和空间大小的最小值作为要读取的字符数
	dwLength = min( (DWORD) nMaxLength, ComStat.cbInQue ) ;
	
	// 如果串口没有数据需要接收，则返回
	if (dwLength <= 0) return dwLength;
	

	// 读取串口的数据
	fReadStat = ReadFile( m_hCom, (void*)rBuf,
		                dwLength, &dwLength, &m_overRead ) ;

	// 如果读串口操作成功，则返回
	if(fReadStat) return dwLength;

	// 如果读串口操作未成功，则获取其错误代码
	dwError = GetLastError();

	// 如果错误是串口读写异步未执行完，则继续读取
	if (dwError == ERROR_IO_PENDING)
	{
		// 首先应该判断接收是否完成
		while(!GetOverlappedResult( m_hCom,
		&m_overRead, &dwLength, TRUE ))
		{
			dwError = GetLastError();
			if(dwError == ERROR_IO_INCOMPLETE)
			{
				// 如果发送还没有完成，则继续等待发送结束						
				continue;
			}
			else
			{
				// 如果发生错误，则处理错误
				m_sError.Format("<%u>", dwError) ;
				ClearCommError(m_hCom, &dwErrorFlags, &ComStat);
				if (dwErrorFlags > 0) 
				{
					printf(m_sError, "<%u>", dwErrorFlags);
				}
				break;
			}
		}				
	}
	// 如果在读取的过程中发生其他错误，则处理错误信息
	else
	{
		dwLength = 0;
		// 如果发生其他错误，则处理错误
		m_sError.Format("<%u>", dwError) ;
		ClearCommError( m_hCom, &dwErrorFlags, &ComStat ) ;
		if (dwErrorFlags > 0) 
		{
			printf(m_sError, "%s<%u>", m_sError, dwErrorFlags);
		}
	}

	// 返回接收到的数据长度
	return dwLength;
}

///////////////////////////////////////////////////////////////////
// 函数名：	Run
// 功  能：	线程的工作函数，其主要是检测串口是否有数据到达，如果有数据到达，则接收串口数据
// 参  数：	
// 返回值：	结束代码
// 备  注： 在检测到串口有数据来时，调用ReceiveData函数接收数据
///////////////////////////////////////////////////////////////////
int CThreadCom::Run() 
{
	// TODO: Add your specialized code here and/or call the base class	
	DWORD		dwEvent;						// 串口事件
	int			nLength ;						// 
	BYTE		rBuf[MAX_COM_IN_LENGTH+1];		// 接收数据的缓冲区
	

	// 如果线程工作结束标识值为FALSE，则检测串口数据，并接收
	while (!m_bDone)
	{		
		// 如果串口句柄是有效值，则执行处理
		while (m_hCom!=INVALID_HANDLE_VALUE)
		{	
			// 检测串口事件
			dwEvent = 0 ;
			WaitCommEvent(m_hCom, &dwEvent, NULL);				

			// 如果有字符接收串口事件，则接收串口数据
			if ((dwEvent & EV_RXCHAR) == EV_RXCHAR)
			{
				// 循环接收串口数据
				do
				{
					// 接收串口数据
					if (nLength = ReceiveData((LPSTR)rBuf, MAX_COM_IN_LENGTH) )
					{
						// 如果串口数据中有字符接收事件，则将事件传送给CDataFlow进行处理
						if(dwEvent & ~EV_RXCHAR) 
						{
							if(m_pWndData)
							{
								m_pWndData->SendMessage(m_dwMsgToData,dwEvent,0);
							}
						}

						//接收到数据后传送给CDataFlow进行处理
						if(nLength)
						{							
							if(m_pWndData)
							{
								m_pWndData->SendMessage(m_dwMsgToData,(DWORD)rBuf,nLength);
							}							
						}
					}
				}while ( nLength > 0 );			
			}
			Sleep(1);
		}
		Sleep(1);	
	}

	// 关闭读异步事件变量
	CloseHandle( m_overRead.hEvent);
	return CWinThread::Run();
}

///////////////////////////////////////////////////////////////////
// 函数名：	CloseCom
// 功  能：	关闭串口
// 参  数：	
// 返回值：	BOOL--关闭串口功，成功返回TRUE，失败返回FALSE
// 备  注： 析构工作一定要处理，否则程序是存在缺陷的
///////////////////////////////////////////////////////////////////
BOOL CThreadCom::CloseCom()
{
	// 如果串口句柄是有效的，则清除串口工作区，关闭句柄。
	if (m_hCom!=INVALID_HANDLE_VALUE)
	{
		PurgeComm(m_hCom,PURGE_RXCLEAR);//clear input buffer
		CloseHandle(m_hCom);
		m_hCom=INVALID_HANDLE_VALUE;
	}	
	m_bOpen=FALSE;
	return TRUE;
}

HANDLE CThreadCom::GetComHandle()
{
	return m_hCom;
}


///////////////////////////////////////////////////////////////////
// 函数名：	OpenCom
// 功  能：	打开串口
// 参  数：	CString com--要打开的串口名称,比如"COM1"
//			DCB dcb--打开串口时，串口的参数配置
//			CWnd *pWndData--串口线程所属的工作区句柄，主要是接收其消息，并对消息做相应处理 
//			DWORD dwMsgToWndData--串口线程与工作区之间通信的消息
//			CWnd *pWndParent--串口的父窗体
//			DWORD dwMsgToParent--串口线程与父窗体进行通信的消息
// 返回值：	BOOL--打开串口是否成功，成功返回TRUE，失败返回FALSE
// 备  注： 
///////////////////////////////////////////////////////////////////
BOOL CThreadCom::OpenCom(   CString com,
							DCB dcb, 
							CWnd *pWndData, 
							DWORD dwMsgToWndData, 
							CWnd *pWndParent, 
							DWORD dwMsgToParent)
{
	// 将传递进来的变量，赋值给成员变量
	m_Com = com;
	m_hCom=INVALID_HANDLE_VALUE;
	m_sError="No Error";	
	m_pWndData			=		pWndData;
	m_dwMsgToData		=		dwMsgToWndData;
	m_pWndParent		=		pWndParent;
	m_dwMsgToParent		=		dwMsgToParent;

	// 打开串口
	m_hCom=::CreateFile(m_Com,
		GENERIC_READ|GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_OVERLAPPED,
		NULL);
	if (m_hCom==INVALID_HANDLE_VALUE)
	{		
		m_sError.Format("Open %s Error", m_Com);
		return FALSE;
	}

	// 设置串口的输入缓冲区大小和输出缓冲区大小，建议在设置时，将其定义为宏
	::SetupComm(m_hCom, MAX_COM_IN_LENGTH, MAX_COM_OUT_LENGTH);

	// 设置串口的工作参数，在NEMA0183中规定，
	// 波特率为4800及其以上，数据位为8位，无奇偶校验，停止位为1位
	DCB tempdcb;
	int nSuccess	=	GetCommState(m_hCom,&tempdcb);
	if (!nSuccess)
	{
		m_sError="Can't get commstate!";
		CloseHandle(m_hCom);
		m_hCom=INVALID_HANDLE_VALUE;
		return FALSE;
	}

	tempdcb.BaudRate	=	dcb.BaudRate;
	tempdcb.ByteSize	=	dcb.ByteSize;
	tempdcb.Parity		=	dcb.Parity;
	tempdcb.StopBits	=	dcb.StopBits;

	if (SetCommState(m_hCom,&tempdcb)==0)
	{
		CloseHandle(m_hCom);
		m_hCom=INVALID_HANDLE_VALUE;		
		m_sError.Format("Init %s Error!", m_Com);
		return FALSE;
	}

	// 设置串口的工作超时参数，此处设置其读超时参数和写超时参数
	::GetCommTimeouts(m_hCom,&m_Commtimeout);
	m_Commtimeout.ReadTotalTimeoutMultiplier=5;
	m_Commtimeout.ReadTotalTimeoutConstant=100;
	m_Commtimeout.WriteTotalTimeoutMultiplier=0;
	m_Commtimeout.WriteTotalTimeoutConstant=1024;
	::SetCommTimeouts(m_hCom, &m_Commtimeout);

	// 设置串口检测的事件
	DWORD CommMask;
	CommMask=0
			|	EV_BREAK	//数据输入时，检测到中断
			|	EV_CTS		//CTS信号改变状态
			|	EV_DSR		//DSR信号改变状态
			|	EV_ERR		//发生行状态错误，包括CE_FRAME,CE_OVERRUN,和CE_RXPARITY.
			|	EV_EVENT1	//
			|	EV_EVENT2	//
			|	EV_PERR		//发生打印错误A printer error occured.
			|	EV_RING		//检测到振铃
			|	EV_RLSD		//RLSD信号改变状态
			|	EV_RX80FULL	//接收缓冲区中已经占用80%以上
			|	EV_RXCHAR	//接收到字符，并将其放入输入缓冲区
			|	EV_RXFLAG	//接收到事件字符，并将其放入到输入缓冲区中
			|	EV_TXEMPTY;	//输出缓冲区中最后一个字符发送出去
	if (!SetCommMask(m_hCom, CommMask))
	{
		return FALSE;
	} 

	// 一切成功，返回
	m_bOpen=TRUE;
	return TRUE;
}

///////////////////////////////////////////////////////////////////
// 函数名：	SendData
// 功  能：	向串口发送数据
// 参  数：	LPCTSTR sBuf--发送数据的缓冲区
//			DWORD dwLen--发送数据的大小
// 返回值：	BOOL--发送数据是否成功，成功返回TRUE，失败返回FALSE
// 备  注： 此函数执行的是异步发送功能
///////////////////////////////////////////////////////////////////
BOOL CThreadCom::SendData(LPCTSTR sBuf, DWORD dwLen)
{
	BOOL bResult = FALSE;
	// 判断串口句柄是否有效
	if (m_hCom != INVALID_HANDLE_VALUE)
	{		
		DWORD   	dwError;			// 发送操作时的错误代码
		DWORD       dwErrorFlags;		// 发送操作时的错误状态
		DWORD       dwByteSent=0;		// 发送的字符数
		DWORD		dwByteWrite;		// 发送字符数临时变量
		COMSTAT		ComStat;			// 串口的工作状态

		// 向串口发送数据，需要注意m_overWrite的使用，这是执行异步写操作的关键
		BOOL fWriteStat = WriteFile(m_hCom, sBuf, dwLen, &dwByteWrite, &m_overWrite);	
		// 如果发送数据发生错误，则处理判断错误的情况
		if (!fWriteStat)
		{			
			dwError = GetLastError();		// 获取错误代码
			// 如果错误是异步读写未完成，则继续等待发送
			if(dwError == ERROR_IO_PENDING)
			{
				// 首先应该判断发送是否完成
				while(!GetOverlappedResult( m_hCom,
				&m_overWrite, &dwByteWrite, TRUE ))
				{
					dwError = GetLastError();

					if(dwError == ERROR_IO_INCOMPLETE)
					{
						// 如果发送还没有完成，则继续等待发送结束
						dwByteSent += dwByteWrite;
						continue;
					}
					else
					{
						// 如果发生错误，则处理错误
						m_sError.Format("<%u>", dwError) ;
						ClearCommError(m_hCom, &dwErrorFlags, &ComStat);
						if (dwErrorFlags > 0) 
						{
							printf(m_sError, "%s<%u>", m_sError, dwErrorFlags);
						}
						break;
					}			
				}		

				// 累计增加发送成功的字符数，并根据情况编写信息提示
				dwByteSent += dwByteWrite;

				if( dwByteSent != dwLen )
				{
					printf(m_sError, "%s-发送超时：%ld/%ld已经发送/共有字节", m_sError, dwByteSent, dwLen);
					bResult = FALSE;
				}				 
				else
				{
					printf(m_sError, "%s-发送完成：共成功发送%ld个字节", m_sError, dwByteSent);					
					bResult = TRUE;
				}
			}
			else
			{				
				// 如果发生其他错误，则处理错误
				m_sError.Format("<%u>", dwError) ;
				ClearCommError( m_hCom, &dwErrorFlags, &ComStat ) ;
				if (dwErrorFlags > 0) 
				{
					printf(m_sError, "%s<%u>", m_sError, dwErrorFlags);
				}
				bResult = FALSE;
			}
		}
		// 如果发送成功，直接编写信息提示
		else
		{
			printf(m_sError, "发送完成：共成功发送%ld个字节", dwByteSent);					
			bResult = TRUE;
		}
	}
	// 如果串口句柄无效，则返回错误
	else
	{
		m_sError="串口句柄无效";
		return FALSE;
	}	

	// 将发送结果发送给主窗口，由主窗口处理界面显示的问题
	::SendMessage(AfxGetApp()->GetMainWnd()->m_hWnd, WM_SEND_COM_DATA_RESULT, (WPARAM)&m_Com, (LPARAM)&m_sError);
	return bResult;
}



