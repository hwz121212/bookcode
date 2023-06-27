// ComWorkFlow.cpp: implementation of the CComWorkFlow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ComWorkFlow.h"
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComWorkFlow::CComWorkFlow()
{
	m_DataFlow = new CDataFlow();
	m_ThreadCom = new CThreadCom();
}

CComWorkFlow::~CComWorkFlow()
{

}

///////////////////////////////////////////////////////////////////
// 函数名：	StartComThread
// 功  能：	启动串口工作线程
// 参  数：	
// 返回值：	BOOL--启动串口工作线程是否成功
// 备  注：
//////////////////////////////////////////////////////////////////
BOOL CComWorkFlow::StartComThread()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->GetMainWnd();
	BOOL bResult = FALSE;
		
	TRY
	{
		if (m_ThreadCom != NULL)
		{
			if (m_ThreadCom->m_bOpen)
			{
				if (pFrame != NULL)	
					pFrame->WriteLog(LOG_LEVEL_INFO, "串口%s已经打开!", m_Com);
				return FALSE;
			}
		}
		m_ThreadCom = (CThreadCom*)AfxBeginThread(RUNTIME_CLASS(CThreadCom));
		bResult = OpenCom();		
		if (pFrame != NULL)
			pFrame->WriteLog(LOG_LEVEL_INFO, "启动串口%s工作线程成功!", m_Com);
	}
	CATCH(CException,e)
	{
		e->ReportError();		
		m_ThreadCom->m_bDone=TRUE;
		StopWinThread((CWinThread*)&m_ThreadCom,INFINITE);	
		if (pFrame != NULL)	
			pFrame->WriteLog(LOG_LEVEL_ERROR, "启动串口%s工作线程错误!", m_Com);
		bResult = FALSE;		
	}
	END_CATCH	
	return bResult;
}

///////////////////////////////////////////////////////////////////
// 函数名：	StopComThread
// 功  能：	停止串口工作线程
// 参  数：	
// 返回值：	BOOL--停止串口工作线程是否成功
// 备  注：
//////////////////////////////////////////////////////////////////
BOOL CComWorkFlow::StopComThread()
{	
	if (m_ThreadCom != NULL)
	{
		m_ThreadCom->CloseCom();
		m_ThreadCom->m_bDone=TRUE;
		StopWinThread((CWinThread*)m_ThreadCom,INFINITE);		
		m_ThreadCom = NULL;	
	}
	return TRUE;
}


///////////////////////////////////////////////////////////////////
// 函数名：	StopWinThread
// 功  能：	停止线程
// 参  数：	CWinThread *pThread--要停止的线程
//			DWORD dwTimeout--超时时间
// 返回值：	BOOL--停止线程的退出码
// 备  注：
//////////////////////////////////////////////////////////////////
DWORD CComWorkFlow::StopWinThread(CWinThread *pThread, DWORD dwTimeout)
{
 	if (pThread==NULL) return NULL;
  	pThread->PostThreadMessage(WM_QUIT,0,0);
 	::WaitForSingleObject(pThread->m_hThread,dwTimeout);
 	DWORD nExitCode=0;
 	BOOL bFlag=::GetExitCodeThread(pThread->m_hThread,&nExitCode);
 	if (bFlag)
 	{
 		delete pThread;
 	}	
 	return nExitCode;
}

///////////////////////////////////////////////////////////////////
// 函数名：	OpenWorkFlow
// 功  能：	打开串口工作区
// 参  数：	
// 返回值：	BOOL--打开串口工作区是否成功，成功返回TRUE，失败返回FALSE
// 备  注： 
///////////////////////////////////////////////////////////////////
BOOL CComWorkFlow::OpenWorkFlow()
{
	BOOL bResult;
	bResult = StartComThread();
	return bResult;
}

///////////////////////////////////////////////////////////////////
// 函数名：	CloseWorkFlow
// 功  能：	关闭串口工作区
// 参  数：	
// 返回值：	BOOL--关闭串口工作区是否成功，成功返回TRUE，失败返回FALSE
// 备  注： 
///////////////////////////////////////////////////////////////////
BOOL CComWorkFlow::CloseWorkFlow()
{
	BOOL bResult;
	bResult = StopComThread();
	return bResult;
}

///////////////////////////////////////////////////////////////////
// 函数名：	InitWorkFlow
// 功  能：	初始化串口工作区
// 参  数：	CString com--工作区对应的工作串口名称
//			DCB dcb--串口工作参数
// 返回值：	BOOL--初始化串口工作区是否成功，成功返回TRUE，失败返回FALSE
// 备  注： 
///////////////////////////////////////////////////////////////////
BOOL CComWorkFlow::InitWorkFlow(CString com, DCB dcb)
{
	m_Com = com;
	m_dcb = dcb;
	m_DataFlow->Create();
	m_DataFlow->SendMessage(WM_INITCENTER,NULL,(LPARAM)0);
	return TRUE;
}

///////////////////////////////////////////////////////////////////
// 函数名：	OpenCom
// 功  能：	打开串口
// 参  数：	
// 返回值：	BOOL--打开串口工作区是否成功，成功返回TRUE，失败返回FALSE
// 备  注： 
///////////////////////////////////////////////////////////////////
BOOL CComWorkFlow::OpenCom()
{
	if (m_ThreadCom == NULL)
	{
		return FALSE;
	}

	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->GetMainWnd();		
		
	if (m_ThreadCom->m_bOpen)
	{	
		if (pFrame != NULL)	
			pFrame->WriteLog(LOG_LEVEL_INFO,"串口%s已经打开!", m_Com);			
		return FALSE;		
	}	

	if (m_ThreadCom->OpenCom(m_Com, m_dcb,
		m_DataFlow, m_DataFlow->GetMeMsg()))
	{	
		if (pFrame != NULL)	
			pFrame->WriteLog(LOG_LEVEL_INFO,"打开串口%s成功!", m_Com);
		m_DataFlow->m_Com = m_Com;
		return TRUE;
	}
	else
	{	
		if (pFrame != NULL)	
			pFrame->WriteLog(LOG_LEVEL_ERROR, m_ThreadCom->m_sError+",请重新配置串口!");
		m_ThreadCom->m_bOpen=FALSE;		
		return FALSE;		
	}
}

///////////////////////////////////////////////////////////////////
// 函数名：	CloseCom
// 功  能：	关闭串口
// 参  数：	
// 返回值：	BOOL--关闭串口工作区是否成功，成功返回TRUE，失败返回FALSE
// 备  注： 停止串口工作线程
///////////////////////////////////////////////////////////////////
BOOL CComWorkFlow::CloseCom()
{
	if (m_ThreadCom == NULL) return FALSE;		
	return m_ThreadCom->CloseCom();	
}
