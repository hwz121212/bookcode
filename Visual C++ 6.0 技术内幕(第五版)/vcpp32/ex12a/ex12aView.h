// ex12aView.h : interface of the CEx12aView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX12AVIEW_H__CD13DB8F_A955_11D1_8ED7_0080C7360DC1__INCLUDED_)
#define AFX_EX12AVIEW_H__CD13DB8F_A955_11D1_8ED7_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx12aView : public CView
{
protected: // create from serialization only
	CEx12aView();
	DECLARE_DYNCREATE(CEx12aView)

// Attributes
public:
	CEx12aDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx12aView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx12aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx12aView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex12aView.cpp
inline CEx12aDoc* CEx12aView::GetDocument()
   { return (CEx12aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX12AVIEW_H__CD13DB8F_A955_11D1_8ED7_0080C7360DC1__INCLUDED_)
