// MyMsgView.h : interface of the CMyMsgView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYMSGVIEW_H__0E3CAD2D_C3FF_11D2_A71D_F9BCAFDAF169__INCLUDED_)
#define AFX_MYMSGVIEW_H__0E3CAD2D_C3FF_11D2_A71D_F9BCAFDAF169__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyDlg.h"
class CMyMsgView : public CView
{
protected: // create from serialization only
	CMyMsgView();
	DECLARE_DYNCREATE(CMyMsgView)

// Attributes
public:
	CMyMsgDoc* GetDocument();
    MyDlg Dlg;
    CString str;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyMsgView)
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
	virtual ~CMyMsgView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyMsgView)
	afx_msg void OnDlg();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
//	afx_msg void OnMyOk();
};

#ifndef _DEBUG  // debug version in MyMsgView.cpp
inline CMyMsgDoc* CMyMsgView::GetDocument()
   { return (CMyMsgDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYMSGVIEW_H__0E3CAD2D_C3FF_11D2_A71D_F9BCAFDAF169__INCLUDED_)
