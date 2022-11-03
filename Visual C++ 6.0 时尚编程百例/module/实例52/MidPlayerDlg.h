// MidPlayerDlg.h : header file
//

#if !defined(AFX_MIDPLAYERDLG_H__68591835_CB2A_11D2_A71D_EC34D8292E66__INCLUDED_)
#define AFX_MIDPLAYERDLG_H__68591835_CB2A_11D2_A71D_EC34D8292E66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Midi.h"
/////////////////////////////////////////////////////////////////////////////
// CMidPlayerDlg dialog

class CMidPlayerDlg : public CDialog
{
// Construction
public:
	CMidPlayerDlg(CWnd* pParent = NULL);	// standard constructor
    CMidi Mymid;
	int nIndex;
// Dialog Data
	//{{AFX_DATA(CMidPlayerDlg)
	enum { IDD = IDD_MIDPLAYER_DIALOG };
	CListBox	m_midbox;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMidPlayerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMidPlayerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpen();
	afx_msg void OnPlay();
	afx_msg void OnSelchangeList();
	afx_msg void OnStop();
	afx_msg void OnNext();
	afx_msg void OnDblclkList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIDPLAYERDLG_H__68591835_CB2A_11D2_A71D_EC34D8292E66__INCLUDED_)
