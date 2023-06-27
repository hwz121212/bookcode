// ex14bView.cpp : implementation of the CEx14bView class
//

#include "stdafx.h"
#include "ex14b.h"

#include "ex14bDoc.h"
#include "ex14bView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx14bView

IMPLEMENT_DYNCREATE(CEx14bView, CView)

BEGIN_MESSAGE_MAP(CEx14bView, CView)
	//{{AFX_MSG_MAP(CEx14bView)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx14bView construction/destruction

CEx14bView::CEx14bView()
{
	// TODO: add construction code here

}

CEx14bView::~CEx14bView()
{
}

BOOL CEx14bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx14bView drawing

void CEx14bView::OnDraw(CDC* pDC)
{
    pDC->TextOut(0, 0,
        "Watch the status bar while you move and click the mouse.");
}

/////////////////////////////////////////////////////////////////////////////
// CEx14bView diagnostics

#ifdef _DEBUG
void CEx14bView::AssertValid() const
{
	CView::AssertValid();
}

void CEx14bView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx14bDoc* CEx14bView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx14bDoc)));
	return (CEx14bDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx14bView message handlers

void CEx14bView::OnMouseMove(UINT nFlags, CPoint point) 
{
    CString str;
    CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
    CStatusBar* pStatus = &pFrame->m_wndStatusBar;
    if (pStatus) {
        str.Format("x = %d", point.x);
        pStatus->SetPaneText(0, str);
        str.Format("y = %d", point.y);
        pStatus->SetPaneText(1, str);
    }
}
