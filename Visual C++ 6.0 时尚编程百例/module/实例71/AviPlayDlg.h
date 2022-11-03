// AviPlayDlg.h : header file
//

#if !defined(AFX_AVIPLAYDLG_H__BA12C5A7_CD17_11D2_A71D_94D5089BEA62__INCLUDED_)
#define AFX_AVIPLAYDLG_H__BA12C5A7_CD17_11D2_A71D_94D5089BEA62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAviPlayDlg dialog

class CAviPlayDlg : public CDialog
{
// Construction
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CAviPlayDlg(CWnd* pParent = NULL);	// standard constructor
    CString AviName;
	CRect AviRect;
	CAnimateCtrl m_AviCtrl;
	CWnd* m_CtrlWnd;
	void AviChanges();
// Dialog Data
	//{{AFX_DATA(CAviPlayDlg)
	enum { IDD = IDD_AVIPLAY_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAviPlayDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolTipCtrl m_tooltip;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAviPlayDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowser();
	afx_msg void OnPlay();
	afx_msg void OnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AVIPLAYDLG_H__BA12C5A7_CD17_11D2_A71D_94D5089BEA62__INCLUDED_)
