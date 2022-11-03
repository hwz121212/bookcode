// Ex06dView.cpp : implementation of the CEx06dView class
//

#include "stdafx.h"
#include "Ex06d.h"

#include "Ex06dDoc.h"
#include "Ex06dView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx06dView

IMPLEMENT_DYNCREATE(CEx06dView, CScrollView)

BEGIN_MESSAGE_MAP(CEx06dView, CScrollView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CEx06dView construction/destruction

CEx06dView::CEx06dView()
{
	// TODO: add construction code here

}

CEx06dView::~CEx06dView()
{
}

BOOL CEx06dView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// CEx06dView drawing

void CEx06dView::OnDraw(CDC* pDC)
{
	CEx06dDoc* pDoc = GetDocument();
	BeginWaitCursor();
    m_dibResource.UsePalette(pDC); // should be in palette
    m_dibFile.UsePalette(pDC);     //  message handlers, not here
    pDC->TextOut(0, 0, 
        "Press the left mouse button here to load a file.");
    CSize sizeResourceDib = m_dibResource.GetDimensions();
    sizeResourceDib.cx *= 30;
    sizeResourceDib.cy *= -30;
    m_dibResource.Draw(pDC, CPoint(0, -800), sizeResourceDib);
    CSize sizeFileDib = m_dibFile.GetDimensions();
    sizeFileDib.cx *= 30;
    sizeFileDib.cy *= -30;
    m_dibFile.Draw(pDC, CPoint(1800, -800), sizeFileDib);
    EndWaitCursor();

}

void CEx06dView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CSize sizeTotal(30000, 40000); // 30-by-40 cm
    CSize sizeLine = CSize(sizeTotal.cx / 100, sizeTotal.cy / 100);
    SetScrollSizes(MM_HIMETRIC, sizeTotal, sizeTotal, sizeLine);

    LPVOID lpvResource = (LPVOID) ::LoadResource(NULL,
        ::FindResource(NULL, MAKEINTRESOURCE(IDB_REDBLOCKS),
                       RT_BITMAP));
    m_dibResource.AttachMemory(lpvResource); // no need for
                                             //  ::LockResource
    CClientDC dc(this);
    TRACE("bits per pixel = %d\n", dc.GetDeviceCaps(BITSPIXEL));

}


// CEx06dView printing

BOOL CEx06dView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx06dView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx06dView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CEx06dView diagnostics

#ifdef _DEBUG
void CEx06dView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CEx06dView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CEx06dDoc* CEx06dView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx06dDoc)));
	return (CEx06dDoc*)m_pDocument;
}
#endif //_DEBUG


// CEx06dView message handlers
#define MEMORY_MAPPED_FILES
void CEx06dView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CFileDialog dlg(TRUE, "bmp", "*.bmp");
    if (dlg.DoModal() != IDOK) {
        return;
    }
#ifdef MEMORY_MAPPED_FILES
    if (m_dibFile.AttachMapFile(dlg.GetPathName(),
            TRUE) == TRUE) { // share
        Invalidate();
    }
 #else
    CFile file;
    file.Open(dlg.GetPathName(), CFile::modeRead);
    if (m_dibFile.Read(&file) == TRUE) {
        Invalidate();
    }
#endif // MEMORY_MAPPED_FILES
    CClientDC dc(this);
    m_dibFile.SetSystemPalette(&dc);

}
