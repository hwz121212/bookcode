// MyOdbcDlg.h : header file
//

#if !defined(AFX_MYODBCDLG_H__AF8F15D8_C5DD_11D2_A71D_A175F8619D69__INCLUDED_)
#define AFX_MYODBCDLG_H__AF8F15D8_C5DD_11D2_A71D_A175F8619D69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PersonInfo.h"
/////////////////////////////////////////////////////////////////////////////
// CMyOdbcDlg dialog

class CMyOdbcDlg : public CDialog
{
// Construction
public:
	CMyOdbcDlg(CWnd* pParent = NULL);	// standard constructor
    void FillPersonInfo();
// Dialog Data
	//{{AFX_DATA(CMyOdbcDlg)
	enum { IDD = IDD_MYODBC_DIALOG };
	CListBox	m_listbox;
	long	m_age;
	CString	m_sex;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyOdbcDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyOdbcDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYODBCDLG_H__AF8F15D8_C5DD_11D2_A71D_A175F8619D69__INCLUDED_)
