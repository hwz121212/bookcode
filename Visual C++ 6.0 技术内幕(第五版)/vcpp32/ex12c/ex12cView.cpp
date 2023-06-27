// ex12cView.cpp : implementation of the CEx12cView class
//

#include "stdafx.h"
#include "ex12c.h"

#include "ex12cDoc.h"
#include "ex12cView.h"
#include "ComputeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx12cView

IMPLEMENT_DYNCREATE(CEx12cView, CView)

BEGIN_MESSAGE_MAP(CEx12cView, CView)
	//{{AFX_MSG_MAP(CEx12cView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx12cView construction/destruction

CEx12cView::CEx12cView()
{
	// TODO: add construction code here

}

CEx12cView::~CEx12cView()
{
}

BOOL CEx12cView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx12cView drawing

void CEx12cView::OnDraw(CDC* pDC)
{
	pDC->TextOut(0, 0, "Press the left mouse button here.");
}

/////////////////////////////////////////////////////////////////////////////
// CEx12cView diagnostics

#ifdef _DEBUG
void CEx12cView::AssertValid() const
{
	CView::AssertValid();
}

void CEx12cView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx12cDoc* CEx12cView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx12cDoc)));
	return (CEx12cDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx12cView message handlers

void CEx12cView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CComputeDlg dlg;
	dlg.DoModal();
}
