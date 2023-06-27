// TTYSendApiView.h : interface of the CTTYSendApiView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TTYSENDAPIVIEW_H__9A1DE178_727A_4964_885A_A1F0D546D4F4__INCLUDED_)
#define AFX_TTYSENDAPIVIEW_H__9A1DE178_727A_4964_885A_A1F0D546D4F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//���Ӷ�ͷ�ļ�������
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

	HANDLE hCom;                               //���ھ��
	OVERLAPPED Wol;                            //д����OVERLAPPED�ṹ����
	BYTE myWByte[300];                         //�����д����

	long dataWLen;                             //�������ݵĳ���

	CSetupDlg mySetupDlg;                      //�������öԻ���ʵ��

	LPCTSTR	myCom;                             //��������
	BYTE	myParity;                          //��żУ������
	DWORD	myfParity;                         //�Ƿ�ʹ����żУ��
	DWORD	myBaudRate;                        //ͨ�Ų�����
	bool	blnOpened;                         //�����Ѿ��򿪱�־
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
