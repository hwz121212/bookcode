// TapiNewDlg.h : header file
//

#if !defined(AFX_TAPINEWDLG_H__2961947E_994D_4491_874E_FBACC4CEF7A0__INCLUDED_)
#define AFX_TAPINEWDLG_H__2961947E_994D_4491_874E_FBACC4CEF7A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Tapi14.h"

/////////////////////////////////////////////////////////////////////////////
// CTapiNewDlg dialog

class CTapiNewDlg : public CDialog
{
// Construction
public:
	CTapiNewDlg(CWnd* pParent = NULL);	// standard constructor

	CTapi14	myTapi14;                         //声明CTapi14类变量
	HWND		myHwnd;                       //声明窗口句柄
	void		OperStatus(CString strDis);   //信息显示函数

// Dialog Data
	//{{AFX_DATA(CTapiNewDlg)
	enum { IDD = IDD_TAPINEW_DIALOG };
	CEdit	m_Dis;
	CString	m_Phonenumber;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTapiNewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTapiNewDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDial();
	afx_msg void OnHangup();
	//}}AFX_MSG
	afx_msg void OnTapiEvent_DIALING(WPARAM wParam,LPARAM lParam);
	afx_msg void OnTapiEvent_CONNECT(WPARAM wParam,LPARAM lParam);
	afx_msg void OnTapiEvent_DISCONNECT(WPARAM wParam,LPARAM lParam);
	afx_msg void OnTapiEvent_IDLE(WPARAM wParam,LPARAM lParam);
	afx_msg void OnTapiEvent_STATUS(WPARAM wParam,LPARAM lParam);
	afx_msg void OnTapiEvent_CALL_PROCEEDING(WPARAM wParam,LPARAM lParam);
	afx_msg void OnTapiEvent_CALL_ACCEPTED(WPARAM wParam,LPARAM lParam);
	afx_msg void OnTapiEvent_LINE_REPLY(WPARAM wParam,LPARAM lParam);
	afx_msg void OnTapiEvent_VOICE_SUPPORT(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TAPINEWDLG_H__2961947E_994D_4491_874E_FBACC4CEF7A0__INCLUDED_)
