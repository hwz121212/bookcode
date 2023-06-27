// ex05cView.h : interface of the CEx05cView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX05CVIEW_H__B6B0A12D_9C84_11D1_8ED7_0080C7360DC1__INCLUDED_)
#define AFX_EX05CVIEW_H__B6B0A12D_9C84_11D1_8ED7_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx05cView : public CScrollView
{
protected: // create from serialization only
	CEx05cView();
	DECLARE_DYNCREATE(CEx05cView)

// Attributes
public:
	CEx05cDoc* GetDocument();

private:
    const CSize m_sizeEllipse; // logical
    CPoint m_pointTopLeft; // logical, top left of ellipse rectangle
    CSize  m_sizeOffset; // device, from rect top left to capture point
    BOOL   m_bCaptured;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx05cView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx05cView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx05cView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex05cView.cpp
inline CEx05cDoc* CEx05cView::GetDocument()
   { return (CEx05cDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX05CVIEW_H__B6B0A12D_9C84_11D1_8ED7_0080C7360DC1__INCLUDED_)
