// DlgToolbarDlg.h : header file
//

#if !defined(AFX_DLGTOOLBARDLG_H__5E17D847_E2D8_11D2_A71D_ED3204A0044B__INCLUDED_)
#define AFX_DLGTOOLBARDLG_H__5E17D847_E2D8_11D2_A71D_ED3204A0044B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDlgToolbarDlg dialog

class CDlgToolbarDlg : public CDialog
{
// Construction
public:
	CDlgToolbarDlg(CWnd* pParent = NULL);	// standard constructor
    CToolBarCtrl *m_toolbarCtrl ;
	TBBUTTON btn[5];
// Dialog Data
	//{{AFX_DATA(CDlgToolbarDlg)
	enum { IDD = IDD_DLGTOOLBAR_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgToolbarDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDlgToolbarDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton(UINT nID);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTOOLBARDLG_H__5E17D847_E2D8_11D2_A71D_ED3204A0044B__INCLUDED_)
