/// GpsServerDoc.h : interface of the CGpsServerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPSSERVERDOC_H__5FE33884_95CB_4D77_A529_B600F923EA13__INCLUDED_)
#define AFX_GPSSERVERDOC_H__5FE33884_95CB_4D77_A529_B600F923EA13__INCLUDED_

#include "StdAfx.h"
#include "RSUser.h"
#include "RSComConfig.h"
#include "ThreadCom.h"
#include "DataFlow.h"
#include "ComWorkFlow.h"
#include "MainFrm.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CGpsServerDoc : public CDocument
{
protected: // create from serialization only
	CGpsServerDoc();
	DECLARE_DYNCREATE(CGpsServerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGpsServerDoc)
	public:
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	
	BOOL ConnectDB();				// 连接数据库
	
	void FuncCommTimer();			// 向串口发送数据的定时器
	BOOL IsUserValid(CString UserName, CString Pass);	// 判断用户是否有效
	BOOL ReadComConfigs();			// 读取串口参数

	BOOL OpenComWorkFlow(CString com);	// 打开指定串口工作区
	BOOL OpenAllComWorkFlow();			// 打开配置的所有串口的工作区
	BOOL CloseComWorkFlow(CString com);	// 关闭串口的工作区
	BOOL CloseAllComWorkFlow();			// 关闭所有的串口工作区

	int GetComCount();					// 获取串口的个数
	CComWorkFlow* GetComWorkFlow(CString com);	// 获取指定串口名称的串口工作区	

	
	void AddGPSPackToDB(GPSPack *pack, CString m_com);

	
	BOOL m_bCom;						// 标识串口是否已经打开
	BOOL m_bInitCom;					// 标识串口是否已经初始化成功
	
	HANDLE MutexObject[5];				
	CArray<CComWorkFlow*,CComWorkFlow*> m_ComWorkFlow;	// 串口工作区集合
	CArray<CSendObject*, CSendObject*> m_CommandList;	// 发送数据列表


	/////////////////////////////////////////
	// 开始--有关数据库操作的变量

	BOOL m_bUseDB;					// 是否使用数据库	
	CDatabase* m_pDBGps;			// 数据库变量	
	CRSUser* m_pRSUser;				// 用户记录表变量	
	CRSComConfig* m_pRSComConfig;	// 串口记录表变量
	
	// 结束--有关数据库操作的变量
	///////////////////////////////////////////
		
	virtual ~CGpsServerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL ReadDBComConfigs();			// 从数据库中读取串口配置信息
	BOOL ReadDefaultComConfigs();		// 读取默认的串口配置信息

	CMainFrame* GetMainFrame();			// 获取主框架

	void CheckSendList();				// 检测发送数据

// Generated message map functions
protected:
	//{{AFX_MSG(CGpsServerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPSSERVERDOC_H__5FE33884_95CB_4D77_A529_B600F923EA13__INCLUDED_)
