// MyCursorView.cpp : implementation of the CMyCursorView class
//

#include "stdafx.h"
#include "MyCursor.h"

#include "MyCursorDoc.h"
#include "MyCursorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyCursorView

IMPLEMENT_DYNCREATE(CMyCursorView, CView)

BEGIN_MESSAGE_MAP(CMyCursorView, CView)
	//{{AFX_MSG_MAP(CMyCursorView)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCursorView construction/destruction

CMyCursorView::CMyCursorView()
{
	// TODO: add construction code here

}

CMyCursorView::~CMyCursorView()
{
}
void CMyCursorView::LoadCursorID(UINT Cur)
{
	CurName=Cur;
}
BOOL CMyCursorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyCursorView drawing

void CMyCursorView::OnDraw(CDC* pDC)
{
	CMyCursorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMyCursorView printing

BOOL CMyCursorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyCursorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyCursorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyCursorView diagnostics

#ifdef _DEBUG
void CMyCursorView::AssertValid() const
{
	CView::AssertValid();
}

void CMyCursorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyCursorDoc* CMyCursorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyCursorDoc)));
	return (CMyCursorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyCursorView message handlers
void CMyCursorView::CapPoint(CPoint MousePos)
{   
	CRect r;
	GetClientRect(&r);
	int Width,Hight;
	Width=MousePos.x/(r.right/3); 
	Hight=MousePos.y/(r.bottom/3);
	switch(Width)
	{case 0:
	         switch(Hight)
			 {
			 case 0:LoadCursorID(IDC_CURSOR1);break;
			 case 1:LoadCursorID(IDC_CURSOR2);break;
			 case 2:LoadCursorID(IDC_CURSOR3);break;
			 }break;
	 case 1:
		      switch(Hight)
			  {
			  case 0:LoadCursorID(IDC_CURSOR4);break;
			  case 1:LoadCursorID(IDC_CURSOR5);break;
			  case 2:LoadCursorID(IDC_CURSOR6);break;
				  
			  }break;
	 case 2:
		      switch(Hight)
			  {
			   case 0:LoadCursorID(IDC_CURSOR7);break;
			   case 1:LoadCursorID(IDC_CURSOR8);break;
			   case 2:LoadCursorID(IDC_CURSOR9);break;
			  }break;
	}	  
    CUR=AfxGetApp()->LoadCursor(CurName);
	Invalidate();
}
void CMyCursorView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CapPoint(point);
	::SetCursor(CUR);
	Invalidate();
	CView::OnMouseMove(nFlags, point);
}
