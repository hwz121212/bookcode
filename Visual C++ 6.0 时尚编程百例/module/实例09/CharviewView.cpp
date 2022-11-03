// CharviewView.cpp : implementation of the CCharviewView class
//

#include "stdafx.h"
#include "Charview.h"

#include "CharviewDoc.h"
#include "CharviewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCharviewView

IMPLEMENT_DYNCREATE(CCharviewView, CView)

BEGIN_MESSAGE_MAP(CCharviewView, CView)
	//{{AFX_MSG_MAP(CCharviewView)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCharviewView construction/destruction

CCharviewView::CCharviewView()
{
	// TODO: add construction code here

}

CCharviewView::~CCharviewView()
{
}

BOOL CCharviewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCharviewView drawing

void CCharviewView::OnDraw(CDC* pDC)
{
	CCharviewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	for(int i=0;i<=pDoc->number;i++)
	{
	pDC->TextOut(0,i*tm.tmHeight,pDoc->Text[i]);
	}
    
}

/////////////////////////////////////////////////////////////////////////////
// CCharviewView printing

BOOL CCharviewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCharviewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCharviewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCharviewView diagnostics

#ifdef _DEBUG
void CCharviewView::AssertValid() const
{
	CView::AssertValid();
}

void CCharviewView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCharviewDoc* CCharviewView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCharviewDoc)));
	return (CCharviewDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCharviewView message handlers

void CCharviewView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CCharviewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(nChar!='\r'){
	if(nChar=='\b')
	{
		pDoc->Text[pDoc->number]=pDoc->Text[pDoc->number].Left(pDoc->Text[pDoc->number].GetLength()-1);
		if(pDoc->Text[pDoc->number].GetLength()==0)
			if(pDoc->number!=0)
			pDoc->number--;
			else
				pDoc->number=0;
	}
	else
	    pDoc->Text[pDoc->number] += (TCHAR)nChar;
	}
	else
	{
		pDoc->number++;
	}
	CView::OnChar(nChar,nRepCnt,nFlags);

	Invalidate( );
}
