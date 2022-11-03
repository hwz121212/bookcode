// MyPenView.cpp : implementation of the CMyPenView class
//

#include "stdafx.h"
#include "MyPen.h"

#include "MyPenDoc.h"
#include "MyPenView.h"
#define RED RGB(255,0,0)
#define GREEN RGB(0,255,0)
#define BLUE RGB(0,0,255)
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
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND_RANGE(ID_BUTTONRED,ID_BUTTONFILL,OnPenChioce)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPenView construction/destruction

CMyPenView::CMyPenView()
:PenState(0)
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
// CMyPenView printing

BOOL CMyPenView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyPenView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyPenView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
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
	CRect r;
	
	if(PenState==0)
	{
		StartPt.x=point.x;
	    StartPt.y=point.y;
	}
	else if(PenState==1)
	{
		Rect.left=point.x;
		Rect.top=point.y;
	}
	else{}
	CView::OnLButtonDown(nFlags, point);
}

void CMyPenView::OnLButtonUp(UINT nFlags, CPoint point) 
{
    if(PenState==0)
	StartPt.x=-1;
	else if(PenState==1)
	{
		Rect.right=point.x;
		Rect.bottom=point.y;
		CDC *pDC=GetDC();
		CPen RectPen(PS_DASH,1,m_colors);
		pDC->SelectObject(&RectPen);
		pDC->MoveTo(Rect.left,Rect.top);
		pDC->LineTo(Rect.right,Rect.top);
		pDC->LineTo(Rect.right,Rect.bottom);
		pDC->LineTo(Rect.left,Rect.bottom);
		pDC->LineTo(Rect.left,Rect.top);
		ReleaseDC(pDC);
		PenState=0;
	}
    
	CView::OnLButtonUp(nFlags, point);
}

void CMyPenView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);
    dc.SelectObject(&Pen);

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
void CMyPenView::FillMyRect()
{
	CDC *pDC=GetDC();

	CBrush Brush;
	Brush.CreateSolidBrush(m_colors);
	pDC->FillRect(&Rect,&Brush);
	ReleaseDC(pDC);
}
void CMyPenView::OnPenChioce(UINT nID)
{
	DWORD PenStyle;
	switch(nID)
	{
	case ID_BUTTONRED:m_colors=RED;break;
	case ID_BUTTONGREEN:m_colors=GREEN;break;
	case ID_BUTTONBLUE:m_colors=BLUE;break;
	case ID_BUTTONDASH:PenStyle=PS_DASH;break;
	case ID_BUTTONSOLID:PenStyle=PS_SOLID;break;
	case ID_BUTTONRECT:PenState=1;break;
	case ID_BUTTONFILL:FillMyRect();break;
	}
	Pen.DeleteObject();
	Pen.CreatePen(PenStyle,1,m_colors);
}