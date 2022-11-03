// ToolbarView.cpp : implementation of the CToolbarView class
//

#include "stdafx.h"
#include "Toolbar.h"

#include "ToolbarDoc.h"
#include "ToolbarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolbarView

IMPLEMENT_DYNCREATE(CToolbarView, CView)

BEGIN_MESSAGE_MAP(CToolbarView, CView)
	//{{AFX_MSG_MAP(CToolbarView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolbarView construction/destruction

CToolbarView::CToolbarView()
{
	// TODO: add construction code here

}

CToolbarView::~CToolbarView()
{
}

BOOL CToolbarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CToolbarView drawing

void CToolbarView::OnDraw(CDC* pDC)
{
	CToolbarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CToolbarView printing

BOOL CToolbarView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CToolbarView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CToolbarView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CToolbarView diagnostics

#ifdef _DEBUG
void CToolbarView::AssertValid() const
{
	CView::AssertValid();
}

void CToolbarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToolbarDoc* CToolbarView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolbarDoc)));
	return (CToolbarDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CToolbarView message handlers
