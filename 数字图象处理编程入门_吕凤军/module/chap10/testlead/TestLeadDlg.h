// TestLeadDlg.h : header file
//
//{{AFX_INCLUDES()
#include "lead.h"
//}}AFX_INCLUDES

#if !defined(AFX_TESTLEADDLG_H__BA0EE528_E514_11D1_A2B6_0000B4810C13__INCLUDED_)
#define AFX_TESTLEADDLG_H__BA0EE528_E514_11D1_A2B6_0000B4810C13__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CTestLeadDlg dialog

class CTestLeadDlg : public CDialog
{
// Construction
public:
	CTestLeadDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestLeadDlg)
	enum { IDD = IDD_TESTLEAD_DIALOG };
	CLead	m_Lead1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestLeadDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestLeadDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTLEADDLG_H__BA0EE528_E514_11D1_A2B6_0000B4810C13__INCLUDED_)
