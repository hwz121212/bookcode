// ex27cView.h : interface of the CEx27cView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX27CVIEW_H__624519A9_F64F_11D1_B30A_D09549C10710__INCLUDED_)
#define AFX_EX27CVIEW_H__624519A9_F64F_11D1_B30A_D09549C10710__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx27cView : public CView
{
protected: // create from serialization only
	CEx27cView();
	DECLARE_DYNCREATE(CEx27cView)

// Attributes
public:
	CEx27cDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx27cView)
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
	virtual ~CEx27cView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx27cView)
	afx_msg void OnStorageRead();
	afx_msg void OnStorageWrite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex27cView.cpp
inline CEx27cDoc* CEx27cView::GetDocument()
   { return (CEx27cDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX27CVIEW_H__624519A9_F64F_11D1_B30A_D09549C10710__INCLUDED_)
