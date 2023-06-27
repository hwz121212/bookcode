// ex13aView.h : interface of the CEx13aView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX13AVIEW_H__08B58E0F_CEDF_11D1_B30A_BEE3C0184301__INCLUDED_)
#define AFX_EX13AVIEW_H__08B58E0F_CEDF_11D1_B30A_BEE3C0184301__INCLUDED_

#include "Property.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx13aView : public CView
{
protected: // create from serialization only
	CEx13aView();
	DECLARE_DYNCREATE(CEx13aView)

// Attributes
public:
	CEx13aDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx13aView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	CRichEditCtrl m_rich;
	virtual ~CEx13aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx13aView)
	afx_msg void OnTransferGetData();
	afx_msg void OnTransferStoreData();
	afx_msg void OnUpdateTransferStoreData(CCmdUI* pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFormatDefault();
	afx_msg void OnFormatSelection();
	afx_msg void OnUpdateFormatSelection(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg LRESULT OnUserApply(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	void Format(CHARFORMAT &cf);
	BOOL m_bDefault; // TRUE default format, FALSE selection
	CFontSheet m_sh;
};

#ifndef _DEBUG  // debug version in ex13aView.cpp
inline CEx13aDoc* CEx13aView::GetDocument()
   { return (CEx13aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX13AVIEW_H__08B58E0F_CEDF_11D1_B30A_BEE3C0184301__INCLUDED_)
