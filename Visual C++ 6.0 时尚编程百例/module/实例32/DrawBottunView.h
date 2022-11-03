// DrawBottunView.h : interface of the CDrawBottunView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWBOTTUNVIEW_H__4AF533ED_C125_11D2_A71D_A0815CB6AA6A__INCLUDED_)
#define AFX_DRAWBOTTUNVIEW_H__4AF533ED_C125_11D2_A71D_A0815CB6AA6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MyDialog.h"

class CDrawBottunView : public CView
{
protected: // create from serialization only
	CDrawBottunView();
	DECLARE_DYNCREATE(CDrawBottunView)

// Attributes
public:
	CDrawBottunDoc* GetDocument();

// Operations
public:
	MyDialog *Dlg;
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawBottunView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDrawBottunView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDrawBottunView)
	afx_msg void OnDisplay();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DrawBottunView.cpp
inline CDrawBottunDoc* CDrawBottunView::GetDocument()
   { return (CDrawBottunDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWBOTTUNVIEW_H__4AF533ED_C125_11D2_A71D_A0815CB6AA6A__INCLUDED_)
