// Ex05aView.cpp : implementation of the CEx05aView class
//

#include "stdafx.h"
#include "Ex05a.h"

#include "Ex05aDoc.h"
#include "Ex05aView.h"

#ifdef _DEBUG
#define new DEBUG_NEW

#endif


// CEx05aView

IMPLEMENT_DYNCREATE(CEx05aView, CView)

BEGIN_MESSAGE_MAP(CEx05aView, CView)
	ON_WM_LBUTTONDOWN()
    	// Standard printing commands
    	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
    	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
    	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)

		ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CEx05aView construction/destruction

CEx05aView::CEx05aView(): m_rectEllipse(0, 0, 200, 200)
{
    m_nColor = GRAY_BRUSH;
}


CEx05aView::~CEx05aView()
{
}

BOOL CEx05aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEx05aView drawing

void CEx05aView::OnDraw(CDC* pDC)
{
	pDC->SelectStockObject(m_nColor);
    pDC->Ellipse(m_rectEllipse);

	CString strRectInfo;
	strRectInfo.Format("%d,%d,%d,%d", m_rectEllipse.left, m_rectEllipse.top, m_rectEllipse.right, m_rectEllipse.bottom);
	pDC->TextOut(m_rectEllipse.right, m_rectEllipse.bottom, strRectInfo);

	CString strPoint;
	strPoint.Format("%d,%d", m_Point.x, m_Point.y);
	pDC->TextOut(m_Point.x, m_Point.y, strPoint);
}

// CEx05aView printing

BOOL CEx05aView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // default preparation
    return DoPreparePrinting(pInfo);
}

void CEx05aView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add extra initialization before printing
}

void CEx05aView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add cleanup after printing
}



// CEx05aView diagnostics

#ifdef _DEBUG
void CEx05aView::AssertValid() const
{
	CView::AssertValid();
}

void CEx05aView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx05aDoc* CEx05aView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx05aDoc)));
	return (CEx05aDoc*)m_pDocument;
}
#endif //_DEBUG


// CEx05aView message handlers

void CEx05aView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_Point = point;
    if (m_rectEllipse.PtInRect(point)) 
	{
        if (m_nColor == GRAY_BRUSH) 
		{
            m_nColor = WHITE_BRUSH;
        }
        else 
		{
            m_nColor = GRAY_BRUSH;
        }
        InvalidateRect(m_rectEllipse);		
    }
}


void CEx05aView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_Point = point;
	Invalidate();
	CView::OnMouseMove(nFlags, point);
}
