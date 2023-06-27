// TTYReceiveMSCommDlg.h : header file
//

#if !defined(AFX_TTYRECEIVEMSCOMMDLG_H__3F27C154_DA3B_407B_B91A_646D34C78E70__INCLUDED_)
#define AFX_TTYRECEIVEMSCOMMDLG_H__3F27C154_DA3B_407B_B91A_646D34C78E70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mscomm.h"
#include "SetupDlg.h"
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// CTTYReceiveMSCommDlg dialog

class CTTYReceiveMSCommDlg : public CDialog
{
// Construction
public:
	CTTYReceiveMSCommDlg(CWnd* pParent = NULL);	// standard constructor

	CMSComm myComm;	                    	//声明myComm变量为CMSComm类型
	CSetupDlg mySetupDlg;                   //声明设置对话框实例
	char myChar[2];
	BYTE	myCom;                          //串口号码
	CString	myParity;                       //奇偶校验类型
	CString	myBaudRate;                     //通信波特率
 
// Dialog Data
	//{{AFX_DATA(CTTYReceiveMSCommDlg)
	enum { IDD = IDD_TTYRECEIVEMSCOMM_DIALOG };
	CButton	m_Closecom;
	CButton	m_Setupcom;
	CButton	m_Opencom;
	CButton	m_Exit;
	CEdit	m_Edit1;
	CString	m_Para;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTTYReceiveMSCommDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTTYReceiveMSCommDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSetupcom();
	afx_msg void OnExit();
	afx_msg void OnOpencom();
	afx_msg void OnClosecom();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnOnCommMscomm1();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TTYRECEIVEMSCOMMDLG_H__3F27C154_DA3B_407B_B91A_646D34C78E70__INCLUDED_)
