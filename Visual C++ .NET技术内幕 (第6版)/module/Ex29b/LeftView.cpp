// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "Ex29b.h"

#include "Ex29bDoc.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CListView)

BEGIN_MESSAGE_MAP(CLeftView, CListView)
END_MESSAGE_MAP()


// CLeftView construction/destruction

CLeftView::CLeftView()
{
	// TODO: add construction code here
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_LIST;
	return CListView::PreCreateWindow(cs);
}

void CLeftView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().
}


// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CListView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CEx29bDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx29bDoc)));
	return (CEx29bDoc*)m_pDocument;
}
#endif //_DEBUG


// CLeftView message handlers
