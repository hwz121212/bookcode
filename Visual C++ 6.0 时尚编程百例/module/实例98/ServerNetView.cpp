// ServerNetView.cpp : implementation of the CServerNetView class
//

#include "stdafx.h"
#include "ServerNet.h"

#include "ServerNetDoc.h"
#include "ServerNetView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerNetView

IMPLEMENT_DYNCREATE(CServerNetView, CView)

BEGIN_MESSAGE_MAP(CServerNetView, CView)
	//{{AFX_MSG_MAP(CServerNetView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerNetView construction/destruction

CServerNetView::CServerNetView()
{
	// TODO: add construction code here

}

CServerNetView::~CServerNetView()
{
}

BOOL CServerNetView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CServerNetView drawing

void CServerNetView::OnDraw(CDC* pDC)
{
	CServerNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CServerNetView printing

BOOL CServerNetView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CServerNetView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CServerNetView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CServerNetView diagnostics

#ifdef _DEBUG
void CServerNetView::AssertValid() const
{
	CView::AssertValid();
}

void CServerNetView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CServerNetDoc* CServerNetView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CServerNetDoc)));
	return (CServerNetDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CServerNetView message handlers
