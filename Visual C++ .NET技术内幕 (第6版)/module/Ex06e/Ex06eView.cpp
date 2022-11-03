// Ex06eView.cpp : implementation of the CEx06eView class
//

#include "stdafx.h"
#include "Ex06e.h"

#include "Ex06eDoc.h"
#include "Ex06eView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx06eView

IMPLEMENT_DYNCREATE(CEx06eView, CView)

BEGIN_MESSAGE_MAP(CEx06eView, CView)
END_MESSAGE_MAP()

// CEx06eView construction/destruction

CEx06eView::CEx06eView()
{
	// TODO: add construction code here

}

CEx06eView::~CEx06eView()
{
}

BOOL CEx06eView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEx06eView drawing

void CEx06eView::OnDraw(CDC* pDC)
{
	CEx06eDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
    pDC->TextOut(0, 0, "Choose About from the Help menu.");
}


// CEx06eView diagnostics

#ifdef _DEBUG
void CEx06eView::AssertValid() const
{
	CView::AssertValid();
}

void CEx06eView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx06eDoc* CEx06eView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx06eDoc)));
	return (CEx06eDoc*)m_pDocument;
}
#endif //_DEBUG


// CEx06eView message handlers
