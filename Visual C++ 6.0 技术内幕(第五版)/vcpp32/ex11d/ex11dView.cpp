// ex11dView.cpp : implementation of the CEx11dView class
//

#include "stdafx.h"
#include "ex11d.h"

#include "ex11dDoc.h"
#include "ex11dView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx11dView

IMPLEMENT_DYNCREATE(CEx11dView, CView)

BEGIN_MESSAGE_MAP(CEx11dView, CView)
	//{{AFX_MSG_MAP(CEx11dView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx11dView construction/destruction

CEx11dView::CEx11dView()
{
	// TODO: add construction code here

}

CEx11dView::~CEx11dView()
{
}

BOOL CEx11dView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx11dView drawing

void CEx11dView::OnDraw(CDC* pDC)
{
	pDC->TextOut(0, 0, "Choose About from the Help menu.");
}

/////////////////////////////////////////////////////////////////////////////
// CEx11dView diagnostics

#ifdef _DEBUG
void CEx11dView::AssertValid() const
{
	CView::AssertValid();
}

void CEx11dView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx11dDoc* CEx11dView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx11dDoc)));
	return (CEx11dDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx11dView message handlers
