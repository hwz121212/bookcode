// ex23aDlg.h : header file
//

#if !defined(AFX_EX23ADLG_H__591DC949_C89D_11D1_B30A_E985A96A8907__INCLUDED_)
#define AFX_EX23ADLG_H__591DC949_C89D_11D1_B30A_E985A96A8907__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEx23aDlg dialog

class CEx23aDlg : public CDialog
{
// Construction
public:
	CEx23aDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEx23aDlg)
	enum { IDD = IDD_EX23A_DIALOG };
	double	m_dLeft;
	double	m_dRight;
	double	m_dResult;
	int		m_nOperation;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx23aDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEx23aDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCompute();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX23ADLG_H__591DC949_C89D_11D1_B30A_E985A96A8907__INCLUDED_)
