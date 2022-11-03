// ClipDemoDlg.h : header file
//

#if !defined(AFX_CLIPDEMODLG_H__63253C06_3758_11D2_BB89_000629EE2C0F__INCLUDED_)
#define AFX_CLIPDEMODLG_H__63253C06_3758_11D2_BB89_000629EE2C0F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CClipDemoDlg dialog

class CClipDemoDlg : public CDialog
{
// Construction
public:
	CClipDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CClipDemoDlg)
	enum { IDD = IDD_CLIPDEMO_DIALOG };
	CString	m_strEdit;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClipDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClipDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCopy();
	afx_msg void OnPaste();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIPDEMODLG_H__63253C06_3758_11D2_BB89_000629EE2C0F__INCLUDED_)
