// MyClipCursorView.h : interface of the CMyClipCursorView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYCLIPCURSORVIEW_H__BF47E8CD_114A_11D4_876D_00001CD613F0__INCLUDED_)
#define AFX_MYCLIPCURSORVIEW_H__BF47E8CD_114A_11D4_876D_00001CD613F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyClipCursorView : public CView
{
protected: // create from serialization only
	CMyClipCursorView();
	DECLARE_DYNCREATE(CMyClipCursorView)

// Attributes
public:
	CMyClipCursorDoc* GetDocument();

// Operations
public:
	HCURSOR m_hCursor;
	int m_hClick;
protected:
	void LoadCur(UINT CurName);
	void GetCur(int ID_NO);
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyClipCursorView)
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
	virtual ~CMyClipCursorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyClipCursorView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyClipCursorView.cpp
inline CMyClipCursorDoc* CMyClipCursorView::GetDocument()
   { return (CMyClipCursorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCLIPCURSORVIEW_H__BF47E8CD_114A_11D4_876D_00001CD613F0__INCLUDED_)
