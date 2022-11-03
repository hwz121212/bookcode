// TimerView.cpp : implementation of the CTimerView class
//

#include "stdafx.h"
#include "Timer.h"

#include "TimerDoc.h"
#include "TimerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimerView

IMPLEMENT_DYNCREATE(CTimerView, CView)

BEGIN_MESSAGE_MAP(CTimerView, CView)
	//{{AFX_MSG_MAP(CTimerView)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimerView construction/destruction

CTimerView::CTimerView()
{
HBITMAP hBitmap = (HBITMAP) LoadImage(NULL, _T("show.bmp"), IMAGE_BITMAP,
                    0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
              
              m_bitmap.Attach(hBitmap); 
			  i=0;
}

CTimerView::~CTimerView()
{
}

BOOL CTimerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTimerView drawing

void CTimerView::OnDraw(CDC* pDC)
{
	CTimerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
		CDC dcImage;
	if (!dcImage.CreateCompatibleDC(pDC))
		return;

	BITMAP bm;
	m_bitmap.GetBitmap(&bm);
	// show the image.
    dcImage.SelectObject(&m_bitmap);
	pDC->BitBlt(i, 0, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCCOPY);
	SetTimer(1,10,NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CTimerView printing

BOOL CTimerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTimerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTimerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTimerView diagnostics

#ifdef _DEBUG
void CTimerView::AssertValid() const
{
	CView::AssertValid();
}

void CTimerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTimerDoc* CTimerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTimerDoc)));
	return (CTimerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTimerView message handlers

void CTimerView::OnTimer(UINT_PTR nIDEvent) 
{
i=i+1;
Invalidate();	
	CView::OnTimer(nIDEvent);
}
