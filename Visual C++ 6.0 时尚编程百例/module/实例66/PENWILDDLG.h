#if !defined(AFX_PENWILDDLG_H__E80D1965_D686_11D2_A71D_C1216DB00460__INCLUDED_)
#define AFX_PENWILDDLG_H__E80D1965_D686_11D2_A71D_C1216DB00460__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PENWILDDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PENWILDDLG dialog

class PENWILDDLG : public CDialog
{
// Construction
public:
	PENWILDDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PENWILDDLG)
	enum { IDD = IDD_DIALOG_WILD };
	CSpinButtonCtrl	m_cwildspin;
	CEdit	m_cpenwild;
	int		m_penwild;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PENWILDDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PENWILDDLG)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PENWILDDLG_H__E80D1965_D686_11D2_A71D_C1216DB00460__INCLUDED_)
