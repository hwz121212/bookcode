// CDPlayerDlg.h : header file
//

#if !defined(AFX_CDPLAYERDLG_H__A754A547_D04C_11D2_A71D_9D57AAEEA066__INCLUDED_)
#define AFX_CDPLAYERDLG_H__A754A547_D04C_11D2_A71D_9D57AAEEA066__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "CDAudio.h"
/////////////////////////////////////////////////////////////////////////////
// CCDPlayerDlg dialog

class CCDPlayerDlg : public CDialog
{
// Construction
public:
	CCDPlayerDlg(CWnd* pParent = NULL);	// standard constructor
    CCDAudio MyPlayer;
	void GetTotalCDCount();
// Dialog Data
	//{{AFX_DATA(CCDPlayerDlg)
	enum { IDD = IDD_CDPLAYER_DIALOG };
	CString	m_count;
	CString	m_current;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCDPlayerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCDPlayerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonBack();
	afx_msg void OnButtonNext();
	afx_msg void OnButtonPlay();
	afx_msg void OnButtonStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDPLAYERDLG_H__A754A547_D04C_11D2_A71D_9D57AAEEA066__INCLUDED_)
