// ManyDlg.h : header file
//

#if !defined(AFX_MANYDLG_H__DB00CEA6_1F8D_11D4_B0E6_00001A012804__INCLUDED_)
#define AFX_MANYDLG_H__DB00CEA6_1F8D_11D4_B0E6_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define WM_FINISHED WM_USER+1

/////////////////////////////////////////////////////////////////////////////
// CManyDlg dialog
UINT CThreadProc(LPVOID pParam);
	

class CManyDlg : public CDialog
{
// Construction

public:
	CManyDlg(CWnd* pParent = NULL);	// standard constructor


// Dialog Data
	//{{AFX_DATA(CManyDlg)
	enum { IDD = IDD_MANY_DIALOG };
	CProgressCtrl	m_progress;
	CAnimateCtrl	m_animate;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CManyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//}}AFX_MSG
	afx_msg LRESULT OnFinished(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANYDLG_H__DB00CEA6_1F8D_11D4_B0E6_00001A012804__INCLUDED_)
