// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__55800FA8_28B3_11D4_9E64_00001A012804__INCLUDED_)
#define AFX_MAINFRM_H__55800FA8_28B3_11D4_9E64_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Request.h"
#include "SendDlg.h"

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CRequest *m_pSocket;//请求socket
    LPCTSTR m_Server; //服务器名
	UINT m_Port;     //端口地址
	CSendDlg dlg2;
    
// Operations
public:
       void FetchMsg(CRequest *pRequest);//接受服务器来的信息
	   void SendMsg(CRequest *pRequest,char *pMsg);//发送信息
	   CRequest  *ConnectServer();//创建Socket并连接到服务器

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnOpen();
	afx_msg void OnClose();
	afx_msg void OnInfoSend();


	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__55800FA8_28B3_11D4_9E64_00001A012804__INCLUDED_)
