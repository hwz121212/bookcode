// ex38aView.cpp : implementation of the CEx38aView class
//

#include "stdafx.h"
#include "ex38a.h"

#include "ex38aDoc.h"
#include "ex38aView.h"
#include "Ex38aDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx38aView

IMPLEMENT_DYNCREATE(CEx38aView, CView)

BEGIN_MESSAGE_MAP(CEx38aView, CView)
	//{{AFX_MSG_MAP(CEx38aView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx38aView construction/destruction

CEx38aView::CEx38aView()
{
	// TODO: add construction code here

}

CEx38aView::~CEx38aView()
{
}

BOOL CEx38aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx38aView drawing

void CEx38aView::OnDraw(CDC* pDC)
{

	CRect rect;
	GetClientRect(rect);

	pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
	pDC->SetBkMode(TRANSPARENT);

	pDC->DrawText(_T("Press the left mouse button here."), 
		rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

/////////////////////////////////////////////////////////////////////////////
// CEx38aView diagnostics

#ifdef _DEBUG
void CEx38aView::AssertValid() const
{
	CView::AssertValid();
}

void CEx38aView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx38aDoc* CEx38aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx38aDoc)));
	return (CEx38aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx38aView message handlers

void CEx38aView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CEx38aDialog dlg;
	dlg.DoModal();
	CView::OnLButtonDown(nFlags, point);
}
