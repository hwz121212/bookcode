#if !defined(AFX_DATAFLOW_H__AB9B89BF_28FC_441A_81E9_3268DDED11A0__INCLUDED_)
#define AFX_DATAFLOW_H__AB9B89BF_28FC_441A_81E9_3268DDED11A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataFlow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDataFlow window

/******************************************************************   

**   类   名:   CDataFlow

**   功   能:   解析NEMA0183的协议数据

**   创建人:    李琳娜

**   日   期:   2008-8-30 

**-----------------------------------------------------------------------------  */ 
class CDataFlow : public CWnd
{
// Construction
public:
	CDataFlow();
	CDataFlow(CString com, DWORD dwMessage);
	virtual ~CDataFlow();

// Attributes
public:	
	CString m_Com;							// 解析的数据对应的串口的名称，比如"COM1"

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataFlow)
	//}}AFX_VIRTUAL

// Implementation
public:	
	DWORD GetMeMsg();						// 返回当前CWnd处理的消息
	// 设置显示控件
	void SetEditCtrl(CEdit * pReceEdit,CEdit *pSendEdit);	
	HWND Create();							// 创建对应的显示控件

	// Generated message map functions
protected:	
	
public:		
	//{{AFX_MSG(CDataFlow)
	virtual void OnComMsg(DWORD dwEvent,DWORD dwLen);
	afx_msg void OnInitCenter(WPARAM wp,LPARAM lp);
	afx_msg void OnDecodeMsg(DWORD dwData,DWORD dwLen);
	afx_msg void OnResponseMsg(DWORD wp,DWORD lp);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// 解析函数
private:
	void InitVariable();						// 初始化类中的变量	
	BOOL SearchFlow();							// 在数据缓冲区中查找是否存在协议数据包
	void DealFlow();							// 处理数据缓冲区中的当前定位的协议数据包	
	BOOL CheckData(CString* check1, int check2);//检测校验码
	//文本格式
	GPSPack* DecodeNEMA_Text(CString source);
	//GPS定位信息
	GPSPack* DecodeNEMA_GPGGA();
	//当前卫星信息
	GPSPack* DecodeNEMA_GPGSA();
	//可见卫星信息
	GPSPack* DecodeNEMA_GPGSV();
	//推荐定位信息
	GPSPack* DecodeNEMA_GPRMC();
	//地面速度信息
	GPSPack* DecodeNEMA_GPVTG();
	//定位地理信息
	GPSPack* DecodeNEMA_GPGLL();
	//时间和日期信息
	GPSPack* DecodeNEMA_GPZDA();
	//大地坐标系信息
	GPSPack* DecodeNEMA_GPDTM();
	//高明公司扩展协议
	//估计误差信息
	GPSPack* DecodeNEMA_PGRME();
	//GPS定位信息
	GPSPack* DecodeNEMA_PGRMF();
	//坐标系统信息
	GPSPack* DecodeNEMA_PGRMM();
	//工作状态信息
	GPSPack* DecodeNEMA_PGRMT();
	//三维速度信息
	GPSPack* DecodeNEMA_PGRMV();
	//信标差分信息
	GPSPack* DecodeNEMA_PGRMB();

	// 变量定义
private:		
	DWORD m_dwToMeMsg;						// CDataFlow处理的消息名称
	DWORD m_dwComEvent;						// 当前串口的错误事件
	
	CEdit * m_pSendEdit;					// 显示发送数据的CEdit控件
	CEdit * m_pReceEdit;					// 显示接收数据的CEdit控件

	CArray<CString*, CString*> m_dataArray;	// 当前数据包中的各个分项数组
	CByteArray	m_Data;						// 要解析的数据缓冲区
	
	int		m_dwDataGramLen;				// 帧长
	DWORD	m_dwDataGramTail;				// 帧尾
	DWORD	m_dwDataGramHead;				// 帧头
	
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAFLOW_H__AB9B89BF_28FC_441A_81E9_3268DDED11A0__INCLUDED_)
