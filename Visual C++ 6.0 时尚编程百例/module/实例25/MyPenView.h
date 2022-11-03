// MyPenView.h : interface of the CMyPenView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYPENVIEW_H__CF5349ED_CCFD_11D2_A71D_E6371E023F65__INCLUDED_)
#define AFX_MYPENVIEW_H__CF5349ED_CCFD_11D2_A71D_E6371E023F65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyPenView : public CView
{
protected: // create from serialization only
	CMyPenView();
	DECLARE_DYNCREATE(CMyPenView)

// Attributes
public:
	CMyPenDoc* GetDocument();
    CPoint StartPt,EndPt;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyPenView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyPenView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyPenView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyPenView.cpp
inline CMyPenDoc* CMyPenView::GetDocument()
   { return (CMyPenDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPENVIEW_H__CF5349ED_CCFD_11D2_A71D_E6371E023F65__INCLUDED_)
