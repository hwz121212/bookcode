// Ex23dView.h : interface of the CEx23dView class
//


#pragma once

#include "BankDriver.h"
#include "CAlarm.h"
#include "autodriver.h"
#include "clockdriver.h"
#include "CApplication.h"  // Excel app
#include "CRange.h"
#include "CWorksheet.h"
#include "CWorksheets.h"
#include "CWorkbooks.h"

class CEx23dView : public CView
{
private:
   CAlarm m_alarm;
   CEx23bAuto m_auto;
   CBank m_bank;
   CEx23c m_clock;
   
   CApplication m_app;
   CRange    m_range[5];
   CWorksheet   m_worksheet;
   CWorkbooks   m_workbooks;
   CWorksheets   m_worksheets;

protected: // create from serialization only
	CEx23dView();
	DECLARE_DYNCREATE(CEx23dView)

// Attributes
public:
	CEx23dDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CEx23dView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBankoleLoad();
    afx_msg void OnUpdateBankoleLoad(CCmdUI *pCmdUI);
    afx_msg void OnBankoleTest();
    afx_msg void OnUpdateBankoleTest(CCmdUI *pCmdUI);
    afx_msg void OnBankoleUnload();
    afx_msg void OnUpdateBankoleUnload(CCmdUI *pCmdUI);
    afx_msg void OnClockoleCreatealarm();
    afx_msg void OnUpdateClockoleCreatealarm(CCmdUI *pCmdUI);
    afx_msg void OnClockoleLoad();
    afx_msg void OnUpdateClockoleLoad(CCmdUI *pCmdUI);
    afx_msg void OnClockoleRefreshtime();
    afx_msg void OnUpdateClockoleRefreshtime(CCmdUI *pCmdUI);
    afx_msg void OnClockoleUnload();
    afx_msg void OnUpdateClockoleUnload(CCmdUI *pCmdUI);
    afx_msg void OnDlloleGetdata();
    afx_msg void OnUpdateDlloleGetdata(CCmdUI *pCmdUI);
    afx_msg void OnDlloleLoad();
    afx_msg void OnUpdateDlloleLoad(CCmdUI *pCmdUI);
    afx_msg void OnExceloleExecute();
    afx_msg void OnUpdateExceloleExecute(CCmdUI *pCmdUI);
    afx_msg void OnExceloleLoad();
    afx_msg void OnUpdateExceloleLoad(CCmdUI *pCmdUI);
    afx_msg void OnDlloleUnload();
    afx_msg void OnUpdateDlloleUnload(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in Ex23dView.cpp
inline CEx23dDoc* CEx23dView::GetDocument() const
   { return reinterpret_cast<CEx23dDoc*>(m_pDocument); }
#endif

