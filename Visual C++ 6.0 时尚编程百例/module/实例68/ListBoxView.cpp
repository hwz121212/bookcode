// ListBoxView.cpp : implementation of the CListBoxView class
//

#include "stdafx.h"
#include "ListBox.h"

#include "ListBoxDoc.h"
#include "ListBoxView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListBoxView

IMPLEMENT_DYNCREATE(CListBoxView, CView)

BEGIN_MESSAGE_MAP(CListBoxView, CView)
	//{{AFX_MSG_MAP(CListBoxView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListBoxView construction/destruction

CListBoxView::CListBoxView()
{
	// TODO: add construction code here

}

CListBoxView::~CListBoxView()
{
}

BOOL CListBoxView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CListBoxView drawing

void CListBoxView::OnDraw(CDC* pDC)
{
	CListBoxDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CListBoxView printing

BOOL CListBoxView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CListBoxView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CListBoxView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CListBoxView diagnostics

#ifdef _DEBUG
void CListBoxView::AssertValid() const
{
	CView::AssertValid();
}

void CListBoxView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CListBoxDoc* CListBoxView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CListBoxDoc)));
	return (CListBoxDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CListBoxView message handlers
