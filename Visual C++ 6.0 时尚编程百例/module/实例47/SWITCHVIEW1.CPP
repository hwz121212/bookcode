// SwitchView1.cpp : implementation file
//

#include "stdafx.h"
#include "switch.h"
#include "SwitchView1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSwitchView1

IMPLEMENT_DYNCREATE(CSwitchView1, CView)

CSwitchView1::CSwitchView1()
{
}

CSwitchView1::~CSwitchView1()
{
}


BEGIN_MESSAGE_MAP(CSwitchView1, CView)
	//{{AFX_MSG_MAP(CSwitchView1)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSwitchView1 drawing

void CSwitchView1::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CSwitchView1 diagnostics

#ifdef _DEBUG
void CSwitchView1::AssertValid() const
{
	CView::AssertValid();
}

void CSwitchView1::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSwitchView1 message handlers

void CSwitchView1::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
   dc.TextOut(0,0,"View 1",6);	
	
	// Do not call CView::OnPaint() for painting messages
}
