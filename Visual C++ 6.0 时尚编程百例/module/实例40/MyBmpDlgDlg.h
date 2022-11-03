// MyBmpDlgDlg.h : header file
//

#if !defined(AFX_MYBMPDLGDLG_H__20F39047_DB52_11D2_A71D_D12047679B5A__INCLUDED_)
#define AFX_MYBMPDLGDLG_H__20F39047_DB52_11D2_A71D_D12047679B5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyBmpDlgDlg dialog

class CMyBmpDlgDlg : public CDialog
{
// Construction
public:
	CMyBmpDlgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMyBmpDlgDlg)
	enum { IDD = IDD_MYBMPDLG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyBmpDlgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyBmpDlgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAboutbox();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYBMPDLGDLG_H__20F39047_DB52_11D2_A71D_D12047679B5A__INCLUDED_)
