#if !defined(AFX_EX06BDIALOG_H__46623A0A_C31F_11D1_B30A_0080C7360DC1__INCLUDED_)
#define AFX_EX06BDIALOG_H__46623A0A_C31F_11D1_B30A_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Ex06bDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEx06bDialog dialog

class CEx06bDialog : public CDialog
{
// Construction
public:
	int m_nTrackbar2;
	int m_nTrackbar1;
	int m_nProgress;
	CEx06bDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEx06bDialog)
	enum { IDD = IDD_DIALOG1 };
	double	m_dSpin;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx06bDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEx06bDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnItemchangedListview1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedTreeview1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	static double dValue[];
	CImageList m_imageList;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX06BDIALOG_H__46623A0A_C31F_11D1_B30A_0080C7360DC1__INCLUDED_)
