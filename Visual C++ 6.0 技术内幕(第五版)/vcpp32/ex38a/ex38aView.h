// ex38aView.h : interface of the CEx38aView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX38AVIEW_H__25B52AEE_0533_11D2_8B47_00104B881C94__INCLUDED_)
#define AFX_EX38AVIEW_H__25B52AEE_0533_11D2_8B47_00104B881C94__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx38aView : public CView
{
protected: // create from serialization only
	CEx38aView();
	DECLARE_DYNCREATE(CEx38aView)

// Attributes
public:
	CEx38aDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx38aView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx38aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx38aView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex38aView.cpp
inline CEx38aDoc* CEx38aView::GetDocument()
   { return (CEx38aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX38AVIEW_H__25B52AEE_0533_11D2_8B47_00104B881C94__INCLUDED_)
