// OpenWebView.cpp : implementation of the COpenWebView class
//

#include "stdafx.h"
#include "OpenWeb.h"

#include "OpenWebDoc.h"
#include "OpenWebView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenWebView

IMPLEMENT_DYNCREATE(COpenWebView, CHtmlView)

BEGIN_MESSAGE_MAP(COpenWebView, CHtmlView)
	//{{AFX_MSG_MAP(COpenWebView)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CHtmlView::OnFilePrint)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenWebView construction/destruction

COpenWebView::COpenWebView()
{
	// TODO: add construction code here

}

COpenWebView::~COpenWebView()
{
}

BOOL COpenWebView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COpenWebView drawing

void COpenWebView::OnDraw(CDC* pDC)
{
	COpenWebDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void COpenWebView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();
 //   Navigate2("The first page.htm",NULL,NULL);
	// TODO: This code navigates to a popular spot on the web.
	//  change the code to go where you'd like.
	
}

/////////////////////////////////////////////////////////////////////////////
// COpenWebView printing


/////////////////////////////////////////////////////////////////////////////
// COpenWebView diagnostics

#ifdef _DEBUG
void COpenWebView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void COpenWebView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

COpenWebDoc* COpenWebView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenWebDoc)));
	return (COpenWebDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COpenWebView message handlers

void COpenWebView::OnFileOpen() 
{
CFileDialog dlg( TRUE,_T("htm"),_T("*.htm"),
	                 OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
	                 _T("อ๘าณ (*.htm)|*.htm|"));	


if(IDOK==dlg.DoModal())
{	Navigate2(dlg.GetPathName(),NULL,NULL);
}
}
