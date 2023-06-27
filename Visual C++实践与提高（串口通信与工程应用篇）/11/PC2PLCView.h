// PC2PLCView.h : interface of the CPC2PLCView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PC2PLCVIEW_H__600BB640_77F9_4E36_968F_5325568C2ED1__INCLUDED_)
#define AFX_PC2PLCVIEW_H__600BB640_77F9_4E36_968F_5325568C2ED1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SetupDlg.h"
#include "MainFrm.h"

class CPC2PLCView : public CEditView
{
protected: // create from serialization only
	CPC2PLCView();
	DECLARE_DYNCREATE(CPC2PLCView)

// Attributes
public:

	CPC2PLCDoc* GetDocument();
	bool	myfuncRead(BYTE ackChar);     //执行读操作，并返回成功与否
	bool	myfuncWrite();                //执行写操作，并返回成功与否
	CSetupDlg mySetupDlg;                 //声明设置对话框实例

	LPCTSTR	myCom;                        //串口名称
	BYTE	myParity;                     //奇偶校验类型
	DWORD	myfParity;                    //是否使用奇偶校验
	DWORD	myBaudRate;                   //通信波特率

	bool	blnOpened;                    //串口已经打开标志

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPC2PLCView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPC2PLCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPC2PLCView)
	afx_msg void OnSetup();
	afx_msg void OnReceive();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnUpdateReceive(CCmdUI* pCmdUI);
	afx_msg void OnOpencom();
	afx_msg void OnUpdateSetup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOpencom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateClosecom(CCmdUI* pCmdUI);
	afx_msg void OnClosecom();
	afx_msg void OnUpdateAppExit(CCmdUI* pCmdUI);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PC2PLCView.cpp
inline CPC2PLCDoc* CPC2PLCView::GetDocument()
   { return (CPC2PLCDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PC2PLCVIEW_H__600BB640_77F9_4E36_968F_5325568C2ED1__INCLUDED_)
