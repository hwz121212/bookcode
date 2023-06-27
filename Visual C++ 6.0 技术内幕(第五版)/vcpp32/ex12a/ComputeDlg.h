#if !defined(AFX_COMPUTEDLG_H__CD13DB97_A955_11D1_8ED7_0080C7360DC1__INCLUDED_)
#define AFX_COMPUTEDLG_H__CD13DB97_A955_11D1_8ED7_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComputeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComputeDlg dialog

class CComputeDlg : public CDialog
{
private:
	int m_nTimer;
	int m_nCount;
	enum { nMaxCount = 10000 };

// Construction
public:
	CComputeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CComputeDlg)
	enum { IDD = IDD_COMPUTE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComputeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CComputeDlg)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnStart();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPUTEDLG_H__CD13DB97_A955_11D1_8ED7_0080C7360DC1__INCLUDED_)
