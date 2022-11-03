// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "switch.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "switchView.h"
#include "switchView1.h"
#include "switchView2.h"

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_SWITCH_VIEW1, OnSwitchView1)
	ON_COMMAND(ID_SWITCH_VIEW2, OnSwitchView2)
	ON_UPDATE_COMMAND_UI(ID_SWITCH_VIEW2, OnUpdateSwitchView2)
	ON_UPDATE_COMMAND_UI(ID_SWITCH_VIEW1, OnUpdateSwitchView1)
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
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
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

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFrameWnd::PreCreateWindow(cs);
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

void CMainFrame::OnSwitchView1() 
{
	// TODO: Add your command handler code here
   CRect cr;	
   GetClientRect(&cr);	
   CSize paneSize1(3*cr.Width()/4, cr.Height());
	CCreateContext Context;	
   Context.m_pNewViewClass=RUNTIME_CLASS(CSwitchView1);
	Context.m_pCurrentDoc=((CSwitchApp*)AfxGetApp())->m_pDoc;
	Context.m_pCurrentFrame=this;
	Context.m_pNewDocTemplate=Context.m_pCurrentDoc->GetDocTemplate();
	Context.m_pLastView=(CView*)m_wndSplitter.GetPane(0,0);
	m_wndSplitter.DeleteView(0, 1);
	m_wndSplitter.CreateView(0, 1,RUNTIME_CLASS(CSwitchView1),paneSize1, &Context);
	CSwitchView1 *pView=(CSwitchView1*)m_wndSplitter.GetPane(0,1);
	pView->GetParentFrame()->RecalcLayout();	
   m_wndSplitter.RecalcLayout();
	pView->OnInitialUpdate(); 	
   m_wndSplitter.SetActivePane(0,1);	
}

void CMainFrame::OnSwitchView2() 
{
	// TODO: Add your command handler code here
   CRect cr;	
   GetClientRect(&cr);	
   CSize paneSize1(3*cr.Width()/4, cr.Height());
	CCreateContext Context;	
   Context.m_pNewViewClass=RUNTIME_CLASS(CSwitchView2);
	Context.m_pCurrentDoc=((CSwitchApp*)AfxGetApp())->m_pDoc;
	Context.m_pCurrentFrame=this;
	Context.m_pNewDocTemplate=Context.m_pCurrentDoc->GetDocTemplate();
	Context.m_pLastView=(CView*)m_wndSplitter.GetPane(0,0);
	m_wndSplitter.DeleteView(0, 1);
	m_wndSplitter.CreateView(0, 1,RUNTIME_CLASS(CSwitchView2),paneSize1, &Context);
	CSwitchView2 *pView=(CSwitchView2*)m_wndSplitter.GetPane(0,1);
	pView->GetParentFrame()->RecalcLayout();	
   m_wndSplitter.RecalcLayout();
	pView->OnInitialUpdate(); 	
   m_wndSplitter.SetActivePane(0,1);		
}

void CMainFrame::OnUpdateSwitchView2(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
pCmdUI->Enable(!m_wndSplitter.GetPane(0,1)->IsKindOf( RUNTIME_CLASS(CSwitchView2))); 		
}

void CMainFrame::OnUpdateSwitchView1(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
pCmdUI->Enable(!m_wndSplitter.GetPane(0,1)->IsKindOf( RUNTIME_CLASS(CSwitchView1))); 	
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	CRect cr;	
   BOOL rc;	
   if (!m_wndSplitter.CreateStatic(this,1,2)){
		TRACE0("Failed to create split bar ");		
      return FALSE; // failed to create	
   }
	GetClientRect(&cr);	
   CSize paneSize(cr.Width()/4, cr.Height());
	CSize paneSize1(3*cr.Width()/4, cr.Height());
	((CSwitchApp*)AfxGetApp())->m_pDoc=(CSwitchDoc*)(pContext->m_pCurrentDoc);
	pContext->m_pCurrentFrame=this;
	rc=m_wndSplitter.CreateView(0, 0,pContext->m_pNewViewClass,paneSize, pContext);
	if(!rc)return FALSE;	
   pContext->m_pNewViewClass=RUNTIME_CLASS(CSwitchView1);
	pContext->m_pCurrentDoc=((CSwitchApp*)AfxGetApp())->m_pDoc;
	pContext->m_pCurrentFrame=this;
	rc=m_wndSplitter.CreateView(0,1,pContext->m_pNewViewClass,paneSize1,pContext);
	m_wndSplitter.RecalcLayout();	
   m_wndSplitter.SetActivePane(0,1);
   return rc;
}
