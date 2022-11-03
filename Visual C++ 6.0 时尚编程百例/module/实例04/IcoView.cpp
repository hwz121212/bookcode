// IcoView.cpp : implementation of the CIcoView class
//

#include "stdafx.h"
#include "Ico.h"

#include "IcoDoc.h"
#include "IcoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIcoView

IMPLEMENT_DYNCREATE(CIcoView, CView)

BEGIN_MESSAGE_MAP(CIcoView, CView)
	//{{AFX_MSG_MAP(CIcoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIcoView construction/destruction

CIcoView::CIcoView()
{
	// TODO: add construction code here

}

CIcoView::~CIcoView()
{
}

BOOL CIcoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CIcoView drawing

void CIcoView::OnDraw(CDC* pDC)
{
	CIcoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CIcoView printing

BOOL CIcoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CIcoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CIcoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CIcoView diagnostics

#ifdef _DEBUG
void CIcoView::AssertValid() const
{
	CView::AssertValid();
}

void CIcoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIcoDoc* CIcoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIcoDoc)));
	return (CIcoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIcoView message handlers
