// ex12bView.h : interface of the CEx12bView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX12BVIEW_H__7D12C144_6C0B_12D0_8FD6_00C04FC2A0C2__INCLUDED_)
#define AFX_EX12BVIEW_H__7D12C144_6C0B_12D0_8FD6_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx12bView : public CView
{
protected: // create from serialization only
	CEx12bView();
	DECLARE_DYNCREATE(CEx12bView)

// Attributes
public:
	CEx12bDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx12bView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx12bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx12bView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex12bView.cpp
inline CEx12bDoc* CEx12bView::GetDocument()
   { return (CEx12bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX12BVIEW_H__7D12C144_6C0B_12D0_8FD6_00C04FC2A0C2__INCLUDED_)
