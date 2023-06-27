// ex12aView.cpp : implementation of the CEx12aView class
//

#include "stdafx.h"
#include "ex12a.h"

#include "ex12aDoc.h"
#include "ex12aView.h"
#include "ComputeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx12aView

IMPLEMENT_DYNCREATE(CEx12aView, CView)

BEGIN_MESSAGE_MAP(CEx12aView, CView)
	//{{AFX_MSG_MAP(CEx12aView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx12aView construction/destruction

CEx12aView::CEx12aView()
{
	// TODO: add construction code here

}

CEx12aView::~CEx12aView()
{
}

BOOL CEx12aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx12aView drawing

void CEx12aView::OnDraw(CDC* pDC)
{
    pDC->TextOut(0, 0, "Press the left mouse button here.");
}

/////////////////////////////////////////////////////////////////////////////
// CEx12aView diagnostics

#ifdef _DEBUG
void CEx12aView::AssertValid() const
{
	CView::AssertValid();
}

void CEx12aView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx12aDoc* CEx12aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx12aDoc)));
	return (CEx12aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx12aView message handlers

void CEx12aView::OnLButtonDown(UINT nFlags, CPoint point) 
{
    CComputeDlg dlg;
    dlg.DoModal();
}
