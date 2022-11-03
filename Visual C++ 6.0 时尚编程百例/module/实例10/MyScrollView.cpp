// MyScrollView.cpp : implementation of the CMyScrollView class
//

#include "stdafx.h"
#include "MyScroll.h"

#include "MyScrollDoc.h"
#include "MyScrollView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyScrollView

IMPLEMENT_DYNCREATE(CMyScrollView, CScrollView)

BEGIN_MESSAGE_MAP(CMyScrollView, CScrollView)
	//{{AFX_MSG_MAP(CMyScrollView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyScrollView construction/destruction

CMyScrollView::CMyScrollView()
{
	// TODO: add construction code here

}

CMyScrollView::~CMyScrollView()
{
}

BOOL CMyScrollView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyScrollView drawing

void CMyScrollView::OnDraw(CDC* pDC)
{
	CMyScrollDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDC->TextOut(30,30,"welcome to VC++");
	// TODO: add draw code for native data here
}

void CMyScrollView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 300;
	SetScrollSizes(MM_TEXT, sizeTotal);

//	GetParentFrame()->RecalcLayout();

	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CMyScrollView printing

BOOL CMyScrollView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyScrollView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyScrollView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyScrollView diagnostics

#ifdef _DEBUG
void CMyScrollView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMyScrollView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMyScrollDoc* CMyScrollView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyScrollDoc)));
	return (CMyScrollDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyScrollView message handlers

void CMyScrollView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
		GetParentFrame()->RecalcLayout();

//	ResizeParentToFit();
	Invalidate();
	CScrollView::OnLButtonDown(nFlags, point);
}
