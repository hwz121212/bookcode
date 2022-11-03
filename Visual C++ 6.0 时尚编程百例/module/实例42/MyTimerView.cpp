// MyTimerView.cpp : implementation of the CMyTimerView class
//

#include "stdafx.h"
#include "MyTimer.h"

#include "MyTimerDoc.h"
#include "MyTimerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyTimerView

IMPLEMENT_DYNCREATE(CMyTimerView, CView)

BEGIN_MESSAGE_MAP(CMyTimerView, CView)
	//{{AFX_MSG_MAP(CMyTimerView)
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTimerView construction/destruction

CMyTimerView::CMyTimerView()
{
	// TODO: add construction code here

}

CMyTimerView::~CMyTimerView()
{
}

BOOL CMyTimerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyTimerView drawing

void CMyTimerView::OnDraw(CDC* pDC)
{
	
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMyTimerView printing

BOOL CMyTimerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyTimerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyTimerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyTimerView diagnostics

#ifdef _DEBUG
void CMyTimerView::AssertValid() const
{
	CView::AssertValid();
}

void CMyTimerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyTimerDoc* CMyTimerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyTimerDoc)));
	return (CMyTimerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyTimerView message handlers

void CMyTimerView::OnTimer(UINT_PTR nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CMyTimerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDC *pDC=GetDC();
	pDC->TextOut(MousePoint.x+10,MousePoint.y,"Your Mouse here!");
	
	CView::OnTimer(nIDEvent);
}

void CMyTimerView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	Invalidate();
	KillTimer(1);
	SetTimer(1,500,NULL);
	MousePoint=point;
	CView::OnMouseMove(nFlags, point);
}
