#if !defined(AFX_TEST22CDIALOG_H__B030BA4D_C874_11D1_B30A_E985A96A8907__INCLUDED_)
#define AFX_TEST22CDIALOG_H__B030BA4D_C874_11D1_B30A_E985A96A8907__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

extern "C" __declspec(dllimport) double Ex22cSquareRoot(double d);

// Test22cDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTest22cDialog dialog

class CTest22cDialog : public CDialog
{
// Construction
public:
	CTest22cDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTest22cDialog)
	enum { IDD = IDD_EX22C };
	double	m_dInput;
	double	m_dOutput;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest22cDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTest22cDialog)
	afx_msg void OnCompute();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST22CDIALOG_H__B030BA4D_C874_11D1_B30A_E985A96A8907__INCLUDED_)
