// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Toolbar.h"

#include "MainFrm.h"

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
	ON_COMMAND(ID_VIEWCOLORTOOLBAR, OnViewcolortoolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEWCOLORTOOLBAR, OnUpdateViewcolortoolbar)
	ON_WM_DESTROY()
	ON_COMMAND(ID_BUTTONBLUE, OnButtonblue)
	ON_COMMAND(ID_BUTTONGREEN, OnButtongreen)
	ON_COMMAND(ID_BUTTONRED, OnButtonred)
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
:m_pColorToolbar(0)
{
	// TODO: add member initialization code here
	
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


void CMainFrame::OnViewcolortoolbar() 
{
if(0==m_pColorToolbar)
{m_pColorToolbar=new CToolBar;
CString ErrMsg;
if(0==m_pColorToolbar->Create(this))
{  ErrMsg.LoadString(IDS_COLOR_CREATE);
::AfxMessageBox(ErrMsg);
   return ;
}
m_pColorToolbar->LoadToolBar(IDR_COLORTOOLBAR);
m_pColorToolbar->EnableDocking(CBRS_ALIGN_ANY);
DockControlBar(m_pColorToolbar);
}
else
    //if the window is visibble, hide it
	if(m_pColorToolbar->IsWindowVisible()==TRUE)
		ShowControlBar(m_pColorToolbar,FALSE,FALSE);
	else
		//Otherwise,show it.
		ShowControlBar(m_pColorToolbar,TRUE,TRUE);

}

void CMainFrame::OnUpdateViewcolortoolbar(CCmdUI* pCmdUI) 
{
if(0==m_pColorToolbar)
pCmdUI->SetCheck(FALSE);
	else
		if(m_pColorToolbar->IsWindowVisible()==TRUE)
			pCmdUI->SetCheck(TRUE);
		else
			pCmdUI->SetCheck(FALSE);

}

void CMainFrame::OnDestroy() 
{
	CFrameWnd::OnDestroy();
	
if(0!=m_pColorToolbar)
{
	delete m_pColorToolbar;
	m_pColorToolbar=0;
}
}

void CMainFrame::OnButtonblue() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnButtongreen() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnButtonred() 
{
	// TODO: Add your command handler code here
	
}
