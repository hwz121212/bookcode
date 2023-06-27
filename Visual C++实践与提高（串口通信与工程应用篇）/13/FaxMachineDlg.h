// FaxMachineDlg.h : header file
//

#if !defined(AFX_FAXMACHINEDLG_H__DD390FE5_5548_4E76_AB85_E57016AA3DF4__INCLUDED_)
#define AFX_FAXMACHINEDLG_H__DD390FE5_5548_4E76_AB85_E57016AA3DF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SmarFaxh.h"                         //加入SmartFax.dll头文件的引用
#pragma comment(lib, "SmartFax.lib")          //编译时加入"SmartFax.lib"库
#pragma comment(lib, "Tapi32.lib")            //编译时加入"Tapi32.lib"库
/////////////////////////////////////////////////////////////////////////////
// CFaxMachineDlg dialog

class CFaxMachineDlg : public CDialog
{
// Construction
public:
	CFaxMachineDlg(CWnd* pParent = NULL);	// standard constructor

	
	bool	m_bEcmFlag;
	int		m_nPage;
	int		ComPortSendFax();
	long	m_nTimes;                  //
	bool	RecvFaxInComPort();
	bool	RecvFaxInTapi();
	bool	m_bFaxing;
	SmartFaxObj g_hFax ;
	
	void	OnSmartFax(WPARAM wParam, LPARAM lParam);
	static void __stdcall FillComboBox(DWORD dwDevice, 
								const char *sLineName, 
								const char *ComPort,
								unsigned long lParam);
	int		TapiSendFax();
	CString m_strSelModem;
	CString GetFullPath(CString FileName);
	CString GetWorkPath();


// Dialog Data
	//{{AFX_DATA(CFaxMachineDlg)
	enum { IDD = IDD_FAXMACHINE_DIALOG };
	CButton	m_SendFax;
	CButton	m_ReceiveFax;
	CButton	m_Exit;
	CButton	m_Abort;
	CComboBox	m_ModemList;
	CString	m_Phone;
	int		m_Volume;
	CString	m_To;
	CString	m_Identity;
	CString	m_Time;
	CString	m_From;
	CString	m_Page;
	CString	m_Status;
	CString	m_File;
	BOOL	m_Ecm;
	BOOL	m_Compress;
	CString	m_CallerNo;
	BOOL	m_AutoReply;
	CString	m_ActualSpeed;
	int		m_PortType;
	int		m_FaxSpeed;
	int		m_FaxProtocol;
	BOOL	m_FaxHead;
	int		m_HighResolution;
	int		m_RadioSend;
	CString	m_Remote;
	CString	m_Data;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFaxMachineDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFaxMachineDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSendfax();
	afx_msg void OnExit();
	afx_msg void OnRadioSend();
	afx_msg void OnRadioRcv();
	afx_msg void OnAbort();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnFaxhead();
	afx_msg void OnReceivefax();
	afx_msg void OnAutoreply();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FAXMACHINEDLG_H__DD390FE5_5548_4E76_AB85_E57016AA3DF4__INCLUDED_)
