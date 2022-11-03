#if !defined(AFX_MYDIALOG_H__4AF533F4_C125_11D2_A71D_A0815CB6AA6A__INCLUDED_)
#define AFX_MYDIALOG_H__4AF533F4_C125_11D2_A71D_A0815CB6AA6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MyDialog dialog

class MyDialog : public CDialog
{
// Construction
public:
	MyDialog(CWnd* pParent = NULL);   // standard constructor
    COLORREF m_colors;
// Dialog Data
	//{{AFX_DATA(MyDialog)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MyDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MyDialog)
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDIALOG_H__4AF533F4_C125_11D2_A71D_A0815CB6AA6A__INCLUDED_)
