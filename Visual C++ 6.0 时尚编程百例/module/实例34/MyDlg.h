#if !defined(AFX_MYDLG_H__D7323AF5_C465_11D2_A71D_A13BEA93DD69__INCLUDED_)
#define AFX_MYDLG_H__D7323AF5_C465_11D2_A71D_A13BEA93DD69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MyDlg dialog

class MyDlg : public CDialog
{
// Construction
public:
	MyDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MyDlg)
	enum { IDD = IDD_MYDIALOG };
	CString	m_String;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MyDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDLG_H__D7323AF5_C465_11D2_A71D_A13BEA93DD69__INCLUDED_)
