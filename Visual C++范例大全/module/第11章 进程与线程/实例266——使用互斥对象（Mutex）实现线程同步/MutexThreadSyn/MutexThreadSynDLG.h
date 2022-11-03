// MutexThreadSynDlg.h : header file
//

#if !defined(AFX_MutexThreadSynDLG_H__7CFB4F80_AD70_4097_ABA9_152B1714FEA9__INCLUDED_)
#define AFX_MutexThreadSynDLG_H__7CFB4F80_AD70_4097_ABA9_152B1714FEA9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMutexThreadSynDlg dialog

class CMutexThreadSynDlg : public CDialog
{
// Construction
public:
	CMutexThreadSynDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMutexThreadSynDlg)
	enum { IDD = IDD_MutexThreadSyn_DIALOG };
	CEdit	m_ReadEdit;
	CEdit	m_WriteEdit;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMutexThreadSynDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMutexThreadSynDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStarw();
	afx_msg void OnStopr();
	afx_msg void OnStopw();
	afx_msg void OnStarr();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MutexThreadSynDLG_H__7CFB4F80_AD70_4097_ABA9_152B1714FEA9__INCLUDED_)
