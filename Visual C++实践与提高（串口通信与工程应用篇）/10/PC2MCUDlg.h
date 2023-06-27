// PC2MCUDlg.h : header file
//
#include "mscomm.h"
#if !defined(AFX_PC2MCUDLG_H__6A7B9938_2641_4E21_A11B_D871C8827871__INCLUDED_)
#define AFX_PC2MCUDLG_H__6A7B9938_2641_4E21_A11B_D871C8827871__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPC2MCUDlg dialog

class CPC2MCUDlg : public CDialog
{
// Construction
public:
	CPC2MCUDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPC2MCUDlg)
	enum { IDD = IDD_PC2MCU_DIALOG };
	CButton	m_Read;
	CString	m_Edit1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPC2MCUDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	CMSComm myComm;               //声明myComm变量为CMSComm类型

	// Generated message map functions
	//{{AFX_MSG(CPC2MCUDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnREAD();
	afx_msg void OnOnCommMscomm1();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PC2MCUDLG_H__6A7B9938_2641_4E21_A11B_D871C8827871__INCLUDED_)
