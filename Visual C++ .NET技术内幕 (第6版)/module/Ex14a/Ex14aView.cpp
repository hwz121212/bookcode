// Ex14aView.cpp : implementation of the CEx14aView class
//

#include "stdafx.h"
#include "Ex14a.h"

#include "Ex14aDoc.h"
#include "Ex14aView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx14aView

IMPLEMENT_DYNCREATE(CEx14aView, CView)

BEGIN_MESSAGE_MAP(CEx14aView, CView)
END_MESSAGE_MAP()

// CEx14aView construction/destruction

CEx14aView::CEx14aView()
{
	// TODO: add construction code here

}

CEx14aView::~CEx14aView()
{
}

BOOL CEx14aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEx14aView drawing

void CEx14aView::OnDraw(CDC* /*pDC*/)
{
	CEx14aDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


// CEx14aView diagnostics

#ifdef _DEBUG
void CEx14aView::AssertValid() const
{
	CView::AssertValid();
}

void CEx14aView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx14aDoc* CEx14aView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx14aDoc)));
	return (CEx14aDoc*)m_pDocument;
}
#endif //_DEBUG


// CEx14aView message handlers
