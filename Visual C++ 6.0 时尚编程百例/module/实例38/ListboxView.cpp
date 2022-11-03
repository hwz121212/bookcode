// ListboxView.cpp : implementation of the CListboxView class
//

#include "stdafx.h"
#include "Listbox.h"

#include "ListboxDoc.h"
#include "ListboxView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListboxView

IMPLEMENT_DYNCREATE(CListboxView, CView)

BEGIN_MESSAGE_MAP(CListboxView, CView)
	//{{AFX_MSG_MAP(CListboxView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListboxView construction/destruction

CListboxView::CListboxView()
{
	// TODO: add construction code here

}

CListboxView::~CListboxView()
{
}

BOOL CListboxView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CListboxView drawing

void CListboxView::OnDraw(CDC* pDC)
{
	CListboxDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CListboxView printing

BOOL CListboxView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CListboxView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CListboxView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CListboxView diagnostics

#ifdef _DEBUG
void CListboxView::AssertValid() const
{
	CView::AssertValid();
}

void CListboxView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CListboxDoc* CListboxView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CListboxDoc)));
	return (CListboxDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CListboxView message handlers
