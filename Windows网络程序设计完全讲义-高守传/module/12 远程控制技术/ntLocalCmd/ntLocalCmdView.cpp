/*
  This project was created and edited using the MFC SelfBanner AppWizard.

  Comment: 管道编程－本地CMD.

  Project: ntLocalCmd.
  Author : dhyao
  Date   : 星期一, 二月 02, 2009
*/
/////////////////////////////////////////////////////////////////////

// ntLocalCmdView.cpp : implementation of the CNtLocalCmdView class
//

#include "stdafx.h"
#include "ntLocalCmd.h"

#include "ntLocalCmdDoc.h"
#include "ntLocalCmdView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNtLocalCmdView

IMPLEMENT_DYNCREATE(CNtLocalCmdView, CCmdView)

BEGIN_MESSAGE_MAP(CNtLocalCmdView, CCmdView)
	//{{AFX_MSG_MAP(CNtLocalCmdView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CCmdView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CCmdView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CCmdView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNtLocalCmdView construction/destruction

CNtLocalCmdView::CNtLocalCmdView()
{
	// TODO: add construction code here

}

CNtLocalCmdView::~CNtLocalCmdView()
{
}

BOOL CNtLocalCmdView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CCmdView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CNtLocalCmdView drawing

void CNtLocalCmdView::OnDraw(CDC* pDC)
{
	CNtLocalCmdDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CNtLocalCmdView printing

BOOL CNtLocalCmdView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CCmdView preparation
	return CCmdView::OnPreparePrinting(pInfo);
}

void CNtLocalCmdView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CCmdView begin printing.
	CCmdView::OnBeginPrinting(pDC, pInfo);
}

void CNtLocalCmdView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CCmdView end printing
	CCmdView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CNtLocalCmdView diagnostics

#ifdef _DEBUG
void CNtLocalCmdView::AssertValid() const
{
	CCmdView::AssertValid();
}

void CNtLocalCmdView::Dump(CDumpContext& dc) const
{
	CCmdView::Dump(dc);
}

CNtLocalCmdDoc* CNtLocalCmdView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNtLocalCmdDoc)));
	return (CNtLocalCmdDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNtLocalCmdView message handlers
