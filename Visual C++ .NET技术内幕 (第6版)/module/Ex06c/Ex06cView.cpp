// Ex06cView.cpp : implementation of the CEx06cView class
//

#include "stdafx.h"
#include "Ex06c.h"

#include "Ex06cDoc.h"
#include "Ex06cView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx06cView

IMPLEMENT_DYNCREATE(CEx06cView, CScrollView)

BEGIN_MESSAGE_MAP(CEx06cView, CScrollView)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CEx06cView construction/destruction

CEx06cView::CEx06cView() : m_sizeEllipse(100, -100),
                           m_pointTopLeft(0, 0),
                           m_sizeOffset(0, 0)
{
    m_bCaptured = FALSE;
}

CEx06cView::~CEx06cView()
{
}

BOOL CEx06cView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// CEx06cView drawing

void CEx06cView::OnDraw(CDC* pDC)
{
    CBrush brushHatch(HS_DIAGCROSS, RGB(255, 0, 0));
    CPoint point(0, 0);                  // logical (0, 0)

    pDC->LPtoDP(&point);                 // In device coordinates,
    pDC->SetBrushOrg(point);             //  align the brush with
                                         //  the window origin
    pDC->SelectObject(&brushHatch);
    pDC->Ellipse(CRect(m_pointTopLeft, m_sizeEllipse));
    pDC->SelectStockObject(BLACK_BRUSH); // Deselect brushHatch
    pDC->Rectangle(CRect(100, -100, 200, -200)); // Test invalid rect
}

void CEx06cView::OnInitialUpdate()
{
    CScrollView::OnInitialUpdate();

    CSize sizeTotal(800, 1050); // 8-by-10.5 inches
    CSize sizePage(sizeTotal.cx / 2, sizeTotal.cy / 2);
    CSize sizeLine(sizeTotal.cx / 50, sizeTotal.cy / 50);
    SetScrollSizes(MM_LOENGLISH, sizeTotal, sizePage, sizeLine);
}


// CEx06cView diagnostics

#ifdef _DEBUG
void CEx06cView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CEx06cView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CEx06cDoc* CEx06cView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx06cDoc)));
	return (CEx06cDoc*)m_pDocument;
}
#endif //_DEBUG


// CEx06cView message handlers

void CEx06cView::OnLButtonDown(UINT nFlags, CPoint point)
{
    CRect rectEllipse(m_pointTopLeft, m_sizeEllipse); // still logical
    CRgn  circle;

    CClientDC dc(this);
    OnPrepareDC(&dc);
    dc.LPtoDP(rectEllipse); // Now it’s in device coordinates
    circle.CreateEllipticRgnIndirect(rectEllipse);
    if (circle.PtInRegion(point)) {
        // Capturing the mouse ensures subsequent LButtonUp message
        SetCapture();
        m_bCaptured = TRUE;
        CPoint pointTopLeft(m_pointTopLeft);
        dc.LPtoDP(&pointTopLeft);
        m_sizeOffset = point - pointTopLeft; // device coordinates
        // New mouse cursor is active while mouse is captured
        ::SetCursor(::LoadCursor(NULL, IDC_CROSS));
    }
}

void CEx06cView::OnLButtonUp(UINT nFlags, CPoint point)
{
    if (m_bCaptured) {
        ::ReleaseCapture();
        m_bCaptured = FALSE;
    }
}

void CEx06cView::OnMouseMove(UINT nFlags, CPoint point)
{
    if (m_bCaptured) {
         CClientDC dc(this);
        OnPrepareDC(&dc);
        CRect rectOld(m_pointTopLeft, m_sizeEllipse);
        dc.LPtoDP(rectOld);
        InvalidateRect(rectOld, TRUE);
        m_pointTopLeft = point - m_sizeOffset;
        dc.DPtoLP(&m_pointTopLeft);
        CRect rectNew(m_pointTopLeft, m_sizeEllipse);
        dc.LPtoDP(rectNew);
        InvalidateRect(rectNew, TRUE);
    }
}
