// MouseClickView.cpp : implementation of the CMouseClickView class
//

#include "stdafx.h"
#include "MouseClick.h"

#include "MouseClickDoc.h"
#include "MouseClickView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMouseClickView

IMPLEMENT_DYNCREATE(CMouseClickView, CView)

BEGIN_MESSAGE_MAP(CMouseClickView, CView)
	//{{AFX_MSG_MAP(CMouseClickView)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDBLCLK()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMouseClickView construction/destruction

CMouseClickView::CMouseClickView()
{
	// TODO: add construction code here

}

CMouseClickView::~CMouseClickView()
{
}

BOOL CMouseClickView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMouseClickView drawing

void CMouseClickView::OnDraw(CDC* pDC)
{
	CMouseClickDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMouseClickView printing

BOOL CMouseClickView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMouseClickView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMouseClickView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMouseClickView diagnostics

#ifdef _DEBUG
void CMouseClickView::AssertValid() const
{
	CView::AssertValid();
}

void CMouseClickView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMouseClickDoc* CMouseClickView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMouseClickDoc)));
	return (CMouseClickDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMouseClickView message handlers

void CMouseClickView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	MessageBox("Left Mouse Click!");

	
	CView::OnLButtonDown(nFlags, point);
}

void CMouseClickView::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	MessageBox("Right Double Click!");
	CView::OnRButtonDblClk(nFlags, point);
}
