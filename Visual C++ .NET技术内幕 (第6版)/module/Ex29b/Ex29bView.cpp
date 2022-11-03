// Ex29bView.cpp : implementation of the CEx29bView class
//

#include "stdafx.h"
#include "Ex29b.h"

#include "Ex29bDoc.h"
#include "Ex29bView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx29bView

IMPLEMENT_DYNCREATE(CEx29bView, CHtmlView)

BEGIN_MESSAGE_MAP(CEx29bView, CHtmlView)
END_MESSAGE_MAP()

// CEx29bView construction/destruction

CEx29bView::CEx29bView()
{
	// TODO: add construction code here

}

CEx29bView::~CEx29bView()
{
}

BOOL CEx29bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

void CEx29bView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();
	Navigate2(_T("http://msdn.microsoft.com"),NULL,NULL);
}


// CEx29bView diagnostics

#ifdef _DEBUG
void CEx29bView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CEx29bView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CEx29bDoc* CEx29bView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx29bDoc)));
	return (CEx29bDoc*)m_pDocument;
}
#endif //_DEBUG


// CEx29bView message handlers
