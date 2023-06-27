// ex12cView.h : interface of the CEx12cView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX12CVIEW_H__7D12C159_6C0B_12D0_8FD6_00C04FC2A0C2__INCLUDED_)
#define AFX_EX12CVIEW_H__7D12C159_6C0B_12D0_8FD6_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx12cView : public CView
{
protected: // create from serialization only
	CEx12cView();
	DECLARE_DYNCREATE(CEx12cView)

// Attributes
public:
	CEx12cDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx12cView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx12cView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx12cView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex12cView.cpp
inline CEx12cDoc* CEx12cView::GetDocument()
   { return (CEx12cDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX12CVIEW_H__7D12C159_6C0B_12D0_8FD6_00C04FC2A0C2__INCLUDED_)
