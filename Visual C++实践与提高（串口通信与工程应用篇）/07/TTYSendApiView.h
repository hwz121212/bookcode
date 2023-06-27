// TTYSendApiView.h : interface of the CTTYSendApiView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TTYSENDAPIVIEW_H__9A1DE178_727A_4964_885A_A1F0D546D4F4__INCLUDED_)
#define AFX_TTYSENDAPIVIEW_H__9A1DE178_727A_4964_885A_A1F0D546D4F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//增加对头文件的引用
#include "SetupDlg.h"
#include "MainFrm.h"

class CTTYSendApiView : public CEditView
{
protected: // create from serialization only
	CTTYSendApiView();
	DECLARE_DYNCREATE(CTTYSendApiView)

// Attributes
public:
	CTTYSendApiDoc* GetDocument();

	HANDLE hCom;                               //串口句柄
	OVERLAPPED Wol;                            //写操作OVERLAPPED结构变量
	BYTE myWByte[300];                         //存放欲写数据

	long dataWLen;                             //发送数据的长度

	CSetupDlg mySetupDlg;                      //声明设置对话框实例

	LPCTSTR	myCom;                             //串口名称
	BYTE	myParity;                          //奇偶校验类型
	DWORD	myfParity;                         //是否使用奇偶校验
	DWORD	myBaudRate;                        //通信波特率
	bool	blnOpened;                         //串口已经打开标志
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTTYSendApiView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTTYSendApiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTTYSendApiView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetupcom();
	afx_msg void OnOpencom();
	afx_msg void OnClosecom();
	afx_msg void OnUpdateClosecom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOpencom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSetupcom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAppExit(CCmdUI* pCmdUI);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TTYSendApiView.cpp
inline CTTYSendApiDoc* CTTYSendApiView::GetDocument()
   { return (CTTYSendApiDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TTYSENDAPIVIEW_H__9A1DE178_727A_4964_885A_A1F0D546D4F4__INCLUDED_)
