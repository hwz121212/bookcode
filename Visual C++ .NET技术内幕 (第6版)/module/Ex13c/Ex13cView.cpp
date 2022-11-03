// Ex13cView.cpp : implementation of the CEx13cView class
//

#include "stdafx.h"
#include "Ex13c.h"

#include "Ex13cDoc.h"
#include "Ex13cView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx13cView

IMPLEMENT_DYNCREATE(CEx13cView, CView)

BEGIN_MESSAGE_MAP(CEx13cView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CEx13cView construction/destruction

CEx13cView::CEx13cView()
{
	// TODO: add construction code here

}

CEx13cView::~CEx13cView()
{
}

BOOL CEx13cView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEx13cView drawing

void CEx13cView::OnDraw(CDC* /*pDC*/)
{
	CEx13cDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


// CEx13cView printing

BOOL CEx13cView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx13cView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx13cView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CEx13cView diagnostics

#ifdef _DEBUG
void CEx13cView::AssertValid() const
{
	CView::AssertValid();
}

void CEx13cView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx13cDoc* CEx13cView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx13cDoc)));
	return (CEx13cDoc*)m_pDocument;
}
#endif //_DEBUG


// CEx13cView message handlers
