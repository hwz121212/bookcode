// MyDialogBarView.cpp : implementation of the CMyDialogBarView class
//

#include "stdafx.h"
#include "MyDialogBar.h"

#include "MyDialogBarDoc.h"
#include "MyDialogBarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDialogBarView

IMPLEMENT_DYNCREATE(CMyDialogBarView, CView)

BEGIN_MESSAGE_MAP(CMyDialogBarView, CView)
	//{{AFX_MSG_MAP(CMyDialogBarView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDialogBarView construction/destruction

CMyDialogBarView::CMyDialogBarView()
{
	// TODO: add construction code here

}

CMyDialogBarView::~CMyDialogBarView()
{
}

BOOL CMyDialogBarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyDialogBarView drawing

void CMyDialogBarView::OnDraw(CDC* pDC)
{
	CMyDialogBarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMyDialogBarView diagnostics

#ifdef _DEBUG
void CMyDialogBarView::AssertValid() const
{
	CView::AssertValid();
}

void CMyDialogBarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyDialogBarDoc* CMyDialogBarView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDialogBarDoc)));
	return (CMyDialogBarDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyDialogBarView message handlers
