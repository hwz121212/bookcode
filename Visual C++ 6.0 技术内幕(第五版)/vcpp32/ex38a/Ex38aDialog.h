#if !defined(AFX_Ex38aDialog_H__25B52AF5_0533_11D2_8B47_00104B881C94__INCLUDED_)
#define AFX_Ex38aDialog_H__25B52AF5_0533_11D2_8B47_00104B881C94__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Ex38aDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEx38aDialog dialog

class CEx38aDialog : public CDialog
{
// Construction
public:
	CEx38aDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEx38aDialog)
	enum { IDD = IDD_DIALOG1 };
	CProgressCtrl	m_pProgressCtrl;
	CComboBox	m_pComboBox;
	BOOL	m_bCheck1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx38aDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEx38aDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio1();
	afx_msg void OnCheck1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_Ex38aDialog_H__25B52AF5_0533_11D2_8B47_00104B881C94__INCLUDED_)
