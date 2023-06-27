// ex15aView.cpp : implementation of the CEx15aView class
//

#include "stdafx.h"
#include "ex15a.h"

#include "ex15aDoc.h"
#include "ex15aView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx15aView

IMPLEMENT_DYNCREATE(CEx15aView, CView)

BEGIN_MESSAGE_MAP(CEx15aView, CView)
	//{{AFX_MSG_MAP(CEx15aView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx15aView construction/destruction

CEx15aView::CEx15aView()
{
	// TODO: add construction code here

}

CEx15aView::~CEx15aView()
{
}

BOOL CEx15aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx15aView drawing

void CEx15aView::OnDraw(CDC* pDC)
{
	CEx15aDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx15aView diagnostics

#ifdef _DEBUG
void CEx15aView::AssertValid() const
{
	CView::AssertValid();
}

void CEx15aView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx15aDoc* CEx15aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx15aDoc)));
	return (CEx15aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx15aView message handlers
