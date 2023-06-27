#if !defined(AFX_EX06ADIALOG_H__466239F5_C31F_11D1_B30A_0080C7360DC1__INCLUDED_)
#define AFX_EX06ADIALOG_H__466239F5_C31F_11D1_B30A_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Ex06aDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEx06aDialog dialog

class CEx06aDialog : public CDialog
{
enum { nMin = 0 };
enum { nMax = 100 };
// Construction
public:
	CEx06aDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEx06aDialog)
	enum { IDD = IDD_DIALOG1 };
	CString	m_strBio;
	int		m_nCat;
	CString	m_strDept;
	BOOL	m_bInsDis;
	CString	m_strEduc;
	int		m_nLang;
	BOOL	m_bInsLife;
	int		m_nLoyal;
	BOOL	m_bInsMed;
	CString	m_strName;
	int		m_nRely;
	CString	m_strSkill;
	int		m_nSsn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx06aDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEx06aDialog)
	afx_msg void OnSpecial();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClickedOk();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX06ADIALOG_H__466239F5_C31F_11D1_B30A_0080C7360DC1__INCLUDED_)
