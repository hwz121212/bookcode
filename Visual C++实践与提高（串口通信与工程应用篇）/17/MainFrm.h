// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__A7784E91_5DBC_4D84_8758_DE877D8FD65F__INCLUDED_)
#define AFX_MAINFRM_H__A7784E91_5DBC_4D84_8758_DE877D8FD65F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "CJTabCtrlBar.h"
#include "ComWorkFlow.h"

class CGpsServerView;
class CGpsServerDoc;
class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

// Implementation
public:		
	
	void WriteLog(CString level, LPCTSTR pstrFormat, ...);
	void WriteSendLog(CSendObject* obj);
	void WriteComWorkFlowLog(CComWorkFlow* obj, BOOL bAdd);

	BOOL AddSendData(CSendObject* pObj);
	BOOL AddViewComData(CString com);

	CGpsServerDoc* GetCurrentDoc();	
	void SetView(CGpsServerView *view);
	

	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	
	CCJTabCtrlBar m_wndOutput;
	CCJTabCtrlBar m_wndOutputCom;

	CGpsServerView* m_pAppView;	

	CImageList	m_ImageList;
	CImageList  m_TabImages;
	CImageList	imaLarge, imaSmall;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void MsgSendData(WPARAM wp,LPARAM lp);
	afx_msg void MsgSendDataResult(WPARAM wp,LPARAM lp);
	afx_msg void MsgDecodedNemaSentence(WPARAM wp,LPARAM lp);	
	afx_msg void MsgReceiveDataResult(WPARAM wp,LPARAM lp);	
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnUpdateComClose(CCmdUI* pCmdUI);
	afx_msg void OnComClose();
	afx_msg void OnComOpen();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSystemClearLog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void StopTimer();
	void StartTimer();

	
	CGpsServerView* GetMainView();

	
	int GetViewComData(CString com);

	CCJTabCtrlBar* GetWndOutputCom();
	CCJTabCtrlBar* GetWndOutput();
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__A7784E91_5DBC_4D84_8758_DE877D8FD65F__INCLUDED_)
