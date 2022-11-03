// StatusView.cpp : implementation of the CStatusView class
//

#include "stdafx.h"
#include "Status.h"

#include "StatusDoc.h"
#include "StatusView.h"
#include "mainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatusView

IMPLEMENT_DYNCREATE(CStatusView, CView)

BEGIN_MESSAGE_MAP(CStatusView, CView)
	//{{AFX_MSG_MAP(CStatusView)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusView construction/destruction

CStatusView::CStatusView()
{
	// TODO: add construction code here

}

CStatusView::~CStatusView()
{
}

BOOL CStatusView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CStatusView drawing

void CStatusView::OnDraw(CDC* pDC)
{
	CStatusDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CStatusView printing

BOOL CStatusView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CStatusView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CStatusView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CStatusView diagnostics

#ifdef _DEBUG
void CStatusView::AssertValid() const
{
	CView::AssertValid();
}

void CStatusView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStatusDoc* CStatusView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStatusDoc)));
	return (CStatusDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStatusView message handlers

void CStatusView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CString str;
	//获取状态栏指针
	CMainFrame *pFrame=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus=&pFrame->m_wndStatusBar;
	if(pStatus){
		//显示x坐标
		str.Format("x= %d",point.x);
		pStatus->SetPaneText(1,str);
		//显示y坐标
		str.Format("y= %d",point.y);
		pStatus->SetPaneText(2,str);
	}
}
