#if !defined(AFX_MODELLESSDIALOG_H__7F0ECE68_1C5D_11D4_B0E6_00001A012804__INCLUDED_)
#define AFX_MODELLESSDIALOG_H__7F0ECE68_1C5D_11D4_B0E6_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModellessDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModellessDialog dialog

class CModellessDialog : public CDialog
{
// Construction
public:
	CModellessDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModellessDialog)
	enum { IDD = IDD_DIALOG1 };
	int		m_add;
	float	m_first;
	float	m_second;
	float	m_result;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModellessDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModellessDialog)
	afx_msg void OnComputer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODELLESSDIALOG_H__7F0ECE68_1C5D_11D4_B0E6_00001A012804__INCLUDED_)
