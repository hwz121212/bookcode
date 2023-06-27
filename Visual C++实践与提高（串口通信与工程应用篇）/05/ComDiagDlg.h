// ComDiagDlg.h : header file
//

#if !defined(AFX_COMDIAGDLG_H__F556AF62_53EE_41B4_994F_B767AAF40526__INCLUDED_)
#define AFX_COMDIAGDLG_H__F556AF62_53EE_41B4_994F_B767AAF40526__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mscomm.h"                      //MSComm控件类的引用
#include "SetupDlg.h"                    //设置对话框类的引用
#include <math.h>                        //数学运算类的引用

/////////////////////////////////////////////////////////////////////////////
// CComDiagDlg dialog

class CComDiagDlg : public CDialog
{
// Construction
public:
	CComDiagDlg(CWnd* pParent = NULL);	// standard constructor

	CMSComm myComm;	                    	//声明myComm变量为CMSComm类型
	CSetupDlg mySetupDlg;                   //声明设置对话框实例
	BYTE	myCom;                          //串口号码
	CString	myParity;                       //奇偶校验类型
	CString	myBaudRate;                     //通信波特率
	void	SendData(CString strInput);
// Dialog Data
	//{{AFX_DATA(CComDiagDlg)
	enum { IDD = IDD_COMDIAG_DIALOG };
	CButton	m_Send7;
	CButton	m_Send6;
	CButton	m_Send5;
	CButton	m_Send4;
	CButton	m_Send3;
	CButton	m_Send2;
	CButton	m_Send1;
	CButton	m_Setupcom;
	CButton	m_Closecom;
	CButton	m_Opencom;
	CButton	m_Exit;
	CEdit	m_Dis;
	int		m_Delay1;
	int		m_Delay2;
	int		m_Delay3;
	int		m_Delay4;
	int		m_Delay5;
	int		m_Delay6;
	int		m_Delay7;
	CString	m_Senddata1;
	CString	m_Senddata2;
	CString	m_Senddata3;
	CString	m_Senddata4;
	CString	m_Senddata5;
	CString	m_Senddata6;
	CString	m_Senddata7;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComDiagDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CComDiagDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnExit();
	afx_msg void OnSetupcom();
	afx_msg void OnOpencom();
	afx_msg void OnClosecom();
	afx_msg void OnOnCommMscomm1();
	afx_msg void OnSend1();
	afx_msg void OnSend2();
	afx_msg void OnSend3();
	afx_msg void OnSend4();
	afx_msg void OnSend5();
	afx_msg void OnSend6();
	afx_msg void OnSend7();
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMDIAGDLG_H__F556AF62_53EE_41B4_994F_B767AAF40526__INCLUDED_)
