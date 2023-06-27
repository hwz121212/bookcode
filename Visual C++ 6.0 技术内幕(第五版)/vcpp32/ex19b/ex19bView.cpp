// ex19bView.cpp : implementation of the CEx19bView class
//

#include "stdafx.h"
#include "ex19b.h"

#include "ex19bDoc.h"
#include "ex19bView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx19bView

IMPLEMENT_DYNCREATE(CEx19bView, CView)

BEGIN_MESSAGE_MAP(CEx19bView, CView)
	//{{AFX_MSG_MAP(CEx19bView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx19bView construction/destruction

CEx19bView::CEx19bView()
{
	// TODO: add construction code here

}

CEx19bView::~CEx19bView()
{
}

BOOL CEx19bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx19bView drawing

void CEx19bView::OnDraw(CDC* pDC)
{
    int i, j;
	
	CEx19bDoc* pDoc = GetDocument();
    j = pDoc->m_ellipseArray.GetUpperBound();
    for (i = 0; i < j; i++) {
        pDC->Ellipse(pDoc->m_ellipseArray[i]);
    }
}

/////////////////////////////////////////////////////////////////////////////
// CEx19bView printing

BOOL CEx19bView::OnPreparePrinting(CPrintInfo* pInfo)
{
    CEx19bDoc* pDoc = GetDocument();
    pInfo->SetMaxPage(pDoc->m_ellipseArray.GetUpperBound() /
                      CEx19bDoc::nLinesPerPage + 1);
	return DoPreparePrinting(pInfo);
}

void CEx19bView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx19bView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEx19bView diagnostics

#ifdef _DEBUG
void CEx19bView::AssertValid() const
{
	CView::AssertValid();
}

void CEx19bView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx19bDoc* CEx19bView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx19bDoc)));
	return (CEx19bDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx19bView message handlers

void CEx19bView::PrintPageHeader(CDC *pDC)
{
    CString str;

    CPoint point(0, 0);
    pDC->TextOut(point.x, point.y, "Bubble Report");
    point += CSize(720, -720);
    str.Format("%6.6s %6.6s %6.6s %6.6s %6.6s",
               "Index", "Left", "Top", "Right", "Bottom");
    pDC->TextOut(point.x, point.y, str);

}

void CEx19bView::PrintPageFooter(CDC *pDC)
{
    CString str;

    CPoint point(0, -14400); // Move 10 inches down
    CEx19bDoc* pDoc = GetDocument();
    str.Format("Document %s", (LPCSTR) pDoc->GetTitle());
    pDC->TextOut(point.x, point.y, str);
    str.Format("Page %d", m_nPage);
    CSize size = pDC->GetTextExtent(str);
    point.x += 11520 - size.cx;
    pDC->TextOut(point.x, point.y, str); // right-justified

}

void CEx19bView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
    pDC->SetMapMode(MM_LOENGLISH);
}

void CEx19bView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
    int        i, nStart, nEnd, nHeight;
    CString    str;
    CPoint     point(720, -1440);
    CFont      font;
    TEXTMETRIC tm;

    pDC->SetMapMode(MM_TWIPS);
    CEx19bDoc* pDoc = GetDocument();
    m_nPage = pInfo->m_nCurPage; // for PrintPageFooter's benefit
    nStart = (m_nPage - 1) * CEx19bDoc::nLinesPerPage;
    nEnd = nStart + CEx19bDoc::nLinesPerPage;
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
