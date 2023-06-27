// ex37aView.cpp : implementation of the CEx37aView class
//

#include "stdafx.h"
#include "ex37a.h"

#include "ex37aDoc.h"
#include "ex37aView.h"
#include <mshtml.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx37aView

IMPLEMENT_DYNCREATE(CEx37aView, CHtmlView)

BEGIN_MESSAGE_MAP(CEx37aView, CHtmlView)
	//{{AFX_MSG_MAP(CEx37aView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CHtmlView::OnFilePrint)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx37aView construction/destruction

CEx37aView::CEx37aView()
{
	// TODO: add construction code here

}

CEx37aView::~CEx37aView()
{
}

BOOL CEx37aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx37aView drawing

void CEx37aView::OnDraw(CDC* pDC)
{
	CEx37aDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

void CEx37aView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	// TODO: This code navigates to a popular spot on the web.
	//  change the code to go where you'd like.
	Navigate2(_T("http://www.microsoft.com/visualc/"),NULL,NULL);
		IDispatch* pDisp = GetHtmlDocument();
	
	
}

/////////////////////////////////////////////////////////////////////////////
// CEx37aView printing


/////////////////////////////////////////////////////////////////////////////
// CEx37aView diagnostics

#ifdef _DEBUG
void CEx37aView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CEx37aView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CEx37aDoc* CEx37aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx37aDoc)));
	return (CEx37aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx37aView message handlers
