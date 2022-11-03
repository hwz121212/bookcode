// SystemTreeView.cpp : implementation of the CSystemTreeView class
//

#include "stdafx.h"
#include "SystemTree.h"

#include "SystemTreeDoc.h"
#include "SystemTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSystemTreeView

IMPLEMENT_DYNCREATE(CSystemTreeView, CView)

BEGIN_MESSAGE_MAP(CSystemTreeView, CView)
	//{{AFX_MSG_MAP(CSystemTreeView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSystemTreeView construction/destruction

CSystemTreeView::CSystemTreeView()
{
	// TODO: add construction code here

}

CSystemTreeView::~CSystemTreeView()
{
}

BOOL CSystemTreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSystemTreeView drawing

void CSystemTreeView::OnDraw(CDC* pDC)
{
	CSystemTreeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSystemTreeView printing

BOOL CSystemTreeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSystemTreeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSystemTreeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSystemTreeView diagnostics

#ifdef _DEBUG
void CSystemTreeView::AssertValid() const
{
	CView::AssertValid();
}

void CSystemTreeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSystemTreeDoc* CSystemTreeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSystemTreeDoc)));
	return (CSystemTreeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSystemTreeView message handlers
