// ex11aView.cpp : implementation of the CEx11aView class
//

#include "stdafx.h"
#include "ex11a.h"

#include "ex11aDoc.h"
#include "ex11aView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx11aView

IMPLEMENT_DYNCREATE(CEx11aView, CScrollView)

BEGIN_MESSAGE_MAP(CEx11aView, CScrollView)
	//{{AFX_MSG_MAP(CEx11aView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx11aView construction/destruction

CEx11aView::CEx11aView()
{
    m_pdcMemory = new CDC;
    m_pBitmap = new CBitmap;

}

CEx11aView::~CEx11aView()
{
    // cleans up the memory device context and the bitmap
    delete m_pdcMemory; // deselects bitmap
    delete m_pBitmap;
}

BOOL CEx11aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx11aView drawing

void CEx11aView::OnDraw(CDC* pDC)
{
    pDC->SetStretchBltMode(COLORONCOLOR);
    pDC->StretchBlt(20, -20, m_sizeDest.cx, -m_sizeDest.cy,
        m_pdcMemory, 0, 0,
        m_sizeSource.cx, m_sizeSource.cy, SRCCOPY);

    pDC->StretchBlt(350, -20, m_sizeSource.cx, -m_sizeSource.cy,
        m_pdcMemory, 0, 0,
        m_sizeSource.cx, m_sizeSource.cy, SRCCOPY);
}

void CEx11aView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

    CSize sizeTotal(800, 1050); // 8-by-10.5 inches
    CSize sizeLine = CSize(sizeTotal.cx / 100, sizeTotal.cy / 100);
    SetScrollSizes(MM_LOENGLISH, sizeTotal, sizeTotal, sizeLine);

    BITMAP bm; // Windows BITMAP data structure; see Win32 help
    if (m_pdcMemory->GetSafeHdc() == NULL) {
        CClientDC dc(this);
        OnPrepareDC(&dc); // necessary
        m_pBitmap->LoadBitmap(IDB_GOLDWEAVE);
         m_pdcMemory->CreateCompatibleDC(&dc);
        m_pdcMemory->SelectObject(m_pBitmap);
        m_pBitmap->GetObject(sizeof(bm), &bm);
        m_sizeSource.cx = bm.bmWidth;
        m_sizeSource.cy = bm.bmHeight;
        m_sizeDest = m_sizeSource;
        dc.DPtoLP(&m_sizeDest);
    }
}

/////////////////////////////////////////////////////////////////////////////
// CEx11aView printing

BOOL CEx11aView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx11aView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx11aView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEx11aView diagnostics

#ifdef _DEBUG
void CEx11aView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CEx11aView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CEx11aDoc* CEx11aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx11aDoc)));
	return (CEx11aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx11aView message handlers
