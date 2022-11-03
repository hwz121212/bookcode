// Ex07cView.cpp : implementation of the CEx07cView class
//

#include "stdafx.h"
#include "Ex07c.h"

#include "Ex07cDoc.h"
#include "Ex07cView.h"
#include "Ex07cDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx07cView

IMPLEMENT_DYNCREATE(CEx07cView, CView)

BEGIN_MESSAGE_MAP(CEx07cView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
    ON_MESSAGE(WM_GOODBYE, OnGoodbye)
END_MESSAGE_MAP()

// CEx07cView construction/destruction

CEx07cView::CEx07cView()
{
    m_pDlg = new CEx07cDialog(this);
}

CEx07cView::~CEx07cView()
{
    delete m_pDlg; // destroys window if not already destroyed
}

BOOL CEx07cView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEx07cView drawing

void CEx07cView::OnDraw(CDC* pDC)
{
	CEx07cDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    pDC->TextOut(0, 0, "Press the left mouse button here.");
}


// CEx07cView diagnostics

#ifdef _DEBUG
void CEx07cView::AssertValid() const
{
	CView::AssertValid();
}

void CEx07cView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx07cDoc* CEx07cView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx07cDoc)));
	return (CEx07cDoc*)m_pDocument;
}
#endif //_DEBUG


// CEx07cView message handlers

void CEx07cView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // creates the dialog if not created already
    if (m_pDlg->GetSafeHwnd() == 0) {
        m_pDlg->Create(); // displays the dialog window
    }
}

void CEx07cView::OnRButtonDown(UINT nFlags, CPoint point)
{
    m_pDlg->DestroyWindow();
    // no problem if window was already destroyed
}

LRESULT CEx07cView::OnGoodbye(WPARAM wParam, LPARAM lParam)
{
    // message received in response to modeless dialog OK
    //  and Cancel buttons
    TRACE("CEx07cView::OnGoodbye %x, %lx\n", wParam, lParam);
    TRACE("Dialog edit1 contents = %s\n", 
          (const char*) m_pDlg->m_strEdit1);
    m_pDlg->DestroyWindow();
    return 0L;
}
