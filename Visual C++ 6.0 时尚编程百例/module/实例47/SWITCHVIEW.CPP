// switchView.cpp : implementation of the CSwitchView class
//

#include "stdafx.h"
#include "switch.h"

#include "switchDoc.h"
#include "switchView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSwitchView

IMPLEMENT_DYNCREATE(CSwitchView, CView)

BEGIN_MESSAGE_MAP(CSwitchView, CView)
	//{{AFX_MSG_MAP(CSwitchView)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSwitchView construction/destruction

CSwitchView::CSwitchView()
{
	// TODO: add construction code here

}

CSwitchView::~CSwitchView()
{
}

BOOL CSwitchView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSwitchView drawing

void CSwitchView::OnDraw(CDC* pDC)
{
	CSwitchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSwitchView printing

BOOL CSwitchView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSwitchView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSwitchView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSwitchView diagnostics

#ifdef _DEBUG
void CSwitchView::AssertValid() const
{
	CView::AssertValid();
}

void CSwitchView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSwitchDoc* CSwitchView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSwitchDoc)));
	return (CSwitchDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSwitchView message handlers

void CSwitchView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
   dc.TextOut(0,0,"View 0",6);	
	// Do not call CView::OnPaint() for painting messages
}
