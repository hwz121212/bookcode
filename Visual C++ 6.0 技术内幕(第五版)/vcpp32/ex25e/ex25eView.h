// ex25eView.h : interface of the CEx25eView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX25eVIEW_H__F02781AD_6269_11D0_8490_00400526305B__INCLUDED_)
#define AFX_EX25eVIEW_H__F02781AD_6269_11D0_8490_00400526305B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "AlarmDialog.h"

class CEx25eView : public CView
{
public:
	IEx25bAutoPtr m_auto;
	IBankPtr m_bank;
	IEx25cPtr m_clock;
	IAlarmPtr m_alarm;
protected: // create from serialization only
	CEx25eView();
	DECLARE_DYNCREATE(CEx25eView)

// Attributes
public:
	CEx25eDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx25eView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx25eView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx25eView)
	afx_msg void OnBankoleLoad();
	afx_msg void OnUpdateBankoleLoad(CCmdUI* pCmdUI);
	afx_msg void OnBankoleTest();
	afx_msg void OnUpdateBankoleTest(CCmdUI* pCmdUI);
	afx_msg void OnBankoleUnload();
	afx_msg void OnUpdateBankoleUnload(CCmdUI* pCmdUI);
	afx_msg void OnClockoleCreatealarm();
	afx_msg void OnUpdateClockoleCreatealarm(CCmdUI* pCmdUI);
	afx_msg void OnClockoleLoad();
	afx_msg void OnUpdateClockoleLoad(CCmdUI* pCmdUI);
	afx_msg void OnClockoleRefreshtime();
	afx_msg void OnUpdateClockoleRefreshtime(CCmdUI* pCmdUI);
	afx_msg void OnClockoleUnload();
	afx_msg void OnUpdateClockoleUnload(CCmdUI* pCmdUI);
	afx_msg void OnDlloleGetdata();
	afx_msg void OnUpdateDlloleGetdata(CCmdUI* pCmdUI);
	afx_msg void OnDlloleLoad();
	afx_msg void OnUpdateDlloleLoad(CCmdUI* pCmdUI);
	afx_msg void OnDlloleUnload();
	afx_msg void OnUpdateDlloleUnload(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex25eView.cpp
inline CEx25eDoc* CEx25eView::GetDocument()
   { return (CEx25eDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX25eVIEW_H__F02781AD_6269_11D0_8490_00400526305B__INCLUDED_)
