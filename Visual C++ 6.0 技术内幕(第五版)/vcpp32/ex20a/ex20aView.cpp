// ex20aView.cpp : implementation of the CEx20aView class
//

#include "stdafx.h"
#include "ex20a.h"

#include "ex20aDoc.h"
#include "ex20aView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx20aView

IMPLEMENT_DYNCREATE(CEx20aView, CView)

BEGIN_MESSAGE_MAP(CEx20aView, CView)
	//{{AFX_MSG_MAP(CEx20aView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx20aView construction/destruction

CEx20aView::CEx20aView()
{
	// TODO: add construction code here

}

CEx20aView::~CEx20aView()
{
}

BOOL CEx20aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx20aView drawing

void CEx20aView::OnDraw(CDC* pDC)
{
	CEx20aDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx20aView printing

BOOL CEx20aView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx20aView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx20aView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEx20aView diagnostics

#ifdef _DEBUG
void CEx20aView::AssertValid() const
{
	CView::AssertValid();
}

void CEx20aView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx20aDoc* CEx20aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx20aDoc)));
	return (CEx20aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx20aView message handlers
