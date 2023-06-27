// usespaceshipsvrDlg.h : header file
//

#if !defined(AFX_USESPACESHIPSVRDLG_H__FACE88FE_06C8_11D2_B77D_0060081EE21C__INCLUDED_)
#define AFX_USESPACESHIPSVRDLG_H__FACE88FE_06C8_11D2_B77D_0060081EE21C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUsespaceshipsvrDlgAutoProxy;

/////////////////////////////////////////////////////////////////////////////
// CUsespaceshipsvrDlg dialog

class CUsespaceshipsvrDlg : public CDialog
{
	DECLARE_DYNAMIC(CUsespaceshipsvrDlg);
	friend class CUsespaceshipsvrDlgAutoProxy;

// Construction
public:
	CUsespaceshipsvrDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CUsespaceshipsvrDlg();

// Dialog Data
	//{{AFX_DATA(CUsespaceshipsvrDlg)
	enum { IDD = IDD_USESPACESHIPSVR_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUsespaceshipsvrDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CUsespaceshipsvrDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	//{{AFX_MSG(CUsespaceshipsvrDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnUsespaceship();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USESPACESHIPSVRDLG_H__FACE88FE_06C8_11D2_B77D_0060081EE21C__INCLUDED_)
