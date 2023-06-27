// ex22bView.h : interface of the CEx22bView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX22BVIEW_H__7C620EDA_C7EE_11D1_B30A_0080C7360DC1__INCLUDED_)
#define AFX_EX22BVIEW_H__7C620EDA_C7EE_11D1_B30A_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx22bView : public CView
{
protected: // create from serialization only
	CEx22bView();
	DECLARE_DYNCREATE(CEx22bView)

// Attributes
public:
	CEx22bDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx22bView)
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
	virtual ~CEx22bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx22bView)
	afx_msg void OnTestEx22cdll();
	afx_msg void OnTestEx22ddll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex22bView.cpp
inline CEx22bDoc* CEx22bView::GetDocument()
   { return (CEx22bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX22BVIEW_H__7C620EDA_C7EE_11D1_B30A_0080C7360DC1__INCLUDED_)
