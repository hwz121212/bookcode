// DrawBottunView.cpp : implementation of the CDrawBottunView class
//

#include "stdafx.h"
#include "DrawBottun.h"

#include "DrawBottunDoc.h"
#include "DrawBottunView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawBottunView

IMPLEMENT_DYNCREATE(CDrawBottunView, CView)

BEGIN_MESSAGE_MAP(CDrawBottunView, CView)
	//{{AFX_MSG_MAP(CDrawBottunView)
	ON_COMMAND(ID_DISPLAY, OnDisplay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawBottunView construction/destruction

CDrawBottunView::CDrawBottunView()
{
	// TODO: add construction code here

}

CDrawBottunView::~CDrawBottunView()
{
}

BOOL CDrawBottunView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDrawBottunView drawing

void CDrawBottunView::OnDraw(CDC* pDC)
{
	CDrawBottunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDrawBottunView diagnostics

#ifdef _DEBUG
void CDrawBottunView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawBottunView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawBottunDoc* CDrawBottunView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawBottunDoc)));
	return (CDrawBottunDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawBottunView message handlers

void CDrawBottunView::OnDisplay() 
{
      Dlg=new MyDialog(this);
	  Dlg->Create(IDD_DIALOG1);
	  Dlg->ShowWindow(SW_RESTORE);
}
