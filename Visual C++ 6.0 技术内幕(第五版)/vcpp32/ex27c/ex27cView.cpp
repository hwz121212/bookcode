// ex27cView.cpp : implementation of the CEx27cView class
//

#include "stdafx.h"
#include "ex27c.h"

#include "ex27cDoc.h"
#include "ex27cView.h"
#include "Thread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx27cView

IMPLEMENT_DYNCREATE(CEx27cView, CView)

BEGIN_MESSAGE_MAP(CEx27cView, CView)
	//{{AFX_MSG_MAP(CEx27cView)
	ON_COMMAND(ID_STORAGE_READ, OnStorageRead)
	ON_COMMAND(ID_STORAGE_WRITE, OnStorageWrite)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx27cView construction/destruction

CEx27cView::CEx27cView()
{
	// TODO: add construction code here

}

CEx27cView::~CEx27cView()
{
}

BOOL CEx27cView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx27cView drawing

void CEx27cView::OnDraw(CDC* pDC)
{
	CEx27cDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx27cView printing

BOOL CEx27cView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx27cView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx27cView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEx27cView diagnostics

#ifdef _DEBUG
void CEx27cView::AssertValid() const
{
	CView::AssertValid();
}

void CEx27cView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx27cDoc* CEx27cView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx27cDoc)));
	return (CEx27cDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx27cView message handlers

void CEx27cView::OnStorageRead() 
{
    CWinThread* pThread = AfxBeginThread(ReadThreadProc, GetSafeHwnd());	
}

void CEx27cView::OnStorageWrite() 
{
    CWinThread* pThread = AfxBeginThread(WriteThreadProc, GetSafeHwnd());	
}
