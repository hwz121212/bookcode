// MySerializeView.cpp : implementation of the CMySerializeView class
//

#include "stdafx.h"
#include "MySerialize.h"

#include "MySerializeDoc.h"
#include "MySerializeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySerializeView

IMPLEMENT_DYNCREATE(CMySerializeView, CView)

BEGIN_MESSAGE_MAP(CMySerializeView, CView)
	//{{AFX_MSG_MAP(CMySerializeView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySerializeView construction/destruction

CMySerializeView::CMySerializeView()
{
	// TODO: add construction code here

}

CMySerializeView::~CMySerializeView()
{
}

BOOL CMySerializeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMySerializeView drawing

void CMySerializeView::OnDraw(CDC* pDC)
{
	CMySerializeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CRect r;
	GetClientRect(&r);
	int x=r.right/2,y=r.bottom/2;
	pDC->SetTextAlign(TA_CENTER|TA_BASELINE);
	pDC->TextOut(x,y,pDoc->StrName);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMySerializeView printing

BOOL CMySerializeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMySerializeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMySerializeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMySerializeView diagnostics

#ifdef _DEBUG
void CMySerializeView::AssertValid() const
{
	CView::AssertValid();
}

void CMySerializeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMySerializeDoc* CMySerializeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMySerializeDoc)));
	return (CMySerializeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMySerializeView message handlers
