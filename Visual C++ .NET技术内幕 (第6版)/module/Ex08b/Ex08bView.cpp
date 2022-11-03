// Ex08bView.cpp : implementation of the CEx08bView class
//

#include "stdafx.h"
#include "Ex08b.h"

#include "Ex08bDoc.h"
#include "Ex08bView.h"

#include "Ex08bDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx08bView

IMPLEMENT_DYNCREATE(CEx08bView, CView)

BEGIN_MESSAGE_MAP(CEx08bView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CEx08bView construction/destruction

CEx08bView::CEx08bView()
{
	// TODO: add construction code here

}

CEx08bView::~CEx08bView()
{
}

BOOL CEx08bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEx08bView drawing

void CEx08bView::OnDraw(CDC* pDC)
{
	CEx08bDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    pDC->TextOut(0, 0, "Press the left mouse button here.");
}


// CEx08bView printing

BOOL CEx08bView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx08bView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx08bView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CEx08bView diagnostics

#ifdef _DEBUG
void CEx08bView::AssertValid() const
{
	CView::AssertValid();
}

void CEx08bView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx08bDoc* CEx08bView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx08bDoc)));
	return (CEx08bDoc*)m_pDocument;
}
#endif //_DEBUG


// CEx08bView message handlers

void CEx08bView::OnLButtonDown(UINT nFlags, CPoint point)
{
    CEx08bDialog dlg;
    dlg.DoModal();

	CView::OnLButtonDown(nFlags, point);
}
