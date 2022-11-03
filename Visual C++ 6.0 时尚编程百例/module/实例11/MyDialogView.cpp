// MyDialogView.cpp : implementation of the CMyDialogView class
//

#include "stdafx.h"
#include "MyDialog.h"

#include "MyDialogDoc.h"
#include "MyDialogView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDialogView

IMPLEMENT_DYNCREATE(CMyDialogView, CView)

BEGIN_MESSAGE_MAP(CMyDialogView, CView)
	//{{AFX_MSG_MAP(CMyDialogView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDialogView construction/destruction

CMyDialogView::CMyDialogView()
{
	// TODO: add construction code here

}

CMyDialogView::~CMyDialogView()
{
}

BOOL CMyDialogView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyDialogView drawing

void CMyDialogView::OnDraw(CDC* pDC)
{
	CMyDialogDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMyDialogView printing

BOOL CMyDialogView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyDialogView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyDialogView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyDialogView diagnostics

#ifdef _DEBUG
void CMyDialogView::AssertValid() const
{
	CView::AssertValid();
}

void CMyDialogView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyDialogDoc* CMyDialogView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDialogDoc)));
	return (CMyDialogDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyDialogView message handlers
