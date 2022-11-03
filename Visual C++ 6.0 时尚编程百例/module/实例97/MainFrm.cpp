// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ClientNet.h"

#include "MainFrm.h"
#include "ConnectDlg.h"

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
	ON_COMMAND(ID_OPEN, OnOpen)
	ON_COMMAND(ID_CLOSE, OnClose)
	ON_COMMAND(ID_INFO_SEND, OnInfoSend)

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
	m_pSocket=NULL;
	m_Server="";
	m_Port=700;
	
}

CMainFrame::~CMainFrame()
{
	if(m_pSocket)
		delete m_pSocket;
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


void CMainFrame::OnOpen() 
{
	if(m_pSocket)
	{
		MessageBox("已经连接到服务器,请关闭连接再试一次!","警告信息",MB_OK);
		return;
	}
	CConnectDlg dlg1;
	if(dlg1.DoModal()==IDOK)
	{
		m_Server=dlg1.m_server ;
		m_Port=dlg1.m_port;
		m_pSocket=new CRequest(this);
		if(!(m_pSocket=ConnectServer()))
		{
			m_pSocket=NULL;
			return;
		}
	}
}

void CMainFrame::OnClose() 
{
	if(m_pSocket)
	{
		delete m_pSocket;
		m_pSocket=NULL;
	}
	else
		MessageBox("没有连接到任何服务器","警告信息",MB_OK);
}

void CMainFrame::OnInfoSend() 
{
	if(!m_pSocket)
	{
		MessageBox("没有连接到任何服务器","警告信息",MB_OK);
		return;
	}
	
	dlg2.DoModal();
		
}
//向服务器发送信息
void CMainFrame::SendMsg(CRequest *pRequest,char *pMsg)
{
	pRequest->Send(pMsg,strlen(pMsg));
}
CRequest *CMainFrame::ConnectServer()
{
	CRequest *pSocket=new CRequest(this);
	if(!(pSocket->Create()))
	{
		delete pSocket;
		MessageBox("创建Socket失败","警告信息",MB_OK);
        return NULL;
	}
	//连接到服务器
	if(!pSocket->Connect(m_Server,m_Port))
	{
		delete pSocket;
		MessageBox("请求连接到服务器失败","警告信息",MB_OK);
        return NULL;
	}
	return pSocket;
}
void CMainFrame::FetchMsg(CRequest *pRequest)
{
	char pMsg[10000],tempMsg[1000];
	int ByteCount;
	int End=0;
	CStringArray *temp=new CStringArray;
	strcpy(pMsg,"");
	do
	{
		strcpy(tempMsg,"");
		ByteCount=pRequest->Receive(tempMsg,1000);
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
	dlg2.m_acceptedit=pMsg;
	
}
