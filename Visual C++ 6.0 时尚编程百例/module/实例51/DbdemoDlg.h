// DbdemoDlg.h : header file
//

#if !defined(AFX_DBDEMODLG_H__9859BEA7_C5B0_11D2_A71D_E1F8995C8269__INCLUDED_)
#define AFX_DBDEMODLG_H__9859BEA7_C5B0_11D2_A71D_E1F8995C8269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDbdemoDlg dialog

class CDbdemoDlg : public CDialog
{
// Construction
public:
	CDbdemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDbdemoDlg)
	enum { IDD = IDD_DBDEMO_DIALOG };
	CListBox	m_MyListBox;
	int		m_age;
	CString	m_sex;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDbdemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	void FillMyListBox();

	// Generated message map functions
	//{{AFX_MSG(CDbdemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeList3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBDEMODLG_H__9859BEA7_C5B0_11D2_A71D_E1F8995C8269__INCLUDED_)
