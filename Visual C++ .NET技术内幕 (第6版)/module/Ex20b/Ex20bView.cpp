// Ex20bView.cpp : implementation of the CEx20bView class
//

#include "stdafx.h"
#include "Ex20b.h"

#include "Ex20bDoc.h"
#include "Ex20bView.h"
#include "Test20cDialog.h"
#include "Test20dDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx20bView

IMPLEMENT_DYNCREATE(CEx20bView, CView)

BEGIN_MESSAGE_MAP(CEx20bView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(ID_TEST_EX20CDLL, OnTestEx20cdll)
	ON_COMMAND(ID_TEST_EX20DDLL, OnTestEx20ddll)
END_MESSAGE_MAP()

// CEx20bView construction/destruction

CEx20bView::CEx20bView()
{
	// TODO: add construction code here

}

CEx20bView::~CEx20bView()
{
}

BOOL CEx20bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEx20bView drawing

void CEx20bView::OnDraw(CDC* /*pDC*/)
{
	CEx20bDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


// CEx20bView printing

BOOL CEx20bView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx20bView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx20bView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CEx20bView diagnostics

#ifdef _DEBUG
void CEx20bView::AssertValid() const
{
	CView::AssertValid();
}

void CEx20bView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx20bDoc* CEx20bView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx20bDoc)));
	return (CEx20bDoc*)m_pDocument;
}
#endif //_DEBUG


// CEx20bView message handlers

void CEx20bView::OnTestEx20cdll()
{
	CTest20cDialog dlg;
    dlg.DoModal();
}

void CEx20bView::OnTestEx20ddll()
{
	CTest20dDialog dlg;
    dlg.DoModal();
}
