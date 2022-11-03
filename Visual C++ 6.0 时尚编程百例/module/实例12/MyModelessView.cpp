// MyModelessView.cpp : implementation of the CMyModelessView class
//

#include "stdafx.h"
#include "MyModeless.h"

#include "MyModelessDoc.h"
#include "MyModelessView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyModelessView

IMPLEMENT_DYNCREATE(CMyModelessView, CView)

BEGIN_MESSAGE_MAP(CMyModelessView, CView)
	//{{AFX_MSG_MAP(CMyModelessView)
	ON_COMMAND(ID_DLG, OnDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyModelessView construction/destruction

CMyModelessView::CMyModelessView()
{
	// TODO: add construction code here

}

CMyModelessView::~CMyModelessView()
{
}

BOOL CMyModelessView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyModelessView drawing

void CMyModelessView::OnDraw(CDC* pDC)
{
	CMyModelessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMyModelessView diagnostics

#ifdef _DEBUG
void CMyModelessView::AssertValid() const
{
	CView::AssertValid();
}

void CMyModelessView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyModelessDoc* CMyModelessView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyModelessDoc)));
	return (CMyModelessDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyModelessView message handlers

void CMyModelessView::OnDlg() 
{
     Dlg=new CDlg(this);
	 Dlg->Create(IDD_DIALOG1);
	 Dlg->ShowWindow(SW_RESTORE);
}
