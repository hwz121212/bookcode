// ex09aView.h : interface of the CEx09aView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX09AVIEW_H__E0A2E3DF_D7BF_11D1_B2A3_FB06F1BF1F48__INCLUDED_)
#define AFX_EX09AVIEW_H__E0A2E3DF_D7BF_11D1_B2A3_FB06F1BF1F48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx09aView : public CView
{
protected: // create from serialization only
	CEx09aView();
	DECLARE_DYNCREATE(CEx09aView)

// Attributes
public:
	CEx09aDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx09aView)
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
	virtual ~CEx09aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx09aView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex09aView.cpp
inline CEx09aDoc* CEx09aView::GetDocument()
   { return (CEx09aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX09AVIEW_H__E0A2E3DF_D7BF_11D1_B2A3_FB06F1BF1F48__INCLUDED_)
