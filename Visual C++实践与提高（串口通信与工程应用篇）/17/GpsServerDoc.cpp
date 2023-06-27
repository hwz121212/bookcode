// GpsServerDoc.cpp : implementation of the CGpsServerDoc class
//

#include "stdafx.h"
#include <afxdb.h>
#include "GpsServer.h"
#include "MainFrm.h"
#include "GpsServerDoc.h"
#include "GpsServerView.h"
#include "ThreadCom.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGpsServerDoc

IMPLEMENT_DYNCREATE(CGpsServerDoc, CDocument)

BEGIN_MESSAGE_MAP(CGpsServerDoc, CDocument)
	//{{AFX_MSG_MAP(CGpsServerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGpsServerDoc construction/destruction

CGpsServerDoc::CGpsServerDoc()
{
	// TODO: add one-time construction code here	
	for (int i=0; i<2 ;i++)
	{
		MutexObject[i]=CreateMutex(NULL,FALSE,NULL);
	}	
}

CGpsServerDoc::~CGpsServerDoc()
{	
	CloseAllComWorkFlow();	
}
/////////////////////////////////////////////////////////////////////////////
// CGpsServerDoc serialization

void CGpsServerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

CMainFrame* CGpsServerDoc::GetMainFrame()
{
	return (CMainFrame*)AfxGetApp()->GetMainWnd();
}

/////////////////////////////////////////////////////////////////////////////
// CGpsServerDoc diagnostics

#ifdef _DEBUG
void CGpsServerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGpsServerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGpsServerDoc commands

///////////////////////////////////////////////////////////////////
// 函数名：	OnNewDocument
// 功  能：	初始化文档对象
// 参  数：	
// 返回值：	BOOL--初始化是否成功，成功返回TRUE，失败返回FALSE
// 备  注： 创建文档使用的数据库对象
///////////////////////////////////////////////////////////////////
BOOL CGpsServerDoc::OnNewDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (!CDocument::OnNewDocument())
		return FALSE;

	
	return ConnectDB();
}

BOOL CGpsServerDoc::ConnectDB() 
{
	BOOL bResult = FALSE;

	// 1、执行数据库的初始化
	TRY
	{
		// 创建数据库对象，并将其超时时间设置为5秒
		m_pDBGps = new CDatabase();
		if (m_pDBGps == NULL) return FALSE;

		m_pDBGps->SetLoginTimeout(5);

		// 数据库对象连接到名称为GPSCOMDB的ODBC数据源
		m_pDBGps->OpenEx("DSN=GPSCOMDB");

		// 判断数据库是否是编辑的
		if(! m_pDBGps->CanUpdate())
		{
			AfxMessageBox("注意：数据库为只读!");
		}

		// 设置当前的工作模式可以使用数据库
		m_bUseDB = TRUE;

		bResult = TRUE;
	}	
	CATCH(CException,e)
	{
		// 当创建数据库对象发生错误时，设置当前的工作模式不可以使用数据库
		e->ReportError();
		delete m_pDBGps;
		m_pDBGps = NULL;		
		bResult = FALSE;
	}
	END_CATCH

	return bResult;
}

//////////////////////////////////////////////////
// 函数名：CheckSendList
// 功  能：检测要发送的数据，并将通过串口发送出去
// 参  数：
// 返回值：
// 备  注：
//////////////////////////////////////////////////
void CGpsServerDoc::CheckSendList()
{	
	while (m_CommandList.GetSize() > 0)	
	{
		if (!m_bInitCom)
		{
			return;
		}

		CSendObject* cmd = (CSendObject*)m_CommandList.GetAt(0);
		CComWorkFlow* pFlow = GetComWorkFlow(cmd->m_Com);
		
		if (pFlow == NULL)	return;
		if (pFlow->m_ThreadCom == NULL) return;

		if (pFlow->m_ThreadCom->m_bOpen)
		{
			pFlow->m_ThreadCom->SendData((LPCTSTR)cmd->command,strlen(cmd->command)+1);	
			WaitForSingleObject(MutexObject[0],INFINITE);		
			m_CommandList.RemoveAt(0);
			ReleaseMutex(MutexObject[0]);	
		}
		
		return;
	}
}

//////////////////////////////////////////////////
// 函数名：GetComCount
// 功  能：获取当前工作的串口数目
// 参  数：
// 返回值：int--当前工作的串口数
// 备  注：
//////////////////////////////////////////////////
int CGpsServerDoc::GetComCount()
{	
	return m_ComWorkFlow.GetSize();
}


///////////////////////////////////////////////////////////////////
// 函数名：	IsUserValid
// 功  能：	判断用户名和密码是否正确
// 参  数：	CString UserName--要判断的用户名
//			CString Pass	--要判断的密码
// 返回值：	BOOL--用户是否有效，有效则返回TRUE，无效则返回FALSE
// 备  注：
//////////////////////////////////////////////////////////////////
BOOL CGpsServerDoc::IsUserValid(CString UserName, CString Pass)
{
	BOOL bValid = FALSE;
		
	TRY
	{
		m_pRSUser = new CRSUser(m_pDBGps);

		char sql[512];	
		sprintf(sql,"select * from User where UserName='%s' and Pass='%s'", UserName, Pass);	
		m_pRSUser->Open(AFX_DB_USE_DEFAULT_TYPE,sql);

		if (!m_pRSUser->IsEOF())
		{
			bValid = TRUE;				
		}
		else
		{
			bValid = FALSE;
		}

		m_pRSUser->Close();		
	}
	CATCH(CException,e)
	{
		e->ReportError();
		bValid = FALSE;
	}
	END_CATCH

	delete m_pRSUser;
	m_pRSUser=NULL;

	return bValid;
}

//////////////////////////////////////////////////
// 函数名：ReadComConfigs
// 功  能：从数据库中读取串口的配置
// 参  数：
// 返回值：BOOL--读取是否成功
// 备  注：
//////////////////////////////////////////////////
BOOL CGpsServerDoc::ReadComConfigs()
{
	if (m_bUseDB)
	{
		return ReadDBComConfigs();
	}
	else
	{
		return ReadDefaultComConfigs();
	}
}

///////////////////////////////////////////////////////////////////
// 函数名：	ReadDefaultComConfigs
// 功  能：	读取默认串口参数
// 参  数：	
// 返回值：	BOOL--读取默认串口参数是否成功
// 备  注：
//////////////////////////////////////////////////////////////////
BOOL CGpsServerDoc::ReadDefaultComConfigs()
{
	// 获取主窗口
	CMainFrame* pFrame = GetMainFrame();
	
	// 初始化串口参数链表
	m_ComWorkFlow.RemoveAll();

	// 设置默认的串口
	CComWorkFlow* pFlow = new CComWorkFlow();
	if (pFlow==NULL) return FALSE;
	DCB dcb;	
	dcb.BaudRate = COM_BAUD_RATE;
	dcb.ByteSize = COM_DATA_BYTE_SIZE;
	dcb.Parity  = COM_PARITY;
	dcb.StopBits = COM_STOP_BIT;
	pFlow->InitWorkFlow(COM_NAME, dcb);	
	m_ComWorkFlow.Add(pFlow);
	
	// 记录日志
	if (pFrame != NULL)
		pFrame->WriteLog(LOG_LEVEL_PROMPT, 
			"读取默认串口信息----名称--%s;波特率--%d;数据位--%d;奇偶校验--%d;停止位--%d;", 
			pFlow->m_Com, pFlow->m_dcb.BaudRate, pFlow->m_dcb.ByteSize,
			pFlow->m_dcb.Parity, pFlow->m_dcb.StopBits);

	return TRUE;
}

///////////////////////////////////////////////////////////////////
// 函数名：	ReadDefaultComConfigs
// 功  能：	从数据库中读取串口参数
// 参  数：	
// 返回值：	BOOL--从数据库中读取串口参数是否成功
// 备  注：
//////////////////////////////////////////////////////////////////
BOOL CGpsServerDoc::ReadDBComConfigs()
{
	BOOL bResult = FALSE;

	// 获取主窗口
	CMainFrame* pFrame= GetMainFrame();

	// 初始化串口参数链表
	m_ComWorkFlow.RemoveAll();	

	TRY
	{
		// 从数据库中获取串口的配置，从表ComConfig中读取配置的参数		
		m_pRSComConfig= new CRSComConfig(m_pDBGps);

		CString sql;
		sql.Format("select * from ComConfig where IsValid=true");		
		m_pRSComConfig->Open(CRecordset::dynaset,sql);
		
		m_pRSComConfig->MoveFirst();
		int iCount = 0;
		CDBVariant varValue;
		while(!m_pRSComConfig->IsEOF())
		{
			iCount ++;

			m_pRSComConfig->GetFieldValue("Name", varValue);

			CComWorkFlow* pFlow = new CComWorkFlow();
			if (pFlow==NULL) continue;
			DCB dcb;
			pFlow->m_Com.Format("%s", *varValue.m_pstring);
			dcb.BaudRate =m_pRSComConfig->m_BoundRate;
			dcb.ByteSize = (unsigned char)m_pRSComConfig->m_ByteSize;
			dcb.Parity  = (unsigned char)m_pRSComConfig->m_Parity;
			dcb.StopBits = (unsigned char)m_pRSComConfig->m_StopBits;
			pFlow->InitWorkFlow(COM_NAME, dcb);	
			m_ComWorkFlow.Add(pFlow);

			if (pFrame != NULL)	
				pFrame->WriteLog(LOG_LEVEL_PROMPT, 
					"读取第%d个串口信息----名称--%s;波特率--%d;数据位--%d;奇偶校验--%d;停止位--%d;", 
					iCount, pFlow->m_Com, 
					pFlow->m_dcb.BaudRate, pFlow->m_dcb.ByteSize,
					pFlow->m_dcb.Parity, pFlow->m_dcb.StopBits);				
			
			m_pRSComConfig->MoveNext();		
		}
		
		m_pRSComConfig->Close();	

		// 获取配置的串口数目，并将其显示的程序界面上
		if (pFrame != NULL)	
			pFrame->WriteLog(LOG_LEVEL_PROMPT,"共获取%d个工作串口", iCount);	
			
		bResult = TRUE;
	}
	CATCH(CDBException, e)
	{
		e->ReportError();		
		bResult = FALSE;
	}
	END_CATCH
		
	// 数据清理
	m_pRSComConfig->Close();		
	delete m_pRSComConfig;
	m_pRSComConfig=NULL;

	return bResult;
}



CComWorkFlow* CGpsServerDoc::GetComWorkFlow(CString com)
{
	for (int i = 0; i < m_ComWorkFlow.GetSize(); i++)
	{
		CComWorkFlow* pFlow = (CComWorkFlow*)m_ComWorkFlow.GetAt(i);
		if (pFlow != NULL)
		{
			if (pFlow->m_Com == com)
			{
				return pFlow;
			}
		}
	}
	return NULL;
}

BOOL CGpsServerDoc::OpenAllComWorkFlow()
{
	for (int i = 0;i < m_ComWorkFlow.GetSize(); i++)
	{
		CComWorkFlow* pFlow = m_ComWorkFlow.GetAt(i);
		if (pFlow == NULL) continue;

		OpenComWorkFlow(pFlow->m_Com);
		
		if (i == 0)
		{
			// 获取主窗口
			CMainFrame* pFrame =  GetMainFrame();
			if (pFrame != NULL)	
				pFrame->AddViewComData(pFlow->m_Com);
		}
	}
	
	return TRUE;
}

BOOL CGpsServerDoc::OpenComWorkFlow(CString com)
{
	// 获取主窗口
	CMainFrame* pFrame =  GetMainFrame();

	CComWorkFlow* pWorkFlow = GetComWorkFlow(com);	
	if (pWorkFlow == NULL)
	{
		return FALSE;
	}

	BOOL bResult = pWorkFlow->OpenWorkFlow();
	if (bResult)
	{		
		if (pFrame != NULL)	
			pFrame->WriteComWorkFlowLog(pWorkFlow, TRUE);
	}	
	
	return bResult;

}

BOOL CGpsServerDoc::CloseAllComWorkFlow()
{	
	for (int i = 0;i < m_ComWorkFlow.GetSize(); i++)
	{
		CComWorkFlow* pFlow = m_ComWorkFlow.GetAt(i);
		if (pFlow == NULL) continue;
		CloseComWorkFlow(pFlow->m_Com);
	}
	return TRUE;
}

BOOL CGpsServerDoc::CloseComWorkFlow(CString com)
{
	CComWorkFlow* pWorkFlow = GetComWorkFlow(com);
	if (pWorkFlow == NULL)
	{
		return FALSE;
	}

	BOOL bResult = pWorkFlow->CloseWorkFlow();
	if (bResult)
	{
		// 获取主窗口
		CMainFrame* pFrame = GetMainFrame();
		if (pFrame != NULL)	
			pFrame->WriteComWorkFlowLog(pWorkFlow, FALSE);
	}
	return bResult;
}


void CGpsServerDoc::FuncCommTimer()
{	
	CheckSendList();
}

void CGpsServerDoc::AddGPSPackToDB(GPSPack *pack, CString m_com)
{
	/*CGpsServerDoc* pDoc=(CGpsServerDoc*)GetDocument();	

	CString tele;
	tele.Format("%s",pack->ToGisInfor.gpsinfor.telephone);
	CString sql;
	CString mydate;
	mydate.Format("%04d-%02d-%02d",pack->ToGisInfor.gpsinfor.time.GetYear(),pack->ToGisInfor.gpsinfor.time.GetMonth(),pack->ToGisInfor.gpsinfor.time.GetDay());
    CString mytime;
	mytime.Format("%04d-%02d-%02d %02d:%02d:%02d",pack->ToGisInfor.gpsinfor.time.GetYear(),pack->ToGisInfor.gpsinfor.time.GetMonth(),pack->ToGisInfor.gpsinfor.time.GetDay(),pack->ToGisInfor.gpsinfor.time.GetHour(),pack->ToGisInfor.gpsinfor.time.GetMinute(),pack->ToGisInfor.gpsinfor.time.GetSecond());
	
	sql.Format("insert into GpsReceStatu (telephone,recetime,recedate,LCDStatu,RAMStatu,OEMStatu,GSMStatu,Reserved) values ('%s','%s','%s','%d','%d','%d','%d','%d')",tele,mytime,mydate,pack->ToGisInfor.gpsinfor.starCondition,pack->ToGisInfor.gpsinfor.starNum,pack->ToGisInfor.gpsinfor.statu,pack->ToGisInfor.gpsinfor.carCondition);
	TRY{
		pDoc->GpsDB->ExecuteSQL(sql);
	}
	CATCH(CDBException, e)
	{
		e->ReportError();	
		InsertOutputstr("添加错误：状态信息入库错误!");
	}
	END_CATCH*/
	return;
}