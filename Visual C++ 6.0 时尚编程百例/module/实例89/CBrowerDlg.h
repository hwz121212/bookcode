// CBrowerDlg.h : header file
//
//{{AFX_INCLUDES()
#include "web.h"
//}}AFX_INCLUDES

#if !defined(AFX_CBROWERDLG_H__A9AEDC08_25E3_11D4_B0E6_00001A012804__INCLUDED_)
#define AFX_CBROWERDLG_H__A9AEDC08_25E3_11D4_B0E6_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCBrowerDlg dialog

class CCBrowerDlg : public CDialog
{
// Construction
public:
	CCBrowerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCBrowerDlg)
	enum { IDD = IDD_CBROWER_DIALOG };
	CTreeCtrl	m_tree;
	CWeb	m_web;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCBrowerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCBrowerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnForward();
	afx_msg void OnBack();
	afx_msg void OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CBROWERDLG_H__A9AEDC08_25E3_11D4_B0E6_00001A012804__INCLUDED_)
