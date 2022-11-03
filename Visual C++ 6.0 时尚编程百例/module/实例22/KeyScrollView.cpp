// KeyScrollView.cpp : implementation of the CKeyScrollView class
//

#include "stdafx.h"
#include "KeyScroll.h"

#include "KeyScrollDoc.h"
#include "KeyScrollView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKeyScrollView

IMPLEMENT_DYNCREATE(CKeyScrollView, CScrollView)

BEGIN_MESSAGE_MAP(CKeyScrollView, CScrollView)
	//{{AFX_MSG_MAP(CKeyScrollView)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeyScrollView construction/destruction

CKeyScrollView::CKeyScrollView()
{
	// TODO: add construction code here

}

CKeyScrollView::~CKeyScrollView()
{
}

BOOL CKeyScrollView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CKeyScrollView drawing

void CKeyScrollView::OnDraw(CDC* pDC)
{
    pDC->TextOut(100,100,"欢迎学习VC++6.0,这里是VC++6.0百例");
	// TODO: add draw code for native data here
}



	void CKeyScrollView::OnInitialUpdate()
{
	 CScrollView::OnInitialUpdate();
        CSize sizeTotal(25000,40000);    // 2.5  by  30cm
        CSize  sizePage(sizeTotal.cx / 3,sizeTotal.cy / 3);
        CSize  sizeLine(sizeTotal.cx / 100,sizeTotal.cy / 100);  	
        SetScrollSizes(MM_TEXT,sizeTotal,sizePage,sizeLine);  //设置滚动模式
}



/////////////////////////////////////////////////////////////////////////////
// CKeyScrollView printing

BOOL CKeyScrollView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CKeyScrollView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CKeyScrollView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CKeyScrollView diagnostics

#ifdef _DEBUG
void CKeyScrollView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CKeyScrollView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CKeyScrollDoc* CKeyScrollView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKeyScrollDoc)));
	return (CKeyScrollDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CKeyScrollView message handlers

void CKeyScrollView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch(nChar){
		case VK_HOME:             //响应HOME键
			 OnVScroll(SB_TOP,0,NULL);
			 OnHScroll(SB_LEFT,0,NULL);
			 break;
        case VK_END:                 //响应END键
			 OnVScroll(SB_BOTTOM,0,NULL);
			 OnHScroll(SB_RIGHT,0,NULL);
			 break;
        case VK_UP:                   //响应UP键
			 OnVScroll(SB_LINEUP,0,NULL);
			 break;
		case VK_DOWN:                //响应DOWN键
			 OnVScroll(SB_LINEDOWN,0,NULL);
			 break;
		case VK_PRIOR:                //响应PRIOR键
			 OnVScroll(SB_PAGEUP,0,NULL);
			 break;                    
		case VK_NEXT:                //响应NEXT键
			 OnVScroll(SB_PAGEDOWN,0,NULL);
			 break;
        case VK_LEFT:                //响应LEFT键
			 OnHScroll(SB_LINELEFT,0,NULL);
			 break;    
		case VK_RIGHT:                //响应RIGHT键
			 OnHScroll(SB_LINERIGHT,0,NULL);
			 break;
		default:
			break;
	   }
}
