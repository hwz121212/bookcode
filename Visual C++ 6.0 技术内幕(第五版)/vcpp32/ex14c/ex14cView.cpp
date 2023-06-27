// ex14cView.cpp : implementation of the CEx14cView class
//

#include "stdafx.h"
#include "ex14c.h"

#include "ex14cDoc.h"
#include "ex14cView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx14cView

IMPLEMENT_DYNCREATE(CEx14cView, CView)

BEGIN_MESSAGE_MAP(CEx14cView, CView)
	//{{AFX_MSG_MAP(CEx14cView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx14cView construction/destruction

CEx14cView::CEx14cView()
{
	// TODO: add construction code here

}

CEx14cView::~CEx14cView()
{
}

BOOL CEx14cView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx14cView drawing

void CEx14cView::OnDraw(CDC* pDC)
{
	CEx14cDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx14cView printing

BOOL CEx14cView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx14cView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx14cView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEx14cView diagnostics

#ifdef _DEBUG
void CEx14cView::AssertValid() const
{
	CView::AssertValid();
}

void CEx14cView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx14cDoc* CEx14cView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx14cDoc)));
	return (CEx14cDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx14cView message handlers
