// DrawLineView.cpp : implementation of the CDrawLineView class
//

#include "stdafx.h"
#include "DrawLine.h"

#include "DrawLineDoc.h"
#include "DrawLineView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawLineView

IMPLEMENT_DYNCREATE(CDrawLineView, CView)

BEGIN_MESSAGE_MAP(CDrawLineView, CView)
	//{{AFX_MSG_MAP(CDrawLineView)
	ON_COMMAND(ID_DRAWLINE, OnDrawline)
	ON_WM_TIMER()
	ON_COMMAND(ID_STOP, OnStop)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawLineView construction/destruction

CDrawLineView::CDrawLineView()
{
	begin[0].x=100;
	begin[0].y=100;
	begin[1].x=350;
	begin[1].y=400;
	rise[0].x=3;
	rise[0].y=5;
	rise[1].x=-5;
	rise[1].y=-3;
	// TODO: add construction code here
}

CDrawLineView::~CDrawLineView()
{
}

BOOL CDrawLineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDrawLineView drawing

void CDrawLineView::OnDraw(CDC* pDC)
{
	CDrawLineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDrawLineView printing

BOOL CDrawLineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDrawLineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDrawLineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDrawLineView diagnostics

#ifdef _DEBUG
void CDrawLineView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawLineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawLineDoc* CDrawLineView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawLineDoc)));
	return (CDrawLineDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawLineView message handlers

COLORREF CDrawLineView::SetColor(int x,int y)
{
  long red,blue,green;
  int px,py;
  CRect rect;
  GetClientRect(&rect);
  px=rect.Width();
  py=rect.Height();
  red=y*255/py;
  blue=((py-y)*255/py+x*255/px)/2;
  green=((py-y)*255/py+(px-x)*255/px)/2;
  return RGB(red+LineRand(2),green+LineRand(2),blue+LineRand(2));
}

UINT CDrawLineView::LineRand(UINT max)
{
	int nRand=rand();
	float fLine=(float)max/RAND_MAX;
	float fVal=(float)fLine*nRand+0.5F;
	return (UINT)fVal;

}

void CDrawLineView::OnDrawline() 
{
    SetTimer(1,100,NULL);
	// TODO: Add your command handler code here
	
}

void CDrawLineView::OnTimer(UINT_PTR nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
   CClientDC dc(this);
   BeginDrawLine(&dc);
	CView::OnTimer(nIDEvent);
}

void CDrawLineView::BeginDrawLine(CClientDC *pDC)
{
	CString str="»­Ïß";
	pDC->TextOut(6,6,str);
	CPen pen;
	pen.CreatePen(PS_SOLID,1,SetColor(begin[1].x,begin[1].y));
	CPen *pOldpen=pDC->SelectObject(&pen);
	pDC->MoveTo(begin[0].x,begin[0].y);
	pDC->LineTo(begin[1].x,begin[1].y);

	for(int i=0;i<2;i++)
	{
		begin[i].x=begin[i].x+rise[i].x;
		begin[i].y=begin[i].y+rise[i].y;
		if(begin[i].x<=5||begin[i].x>=630) rise[i].x=-rise[i].x;
		if(begin[i].y<=5||begin[i].y>=490) rise[i].y=-rise[i].y;
	}
	pDC->SelectObject(pOldpen);

}

void CDrawLineView::OnStop() 
{
    KillTimer(1);	
}
