// ntBlockServerDlg.h : header file
//

#if !defined(AFX_ntBlockServerDLG_H__0636A29E_A34E_453C_AA5B_C6CED2CD17A7__INCLUDED_)
#define AFX_ntBlockServerDLG_H__0636A29E_A34E_453C_AA5B_C6CED2CD17A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CntBlockServerDlg dialog

class CntBlockServerDlg : public CDialog
{
// Construction
public:
	CntBlockServerDlg(CWnd* pParent = NULL);	// standard constructor
	CSocket m_sockListen;					//����һ�������׽���
	CSocket m_sockSend;					//����һ�������׽���
// Dialog Data
	//{{AFX_DATA(CntBlockServerDlg)
	enum { IDD = IDD_ntBlockServer_DIALOG };
	CString	m_ServerStatus;
	int		m_sendcount;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CntBlockServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CntBlockServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSend();
	afx_msg void OnStop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ntBlockServerDLG_H__0636A29E_A34E_453C_AA5B_C6CED2CD17A7__INCLUDED_)
