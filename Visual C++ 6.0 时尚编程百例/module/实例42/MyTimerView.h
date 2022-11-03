// MyTimerView.h : interface of the CMyTimerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYTIMERVIEW_H__5862DF0D_DB10_11D2_A71D_B295A824025F__INCLUDED_)
#define AFX_MYTIMERVIEW_H__5862DF0D_DB10_11D2_A71D_B295A824025F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyTimerView : public CView
{
protected: // create from serialization only
	CMyTimerView();
	DECLARE_DYNCREATE(CMyTimerView)
    CPoint MousePoint;
// Attributes
public:
	CMyTimerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTimerView)
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
	virtual ~CMyTimerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyTimerView)
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyTimerView.cpp
inline CMyTimerDoc* CMyTimerView::GetDocument()
   { return (CMyTimerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTIMERVIEW_H__5862DF0D_DB10_11D2_A71D_B295A824025F__INCLUDED_)
