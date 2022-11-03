// MyPenView.cpp : implementation of the CMyPenView class
//

#include "stdafx.h"
#include "MyPen.h"

#include "MyPenDoc.h"
#include "MyPenView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyPenView

IMPLEMENT_DYNCREATE(CMyPenView, CView)

BEGIN_MESSAGE_MAP(CMyPenView, CView)
	//{{AFX_MSG_MAP(CMyPenView)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPenView construction/destruction

CMyPenView::CMyPenView()
{
	// TODO: add construction code here

}

CMyPenView::~CMyPenView()
{
}

BOOL CMyPenView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyPenView drawing

void CMyPenView::OnDraw(CDC* pDC)
{
	CMyPenDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMyPenView diagnostics

#ifdef _DEBUG
void CMyPenView::AssertValid() const
{
	CView::AssertValid();
}

void CMyPenView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyPenDoc* CMyPenView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyPenDoc)));
	return (CMyPenDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyPenView message handlers

void CMyPenView::OnLButtonDown(UINT nFlags, CPoint point) 
{
    StartPt.x=point.x;
	StartPt.y=point.y;

	CView::OnLButtonDown(nFlags, point);
}

void CMyPenView::OnMouseMove(UINT nFlags, CPoint point) 
{
    CClientDC dc(this);

	EndPt.x=point.x;
	EndPt.y=point.y;
	
	if(StartPt.x>=0)
	{
		dc.MoveTo(StartPt.x,StartPt.y);
		dc.LineTo(EndPt);

		StartPt.x=EndPt.x;
		StartPt.y=EndPt.y;
	}
	CView::OnMouseMove(nFlags, point);
}

void CMyPenView::OnLButtonUp(UINT nFlags, CPoint point) 
{
    StartPt.x=-1;	

	CView::OnLButtonUp(nFlags, point);
}
