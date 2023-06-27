#if !defined(AFX_TEST22DDIALOG_H__B030BA5D_C874_11D1_B30A_E985A96A8907__INCLUDED_)
#define AFX_TEST22DDIALOG_H__B030BA5D_C874_11D1_B30A_E985A96A8907__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Test22dDialog.h : header file
//

extern "C" __declspec(dllimport) void Ex22dEntry(); // dummy function
#define RYG_SETSTATE WM_USER + 0
#define RYG_GETSTATE WM_USER + 1

/////////////////////////////////////////////////////////////////////////////
// CTest22dDialog dialog

class CTest22dDialog : public CDialog
{
private:
	enum { OFF, RED, YELLOW, GREEN } m_nState;

// Construction
public:
	CTest22dDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTest22dDialog)
	enum { IDD = IDD_EX22D };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest22dDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTest22dDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	afx_msg void OnClickedRyg();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST22DDIALOG_H__B030BA5D_C874_11D1_B30A_E985A96A8907__INCLUDED_)
