// ex37bView.cpp : implementation of the CEx37bView class
//

#include "stdafx.h"
#include "ex37b.h"

#include "ex37bDoc.h"
#include "ex37bView.h"
#include "MainFrm.h" //TODO

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx37bView

IMPLEMENT_DYNCREATE(CEx37bView, CHtmlView)

BEGIN_MESSAGE_MAP(CEx37bView, CHtmlView)
	//{{AFX_MSG_MAP(CEx37bView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CHtmlView::OnFilePrint)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx37bView construction/destruction

CEx37bView::CEx37bView()
{
	// TODO: add construction code here

}

CEx37bView::~CEx37bView()
{
}

BOOL CEx37bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx37bView drawing

void CEx37bView::OnDraw(CDC* pDC)
{
	CEx37bDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

void CEx37bView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	// TODO: This code navigates to a popular spot on the web.
	//  change the code to go where you'd like.
	Navigate2(_T("res://ie4tour.dll/welcome.htm"),NULL,NULL);

	CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->DoDHTMLExplore();

}

/////////////////////////////////////////////////////////////////////////////
// CEx37bView printing


/////////////////////////////////////////////////////////////////////////////
// CEx37bView diagnostics

#ifdef _DEBUG
void CEx37bView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CEx37bView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CEx37bDoc* CEx37bView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx37bDoc)));
	return (CEx37bDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx37bView message handlers
