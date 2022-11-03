// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ServerNet.h"

#include "MainFrm.h"

#include "SetDlg.h"

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
	ON_COMMAND(ID_SET, OnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_pListening=NULL;
	m_pList.RemoveAll();
}

CMainFrame::~CMainFrame()
{
	delete m_pListening;
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

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

    OnSet();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
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


void CMainFrame::OnSet() 
{
	// TODO: Add your command handler code here
    CSetDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		m_pListening=new CLisent(this);
		if(m_pListening->Create(dlg.m_port))
		{
			if(!m_pListening->Listen())
			{
				MessageBox("端口设置错误!","网络信息",MB_OK);
			}
		}
	}
}

void CMainFrame::SendMsg(CClient *pClientSocket,char *pMsg)
{
	pClientSocket->Send(pMsg,strlen(pMsg));
}

void CMainFrame::FetchMsg(CClient *pClientSocket)
{
	char pMsg[10000],tempMsg[1000];
	int ByteCount;
	int End=0;
	char AnMsg[10100];
	
	strcpy(pMsg,"");
	do
	{
		strcpy(tempMsg,"");
		ByteCount=pClientSocket->Receive(tempMsg,1000);
		if(ByteCount>1000||ByteCount<=0)
		{
			MessageBox("接受网络信息发生错误","警告信息",MB_OK);
			return ;
        }
		else if(ByteCount<1000&&ByteCount>0)
		{
			End=1;
		}
		tempMsg[ByteCount]=0;
		strcat(pMsg,tempMsg);
	}while(End==0);

	MessageBox(pMsg,"网络信息",MB_OK);

	sprintf(AnMsg,"我们收到您发来的信息\n%s\n谢谢!",pMsg);
		SendMsg(pClientSocket,AnMsg);
}
