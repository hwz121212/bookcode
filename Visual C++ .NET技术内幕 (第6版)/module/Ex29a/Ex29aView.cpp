// Ex29aView.cpp : implementation of the CEx29aView class
//

#include "stdafx.h"
#include "Ex29a.h"

#include "Ex29aDoc.h"
#include "Ex29aView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx29aView

IMPLEMENT_DYNCREATE(CEx29aView, CHtmlView)

BEGIN_MESSAGE_MAP(CEx29aView, CHtmlView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CHtmlView::OnFilePrint)
END_MESSAGE_MAP()

// CEx29aView construction/destruction

CEx29aView::CEx29aView()
{
	// TODO: add construction code here

}

CEx29aView::~CEx29aView()
{
}

BOOL CEx29aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

void CEx29aView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();
	Navigate2(_T("http://www.msdn.microsoft.com/visualc/"),NULL,NULL);
}


// CEx29aView printing



// CEx29aView diagnostics

#ifdef _DEBUG
void CEx29aView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CEx29aView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CEx29aDoc* CEx29aView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx29aDoc)));
	return (CEx29aDoc*)m_pDocument;
}
#endif //_DEBUG


// CEx29aView message handlers
