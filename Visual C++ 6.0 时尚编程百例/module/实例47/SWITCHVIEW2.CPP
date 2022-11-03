// SwitchView2.cpp : implementation file
//

#include "stdafx.h"
#include "switch.h"
#include "SwitchView2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSwitchView2

IMPLEMENT_DYNCREATE(CSwitchView2, CView)

CSwitchView2::CSwitchView2()
{
}

CSwitchView2::~CSwitchView2()
{
}


BEGIN_MESSAGE_MAP(CSwitchView2, CView)
	//{{AFX_MSG_MAP(CSwitchView2)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSwitchView2 drawing

void CSwitchView2::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CSwitchView2 diagnostics

#ifdef _DEBUG
void CSwitchView2::AssertValid() const
{
	CView::AssertValid();
}

void CSwitchView2::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSwitchView2 message handlers

void CSwitchView2::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
   dc.TextOut(0,0,"View 2",6);	
	
	// Do not call CView::OnPaint() for painting messages
}
