// MyRectView.cpp : implementation of the CMyRectView class
//

#include "stdafx.h"
#include "MyRect.h"

#include "MyRectDoc.h"
#include "MyRectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define RED RGB(255,0,0)
#define GREEN RGB(0,255,0)
#define BLUE RGB(0,0,255)
#define BLACK RGB(0,0,0)
/////////////////////////////////////////////////////////////////////////////
// CMyRectView

IMPLEMENT_DYNCREATE(CMyRectView, CView)

BEGIN_MESSAGE_MAP(CMyRectView, CView)
	//{{AFX_MSG_MAP(CMyRectView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyRectView construction/destruction

CMyRectView::CMyRectView()
{
	// TODO: add construction code here

}

CMyRectView::~CMyRectView()
{
}

BOOL CMyRectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyRectView drawing

void CMyRectView::OnDraw(CDC* pDC)
{
	CMyRectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	GetClientRect(r);
	if(r.right>750&&r.right<1000||r.bottom>750&&r.bottom<1000)
	pDC->FillSolidRect(r,RED);
	else if(r.right>500&&r.right<750||r.bottom>500&&r.bottom<750)
		pDC->FillSolidRect(r,GREEN);
	else if(r.right<500||r.bottom<500)
		pDC->FillSolidRect(r,BLUE);
	else 
		pDC->FillSolidRect(r,BLACK);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMyRectView printing

BOOL CMyRectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyRectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyRectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyRectView diagnostics

#ifdef _DEBUG
void CMyRectView::AssertValid() const
{
	CView::AssertValid();
}

void CMyRectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyRectDoc* CMyRectView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyRectDoc)));
	return (CMyRectDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyRectView message handlers
