// ex12bView.cpp : implementation of the CEx12bView class
//

#include "stdafx.h"
#include "ex12b.h"

#include "ex12bDoc.h"
#include "ex12bView.h"
#include "ComputeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx12bView

IMPLEMENT_DYNCREATE(CEx12bView, CView)

BEGIN_MESSAGE_MAP(CEx12bView, CView)
	//{{AFX_MSG_MAP(CEx12bView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx12bView construction/destruction

CEx12bView::CEx12bView()
{
	// TODO: add construction code here

}

CEx12bView::~CEx12bView()
{
}

BOOL CEx12bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx12bView drawing

void CEx12bView::OnDraw(CDC* pDC)
{
	pDC->TextOut(0, 0, "Press the left mouse button here.");
}

/////////////////////////////////////////////////////////////////////////////
// CEx12bView diagnostics

#ifdef _DEBUG
void CEx12bView::AssertValid() const
{
	CView::AssertValid();
}

void CEx12bView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx12bDoc* CEx12bView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx12bDoc)));
	return (CEx12bDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx12bView message handlers

void CEx12bView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CComputeDlg dlg;
	dlg.DoModal();
}
