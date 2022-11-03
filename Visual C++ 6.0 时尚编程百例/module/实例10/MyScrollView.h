// MyScrollView.h : interface of the CMyScrollView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSCROLLVIEW_H__88511F0F_B947_11D2_A71D_EEA983D5DD6C__INCLUDED_)
#define AFX_MYSCROLLVIEW_H__88511F0F_B947_11D2_A71D_EEA983D5DD6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyScrollView : public CScrollView
{
protected: // create from serialization only
	CMyScrollView();
	DECLARE_DYNCREATE(CMyScrollView)

// Attributes
public:
	CMyScrollDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyScrollView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyScrollView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyScrollView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyScrollView.cpp
inline CMyScrollDoc* CMyScrollView::GetDocument()
   { return (CMyScrollDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSCROLLVIEW_H__88511F0F_B947_11D2_A71D_EEA983D5DD6C__INCLUDED_)
