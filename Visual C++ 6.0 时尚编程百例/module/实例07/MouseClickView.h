// MouseClickView.h : interface of the CMouseClickView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOUSECLICKVIEW_H__34D8A461_0B96_11D4_876D_00001CD613F0__INCLUDED_)
#define AFX_MOUSECLICKVIEW_H__34D8A461_0B96_11D4_876D_00001CD613F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMouseClickView : public CView
{
protected: // create from serialization only
	CMouseClickView();
	DECLARE_DYNCREATE(CMouseClickView)

// Attributes
public:
	CMouseClickDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMouseClickView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMouseClickView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMouseClickView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MouseClickView.cpp
inline CMouseClickDoc* CMouseClickView::GetDocument()
   { return (CMouseClickDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOUSECLICKVIEW_H__34D8A461_0B96_11D4_876D_00001CD613F0__INCLUDED_)
