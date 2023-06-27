// PC2PCView.h : interface of the CPC2PCView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PC2PCVIEW_H__7BD26DAC_2B97_4A1E_BCA4_8EBF77605496__INCLUDED_)
#define AFX_PC2PCVIEW_H__7BD26DAC_2B97_4A1E_BCA4_8EBF77605496__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SetupDlg.h"
#include "MainFrm.h"

#define WM_MYMSG WM_USER+100  

class CPC2PCView : public CEditView
{
protected: // create from serialization only
	CPC2PCView();
	DECLARE_DYNCREATE(CPC2PCView)

// Attributes
public:
	CPC2PCDoc* GetDocument();
	bool	DisSend(BYTE bytType);//发送态显示信息函数，bytType决定显示信息的内容
	bool	DisRcv(BYTE bytType);//接收态显示信息函数，bytType决定显示信息的内容
	BYTE	Read(BYTE arrBin[],int count);//读数据函数，arrBin[]存放数据，count是读的个数
										//成功返回0，读失败返回16，超时错误返回4
	bool	Write(BYTE arrBin[],int count);//发送数据函数，arrBin[]存放数据，count是发送个数
	BYTE	Detect(int count);//检测串口输入缓冲区中是否有指定个数的数据
								//返回0－有，4－超时错误,8-无效消息
	CSetupDlg  mySetupDlg;
	CStdioFile myFile;
	LPCTSTR	myCom;
	BYTE	myParity;
	DWORD	myfParity;
	DWORD	myBaudRate;

	BYTE	arrSendDataLast[1100];//存储上一次发送的数据流
	UINT	uintSendLenLast;//存储上一次发送数据的个数
	BYTE	arrSendData[1100];//存储本次发送的数据流
	UINT	uintSendLen;//存储本次发送数据的个数

	DWORD	dwFileLen;//存储文件长度
	UINT	uintStxCurNo;//发送或接收数据的当前序号

	BYTE	arrRcvData[1100];//存储本次接收的数据流
	UINT	uintRcvLen;//存储本次接收数据的个数

	bool	blnOpened;//端口已经打开
	bool	blnSeted;//设置过串口参数

	bool	blnNoTimeout;//不处理超时消息标志

	BYTE	bytTimeoutCounter;//发送操作中，处于1态时发送ENQ后
	                          //需要较长的延时，以便对方进行处理存盘文件
						   	//该变量对超时时间计数，大于某个值后才认为超时。

	BYTE	bytActStatus;   //操作状态，1－发送态，10－接收态
	BYTE	bytRcvStatus;   //接收操作当前状态，0－等待ENQ，1－等待STX或ETX
	BYTE	bytSendStatus;  //发送操作的当前状态，0－初始状态，1－发送完ENQ，2－发送完STX，3－发送完ETX
	BYTE	bytResendCount; //重发次数
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPC2PCView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPC2PCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// Generated message map functions
protected:
	//{{AFX_MSG(CPC2PCView)
	afx_msg void OnSetupcom();
	afx_msg void OnSendfile();
	afx_msg void OnOpencom();
	afx_msg void OnClosecom();
	afx_msg void OnUpdateSendfile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSetupcom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOpencom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateClosecom(CCmdUI* pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnUpdateAppExit(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg LONG OnReceiveEvent(WPARAM wParam,LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PC2PCView.cpp
inline CPC2PCDoc* CPC2PCView::GetDocument()
   { return (CPC2PCDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PC2PCVIEW_H__7BD26DAC_2B97_4A1E_BCA4_8EBF77605496__INCLUDED_)
