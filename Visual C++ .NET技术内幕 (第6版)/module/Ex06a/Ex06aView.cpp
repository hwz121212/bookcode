// Ex06aView.cpp : implementation of the CEx06aView class
//

#include "stdafx.h"
#include "Ex06a.h"

#include "Ex06aDoc.h"
#include "Ex06aView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx06aView

IMPLEMENT_DYNCREATE(CEx06aView, CView)

BEGIN_MESSAGE_MAP(CEx06aView, CView)
END_MESSAGE_MAP()

// CEx06aView construction/destruction

CEx06aView::CEx06aView()
{
	// TODO: add construction code here

}

CEx06aView::~CEx06aView()
{
}

BOOL CEx06aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEx06aView drawing

void CEx06aView::OnDraw(CDC* pDC)
{
    int nPosition = 0;

    for (int i = 6; i <= 24; i += 2) {
        ShowFont(pDC, nPosition, i);
    }
    TRACE("LOGPIXELSX = %d, LOGPIXELSY = %d\n",
          pDC->GetDeviceCaps(LOGPIXELSX),
          pDC->GetDeviceCaps(LOGPIXELSY)); 
    TRACE("HORZSIZE = %d, VERTSIZE = %d\n",
           pDC->GetDeviceCaps(HORZSIZE),
          pDC->GetDeviceCaps(VERTSIZE)); 
    TRACE("HORZRES = %d, VERTRES = %d\n",
          pDC->GetDeviceCaps(HORZRES),
          pDC->GetDeviceCaps(VERTRES));
}


// CEx06aView diagnostics

#ifdef _DEBUG
void CEx06aView::AssertValid() const
{
	CView::AssertValid();
}

void CEx06aView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx06aDoc* CEx06aView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx06aDoc)));
	return (CEx06aDoc*)m_pDocument;
}
#endif //_DEBUG


// CEx06aView message handlers

void CEx06aView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
    pDC->SetMapMode(MM_ANISOTROPIC);
    pDC->SetWindowExt(1440, 1440);
    pDC->SetViewportExt(pDC->GetDeviceCaps(LOGPIXELSX),
                 pDC->GetDeviceCaps(LOGPIXELSY));
}

void CEx06aView::ShowFont(CDC* pDC, int& nPos, int nPoints)
{
    TEXTMETRIC tm;
    CFont      fontText;
    CString    strText;
    CSize      sizeText;

    fontText.CreateFont(-nPoints * 20, 0, 0, 0, 400, FALSE, FALSE, 0,
                        ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                        DEFAULT_PITCH | FF_SWISS, "Arial");
    CFont* pOldFont = (CFont*) pDC->SelectObject(&fontText);
    pDC->GetTextMetrics(&tm);
    TRACE("points = %d, tmHeight = %d, tmInternalLeading = %d,"
          " tmExternalLeading = %d\n", nPoints, tm.tmHeight,
          tm.tmInternalLeading, tm.tmExternalLeading);
    strText.Format("This is %d-point Arial", nPoints);
    sizeText = pDC->GetTextExtent(strText);
    TRACE("string width = %d, string height = %d\n", sizeText.cx,
          sizeText.cy);
    pDC->TextOut(0, nPos, strText);
    pDC->SelectObject(pOldFont);
    nPos += tm.tmHeight + tm.tmExternalLeading;
}
