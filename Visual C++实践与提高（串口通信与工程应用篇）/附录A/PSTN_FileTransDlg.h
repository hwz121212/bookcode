// PSTN_FileTransDlg.h : header file
//

#if !defined(AFX_PSTN_FILETRANSDLG_H__974EC735_A1A6_4D9D_849C_079A8994F2E2__INCLUDED_)
#define AFX_PSTN_FILETRANSDLG_H__974EC735_A1A6_4D9D_849C_079A8994F2E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mscomm.h"
//#include "SetupDlg.h"
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// CPSTN_FileTransDlg dialog

class CPSTN_FileTransDlg : public CDialog
{
// Construction
public:
	CPSTN_FileTransDlg(CWnd* pParent = NULL);	// standard constructor

	CMSComm myComm;	                    	//声明myComm变量为CMSComm类型
	int		iRelay;							//延时次数
	int		iRcvStatus;						//接收状态
	int		iSendStatus;					//发送状态
	int		iActStatus;                     //操作状态，0－无效，1－发送态，2－接收态
	int		iSendCur;                       //当前发送次数
	int		iRcvCur;						//当前接收次数
	long	lFileLen;                       //文件长度
	char	charSendData[10240];            //从文件中读出的数据
	char	charRcvData[10240];             //接收到的所有数据
	char	charSendNow[132];               //本次发送数据
	int		iAgain;                         //重试次数
	BYTE	bytSendNow;                     //发送时，本次帧中的序号
	BYTE	bytRcvNow;                      //接收时，本次帧中应该的序号
	CByteArray ArraySend;                   //创建存放二进制数据的CByteArray类实例，刚发送的数据


// Dialog Data
	//{{AFX_DATA(CPSTN_FileTransDlg)
	enum { IDD = IDD_PSTN_FILETRANS_DIALOG };
	CEdit	m_Dis;
	CButton	m_Exit;
	CButton	m_Closecom;
	CButton	m_Sendfile;
	CButton	m_Rcvfile;
	CButton	m_Opencom;
	int		m_Com;
	int		m_BaudRate;
	int		m_Parity;
	CString	m_Number;
	CString	m_Again;
	CString	m_Phone;
	//}}AFX_DATA


	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSTN_FileTransDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPSTN_FileTransDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnExit();
	afx_msg void OnOpencom();
	afx_msg void OnClosecom();
	afx_msg void OnSendfile();
	afx_msg void OnOnCommMscomm1();
	afx_msg void OnRcvfile();
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSTN_FILETRANSDLG_H__974EC735_A1A6_4D9D_849C_079A8994F2E2__INCLUDED_)
