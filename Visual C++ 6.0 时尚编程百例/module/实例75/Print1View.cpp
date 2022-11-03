// Print1View.cpp : implementation of the CPrint1View class
//

#include "stdafx.h"
#include "Print1.h"

#include "Print1Doc.h"
#include "Print1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrint1View

IMPLEMENT_DYNCREATE(CPrint1View, CScrollView)

BEGIN_MESSAGE_MAP(CPrint1View, CScrollView)
	//{{AFX_MSG_MAP(CPrint1View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrint1View construction/destruction

CPrint1View::CPrint1View():m_rectPrint(0,0,11520,-15120)
{
	// TODO: add construction code here

}

CPrint1View::~CPrint1View()
{
}

BOOL CPrint1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPrint1View drawing

void CPrint1View::OnDraw(CDC* pDC)
{
	int i,j,nHeight;
	CString str;
	TEXTMETRIC tm;

	CPrint1Doc* pDoc = GetDocument();
	pDC->Rectangle(m_rectPrint+CRect(0,0,-20,20));//打印矩形
	j=m_rectPrint.Width()/1440;
	for(i=0;i<=j;i++)//设置横向尺寸
	{
		str.Format("%02d",i);
		pDC->TextOut(i*1440,0,str);
	}
	j=-m_rectPrint.Height()/1440;
	for(i=0;i<=j;i++)//设置纵向尺寸
	{
        str.Format("%02d",i);
		pDC->TextOut(0,-i*1440,str);
	}
	pDC->GetTextMetrics(&tm);//得到字体结构
	nHeight=tm.tmHeight+tm.tmExternalLeading;//得到字体高度
	j=pDoc->m_StringArray.GetSize();
	for(i=0;i<j;i++)//输出打印文本
	{
		pDC->TextOut(720,-i*nHeight-720,pDoc->m_StringArray[i]);
	}
	
	// TODO: add draw code for native data here
}

void CPrint1View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal(m_rectPrint.Width(),-m_rectPrint.Height());
	CSize sizePage(sizeTotal.cx/4,sizeTotal.cy/4);
	CSize sizeLine(sizeTotal.cx/50,sizeTotal.cy/50);
	SetScrollSizes(MM_TWIPS, sizeTotal,sizePage,sizeLine);
}

/////////////////////////////////////////////////////////////////////////////
// CPrint1View printing

BOOL CPrint1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	pInfo->SetMaxPage(1);//设置打印最大页数
	return DoPreparePrinting(pInfo);
}

void CPrint1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPrint1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPrint1View diagnostics

#ifdef _DEBUG
void CPrint1View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CPrint1View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CPrint1Doc* CPrint1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPrint1Doc)));
	return (CPrint1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPrint1View message handlers
