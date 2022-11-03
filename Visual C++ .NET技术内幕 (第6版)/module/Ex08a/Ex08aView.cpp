// Ex08aView.cpp : implementation of the CEx08aView class
//

#include "stdafx.h"
#include "Ex08a.h"

#include "Ex08aDoc.h"
#include "Ex08aView.h"
#include "Ex08aDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx08aView

IMPLEMENT_DYNCREATE(CEx08aView, CView)

BEGIN_MESSAGE_MAP(CEx08aView, CView)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CEx08aView construction/destruction

CEx08aView::CEx08aView()
{
	// TODO: add construction code here

}

CEx08aView::~CEx08aView()
{
}

BOOL CEx08aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEx08aView drawing

void CEx08aView::OnDraw(CDC* pDC)
{
	CEx08aDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    pDC->TextOut(0, 0, "Press the left mouse button here.");
}


// CEx08aView diagnostics

#ifdef _DEBUG
void CEx08aView::AssertValid() const
{
	CView::AssertValid();
}

void CEx08aView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx08aDoc* CEx08aView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx08aDoc)));
	return (CEx08aDoc*)m_pDocument;
}
#endif //_DEBUG


// CEx08aView message handlers

void CEx08aView::OnLButtonDown(UINT nFlags, CPoint point)
{
    CEx08aDialog dlg;

    dlg.m_nSlider1 = 20;
    dlg.m_nSlider2 = 2; // index for 8.0
    dlg.m_nProgress = 70; // write-only
    dlg.m_dSpin = 3.2;

    dlg.DoModal();

	CView::OnLButtonDown(nFlags, point);
}
