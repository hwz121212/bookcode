// DlgAppDlg.h : header file
//

#if !defined(AFX_DLGAPPDLG_H__2D2A2C6C_E2F1_11D2_A71D_F998D259734B__INCLUDED_)
#define AFX_DLGAPPDLG_H__2D2A2C6C_E2F1_11D2_A71D_F998D259734B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDlgAppDlg dialog

class CDlgAppDlg : public CDialog
{
// Construction
public:
	CDlgAppDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAppDlg)
	enum { IDD = IDD_DLGAPP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAppDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDlgAppDlg)
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

#endif // !defined(AFX_DLGAPPDLG_H__2D2A2C6C_E2F1_11D2_A71D_F998D259734B__INCLUDED_)
