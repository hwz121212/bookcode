// novelView.cpp : implementation of the CNovelView class
//

#include "stdafx.h"
#include "novel.h"

#include "novelDoc.h"
#include "novelView.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNovelView

IMPLEMENT_DYNCREATE(CNovelView, CHtmlView)

BEGIN_MESSAGE_MAP(CNovelView, CHtmlView)
	//{{AFX_MSG_MAP(CNovelView)
	ON_CBN_EDITCHANGE(IDC_COMBOSITE, OnEditchangeCombosite)
	ON_CBN_SELCHANGE(IDC_COMBOSITE, OnSelchangeCombosite)
	ON_BN_CLICKED(IDC_BUTTONSITE, OnButtonsite)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CHtmlView::OnFilePrint)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNovelView construction/destruction

CNovelView::CNovelView()
{
	// TODO: add construction code here

}

CNovelView::~CNovelView()
{
}

BOOL CNovelView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CNovelView drawing

void CNovelView::OnDraw(CDC* pDC)
{
	CNovelDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CNovelView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();
	site="http://mfc2000.yeah.net";
	// TODO: This code navigates to a popular spot on the web.
	//  change the code to go where you'd like.
	// Navigate2(_T("d:/yninfo/home.htm"),NULL,NULL);
	Navigate2(site,NULL,NULL);

}

/////////////////////////////////////////////////////////////////////////////
// CNovelView printing


/////////////////////////////////////////////////////////////////////////////
// CNovelView diagnostics

#ifdef _DEBUG
void CNovelView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CNovelView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CNovelDoc* CNovelView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNovelDoc)));
	return (CNovelDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNovelView message handlers

void CNovelView::OnEditchangeCombosite() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *pw=(CMainFrame *)AfxGetMainWnd();
	CDialogBar *pb=pw->GetDialogBar();
	pb->GetDlgItemText(IDC_COMBOSITE,site);
}

void CNovelView::OnSelchangeCombosite() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *pw=(CMainFrame *)AfxGetMainWnd();
	CDialogBar *pb=pw->GetDialogBar();
	pb->GetDlgItemText(IDC_COMBOSITE,site);
	OnButtonsite();	
}

void CNovelView::OnButtonsite() 
{
	// TODO: Add your control notification handler code here
	CClientDC dc(this);
	dc.TextOut(2,8,CString("Linking to <")+site+">...");
	Navigate2(site,NULL,NULL);
	Invalidate(FALSE);
}
