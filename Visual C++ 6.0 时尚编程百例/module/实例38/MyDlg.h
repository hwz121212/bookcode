#if !defined(AFX_MYDLG_H__9859BEC8_C5B0_11D2_A71D_E1F8995C8269__INCLUDED_)
#define AFX_MYDLG_H__9859BEC8_C5B0_11D2_A71D_E1F8995C8269__INCLUDED_

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
    int nIndex;
// Dialog Data
	//{{AFX_DATA(MyDlg)
	enum { IDD = IDD_DIALOG1 };
	CListBox	m_mylistbox;
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
	virtual BOOL OnInitDialog();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnSelchangeList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDLG_H__9859BEC8_C5B0_11D2_A71D_E1F8995C8269__INCLUDED_)
