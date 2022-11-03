// StringView.cpp : implementation of the CHexView class
//

#include "stdafx.h"
#include "Ex19b.h"

#include "LogScrollView.h"

#include "PoemDoc.h"
#include "HexView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHexView

IMPLEMENT_DYNCREATE(CHexView, CLogScrollView)

BEGIN_MESSAGE_MAP(CHexView, CLogScrollView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CLogScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CLogScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CLogScrollView::OnFilePrintPreview)
	ON_MESSAGE(WM_COMMANDHELP, OnCommandHelp)
	ON_MESSAGE(WM_HELPHITTEST, OnHelpHitTest)
END_MESSAGE_MAP()

// CHexView construction/destruction

CHexView::CHexView() : m_rectPrint(0, 0, 11520, -15120)
{
}

CHexView::~CHexView()
{
}

BOOL CHexView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CLogScrollView::PreCreateWindow(cs);
}

// CHexView drawing

void CHexView::OnDraw(CDC* pDC)
{
    // hex dump of document strings
    int        i, j, k, l, n, nHeight;
    CString    outputLine, str;
    CFont      font;
    TEXTMETRIC tm;

    CPoemDoc* pDoc = GetDocument();
    font.CreateFont(-160, 80, 0, 0, 400, FALSE, FALSE, 0,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
    CFont* pOldFont = pDC->SelectObject(&font);
    pDC->GetTextMetrics(&tm);
    nHeight = tm.tmHeight + tm.tmExternalLeading;

    j = pDoc->m_stringArray.GetSize();
    for (i = 0; i < j; i++) {
        outputLine.Format("%02x   ", i);
        l = pDoc->m_stringArray[i].GetLength();
        for (k = 0; k < l; k++) {
            n = pDoc->m_stringArray[i][k] & 0x00ff;
            str.Format("%02x ", n);
            outputLine += str;
        }
        pDC->TextOut(720, -i * nHeight - 720, outputLine);
    }
    pDC->SelectObject(pOldFont);
}

void CHexView::OnInitialUpdate()
{
    CLogScrollView::OnInitialUpdate();
    CSize sizeTotal(m_rectPrint.Width(), -m_rectPrint.Height());
    SetLogScrollSizes(sizeTotal);
}

// CHexView printing

BOOL CHexView::OnPreparePrinting(CPrintInfo* pInfo)
{
    pInfo->SetMaxPage(1);
    return DoPreparePrinting(pInfo);
}

void CHexView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHexView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CHexView diagnostics

#ifdef _DEBUG
void CHexView::AssertValid() const
{
	CLogScrollView::AssertValid();
}

void CHexView::Dump(CDumpContext& dc) const
{
	CLogScrollView::Dump(dc);
}

CPoemDoc* CHexView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPoemDoc)));
	return (CPoemDoc*)m_pDocument;
}
#endif //_DEBUG


// CHexView message handlers
LRESULT CHexView::OnCommandHelp(WPARAM wParam, LPARAM lParam)
{
    if (lParam == 0) { // context not already determined
        lParam = HID_BASE_RESOURCE + IDR_HEXVIEW;
    }
    AfxGetApp()->WinHelp(lParam);
    return TRUE;
}

LRESULT CHexView::OnHelpHitTest(WPARAM wParam, LPARAM lParam)
{
    return HID_BASE_RESOURCE + IDR_HEXVIEW;
}