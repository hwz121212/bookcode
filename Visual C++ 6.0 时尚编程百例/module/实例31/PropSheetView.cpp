// PropSheetView.cpp : implementation of the CPropSheetView class
//
#include "Sheet.h"
#include "stdafx.h"
#include "PropSheet.h"

#include "PropSheetDoc.h"
#include "PropSheetView.h"
#include "Sheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropSheetView

IMPLEMENT_DYNCREATE(CPropSheetView, CView)

BEGIN_MESSAGE_MAP(CPropSheetView, CView)
	//{{AFX_MSG_MAP(CPropSheetView)
	ON_COMMAND(ID_SHEET, OnSheet)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropSheetView construction/destruction

CPropSheetView::CPropSheetView()
{
	// TODO: add construction code here

}

CPropSheetView::~CPropSheetView()
{
}

BOOL CPropSheetView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPropSheetView drawing

void CPropSheetView::OnDraw(CDC* pDC)
{
	CPropSheetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CPropSheetView printing

BOOL CPropSheetView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPropSheetView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPropSheetView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPropSheetView diagnostics

#ifdef _DEBUG
void CPropSheetView::AssertValid() const
{
	CView::AssertValid();
}

void CPropSheetView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPropSheetDoc* CPropSheetView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPropSheetDoc)));
	return (CPropSheetDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPropSheetView message handlers

void CPropSheetView::OnSheet() 
{
  CSheet sheet("PropertySheet",this ,0);
  sheet.m_page2.m_red=1;
  sheet.DoModal();
}
