#if !defined(AFX_DLGCOMCONFIG_H__E1904B9D_DD30_4AD5_BA77_E0DD7B0798BA__INCLUDED_)
#define AFX_DLGCOMCONFIG_H__E1904B9D_DD30_4AD5_BA77_E0DD7B0798BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgComConfig.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgComConfig dialog

class CDlgComConfig : public CDialog
{
// Construction
public:
	
	CDlgComConfig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgComConfig)
	enum { IDD = IDD_DIALOG_COM_CONFIG };
	CComboBox	m_combCom;
	CString	m_strCom;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgComConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgComConfig)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCOMCONFIG_H__E1904B9D_DD30_4AD5_BA77_E0DD7B0798BA__INCLUDED_)
