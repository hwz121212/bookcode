// ex09aView.cpp : implementation of the CEx09aView class
//

#include "stdafx.h"
#include "ex09a.h"

#include "ex09aDoc.h"
#include "ex09aView.h"
#include "dialog1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx09aView

IMPLEMENT_DYNCREATE(CEx09aView, CView)

BEGIN_MESSAGE_MAP(CEx09aView, CView)
	//{{AFX_MSG_MAP(CEx09aView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////
// CEx09aView drawing

void CEx09aView::OnDraw(CDC* pDC)
{
	CEx09aDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDC->TextOut(0, 0, "Press the left mouse button here.");

}

/////////////////////////////////////////////////////////////////////////////
// CEx09aView printing

BOOL CEx09aView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx09aView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx09aView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
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

CEx09aDoc* CEx09aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx09aDoc)));
	return (CEx09aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx09aView message handlers

void CEx09aView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CDialog1 dlg;
	dlg.DoModal();
	CView::OnLButtonDown(nFlags, point);
}
