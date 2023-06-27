// ex11cView.h : interface of the CEx11cView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX11CVIEW_H__3C766E0F_A77D_11D1_8ED7_0080C7360DC1__INCLUDED_)
#define AFX_EX11CVIEW_H__3C766E0F_A77D_11D1_8ED7_0080C7360DC1__INCLUDED_

#include "cdib.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx11cView : public CScrollView
{
protected: // create from serialization only
	CEx11cView();
	DECLARE_DYNCREATE(CEx11cView)

// Attributes
public:
	CEx11cDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx11cView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx11cView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx11cView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CDib m_dibFile;
	CDib m_dibResource;
};

#ifndef _DEBUG  // debug version in ex11cView.cpp
inline CEx11cDoc* CEx11cView::GetDocument()
   { return (CEx11cDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX11CVIEW_H__3C766E0F_A77D_11D1_8ED7_0080C7360DC1__INCLUDED_)
