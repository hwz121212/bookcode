// Font1View.cpp : implementation of the CFont1View class
//

#include "stdafx.h"
#include "Font1.h"

#include "Font1Doc.h"
#include "Font1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFont1View

IMPLEMENT_DYNCREATE(CFont1View, CView)

BEGIN_MESSAGE_MAP(CFont1View, CView)
	//{{AFX_MSG_MAP(CFont1View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFont1View construction/destruction

CFont1View::CFont1View()
{
	// TODO: add construction code here

}

CFont1View::~CFont1View()
{
}

BOOL CFont1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFont1View drawing

void CFont1View::OnDraw(CDC* pDC)
{
	CFont1Doc *pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	
	int cHeight;
    UINT position=0;

	for(UINT x=0;x<8;x++)
    {
	    CFont font;
		cHeight=16+x*8;
		font.CreateFont(-cHeight,           //字体字符的逻辑高度
			             0,                //字符平均宽度取默认值
						 0,                //文本行角度为0，水平
						 0,                //字符角度为0，正立
						 FW_NORMAL,        //正常字体
						 FALSE,            //不倾斜 
						 FALSE,            //不加下划线
						 FALSE,            //不加删除线
						 ANSI_CHARSET,       
						 OUT_DEFAULT_PRECIS,
						 CLIP_DEFAULT_PRECIS,
						 DEFAULT_QUALITY,
						 DEFAULT_PITCH|FF_MODERN,
						 "Times New Roman");
		CFont *oldFont=pDC->SelectObject (&font);
		position+=cHeight;
		pDC->TextOut(20,position,"VC++6.0百例");
		pDC->SelectObject(oldFont);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFont1View printing

BOOL CFont1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFont1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFont1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFont1View diagnostics

#ifdef _DEBUG
void CFont1View::AssertValid() const
{
	CView::AssertValid();
}

void CFont1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFont1Doc* CFont1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFont1Doc)));
	return (CFont1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFont1View message handlers
