// ex36aView.cpp : implementation of the CEx36aView class
//

#include "stdafx.h"
#include "ex36a.h"

#include "ex36aDoc.h"
#include "CntrItem.h"
#include "ex36aView.h"
#include "UrlThread.h"
#include "MainFrm.h"
#include "IpFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx36aView

IMPLEMENT_DYNCREATE(CEx36aView, CRichEditView)

BEGIN_MESSAGE_MAP(CEx36aView, CRichEditView)
	//{{AFX_MSG_MAP(CEx36aView)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearAll)
	ON_COMMAND(IDC_START, OnStart)
	ON_UPDATE_COMMAND_UI(IDC_START, OnUpdateStart)
	ON_COMMAND(IDC_STOP, OnStop)
	ON_UPDATE_COMMAND_UI(IDC_STOP, OnUpdateStop)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRichEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx36aView construction/destruction

CEx36aView::CEx36aView()
{
	// TODO: add construction code here

}

CEx36aView::~CEx36aView()
{
}

BOOL CEx36aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}

void CEx36aView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();

	// Set the printing margins (720 twips = 1/2 inch).
	SetMargins(CRect(720, 720, 720, 720));
}

/////////////////////////////////////////////////////////////////////////////
// CEx36aView printing

BOOL CEx36aView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}


/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void CEx36aView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CEx36aView diagnostics

#ifdef _DEBUG
void CEx36aView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CEx36aView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CEx36aDoc* CEx36aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx36aDoc)));
	return (CEx36aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx36aView message handlers

void CEx36aView::OnEditClearAll() 
{
	SetWindowText("");
}

void CEx36aView::OnStart() 
{
	CWnd* pFrm = GetParent(); // SDI only
	CWnd* pBar;
	if(pFrm->IsKindOf(RUNTIME_CLASS(CMainFrame))) {
		pBar = &((CMainFrame*) pFrm)->m_wndDialogBar;
	}
	else {
		pBar = &((CInPlaceFrame*) pFrm)->m_wndDialogBar;
	}
	// g_strURL: thread sync?
	pBar->GetDlgItemText(IDC_URL, g_strURL);
	TRACE("CEx36aView::OnRequest -- URL = %s\n", g_strURL);
	AfxBeginThread(UrlThreadProc, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}

void CEx36aView::OnStop() 
{
	g_eKill.SetEvent();
}

void CEx36aView::OnUpdateStop(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(g_bThreadStarted);
}

void CEx36aView::OnUpdateStart(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!g_bThreadStarted);
}

