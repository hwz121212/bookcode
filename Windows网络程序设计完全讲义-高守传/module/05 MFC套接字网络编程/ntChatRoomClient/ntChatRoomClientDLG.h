// ntChatRoomClientDlg.h : header file
//

#if !defined(AFX_ntChatRoomClientDLG_H__4DF07865_B696_4641_82F8_4B32BF395959__INCLUDED_)
#define AFX_ntChatRoomClientDLG_H__4DF07865_B696_4641_82F8_4B32BF395959__INCLUDED_

#include "ServerSocket.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//class ClientSocket;
/////////////////////////////////////////////////////////////////////////////

class CntChatRoomClientDlg : public CDialog
{
// Construction
public:
	CServerSocket * myServerSocket;//声明CServerSocket对象指针
	BOOL GetMessage();
	CntChatRoomClientDlg(CServerSocket *,CWnd* pParent = NULL);	//带参数的构造函数

// Dialog Data
	//{{AFX_DATA(CntChatRoomClientDlg)
	enum { IDD = IDD_ntChatRoomClient_DIALOG };
	CListBox	m_IDC_LIST_CHATBOX_CONTROL;
	CString	m_IDC_EDIT_MESSAGE;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CntChatRoomClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CntChatRoomClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonSend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ntChatRoomClientDLG_H__4DF07865_B696_4641_82F8_4B32BF395959__INCLUDED_)
