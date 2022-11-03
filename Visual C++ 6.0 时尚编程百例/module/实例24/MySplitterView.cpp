// MySplitterView.cpp : implementation of the CMySplitterView class
//

#include "stdafx.h"
#include "MySplitter.h"

#include "MySplitterDoc.h"
#include "MySplitterView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySplitterView

IMPLEMENT_DYNCREATE(CMySplitterView, CView)

BEGIN_MESSAGE_MAP(CMySplitterView, CView)
	//{{AFX_MSG_MAP(CMySplitterView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySplitterView construction/destruction

CMySplitterView::CMySplitterView()
{
	// TODO: add construction code here

}

CMySplitterView::~CMySplitterView()
{
}

BOOL CMySplitterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMySplitterView drawing

void CMySplitterView::OnDraw(CDC* pDC)
{

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMySplitterView printing

BOOL CMySplitterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMySplitterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMySplitterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMySplitterView diagnostics

#ifdef _DEBUG
void CMySplitterView::AssertValid() const
{
	CView::AssertValid();
}

void CMySplitterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}


#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMySplitterView message handlers
