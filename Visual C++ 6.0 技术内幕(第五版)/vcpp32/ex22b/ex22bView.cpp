// ex22bView.cpp : implementation of the CEx22bView class
//

#include "stdafx.h"
#include "ex22b.h"

#include "ex22bDoc.h"
#include "ex22bView.h"
#include "Test22cDialog.h"
#include "Test22dDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx22bView

IMPLEMENT_DYNCREATE(CEx22bView, CView)

BEGIN_MESSAGE_MAP(CEx22bView, CView)
	//{{AFX_MSG_MAP(CEx22bView)
	ON_COMMAND(ID_TEST_EX22CDLL, OnTestEx22cdll)
	ON_COMMAND(ID_TEST_EX22DDLL, OnTestEx22ddll)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx22bView construction/destruction

CEx22bView::CEx22bView()
{
	// TODO: add construction code here

}

CEx22bView::~CEx22bView()
{
}

BOOL CEx22bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx22bView drawing

void CEx22bView::OnDraw(CDC* pDC)
{
	CEx22bDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx22bView printing

BOOL CEx22bView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx22bView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx22bView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEx22bView diagnostics

#ifdef _DEBUG
void CEx22bView::AssertValid() const
{
	CView::AssertValid();
}

void CEx22bView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx22bDoc* CEx22bView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx22bDoc)));
	return (CEx22bDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx22bView message handlers

void CEx22bView::OnTestEx22cdll() 
{
    CTest22cDialog dlg;
    dlg.DoModal();
	
}

void CEx22bView::OnTestEx22ddll() 
{
    CTest22dDialog dlg;
    dlg.DoModal();
	
}
