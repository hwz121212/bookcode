// PC2ClientDlg.h : header file
//

#if !defined(AFX_PC2CLIENTDLG_H__9BB46ADB_C278_4186_97ED_EBC8B6AB9578__INCLUDED_)
#define AFX_PC2CLIENTDLG_H__9BB46ADB_C278_4186_97ED_EBC8B6AB9578__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SetupDlg.h"
#include "mscomm.h"
/////////////////////////////////////////////////////////////////////////////
// CPC2ClientDlg dialog

class CPC2ClientDlg : public CDialog
{
// Construction
public:
	CPC2ClientDlg(CWnd* pParent = NULL);	// standard constructor

	CSetupDlg mySetupDlg;            //设置对话框对象声明
	CMSComm myComm;                  //MSComm控件对象声明

	float arrMantissa[23];           //存放0.5、0.25、0.125、0.0625、0.01325...
	BYTE arrCompare[8];              //存放128、64、32、16、8...
	BYTE arrTypeLong[5];             //存放4种数据类型所占字节数
	BYTE arrB[5];                    //定义字节型数据，对应B0~B4
	float arrF[5];                   //定义浮点型数据，对应F0~F4
	BYTE arrReceive[1024];           //存放接收到的串行信号原始值
	BYTE bytCount;                   //已接收的字节数
	BYTE bytSum;                     //应接收的字节总数
	double	dblIncStep;              //模拟现场变量时使用的步长
	double	dblVarible;              //模拟现场的变量
	//32位二进制数转浮点数程序
	bool  Bin2Float(BYTE arrBin[],float *fOutput); 
	//浮点数转32位二进制数程序
	bool  Float2Bin(float fInput,BYTE *arrBin);
	bool	AckError(BYTE errCode); //返回错误响应程序
	bool	AckCorrect();           //返回正确响应程序








// Dialog Data
	//{{AFX_DATA(CPC2ClientDlg)
	enum { IDD = IDD_PC2CLIENT_DIALOG };
	CStatic	m_Volume4;
	CStatic	m_Volume3;
	CStatic	m_Volume2;
	CStatic	m_Volume1;
	CStatic	m_Valve4;
	CStatic	m_Valve2;
	CStatic	m_Valve1;
	CButton	m_Setup;
	CButton	m_Open;
	CButton	m_Close;
	CEdit	m_Edit1;
	CStatic	m_Valve3;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPC2ClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPC2ClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSetupcom();
	afx_msg void OnOnCommMscomm1();
	afx_msg void OnOpencom();
	afx_msg void OnClosecom();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PC2CLIENTDLG_H__9BB46ADB_C278_4186_97ED_EBC8B6AB9578__INCLUDED_)
