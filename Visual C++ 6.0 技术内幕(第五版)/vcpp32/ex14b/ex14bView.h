// ex14bView.h : interface of the CEx14bView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX14BVIEW_H__361E2163_B1BB_11D1_8ED7_0080C7360DC1__INCLUDED_)
#define AFX_EX14BVIEW_H__361E2163_B1BB_11D1_8ED7_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx14bView : public CView
{
protected: // create from serialization only
	CEx14bView();
	DECLARE_DYNCREATE(CEx14bView)

// Attributes
public:
	CEx14bDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx14bView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx14bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx14bView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex14bView.cpp
inline CEx14bDoc* CEx14bView::GetDocument()
   { return (CEx14bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX14BVIEW_H__361E2163_B1BB_11D1_8ED7_0080C7360DC1__INCLUDED_)
