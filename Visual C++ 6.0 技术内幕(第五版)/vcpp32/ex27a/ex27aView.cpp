// ex27aView.cpp : implementation of the CEx27aView class
//

#include "stdafx.h"
#include "ex27a.h"

#include "ex27aDoc.h"
#include "ex27aView.h"
#include "Thread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx27aView

IMPLEMENT_DYNCREATE(CEx27aView, CView)

BEGIN_MESSAGE_MAP(CEx27aView, CView)
	//{{AFX_MSG_MAP(CEx27aView)
	ON_COMMAND(ID_STORAGE_READ, OnStorageRead)
	ON_COMMAND(ID_STORAGE_WRITE, OnStorageWrite)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx27aView construction/destruction

CEx27aView::CEx27aView()
{
	// TODO: add construction code here

}

CEx27aView::~CEx27aView()
{
}

BOOL CEx27aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx27aView drawing

void CEx27aView::OnDraw(CDC* pDC)
{
	CEx27aDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx27aView printing

BOOL CEx27aView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx27aView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx27aView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEx27aView diagnostics

#ifdef _DEBUG
void CEx27aView::AssertValid() const
{
	CView::AssertValid();
}

void CEx27aView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx27aDoc* CEx27aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx27aDoc)));
	return (CEx27aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx27aView message handlers

void CEx27aView::OnStorageRead() 
{
    CWinThread* pThread = AfxBeginThread(ReadThreadProc, GetSafeHwnd());	
}

void CEx27aView::OnStorageWrite() 
{
    CWinThread* pThread = AfxBeginThread(WriteThreadProc, GetSafeHwnd());	
}
