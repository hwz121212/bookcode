// RoundRectDlg.h : header file
//

#if !defined(AFX_ROUNDRECTDLG_H__65D95CA4_A6D7_433E_8C72_11E24A640A6A__INCLUDED_)
#define AFX_ROUNDRECTDLG_H__65D95CA4_A6D7_433E_8C72_11E24A640A6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
#include "BtnMenu.h"

class CRoundRectDlg : public CDialog
{
// Construction
public:
	CString m_strFontFace;
	LOGFONT lf;
	CFont m_fontMe;
	CRoundRectDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRoundRectDlg)
	enum { IDD = IDD_ROUNDRECT_DIALOG };
	CBtnMenu	m_btnTest;
	CBtnMenu	m_btnOK;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoundRectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CRgn myrgn;
    CBrush brush;

	// Generated message map functions
	//{{AFX_MSG(CRoundRectDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROUNDRECTDLG_H__65D95CA4_A6D7_433E_8C72_11E24A640A6A__INCLUDED_)
