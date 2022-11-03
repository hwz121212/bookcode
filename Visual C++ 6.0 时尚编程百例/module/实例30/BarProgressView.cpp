// BarProgressView.cpp : implementation of the CBarProgressView class
//

#include "stdafx.h"
#include "BarProgress.h"

#include "BarProgressDoc.h"
#include "BarProgressView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBarProgressView

IMPLEMENT_DYNCREATE(CBarProgressView, CView)

BEGIN_MESSAGE_MAP(CBarProgressView, CView)
	//{{AFX_MSG_MAP(CBarProgressView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBarProgressView construction/destruction

CBarProgressView::CBarProgressView()
{
	// TODO: add construction code here

}

CBarProgressView::~CBarProgressView()
{
}

BOOL CBarProgressView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBarProgressView drawing

void CBarProgressView::OnDraw(CDC* pDC)
{
	CBarProgressDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CBarProgressView printing

BOOL CBarProgressView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBarProgressView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBarProgressView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBarProgressView diagnostics

#ifdef _DEBUG
void CBarProgressView::AssertValid() const
{
	CView::AssertValid();
}

void CBarProgressView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBarProgressDoc* CBarProgressView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBarProgressDoc)));
	return (CBarProgressDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBarProgressView message handlers
