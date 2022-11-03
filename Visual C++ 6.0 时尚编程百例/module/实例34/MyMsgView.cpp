// MyMsgView.cpp : implementation of the CMyMsgView class
//

#include "stdafx.h"
#include "MyMsg.h"

#include "MyMsgDoc.h"
#include "MyMsgView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyMsgView

IMPLEMENT_DYNCREATE(CMyMsgView, CView)

BEGIN_MESSAGE_MAP(CMyMsgView, CView)
	//{{AFX_MSG_MAP(CMyMsgView)
	ON_COMMAND(ID_DLG, OnDlg)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyMsgView construction/destruction

CMyMsgView::CMyMsgView()
{
}

CMyMsgView::~CMyMsgView()
{
}

BOOL CMyMsgView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyMsgView drawing

void CMyMsgView::OnDraw(CDC* pDC)
{
	CMyMsgDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CRect r;
	GetClientRect(&r);
	int x=r.right/2,y=r.bottom/2;
	pDC->SetTextAlign(TA_CENTER|TA_BASELINE);
	pDC->TextOut(x,y,str);
}

/////////////////////////////////////////////////////////////////////////////
// CMyMsgView printing

BOOL CMyMsgView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyMsgView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyMsgView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyMsgView diagnostics

#ifdef _DEBUG
void CMyMsgView::AssertValid() const
{
	CView::AssertValid();
}

void CMyMsgView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyMsgDoc* CMyMsgView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyMsgDoc)));
	return (CMyMsgDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////


void CMyMsgView::OnDlg() 
{
	// TODO: Add your command handler code here
    if(Dlg.DoModal()==IDOK)
		str=Dlg.m_String;
	Invalidate();
}
