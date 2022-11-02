/*
  This project was created and edited using the MFC SelfBanner AppWizard.

  Comment: 远程控制－远程Cmd客户端.

  Project: ntCmdCliennt.
  Author : dhyao
  Date   : 星期一, 二月 02, 2009
*/
/////////////////////////////////////////////////////////////////////
// ntCmdClienntDlg.h : header file
//

#if !defined(AFX_ntCmdClienntDLG_H__070A1FA9_FDE8_4D41_9DA4_6A047592DC0B__INCLUDED_)
#define AFX_ntCmdClienntDLG_H__070A1FA9_FDE8_4D41_9DA4_6A047592DC0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*
在使用该库时，除了ResizableLib的htm文档说明外，
还要在在“project|dependencies...”中指定它所依赖的库ResizableLib，
以便为其在External Dependencies中导入所需的头文件。
*/

#include "ResizableDialog.h"

#include "CmdEditCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CntCmdClienntDlg dialog

class CntCmdClienntDlg : public CResizableDialog
{
// Construction
public:
	DWORD StartNewConnet(LPVOID lpvoid);
	CntCmdClienntDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CntCmdClienntDlg)
	enum { IDD = IDD_ntCmdCliennt_DIALOG };
	CCmdEditCtrl	m_edit;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CntCmdClienntDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	typedef	struct  MasterInfor
	{
		DWORD	dwIP;
		USHORT	uPort;
	}MasterInfor;
	
	MasterInfor msInfor;
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CntCmdClienntDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ntCmdClienntDLG_H__070A1FA9_FDE8_4D41_9DA4_6A047592DC0B__INCLUDED_)
