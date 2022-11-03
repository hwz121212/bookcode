// ClientNetView.cpp : implementation of the CClientNetView class
//

#include "stdafx.h"
#include "ClientNet.h"

#include "ClientNetDoc.h"
#include "ClientNetView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientNetView

IMPLEMENT_DYNCREATE(CClientNetView, CView)

BEGIN_MESSAGE_MAP(CClientNetView, CView)
	//{{AFX_MSG_MAP(CClientNetView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientNetView construction/destruction

CClientNetView::CClientNetView()
{
	// TODO: add construction code here

}

CClientNetView::~CClientNetView()
{
}

BOOL CClientNetView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CClientNetView drawing

void CClientNetView::OnDraw(CDC* pDC)
{
	CClientNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CClientNetView printing

BOOL CClientNetView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CClientNetView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CClientNetView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CClientNetView diagnostics

#ifdef _DEBUG
void CClientNetView::AssertValid() const
{
	CView::AssertValid();
}

void CClientNetView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CClientNetDoc* CClientNetView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClientNetDoc)));
	return (CClientNetDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CClientNetView message handlers
