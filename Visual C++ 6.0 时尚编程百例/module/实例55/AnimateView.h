// AnimateView.h : interface of the CAnimateView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANIMATEVIEW_H__C28396CC_1D06_11D4_B0E6_00001A012804__INCLUDED_)
#define AFX_ANIMATEVIEW_H__C28396CC_1D06_11D4_B0E6_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAnimateView : public CView
{
protected: // create from serialization only
	CAnimateView();
	DECLARE_DYNCREATE(CAnimateView)

// Attributes
public:
	CAnimateDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimateView)
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
	virtual ~CAnimateView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAnimateView)
	afx_msg void OnOpen1();
	afx_msg void OnAnimate();
	afx_msg void OnStop();
	afx_msg void OnUpdateOpen1(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CAnimateCtrl *m_Animate;
};

#ifndef _DEBUG  // debug version in AnimateView.cpp
inline CAnimateDoc* CAnimateView::GetDocument()
   { return (CAnimateDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANIMATEVIEW_H__C28396CC_1D06_11D4_B0E6_00001A012804__INCLUDED_)
