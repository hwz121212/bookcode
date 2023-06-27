// ComWorkFlow.h: interface for the CComWorkFlow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMWORKFLOW_H__A096D640_8212_45A7_A555_01F42033DFCF__INCLUDED_)
#define AFX_COMWORKFLOW_H__A096D640_8212_45A7_A555_01F42033DFCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataFlow.h"
#include "ThreadCom.h"

class CComWorkFlow  
{
public:
	CComWorkFlow();				// 构造函数
	virtual ~CComWorkFlow();	// 析构函数

private:
	DWORD StopWinThread(CWinThread *pThread, DWORD dwTimeout);	// 停止Windows线程
	BOOL StartComThread();		// 启动串口线程
	BOOL StopComThread();		// 停止串口线程

	BOOL OpenCom();				// 打开串口
	BOOL CloseCom();			// 关闭串口

public:
	BOOL InitWorkFlow(CString com, DCB dcb);	// 初始化工作区
	BOOL OpenWorkFlow();						// 打开工作区
	BOOL CloseWorkFlow();						// 关闭工作区

	DCB m_dcb;									// 串口参数配置结构
	CString m_Com;								// 要操作的串口
	CDataFlow* m_DataFlow;						// 串口对应的NEMA0183协议解析器
	CThreadCom* m_ThreadCom;					// 串口对应的工作线程
};

#endif // !defined(AFX_COMWORKFLOW_H__A096D640_8212_45A7_A555_01F42033DFCF__INCLUDED_)
