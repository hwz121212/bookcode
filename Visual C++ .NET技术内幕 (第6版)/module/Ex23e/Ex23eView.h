// Ex23eView.h : interface of the CEx23eView class
//


#pragma once


class CEx23eView : public CView
{
private:
    IEx23bAutoPtr m_auto;
    IBankPtr m_bank;
    IEx23cPtr m_clock;
    IAlarmPtr m_alarm;

protected: // create from serialization only
	CEx23eView();
	DECLARE_DYNCREATE(CEx23eView)

// Attributes
public:
	CEx23eDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CEx23eView();
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
    afx_msg void OnDlloleUnload();
    afx_msg void OnUpdateDlloleUnload(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in Ex23eView.cpp
inline CEx23eDoc* CEx23eView::GetDocument() const
   { return reinterpret_cast<CEx23eDoc*>(m_pDocument); }
#endif

