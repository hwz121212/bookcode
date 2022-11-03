// Ex17bView.cpp : implementation of the CEx17bView class
//

#include "stdafx.h"
#include "Ex17b.h"

#include "Ex17bDoc.h"
#include "Ex17bView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx17bView

IMPLEMENT_DYNCREATE(CEx17bView, CView)

BEGIN_MESSAGE_MAP(CEx17bView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CEx17bView construction/destruction

CEx17bView::CEx17bView()
: m_nPage(0)
{
	// TODO: add construction code here

}

CEx17bView::~CEx17bView()
{
}

BOOL CEx17bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEx17bView drawing

void CEx17bView::OnDraw(CDC* pDC)
{
	int i, j;

	CEx17bDoc* pDoc = GetDocument();
	j = pDoc->m_ellipseArray.GetUpperBound();
    for (i = 0; i < j; i++) {
        pDC->Ellipse(pDoc->m_ellipseArray[i]);
    }

}


// CEx17bView printing

BOOL CEx17bView::OnPreparePrinting(CPrintInfo* pInfo)
{
	CEx17bDoc* pDoc = GetDocument();
    pInfo->SetMaxPage(pDoc->m_ellipseArray.GetUpperBound() /
                      CEx17bDoc::nLinesPerPage + 1);

	return DoPreparePrinting(pInfo);
}

void CEx17bView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx17bView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CEx17bView diagnostics

#ifdef _DEBUG
void CEx17bView::AssertValid() const
{
	CView::AssertValid();
}

void CEx17bView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx17bDoc* CEx17bView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx17bDoc)));
	return (CEx17bDoc*)m_pDocument;
}
#endif //_DEBUG


// CEx17bView message handlers

void CEx17bView::PrintPageHeader(CDC *pDC)
{
	CString str;

    CPoint point(0, 0);
    pDC->TextOut(point.x, point.y, "Bubble Report");
    point += CSize(720, -720);
    str.Format("%6.6s %6.6s %6.6s %6.6s %6.6s",
               "Index", "Left", "Top", "Right", "Bottom");
    pDC->TextOut(point.x, point.y, str);

}

void CEx17bView::PrintPageFooter(CDC *pDC)
{
	CString str;

    CPoint point(0, -14400); // Move 10 inches down
    CEx17bDoc* pDoc = GetDocument();
    str.Format("Document %s", (LPCSTR) pDoc->GetTitle());
    pDC->TextOut(point.x, point.y, str);
    str.Format("Page %d", m_nPage);
    CSize size = pDC->GetTextExtent(str);
    point.x += 11520 - size.cx;
    pDC->TextOut(point.x, point.y, str); // right-justified

}

void CEx17bView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	pDC->SetMapMode(MM_LOENGLISH);
}

void CEx17bView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	int        i, nStart, nEnd, nHeight;
    CString    str;
    CPoint     point(720, -1440);
    CFont      font;
    TEXTMETRIC tm;

    pDC->SetMapMode(MM_TWIPS);
    CEx17bDoc* pDoc = GetDocument();
    m_nPage = pInfo->m_nCurPage; // for PrintPageFooter’s benefit
    nStart = (m_nPage - 1) * CEx17bDoc::nLinesPerPage;
    nEnd = nStart + CEx17bDoc::nLinesPerPage;
     // 14-point fixed-pitch font
    font.CreateFont(-280, 0, 0, 0, 400, FALSE, FALSE,
                    0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                    CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                    DEFAULT_PITCH | FF_MODERN, "Courier New");
                    // Courier New is a TrueType font
    CFont* pOldFont = (CFont*) (pDC->SelectObject(&font));
    PrintPageHeader(pDC);
    pDC->GetTextMetrics(&tm);
    nHeight = tm.tmHeight + tm.tmExternalLeading;
    for (i = nStart; i < nEnd; i++) {
        if (i > pDoc->m_ellipseArray.GetUpperBound()) {
            break;
        }
        str.Format("%6d %6d %6d %6d %6d", i + 1,
                   pDoc->m_ellipseArray[i].left,
                   pDoc->m_ellipseArray[i].top,
                   pDoc->m_ellipseArray[i].right,
                   pDoc->m_ellipseArray[i].bottom);
        point.y -= nHeight;
        pDC->TextOut(point.x, point.y, str);
    }
    PrintPageFooter(pDC);
    pDC->SelectObject(pOldFont);

}
