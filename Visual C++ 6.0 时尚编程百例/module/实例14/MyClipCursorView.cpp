// MyClipCursorView.cpp : implementation of the CMyClipCursorView class
//

#include "stdafx.h"
#include "MyClipCursor.h"

#include "MyClipCursorDoc.h"
#include "MyClipCursorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyClipCursorView

IMPLEMENT_DYNCREATE(CMyClipCursorView, CView)

BEGIN_MESSAGE_MAP(CMyClipCursorView, CView)
	//{{AFX_MSG_MAP(CMyClipCursorView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyClipCursorView construction/destruction

CMyClipCursorView::CMyClipCursorView()
{
	m_hClick=0;
    
}

CMyClipCursorView::~CMyClipCursorView()
{
}

BOOL CMyClipCursorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyClipCursorView drawing

void CMyClipCursorView::OnDraw(CDC* pDC)
{
	CMyClipCursorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMyClipCursorView printing

BOOL CMyClipCursorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyClipCursorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyClipCursorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyClipCursorView diagnostics

#ifdef _DEBUG
void CMyClipCursorView::AssertValid() const
{
	CView::AssertValid();
}

void CMyClipCursorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyClipCursorDoc* CMyClipCursorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyClipCursorDoc)));
	return (CMyClipCursorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyClipCursorView message handlers
void CMyClipCursorView::LoadCur(UINT CurName)
{
	m_hCursor=AfxGetApp()->LoadCursor(CurName);
}
void CMyClipCursorView::GetCur(int ID_NO)
{
	if(m_hClick>6)
		m_hClick=1;
	switch(m_hClick)
	{
	  case 1:LoadCur(IDC_CURSOR1);break;
      case 2:LoadCur(IDC_CURSOR2);break;
      case 3:LoadCur(IDC_CURSOR3);break;
	  case 4:LoadCur(IDC_CURSOR4);break;
	  case 5:LoadCur(IDC_CURSOR5);break;
	  case 6:LoadCur(IDC_CURSOR6);break;
	}
}
void CMyClipCursorView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	++m_hClick;
    GetCur(m_hClick);
	SetCursor(m_hCursor);
    RECT rect;
    GetClientRect(&rect);
    ClientToScreen(&rect);
    ClipCursor(&rect);	
    
	CView::OnLButtonDown(nFlags, point);
}

void CMyClipCursorView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	ClipCursor(NULL);
	CView::OnLButtonUp(nFlags, point);
}

void CMyClipCursorView::OnMouseMove(UINT nFlags, CPoint point) 
{
	SetCursor(m_hCursor);
	
	CView::OnMouseMove(nFlags, point);
}
