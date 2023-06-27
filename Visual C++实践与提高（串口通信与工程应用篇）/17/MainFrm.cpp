// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "GpsServer.h"
#include "MainFrm.h"
#include "GpsServerView.h"
#include "GpsServerDoc.h"
#include "DlgComConfig.h"
#include "CJTabCtrlBar.h"
#include "ViewLog.h"
#include "ViewSendData.h"
#include "ViewReceiveData.h"
#include "ViewReceivePosition.h"
#include "ViewTreeCom.h"
#include "ViewNemaData.h"
#include "ViewComData.h"
#include "DlgLogin.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)    	
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_MESSAGE(WM_SEND_COM_DATA,MsgSendData)
	ON_MESSAGE(WM_SEND_COM_DATA_RESULT,MsgSendDataResult)
	ON_MESSAGE(WM_DECODED_NEMA_SENTENCE,MsgDecodedNemaSentence)	
	ON_MESSAGE(WM_RECEIVE_COM_DATA,MsgReceiveDataResult)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_UPDATE_COMMAND_UI(ID_COM_CLOSE, OnUpdateComClose)
	ON_COMMAND(ID_COM_CLOSE, OnComClose)
	ON_COMMAND(ID_SYSTEM_CLEAR_LOG, OnSystemClearLog)
	ON_COMMAND(ID_COM_OPEN, OnComOpen)
	ON_COMMAND_EX(CG_OUTPUT_DLG, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_OUTPUT_DLG, OnUpdateControlBarMenu)
	ON_COMMAND_EX(CG_OUTPUT_DLG1, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_OUTPUT_DLG1, OnUpdateControlBarMenu)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{	
	ID_SEPARATOR,           // status line indicator	
	ID_INDICATOR_TIME,      // time
	ID_INDICATOR_DATE,      // date
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,		
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_pAppView=NULL;	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetPaneInfo(2,ID_INDICATOR_TIME,0,75);       //statubar time
	m_wndStatusBar.SetPaneInfo(3,ID_INDICATOR_DATE,0,75);       //statubar date	

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	m_ImageList.Create(IDB_IMAGELIST, 13, 2, RGB(0,255,0));
//	InstallCoolMenus(this, IDR_MAINFRAME);
	{
		m_wndOutput.SetBtnImageList (&m_ImageList);		
		m_wndOutputCom.SetBtnImageList (&m_ImageList);		
				
		// Initialize dialog bar m_wndWorkspace
		if (!m_wndOutput.Create(this, CG_OUTPUT_DLG,_T("信息窗口"), CSize(200,200)))
		{
			TRACE0("创建信息窗口错误\n");
			return -1;	
		}
		

		// Add the views to the tab control.
		m_wndOutput.AddView(_T("操作日志"),RUNTIME_CLASS(CViewLog));
		m_wndOutput.AddView(_T("发送数据"), RUNTIME_CLASS(CViewSendData));
		m_wndOutput.AddView(_T("接收数据"),RUNTIME_CLASS(CViewReceiveData));
		m_wndOutput.AddView(_T("GPS数据"),RUNTIME_CLASS(CViewReceivePosition));
		m_wndOutput.AddView(_T("NEMA语句"),RUNTIME_CLASS(CViewNemaData));

		
		// Define the image list to use with the tab control		
	    // allow bar to be resized when floating
	    m_wndOutput.SetBarStyle(m_wndOutput.GetBarStyle() |
		    CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);		
	
		m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
		
		EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&m_wndOutput, AFX_IDW_DOCKBAR_BOTTOM);
		m_wndOutput.ShowWindow(SW_SHOW);	

		// Initialize dialog bar m_wndWorkspace
		if (!m_wndOutputCom.Create(this, CG_OUTPUT_DLG1,_T("COM端口"), CSize(300,400)))
		{
			TRACE0("创建COM端口错误\n");
			return -1;		// fail to create
		}

		// Add the views to the tab control.
		m_wndOutputCom.AddView(_T("串口数据"), RUNTIME_CLASS(CViewComData));
		m_wndOutputCom.AddView(_T("COM端口"), RUNTIME_CLASS(CViewTreeCom));
	
		
		// Define the image list to use with the tab control		
	    // allow bar to be resized when floating
	    m_wndOutputCom.SetBarStyle(m_wndOutput.GetBarStyle() |
		    CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

		
		m_wndOutputCom.EnableDocking(CBRS_ALIGN_ANY);
		
		EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&m_wndOutputCom, AFX_IDW_DOCKBAR_LEFT);
		m_wndOutputCom.ShowWindow(SW_SHOW);			
	}

	
	StartTimer();
	SetActiveView(NULL);
	
	// CG: The following line was added by the Splash Screen component.
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	if (nIDEvent == EVENT_REFRESH_DATETIME)//statubar timer
	{
		char time[12];
		char date[12];
		CTime t=CTime::GetCurrentTime();		
		sprintf(time,"%02d:%02d:%02d",t.GetHour(),t.GetMinute(),t.GetSecond());
		sprintf(date,"%04d-%02d-%02d",t.GetYear(),t.GetMonth(),t.GetDay());
		m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_INDICATOR_TIME),time);
		m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_INDICATOR_DATE),date);		
	}
	else if (nIDEvent == EVENT_CHECK_SENDCOMDATA)
	{
		CGpsServerDoc* pDoc=(CGpsServerDoc*)GetCurrentDoc();
		if (pDoc == NULL) return;

		pDoc->FuncCommTimer();
	}
	
	CFrameWnd::OnTimer(nIDEvent);
}

CGpsServerView* CMainFrame::GetMainView()
{
	if(m_pAppView !=NULL ) return m_pAppView;
	CView* pWnd=GetActiveView();
	if(pWnd->GetSafeHwnd()==NULL) return NULL;
	CGpsServerView* pView = DYNAMIC_DOWNCAST(CGpsServerView, pWnd);
	return pView;
}

void CMainFrame::SetView(CGpsServerView *view)
{
	m_pAppView=view;
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default		

	StopTimer();
	
	CFrameWnd::OnClose();
}



void CMainFrame::OnSetFocus(CWnd* pOldWnd) 
{
	CFrameWnd::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	CGpsServerView* view=GetMainView();
	if(view->GetSafeHwnd())	//view->SetFocus();	
		SetActiveView(view,true);	
}


CGpsServerDoc* CMainFrame::GetCurrentDoc()
{
	CGpsServerView* pView=GetMainView();
	if (pView == NULL) return NULL;
	
	return (CGpsServerDoc*)pView->GetDocument();	
}

void CMainFrame::OnUpdateComClose(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (pCmdUI == NULL) return;
	CGpsServerDoc* pDoc=(CGpsServerDoc*)GetCurrentDoc();
	if(pDoc==NULL) return;
	if (pDoc->m_bCom) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);
	
}


CCJTabCtrlBar* CMainFrame::GetWndOutputCom()
{
	return &m_wndOutputCom;
}

CCJTabCtrlBar* CMainFrame::GetWndOutput()
{
	return &m_wndOutput;
}


void CMainFrame::OnSystemClearLog() 
{
	// TODO: Add your command handler code here
	CViewLog* pView=(CViewLog*)GetWndOutput()->GetView(RUNTIME_CLASS(CViewLog));
	if (pView==NULL) return;

	pView->ClearLogs();
}


///////////////////////////////////////////////////////////////////
// 函数名：	OnComClose
// 功  能：	关闭串口菜单响应处理函数
// 参  数：	
// 返回值：	
// 备  注：
//////////////////////////////////////////////////////////////////   
void CMainFrame::OnComClose() 
{
	// TODO: Add your command handler code here
	CDlgComConfig dlg;
	if (dlg.DoModal()==IDOK)
	{
		CGpsServerDoc* pDoc=GetCurrentDoc();	
		if (pDoc==NULL) return;

		CString com = dlg.m_strCom;
		
		if(pDoc->CloseComWorkFlow(com)) 
		{			
			WriteLog(LOG_LEVEL_PROMPT,"关闭串口%s成功", com);			
		}
		else 
		{
			WriteLog(LOG_LEVEL_ERROR,"关闭串口%s错误", com);				
		}
	}
}

//////////////////////////////////////////////////
// 函数名：OnComOpen
// 功  能：打开串口菜单响应处理函数
// 参  数：	
// 返回值：
// 备  注：
//////////////////////////////////////////////////
void CMainFrame::OnComOpen() 
{
	// TODO: Add your command handler code here
	CDlgComConfig dlg;
	if (dlg.DoModal()==IDOK)
	{		
		CString com = dlg.m_strCom;
		CGpsServerDoc* pDoc=GetCurrentDoc();
		if (pDoc==NULL) return;

		if (pDoc->OpenComWorkFlow(com))
		{			
			WriteLog(LOG_LEVEL_PROMPT,"打开串口%s成功", com);			
		}
		else 
		{
			WriteLog(LOG_LEVEL_ERROR,"打开串口%s错误", com);				
		}
	}	
}

//////////////////////////////////////////////////
// 函数名：WriteLog
// 功  能：往视图中写日志
// 参  数：	level--字符串，日志级别
//			pstrFormat--LPCTSTR，日志信息
// 返回值：
// 备  注：
//////////////////////////////////////////////////
void CMainFrame::WriteLog(CString level, LPCTSTR pstrFormat, ...)
{
	CViewLog* pView=(CViewLog*)GetWndOutput()->GetView(RUNTIME_CLASS(CViewLog));
	if (pView==NULL) return;

	// 将日志写入输出窗口
	CString log;

	va_list args;
    va_start(args, pstrFormat);
    log.FormatV(pstrFormat, args);

	pView->InsertLog(level, log);
}

void CMainFrame::WriteSendLog(CSendObject* obj)
{
	CViewSendData* pView = (CViewSendData*)GetWndOutput()->GetView(RUNTIME_CLASS(CViewSendData));
	if (pView == NULL) return;

	pView->InsertSendLog(obj->m_Com, obj->command);
}


void CMainFrame::WriteComWorkFlowLog(CComWorkFlow* obj, BOOL bAdd)
{
	CViewTreeCom* pView = (CViewTreeCom*)GetWndOutputCom()->GetView(RUNTIME_CLASS(CViewTreeCom));
	if (pView == NULL) return;

	if (bAdd)
	{
		pView->InsertCom(obj);
	}
	else
	{
		pView->DeleteCom(obj);
	}
}



int CMainFrame::GetViewComData(CString com)
{
	int viewCount = m_wndOutputCom.m_tabctrl.GetItemCount();
	for (int i = 0;i<viewCount; i++)
	{
		CView* pView = m_wndOutputCom.GetView(i);
		if (pView == NULL) continue;
		if (pView->IsKindOf(RUNTIME_CLASS(CViewComData)))			
		{
			return i;		
		}
	}
	return -1;
}

BOOL CMainFrame::AddViewComData(CString com)
{
	CViewComData* pView=(CViewComData*)GetWndOutputCom()->GetView(RUNTIME_CLASS(CViewComData));	
	if (pView == NULL) return FALSE;

	pView->m_Com = com;
	pView->UpdateData(FALSE);
	CGpsServerDoc* pDoc=(CGpsServerDoc*)GetCurrentDoc();
	if (pDoc==NULL) return FALSE;	
	return TRUE;
}

void CMainFrame::MsgSendData(WPARAM wp,LPARAM lp)
{
	// TODO: Add your specialized code here and/or call the base class
	if ((lp==NULL) || (wp==NULL)) return ;
	
	CSendObject* pObj = new CSendObject();
	pObj->m_Com = *(CString*)wp;
	sprintf(pObj->command, "%s", *(CString*)lp);
				
	AddSendData(pObj);
}

BOOL CMainFrame::AddSendData(CSendObject* pObj)
{
	CGpsServerDoc* pDoc=GetCurrentDoc();
	if (pDoc == NULL) return FALSE;

	WaitForSingleObject(pDoc->MutexObject[0],INFINITE);		
	pDoc->m_CommandList.Add(pObj);
	ReleaseMutex(pDoc->MutexObject[0]);
	WriteSendLog(pObj);

	return TRUE;
}

void CMainFrame::MsgDecodedNemaSentence(WPARAM wp,LPARAM lp)
{
	CString* pTitle = (CString*)wp;
	GPSPack* pack = (GPSPack*)lp;
	if ((pack->GPS_NEMA_TEXT.bodyType == NEMATYPE_TEXT_POS)
		|| (pack->GPS_NEMA_GPGGA.bodyType == NEMATYPE_STANDARD_GPGGA)
		|| (pack->GPS_NEMA_GPRMC.bodyType == NEMATYPE_STANDARD_GPRMC)
		|| (pack->GPS_NEMA_PGRMF.bodyType == NEMATYPE_STANDARD_GPGLL)
		|| (pack->GPS_NEMA_PGRMF.bodyType == NEMATYPE_STANDARD_GPZDA)
		|| (pack->GPS_NEMA_PGRMF.bodyType == NEMATYPE_GARMIN_PGRMF)
		|| (pack->GPS_NEMA_PGRMF.bodyType == NEMATYPE_GARMIN_PGRMV))
	{
		CViewReceivePosition* pView = (CViewReceivePosition*)GetWndOutput()->GetView(RUNTIME_CLASS(CViewReceivePosition));
		if (pView == NULL) return;
		pView->InsertPosition(*pTitle, pack);

		CGpsServerView* pMap = (CGpsServerView*)GetMainView();
		if (pMap == NULL) return;
		pMap->DrawPositionOnMap(pack);
	}
	else 
	{	
		CViewNemaData* pNemaView = (CViewNemaData*)GetWndOutput()->GetView(RUNTIME_CLASS(CViewNemaData));
		if (pNemaView == NULL) return;

		pNemaView->InsertNema(*pTitle, pack);
	}
}

void CMainFrame::MsgSendDataResult(WPARAM wp,LPARAM lp)
{
	// TODO: Add your specialized code here and/or call the base class
	CViewSendData* pView = (CViewSendData*)GetWndOutput()->GetView(RUNTIME_CLASS(CViewSendData));
	if (pView == NULL) return;

	CString* pTitle = (CString*)wp;
	CString* pContent = (CString*)lp;
	if ((pTitle != NULL) && (pContent != NULL))
	{
		pView->InsertSendLog(*pTitle, *pContent);
	}	
}

void CMainFrame::MsgReceiveDataResult(WPARAM wp, LPARAM lp)
{
	// TODO: Add your specialized code here and/or call the base class
	CString* pTitle = (CString*)wp;
	CString* pContent = (CString*)lp;

	CViewComData* pViewCom = (CViewComData*)GetWndOutputCom()->GetView(RUNTIME_CLASS(CViewComData));
	if (pViewCom != NULL) 
	{
		if ((pTitle != NULL) && (pContent != NULL))
		{
			pViewCom->InsertReceiveData(*pTitle, *pContent);
		}
	}

	CViewReceiveData* pView = (CViewReceiveData*)GetWndOutput()->GetView(RUNTIME_CLASS(CViewReceiveData));
	if (pView == NULL) return;
	
	if ((pTitle != NULL) && (pContent != NULL))
	{
		pView->InsertReceiveLog(*pTitle, *pContent);
	}	
}


void CMainFrame::StartTimer()
{
	// 时间状态栏更新
	SetTimer(EVENT_REFRESH_DATETIME, EVENT_INTERVAL_REFRESH_DATETIME, 0);
	// 数据发送检查
	SetTimer(EVENT_CHECK_SENDCOMDATA, EVENT_INTERVAL_CHECK_SENDCOMDATA, 0);
}

void CMainFrame::StopTimer()
{
	KillTimer(EVENT_CHECK_SENDCOMDATA);
	KillTimer(EVENT_REFRESH_DATETIME);	
}

