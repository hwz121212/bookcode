// ex11bView.cpp : implementation of the CEx11bView class
//

#include "stdafx.h"
#include "ex11b.h"

#include "ex11bDoc.h"
#include "ex11bView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx11bView

IMPLEMENT_DYNCREATE(CEx11bView, CScrollView)

BEGIN_MESSAGE_MAP(CEx11bView, CScrollView)
	//{{AFX_MSG_MAP(CEx11bView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx11bView construction/destruction

CEx11bView::CEx11bView(): m_sizeEllipse(100, -100),
                          m_pointTopLeft(10, -10),
                          m_sizeOffset(0, 0)

{
    m_bCaptured = FALSE;
    m_pdcMemory = new CDC;
    m_pBitmap   = new CBitmap;

}

CEx11bView::~CEx11bView()
{
    delete m_pBitmap; // already deselected
    delete m_pdcMemory;
}

BOOL CEx11bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx11bView drawing

void CEx11bView::OnDraw(CDC* pDC)
{
	CBrush brushHatch(HS_DIAGCROSS, RGB(255, 0, 0));
	CPoint point(0, 0);
	
	pDC->LPtoDP(&point);
	pDC->SetBrushOrg(point);

	pDC->SelectObject(&brushHatch);
	pDC->Ellipse(CRect(m_pointTopLeft, m_sizeEllipse));
	pDC->SelectStockObject(BLACK_BRUSH);
	pDC->Rectangle(CRect(100, -100, 200, -200));
}

void CEx11bView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

    CSize sizeTotal(800, 1050); // 8-by-10.5 inches
    CSize sizePage(sizeTotal.cx / 2, sizeTotal.cy / 2);
    CSize sizeLine(sizeTotal.cx / 50, sizeTotal.cy / 50);
    SetScrollSizes(MM_LOENGLISH, sizeTotal, sizePage, sizeLine);
    // creates the memory device context and the bitmap
    if (m_pdcMemory->GetSafeHdc() == NULL) {
        CClientDC dc(this);
        OnPrepareDC(&dc);
        CRect rectMax(0, 0, sizeTotal.cx, -sizeTotal.cy);
        dc.LPtoDP(rectMax);
        m_pdcMemory->CreateCompatibleDC(&dc);
        // makes bitmap same size as display window
        m_pBitmap->CreateCompatibleBitmap(&dc, rectMax.right,
                                          rectMax.bottom);
        m_pdcMemory->SetMapMode(MM_LOENGLISH);
    }
}

/////////////////////////////////////////////////////////////////////////////
// CEx11bView printing

BOOL CEx11bView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx11bView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx11bView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEx11bView diagnostics

#ifdef _DEBUG
void CEx11bView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CEx11bView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CEx11bDoc* CEx11bView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx11bDoc)));
	return (CEx11bDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx11bView message handlers

void CEx11bView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect rectEllipse(m_pointTopLeft, m_sizeEllipse);
	CRgn circle;

	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.LPtoDP(rectEllipse);
	circle.CreateEllipticRgnIndirect(rectEllipse);
	if (circle.PtInRegion(point)) {
		//Capturing the mouse ensures subsequent LButtonUp message
		SetCapture();
		m_bCaptured = TRUE;
		CPoint pointTopLeft(m_pointTopLeft);
		dc.LPtoDP(&pointTopLeft);
		m_sizeOffset = point - pointTopLeft; //device coordinates
		// New mouse cursor is active while mouse is captured
		::SetCursor(::LoadCursor(NULL, IDC_CROSS));
	}
}

void CEx11bView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bCaptured) {
		::ReleaseCapture();
		m_bCaptured = FALSE;
	}
}

void CEx11bView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_bCaptured) {
		CClientDC dc(this);
		OnPrepareDC(&dc);
		CRect rectOld(m_pointTopLeft, m_sizeEllipse);
		dc.LPtoDP(rectOld);
		InvalidateRect(rectOld, FALSE);
		m_pointTopLeft = point - m_sizeOffset;
		dc.DPtoLP(&m_pointTopLeft);
		CRect rectNew(m_pointTopLeft, m_sizeEllipse);
		dc.LPtoDP(rectNew);
		InvalidateRect(rectNew, FALSE);
	}
}

void CEx11bView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
    OnPrepareDC(&dc);
    CRect rectUpdate;
    dc.GetClipBox(&rectUpdate);
    CBitmap* pOldBitmap = m_pdcMemory->SelectObject(m_pBitmap);
    m_pdcMemory->SelectClipRgn(NULL);
    m_pdcMemory->IntersectClipRect(&rectUpdate);
    CBrush backgroundBrush((COLORREF) ::GetSysColor(COLOR_WINDOW));
    CBrush* pOldBrush = m_pdcMemory->SelectObject(&backgroundBrush);
    m_pdcMemory->PatBlt(rectUpdate.left, rectUpdate.top,
                        rectUpdate.Width(), rectUpdate.Height(),
                        PATCOPY); 
    OnDraw(m_pdcMemory);
    dc.BitBlt(rectUpdate.left, rectUpdate.top,
              rectUpdate.Width(), rectUpdate.Height(),
              m_pdcMemory, rectUpdate.left, rectUpdate.top,
              SRCCOPY);
    m_pdcMemory->SelectObject(pOldBitmap);
    m_pdcMemory->SelectObject(pOldBrush);
}
