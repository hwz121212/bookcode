// Ex05bView.cpp : implementation of the CEx05bView class
//

#include "stdafx.h"
#include "Ex05b.h"

#include "Ex05bDoc.h"
#include "Ex05bView.h"

#ifdef _DEBUG
#define new DEBUG_NEW

#endif


// CEx05bView

IMPLEMENT_DYNCREATE(CEx05bView, CView)

BEGIN_MESSAGE_MAP(CEx05bView, CView)
	ON_WM_LBUTTONDOWN()
    	// Standard printing commands
    	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
    	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
    	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)

END_MESSAGE_MAP()

// CEx05bView construction/destruction

CEx05bView::CEx05bView(): m_rectEllipse(0, 0, 4000, -4000)
{
    m_nColor = GRAY_BRUSH;
}


CEx05bView::~CEx05bView()
{
}

BOOL CEx05bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEx05bView drawing

void CEx05bView::OnDraw(CDC* pDC)
{
	pDC->SelectStockObject(m_nColor);
    	pDC->Ellipse(m_rectEllipse);

}

// CEx05bView printing

BOOL CEx05bView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // default preparation
    return DoPreparePrinting(pInfo);
}

void CEx05bView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add extra initialization before printing
}

void CEx05bView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add cleanup after printing
}



// CEx05bView diagnostics

#ifdef _DEBUG
void CEx05bView::AssertValid() const
{
	CView::AssertValid();
}

void CEx05bView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx05bDoc* CEx05bView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx05bDoc)));
	return (CEx05bDoc*)m_pDocument;
}
#endif //_DEBUG


// CEx05bView message handlers

void CEx05bView::OnLButtonDown(UINT nFlags, CPoint point) 
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



void CEx05bView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	pDC->SetMapMode(MM_HIMETRIC);
	CView::OnPrepareDC(pDC, pInfo);
}
