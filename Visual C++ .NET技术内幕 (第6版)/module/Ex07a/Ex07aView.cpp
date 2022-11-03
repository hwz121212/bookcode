// Ex07aView.cpp : implementation of the CEx07aView class
//

#include "stdafx.h"
#include "Ex07a.h"

#include "Ex07aDoc.h"
#include "Ex07aView.h"
#include "Ex07aDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx07aView

IMPLEMENT_DYNCREATE(CEx07aView, CView)

BEGIN_MESSAGE_MAP(CEx07aView, CView)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CEx07aView construction/destruction

CEx07aView::CEx07aView()
{
	// TODO: add construction code here

}

CEx07aView::~CEx07aView()
{
}

BOOL CEx07aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEx07aView drawing

void CEx07aView::OnDraw(CDC* pDC)
{
	CEx07aDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDC->TextOut(0, 0, "Press the left mouse button here.");
}


// CEx07aView diagnostics

#ifdef _DEBUG
void CEx07aView::AssertValid() const
{
	CView::AssertValid();
}

void CEx07aView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx07aDoc* CEx07aView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx07aDoc)));
	return (CEx07aDoc*)m_pDocument;
}
#endif //_DEBUG


// CEx07aView message handlers

void CEx07aView::OnLButtonDown(UINT nFlags, CPoint point)
{
    CEx07aDialog dlg;
    dlg.m_strName  = "Shakespeare, Will";
    dlg.m_nSsn     = 307806636;
    dlg.m_nCat     = 1;  // 0 = hourly, 1 = salary
    dlg.m_strBio   = "This person is not a well-motivated tech writer";
    dlg.m_bInsLife = TRUE;
    dlg.m_bInsDis  = FALSE;
    dlg.m_bInsMed  = TRUE;
    dlg.m_strDept  = "Documentation";
    dlg.m_strSkill = "Writer";
    dlg.m_nLang    = 0;
    dlg.m_strEduc  = "College";
    dlg.m_nLoyal   = dlg.m_nRely = 50;
    int ret = dlg.DoModal();
    TRACE("DoModal return = %d\n", ret);
    TRACE("name = %s, ssn = %d, cat = %d\n",
          dlg.m_strName, dlg.m_nSsn, dlg.m_nCat);
    TRACE("dept = %s, skill = %s, lang = %d, educ = %s\n",
          dlg.m_strDept, dlg.m_strSkill, dlg.m_nLang, dlg.m_strEduc);
    TRACE("life = %d, dis = %d, med = %d, bio = %s\n",
          dlg.m_bInsLife, dlg.m_bInsDis, dlg.m_bInsMed, dlg.m_strBio);
    TRACE("loyalty = %d, reliability = %d\n",
          dlg.m_nLoyal, dlg.m_nRely);
}
