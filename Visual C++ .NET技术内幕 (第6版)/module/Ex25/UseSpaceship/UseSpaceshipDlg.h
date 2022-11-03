// UseSpaceshipDlg.h : header file
//

#pragma once


// CUseSpaceshipDlg dialog
class CUseSpaceshipDlg : public CDialog
{
// Construction
public:
	CUseSpaceshipDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_USESPACESHIP_DIALOG };

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
    afx_msg void OnBnClickedUseattributedatlspaceship();
    afx_msg void OnBnClickedUseclassicatlspaceship();
};
