// ex38bView.cpp : implementation of the CEx38bView class
//

#include "stdafx.h"
#include "ex38b.h"

#include "ex38bDoc.h"
#include "ex38bView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx38bView

IMPLEMENT_DYNCREATE(CEx38bView, CView)

BEGIN_MESSAGE_MAP(CEx38bView, CView)
	//{{AFX_MSG_MAP(CEx38bView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx38bView construction/destruction

CEx38bView::CEx38bView()
{
	// TODO: add construction code here

}

CEx38bView::~CEx38bView()
{
}

BOOL CEx38bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx38bView drawing

void CEx38bView::OnDraw(CDC* pDC)
{
	CEx38bDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx38bView diagnostics

#ifdef _DEBUG
void CEx38bView::AssertValid() const
{
	CView::AssertValid();
}

void CEx38bView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx38bDoc* CEx38bView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx38bDoc)));
	return (CEx38bDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx38bView message handlers
