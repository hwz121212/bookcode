// AcceleratorView.cpp : implementation of the CAcceleratorView class
//

#include "stdafx.h"
#include "Accelerator.h"

#include "AcceleratorDoc.h"
#include "AcceleratorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAcceleratorView

IMPLEMENT_DYNCREATE(CAcceleratorView, CView)

BEGIN_MESSAGE_MAP(CAcceleratorView, CView)
	//{{AFX_MSG_MAP(CAcceleratorView)
	ON_COMMAND(IDR_COLOR_BLUE, OnColorBlue)
	ON_COMMAND(IDR_COLOR_GREEN, OnColorGreen)
	ON_COMMAND(IDR_COLOR_RED, OnColorRed)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAcceleratorView construction/destruction

CAcceleratorView::CAcceleratorView()
{
	// TODO: add construction code here
    m_pColor=RGB(0,0,0);
}

CAcceleratorView::~CAcceleratorView()
{
}

BOOL CAcceleratorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAcceleratorView drawing

void CAcceleratorView::OnDraw(CDC* pDC)
{
	CAcceleratorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
  
	CRect r;
	GetClientRect(&r);
	int x = r.right / 2, y = r.bottom / 2;
	pDC->SetTextColor(m_pColor);
	pDC->SetTextAlign (TA_CENTER | TA_BASELINE);
	pDC->TextOut(x,y,"VC++6.0°ÙÀý");
}

/////////////////////////////////////////////////////////////////////////////
// CAcceleratorView printing

BOOL CAcceleratorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAcceleratorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAcceleratorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CAcceleratorView diagnostics

#ifdef _DEBUG
void CAcceleratorView::AssertValid() const
{
	CView::AssertValid();
}

void CAcceleratorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAcceleratorDoc* CAcceleratorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAcceleratorDoc)));
	return (CAcceleratorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAcceleratorView message handlers

void CAcceleratorView::OnColorBlue() 
{
	// TODO: Add your command handler code here
	m_pColor=RGB(0,0,255);
	Invalidate();
}

void CAcceleratorView::OnColorGreen() 
{
	// TODO: Add your command handler code here
	m_pColor=RGB(0,255,0);
	Invalidate();
}

void CAcceleratorView::OnColorRed() 
{
	// TODO: Add your command handler code here
	m_pColor=RGB(255,0,0);
	Invalidate();
}
