// Ex24aView.cpp : implementation of the CEx24aView class
//

#include "stdafx.h"
#include "Ex24a.h"
#include "cdib.h"
#include "Ex24aDoc.h"
#include "Ex24aView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx24aView

IMPLEMENT_DYNCREATE(CEx24aView, CScrollView)

BEGIN_MESSAGE_MAP(CEx24aView, CScrollView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
    ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
    ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
    ON_COMMAND(ID_EDIT_CUT, OnEditCut)
    ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
    ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
    ON_COMMAND(ID_EDIT_COPYTO, OnEditCopyto)
    ON_COMMAND(ID_EDIT_PASTEFROM, OnEditPastefrom)
    ON_WM_LBUTTONDOWN()
    ON_WM_SETCURSOR()
    ON_WM_SETFOCUS()
	ON_MESSAGE(WM_VIEWPALETTECHANGED, OnViewPaletteChanged)
END_MESSAGE_MAP()

// CEx24aView construction/destruction

CEx24aView::CEx24aView() : m_sizeTotal(800, 1050), // 8-by-10.5 inches
                                                   //  when printed
    m_rectTracker(50, 50, 250, 250)
{
}

CEx24aView::~CEx24aView()
{
}

BOOL CEx24aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// CEx24aView drawing

void CEx24aView::OnDraw(CDC* pDC)
{
    CDib& dib = GetDocument()->m_dib;
    m_tracker.m_rect = m_rectTracker;
    pDC->LPtoDP(m_tracker.m_rect); // tracker wants device coordinates
    m_tracker.Draw(pDC);
    dib.Draw(pDC, m_rectTracker.TopLeft(), m_rectTracker.Size());
}


// CEx24aView printing

BOOL CEx24aView::OnPreparePrinting(CPrintInfo* pInfo)
{
    pInfo->SetMaxPage(1);
    return DoPreparePrinting(pInfo);
}

void CEx24aView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx24aView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CEx24aView diagnostics

#ifdef _DEBUG
void CEx24aView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CEx24aView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CEx24aDoc* CEx24aView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx24aDoc)));
	return (CEx24aDoc*)m_pDocument;
}
#endif //_DEBUG



// helper functions used for clipboard and drag-drop 

BOOL CEx24aView::DoPasteDib(COleDataObject* pDataObject)
{
    // update command user interface should keep us out of 
    //  here if not CF_DIB
    if (!pDataObject->IsDataAvailable(CF_DIB)) {
        TRACE("CF_DIB format is unavailable\n");
        return FALSE;
    }
    CEx24aDoc* pDoc = GetDocument();
    // Seems to be MOVEABLE memory, so we must use GlobalLock!
    //  (hDib != lpDib) GetGlobalData copies the memory, so we can
    //  hang onto it until we delete the CDib.
    HGLOBAL hDib = pDataObject->GetGlobalData(CF_DIB);
    ASSERT(hDib != NULL);
    LPVOID lpDib = ::GlobalLock(hDib);
    ASSERT(lpDib != NULL);
     pDoc->m_dib.AttachMemory(lpDib, TRUE, hDib);
    pDoc->SetModifiedFlag();
    pDoc->UpdateAllViews(NULL);
    return TRUE;
}

COleDataSource* CEx24aView::SaveDib()
{
    CDib& dib = GetDocument()->m_dib;
    if (dib.GetSizeImage() > 0) {
        COleDataSource* pSource = new COleDataSource();
        int nHeaderSize = dib.GetSizeHeader();
        int nImageSize = dib.GetSizeImage();
        HGLOBAL hHeader = ::GlobalAlloc(GMEM_SHARE,
            nHeaderSize + nImageSize);
        LPVOID pHeader = ::GlobalLock(hHeader);
        ASSERT(pHeader != NULL);
        LPVOID pImage = (LPBYTE) pHeader + nHeaderSize;
        memcpy(pHeader, dib.m_lpBMIH, nHeaderSize); 
        memcpy(pImage, dib.m_lpImage, nImageSize);
        // Receiver is supposed to free the global memory 
        ::GlobalUnlock(hHeader);
        pSource->CacheGlobalData(CF_DIB, hHeader);
        return pSource;
    }
    return NULL;
}

// CEx24aView message handlers

void CEx24aView::OnEditCopy()
{
    COleDataSource* pSource = SaveDib();
    if (pSource) {
        pSource->SetClipboard(); // OLE deletes data source
    }
}

void CEx24aView::OnUpdateEditCopy(CCmdUI *pCmdUI)
{
    // serves Copy, Cut, and Copy To
    CDib& dib = GetDocument()->m_dib;
    pCmdUI->Enable(dib.GetSizeImage() > 0L);
}

void CEx24aView::OnEditCut()
{
    OnEditCopy();  
    GetDocument()->OnEditClearall();
}

void CEx24aView::OnEditPaste()
{
    CEx24aDoc* pDoc = GetDocument();
    COleDataObject dataObject;
    VERIFY(dataObject.AttachClipboard());
    DoPasteDib(&dataObject);
    CClientDC dc(this);
    pDoc->m_dib.UsePalette(&dc);
    pDoc->SetModifiedFlag();
    pDoc->UpdateAllViews(NULL);
}

void CEx24aView::OnUpdateEditPaste(CCmdUI *pCmdUI)
{
    COleDataObject dataObject;
    BOOL bAvail = dataObject.AttachClipboard() &&
        dataObject.IsDataAvailable(CF_DIB);
    pCmdUI->Enable(bAvail);

}

void CEx24aView::OnEditCopyto()
{
    CDib& dib = GetDocument()->m_dib;
    CFileDialog dlg(FALSE, "bmp", "*.bmp");
    if (dlg.DoModal() != IDOK) return;

    BeginWaitCursor();
    dib.CopyToMapFile(dlg.GetPathName());
    EndWaitCursor();
}

void CEx24aView::OnEditPastefrom()
{
    CEx24aDoc* pDoc = GetDocument();
    CFileDialog dlg(TRUE, "bmp", "*.bmp");
    if (dlg.DoModal() != IDOK) return;
    if (pDoc->m_dib.AttachMapFile(dlg.GetPathName(), TRUE)) { // share
        CClientDC dc(this);
        pDoc->m_dib.SetSystemPalette(&dc);
        pDoc->m_dib.UsePalette(&dc);
        pDoc->SetModifiedFlag();
         pDoc->UpdateAllViews(NULL);
    }
}

void CEx24aView::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (m_tracker.Track(this, point, FALSE, NULL)) {
        CClientDC dc(this);
        OnPrepareDC(&dc);
        m_rectTracker = m_tracker.m_rect;
        dc.DPtoLP(m_rectTracker); // Update logical coordinates
        Invalidate();
    }
}

BOOL CEx24aView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
    if (m_tracker.SetCursor(pWnd, nHitTest)) {
        return TRUE;
    }
    else {
        return CScrollView::OnSetCursor(pWnd, nHitTest, message);
    }
}

void CEx24aView::OnSetFocus(CWnd* pOldWnd)
{
    CScrollView::OnSetFocus(pOldWnd);
    AfxGetApp()->m_pMainWnd->SendMessage(WM_PALETTECHANGED, 
        (UINT) GetSafeHwnd());
}

void CEx24aView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
    // custom MM_LOENGLISH; positive y is down
    if (pDC->IsPrinting()) {
        int nHsize = pDC->GetDeviceCaps(HORZSIZE) * 1000 / 254;
        int nVsize = pDC->GetDeviceCaps(VERTSIZE) * 1000 / 254;
        pDC->SetMapMode(MM_ANISOTROPIC);
        pDC->SetWindowExt(nHsize, nVsize);
        pDC->SetViewportExt(pDC->GetDeviceCaps(HORZRES),
                            pDC->GetDeviceCaps(VERTRES));
    }
    else {
        CScrollView::OnPrepareDC(pDC, pInfo);
    }
}

void CEx24aView::OnInitialUpdate()
{
    SetScrollSizes(MM_TEXT, m_sizeTotal);
    m_tracker.m_nStyle = CRectTracker::solidLine |
        CRectTracker::resizeOutside;
    CScrollView::OnInitialUpdate();
}

LRESULT CEx24aView::OnViewPaletteChanged(WPARAM wParam, LPARAM lParam)
{
	TRACE("CEx24aView::OnViewPaletteChanged, HWND = %x, code = %d\n", GetSafeHwnd(), wParam);
	CClientDC dc(this);
    GetDocument()->m_dib.UsePalette(&dc, wParam);
	Invalidate();
	return 0;
}