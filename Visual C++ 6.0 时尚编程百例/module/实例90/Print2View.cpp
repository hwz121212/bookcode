// Print2View.cpp : implementation of the CPrint2View class
//

#include "stdafx.h"
#include "Print2.h"

#include "Print2Doc.h"
#include "Print2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrint2View

IMPLEMENT_DYNCREATE(CPrint2View, CView)

BEGIN_MESSAGE_MAP(CPrint2View, CView)
	//{{AFX_MSG_MAP(CPrint2View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrint2View construction/destruction

CPrint2View::CPrint2View()
{
	// TODO: add construction code here

}

CPrint2View::~CPrint2View()
{
}

BOOL CPrint2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPrint2View drawing

void CPrint2View::OnDraw(CDC* pDC)
{
    int i,j;
	CPrint2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	j=pDoc->m_rectArray.GetUpperBound();
	for(i=0;i<j;i++)
	{
		pDC->Rectangle(pDoc->m_rectArray[i]);
	}
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CPrint2View printing

BOOL CPrint2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	CPrint2Doc *pDoc=GetDocument();
	pInfo->SetMaxPage(pDoc->m_rectArray.GetUpperBound()/
		CPrint2Doc::nLinesPage+1);
	return DoPreparePrinting(pInfo);
}

void CPrint2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPrint2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPrint2View diagnostics

#ifdef _DEBUG
void CPrint2View::AssertValid() const
{
	CView::AssertValid();
}

void CPrint2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPrint2Doc* CPrint2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPrint2Doc)));
	return (CPrint2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPrint2View message handlers

void CPrint2View::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	pDC->SetMapMode(MM_LOENGLISH);
	
}
void CPrint2View::PrintPageHead(CDC *pDC)
{
	CString str;
	CPoint point(0,0);
	pDC->TextOut(point.x,point.y,"Rect drawing");
	point+=CSize(720,-720);
	str.Format("%6.6s%6.6s%6.6s%6.6s%6.6s",
		       "Index","Left","Top","Right","Bottom");
	pDC->TextOut(point.x,point.y,str);
}
void CPrint2View::PrintPageFooter(CDC *pDC)
{
	CString str;
	CPoint point(0,-14400);
	CPrint2Doc *pDoc=GetDocument();
	str.Format("Document %s",(LPCSTR)pDoc->GetTitle());
	pDC->TextOut(point.x,point.y,str);
	str.Format("Page %d",m_Page);
	CSize size=pDC->GetTextExtent(str);
	point.x+=11520-size.cx;
	pDC->TextOut(point.x,point.y,str);
}

void CPrint2View::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	int i,nStart,nEnd,nHeight;
	CString str;
	CPoint point(720,-1440);
	CFont font;
	TEXTMETRIC tm;

    pDC->SetMapMode(MM_TWIPS);
	CPrint2Doc *pDoc=GetDocument();
	m_Page=pInfo->m_nCurPage;
    nStart=(m_Page-1)*CPrint2Doc::nLinesPage;
	nEnd=nStart*CPrint2Doc::nLinesPage;

	font.CreateFont(-280,0,0,0,400,FALSE,FALSE,0,ANSI_CHARSET,
		            OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
					DEFAULT_QUALITY,DEFAULT_PITCH|FF_MODERN,
					"Courier New");
	CFont *pOld=(CFont *)(pDC->SelectObject(&font));
	PrintPageHead(pDC);
	pDC->GetTextMetrics(&tm);
	nHeight=tm.tmHeight+tm.tmExternalLeading;
	for(i=nStart;i<nEnd;i++){
		if(i>pDoc->m_rectArray.GetUpperBound()){
			break;
		}
	str.Format("%6d%6d%6d%6d%6d",i+1,
		        pDoc->m_rectArray[i].left,
				pDoc->m_rectArray[i].top,
				pDoc->m_rectArray[i].right,
	            pDoc->m_rectArray[i].bottom);
	point.y-=nHeight;
	pDC->TextOut(point.x,point.y,str);
			}
	PrintPageFooter(pDC);
	pDC->SelectObject(pOld);
}
