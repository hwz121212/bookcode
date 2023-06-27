#if !defined(AFX_DLGLOGIN_H__862B888E_D634_46D9_B6D1_0743DA4CEB61__INCLUDED_)
#define AFX_DLGLOGIN_H__862B888E_D634_46D9_B6D1_0743DA4CEB61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLogin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLogin dialog

class CDlgLogin : public CDialog
{
// Construction
public:
	CDlgLogin(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLogin)
	enum { IDD = IDD_DIALOG_LOGIN };
	CButton	m_buttonUseDB;
	CEdit	m_editUser;
	CEdit	m_editPass;
	CString	m_pass;
	CString	m_user;
	BOOL	m_bUseDB;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLogin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLogin)
	afx_msg void OnCheckUsedb();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLOGIN_H__862B888E_D634_46D9_B6D1_0743DA4CEB61__INCLUDED_)
