// Ex21aDlg.h : header file
//

#pragma once


// CEx21aDlg dialog
class CEx21aDlg : public CDialog
{
// Construction
public:
	CEx21aDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_EX21A_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio2();
	double m_dLeft;
	double m_dRight;
	double m_dResult;
	afx_msg void OnBnClickedCompute();
	int m_nOperation;
};
