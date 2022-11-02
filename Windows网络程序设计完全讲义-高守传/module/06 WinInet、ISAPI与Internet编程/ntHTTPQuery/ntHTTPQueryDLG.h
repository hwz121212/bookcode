// ntHTTPQueryDlg.h : header file
//

#if !defined(AFX_ntHTTPQueryDLG_H__70D29E5F_C6F9_47E9_8949_76230547C028__INCLUDED_)
#define AFX_ntHTTPQueryDLG_H__70D29E5F_C6F9_47E9_8949_76230547C028__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CntHTTPQueryDlg dialog

class CntHTTPQueryDlg : public CDialog
{
// Construction
public:
	CntHTTPQueryDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CntHTTPQueryDlg)
	enum { IDD = IDD_ntHTTPQuery_DIALOG };
	CString	m_Url;
	CString	m_Text;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CntHTTPQueryDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CntHTTPQueryDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeEdit1();
	afx_msg void OnShow();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ntHTTPQueryDLG_H__70D29E5F_C6F9_47E9_8949_76230547C028__INCLUDED_)
