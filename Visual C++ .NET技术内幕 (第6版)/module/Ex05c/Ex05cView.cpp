// Ex05cView.cpp : implementation of the CEx05cView class
//

#include "stdafx.h"
#include "Ex05c.h"

#include "Ex05cDoc.h"
#include "Ex05cView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx05cView

IMPLEMENT_DYNCREATE(CEx05cView, CScrollView)

BEGIN_MESSAGE_MAP(CEx05cView, CScrollView)
    ON_WM_KEYDOWN()
    ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CEx05cView construction/destruction

CEx05cView::CEx05cView() : m_rectEllipse(0, 0, 4000, -4000)
{
    m_nColor = GRAY_BRUSH;
}

CEx05cView::~CEx05cView()
{
}

BOOL CEx05cView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// CEx05cView drawing

void CEx05cView::OnDraw(CDC* pDC)
{
    pDC->SelectStockObject(m_nColor);
    pDC->Ellipse(m_rectEllipse);


	CString strPoint;
	strPoint.Format("%d,%d", m_Point.x, m_Point.y);
	pDC->TextOut(m_Point.x, m_Point.y, strPoint);
}

void CEx05cView::OnInitialUpdate()
{
    CScrollView::OnInitialUpdate();
    CSize sizeTotal(20000, 30000); // 20 by 30 cm
    CSize sizePage(sizeTotal.cx / 2, sizeTotal.cy / 2);
    CSize sizeLine(sizeTotal.cx / 50, sizeTotal.cy / 50);
    SetScrollSizes(MM_HIMETRIC, sizeTotal, sizePage, sizeLine);
}


// CEx05cView diagnostics

#ifdef _DEBUG
void CEx05cView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CEx05cView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CEx05cDoc* CEx05cView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx05cDoc)));
	return (CEx05cDoc*)m_pDocument;
}
#endif //_DEBUG


// CEx05cView message handlers

void CEx05cView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    switch (nChar) {
    case VK_HOME:
        OnVScroll(SB_TOP, 0, NULL);
        OnHScroll(SB_LEFT, 0, NULL);
        break;
    case VK_END:
        OnVScroll(SB_BOTTOM, 0, NULL);
        OnHScroll(SB_RIGHT, 0, NULL);
        break;
    case VK_UP:
        OnVScroll(SB_LINEUP, 0, NULL);
        break;
    case VK_DOWN:
        OnVScroll(SB_LINEDOWN, 0, NULL);
        break;
    case VK_PRIOR:
        OnVScroll(SB_PAGEUP, 0, NULL);
        break;
    case VK_NEXT:
        OnVScroll(SB_PAGEDOWN, 0, NULL);
        break;
    case VK_LEFT:
        OnHScroll(SB_LINELEFT, 0, NULL);
        break;
    case VK_RIGHT:
        OnHScroll(SB_LINERIGHT, 0, NULL);
        break;
    default:
        break;
    }
}

void CEx05cView::OnLButtonDown(UINT nFlags, CPoint point)
{
    CClientDC dc(this);
    OnPrepareDC(&dc);
    CRect rectDevice = m_rectEllipse;
    dc.LPtoDP(rectDevice);
    if (rectDevice.PtInRect(point)) {
        if (m_nColor == GRAY_BRUSH) {
            m_nColor = WHITE_BRUSH;
        }
        else {
            m_nColor = GRAY_BRUSH;
        }
        InvalidateRect(rectDevice);
    }
}


void CEx05cView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CClientDC dc(this);
	OnPrepareDC(&dc);
	CPoint pointTemp = point;
	dc.DPtoLP(&pointTemp, 1);
	m_Point = pointTemp;
	Invalidate();
	CScrollView::OnMouseMove(nFlags, point);
}
