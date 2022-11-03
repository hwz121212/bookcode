// Ex09aView.cpp : implementation of the CEx09aView class
//

#include "stdafx.h"
#include "Ex09a.h"
#include "ActiveXDialog.h"

#include "Ex09aDoc.h"
#include "Ex09aView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx09aView

IMPLEMENT_DYNCREATE(CEx09aView, CView)

BEGIN_MESSAGE_MAP(CEx09aView, CView)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CEx09aView construction/destruction

CEx09aView::CEx09aView()
{
	// TODO: add construction code here

}

CEx09aView::~CEx09aView()
{
}

BOOL CEx09aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEx09aView drawing

void CEx09aView::OnDraw(CDC* pDC)
{
	pDC->TextOut(0, 0, "Press the left mouse button here.");
}


// CEx09aView diagnostics

#ifdef _DEBUG
void CEx09aView::AssertValid() const
{
	CView::AssertValid();
}

void CEx09aView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx09aDoc* CEx09aView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx09aDoc)));
	return (CEx09aDoc*)m_pDocument;
}
#endif //_DEBUG


// CEx09aView message handlers

void CEx09aView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CActiveXDialog dlg;
    dlg.m_BackColor = RGB(255, 251, 240); // light yellow
    COleDateTime today = COleDateTime::GetCurrentTime();
    dlg.m_varValue = COleDateTime(today.GetYear(), today.GetMonth(),
                                  today.GetDay(), 0, 0, 0);
    if (dlg.DoModal() == IDOK) {
        COleDateTime date(dlg.m_varValue);
        AfxMessageBox(date.Format("%B %d, %Y"));

	}

}
