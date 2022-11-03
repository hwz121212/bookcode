// TimerView.h : interface of the CTimerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMERVIEW_H__1E490D1D_E392_11D2_A71D_924A9FFD7F4B__INCLUDED_)
#define AFX_TIMERVIEW_H__1E490D1D_E392_11D2_A71D_924A9FFD7F4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTimerView : public CView
{
protected: // create from serialization only
	CTimerView();
	DECLARE_DYNCREATE(CTimerView)

// Attributes
public:
	CTimerDoc* GetDocument();
    CBitmap m_bitmap;
	int i;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimerView)
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
	virtual ~CTimerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTimerView)
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TimerView.cpp
inline CTimerDoc* CTimerView::GetDocument()
   { return (CTimerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMERVIEW_H__1E490D1D_E392_11D2_A71D_924A9FFD7F4B__INCLUDED_)
