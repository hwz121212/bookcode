// ex04bView.h : interface of the CEx04bView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX04BVIEW_H__B4D49381_B379_11D1_8ED7_0080C7360DC1__INCLUDED_)
#define AFX_EX04BVIEW_H__B4D49381_B379_11D1_8ED7_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx04bView : public CView
{
protected: // create from serialization only
	CEx04bView();
	DECLARE_DYNCREATE(CEx04bView)

// Attributes
public:
	CEx04bDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx04bView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx04bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx04bView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_nColor;
	CRect m_rectEllipse;
};

#ifndef _DEBUG  // debug version in ex04bView.cpp
inline CEx04bDoc* CEx04bView::GetDocument()
   { return (CEx04bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX04BVIEW_H__B4D49381_B379_11D1_8ED7_0080C7360DC1__INCLUDED_)
