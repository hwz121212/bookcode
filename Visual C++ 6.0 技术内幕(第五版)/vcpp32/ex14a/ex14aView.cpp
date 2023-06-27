// ex14aView.cpp : implementation of the CEx14aView class
//

#include "stdafx.h"
#include "ex14a.h"

#include "ex14aDoc.h"
#include "ex14aView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx14aView

IMPLEMENT_DYNCREATE(CEx14aView, CView)

BEGIN_MESSAGE_MAP(CEx14aView, CView)
	//{{AFX_MSG_MAP(CEx14aView)
	ON_COMMAND(ID_DRAW_CIRCLE, OnDrawCircle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CIRCLE, OnUpdateDrawCircle)
	ON_COMMAND(ID_DRAW_PATTERN, OnDrawPattern)
	ON_UPDATE_COMMAND_UI(ID_DRAW_PATTERN, OnUpdateDrawPattern)
	ON_COMMAND(ID_DRAW_SQUARE, OnDrawSquare)
	ON_UPDATE_COMMAND_UI(ID_DRAW_SQUARE, OnUpdateDrawSquare)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx14aView construction/destruction

CEx14aView::CEx14aView() : m_rect(0, 0, 100, 100)
{
    m_bCircle = TRUE;
    m_bPattern = FALSE;

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

/////////////////////////////////////////////////////////////////////////////
// CEx14aView drawing

void CEx14aView::OnDraw(CDC* pDC)
{
    CBrush brush(HS_BDIAGONAL, 0L); // brush with diagonal pattern

    if (m_bPattern) {
        pDC->SelectObject(&brush);
    }
    else {
        pDC->SelectStockObject(WHITE_BRUSH);
    }
    if (m_bCircle) {
        pDC->Ellipse(m_rect);
    }
    else {
        pDC->Rectangle(m_rect);
    }
    pDC->SelectStockObject(WHITE_BRUSH); // Deselects brush
                                         //  if selected
}

/////////////////////////////////////////////////////////////////////////////
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

CEx14aDoc* CEx14aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx14aDoc)));
	return (CEx14aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx14aView message handlers

void CEx14aView::OnDrawCircle() 
{
    m_bCircle = TRUE;
    m_rect += CPoint(25, 25);
    InvalidateRect(m_rect);
	
}

void CEx14aView::OnUpdateDrawCircle(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(!m_bCircle);	
}

void CEx14aView::OnDrawPattern() 
{
    m_bPattern ^= 1;	
}

void CEx14aView::OnUpdateDrawPattern(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck(m_bPattern);	
}

void CEx14aView::OnDrawSquare() 
{
    m_bCircle = FALSE;
    m_rect += CPoint(25, 25);
    InvalidateRect(m_rect);
	
}

void CEx14aView::OnUpdateDrawSquare(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(m_bCircle);	
}
