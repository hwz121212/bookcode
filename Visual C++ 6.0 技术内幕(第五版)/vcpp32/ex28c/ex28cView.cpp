// ex28cView.cpp : implementation of the CEx28cView class
//

#include "stdafx.h"
#include "ex28c.h"

#include "ex28cDoc.h"
#include "ex28cView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx28cView

IMPLEMENT_DYNCREATE(CEx28cView, CView)

BEGIN_MESSAGE_MAP(CEx28cView, CView)
	//{{AFX_MSG_MAP(CEx28cView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx28cView construction/destruction

CEx28cView::CEx28cView()
{
	// TODO: add construction code here

}

CEx28cView::~CEx28cView()
{
}

BOOL CEx28cView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx28cView drawing

void CEx28cView::OnDraw(CDC* pDC)
{
	CEx28cDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDC->Rectangle(CRect(500, -1000, 1500, -2000));
	pDC->TextOut(0, 0, pDoc->m_strText);
}

/////////////////////////////////////////////////////////////////////////////
// CEx28cView printing

BOOL CEx28cView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx28cView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx28cView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEx28cView diagnostics

#ifdef _DEBUG
void CEx28cView::AssertValid() const
{
	CView::AssertValid();
}

void CEx28cView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx28cDoc* CEx28cView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx28cDoc)));
	return (CEx28cDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx28cView message handlers

void CEx28cView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	pDC->SetMapMode(MM_HIMETRIC);
}
