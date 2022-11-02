/*
  This project was created and edited using the MFC SelfBanner AppWizard.

  Comment: 远程控制－远程Cmd客户端.

  Project: ntCmdClient.
  Author : dhyao
  Date   : 星期一, 二月 02, 2009
*/
/////////////////////////////////////////////////////////////////////
// ntCmdClientDlg.h : header file
//

#if !defined(AFX_ntCmdClientDLG_H__070A1FA9_FDE8_4D41_9DA4_6A047592DC0B__INCLUDED_)
#define AFX_ntCmdClientDLG_H__070A1FA9_FDE8_4D41_9DA4_6A047592DC0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#include "CmdEditCtrl.h"
#include "FullScreenTitleBar.h"
#include "FullScreenTitleBarConst.h"

/////////////////////////////////////////////////////////////////////////////
// CntCmdClientDlg dialog

class CntCmdClientDlg : public CDialog
{
// Construction
public:
	void SetFullScreen(BOOL OnOff);
	DWORD StartNewConnet(LPVOID lpvoid);
	CntCmdClientDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CntCmdClientDlg();

// Dialog Data
	//{{AFX_DATA(CntCmdClientDlg)
	enum { IDD = IDD_ntCmdClient_DIALOG };
	CCmdEditCtrl	m_edit;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CntCmdClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	typedef	struct  MasterInfor
	{
		DWORD	dwIP;
		USHORT	uPort;
	}MasterInfor;
	
	MasterInfor msInfor;
	CTitleBar *TitleBar;
	BOOL IsFullScreen;
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CntCmdClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	afx_msg LRESULT OnTbClose(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnTbMinimize(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnTbMaximize(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ntCmdClientDLG_H__070A1FA9_FDE8_4D41_9DA4_6A047592DC0B__INCLUDED_)
