// MyHtmlViewView.cpp : implementation of the CMyHtmlViewView class
//

#include "stdafx.h"
#include "MyHtmlView.h"

#include "MyHtmlViewDoc.h"
#include "MyHtmlViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyHtmlViewView

IMPLEMENT_DYNCREATE(CMyHtmlViewView, CHtmlView)

BEGIN_MESSAGE_MAP(CMyHtmlViewView, CHtmlView)
	//{{AFX_MSG_MAP(CMyHtmlViewView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CHtmlView::OnFilePrint)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyHtmlViewView construction/destruction

CMyHtmlViewView::CMyHtmlViewView()
{
	// TODO: add construction code here

}

CMyHtmlViewView::~CMyHtmlViewView()
{
}

BOOL CMyHtmlViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyHtmlViewView drawing

void CMyHtmlViewView::OnDraw(CDC* pDC)
{
	CMyHtmlViewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CMyHtmlViewView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	// TODO: This code navigates to a popular spot on the web.
	//  change the code to go where you'd like.
	Navigate2(_T("http://www.microsoft.com/visualc/"),NULL,NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CMyHtmlViewView printing


/////////////////////////////////////////////////////////////////////////////
// CMyHtmlViewView diagnostics

#ifdef _DEBUG
void CMyHtmlViewView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CMyHtmlViewView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CMyHtmlViewDoc* CMyHtmlViewView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyHtmlViewDoc)));
	return (CMyHtmlViewDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyHtmlViewView message handlers
