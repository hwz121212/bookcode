// ModellessView.h : interface of the CModellessView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODELLESSVIEW_H__7F0ECE60_1C5D_11D4_B0E6_00001A012804__INCLUDED_)
#define AFX_MODELLESSVIEW_H__7F0ECE60_1C5D_11D4_B0E6_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ModellessDialog.h"

class CModellessView : public CView
{
protected: // create from serialization only
	CModellessView();
	DECLARE_DYNCREATE(CModellessView)

// Attributes
public:
	CModellessDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModellessView)
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
	CModellessDialog * m_pModelless;
	virtual ~CModellessView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CModellessView)
	afx_msg void OnModelless();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ModellessView.cpp
inline CModellessDoc* CModellessView::GetDocument()
   { return (CModellessDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODELLESSVIEW_H__7F0ECE60_1C5D_11D4_B0E6_00001A012804__INCLUDED_)
