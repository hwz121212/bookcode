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
	bool	DisSend(BYTE bytType);//����̬��ʾ��Ϣ������bytType������ʾ��Ϣ������
	bool	DisRcv(BYTE bytType);//����̬��ʾ��Ϣ������bytType������ʾ��Ϣ������
	BYTE	Read(BYTE arrBin[],int count);//�����ݺ�����arrBin[]������ݣ�count�Ƕ��ĸ���
										//�ɹ�����0����ʧ�ܷ���16����ʱ���󷵻�4
	bool	Write(BYTE arrBin[],int count);//�������ݺ�����arrBin[]������ݣ�count�Ƿ��͸���
	BYTE	Detect(int count);//��⴮�����뻺�������Ƿ���ָ������������
								//����0���У�4����ʱ����,8-��Ч��Ϣ
	CSetupDlg  mySetupDlg;
	CStdioFile myFile;
	LPCTSTR	myCom;
	BYTE	myParity;
	DWORD	myfParity;
	DWORD	myBaudRate;

	BYTE	arrSendDataLast[1100];//�洢��һ�η��͵�������
	UINT	uintSendLenLast;//�洢��һ�η������ݵĸ���
	BYTE	arrSendData[1100];//�洢���η��͵�������
	UINT	uintSendLen;//�洢���η������ݵĸ���

	DWORD	dwFileLen;//�洢�ļ�����
	UINT	uintStxCurNo;//���ͻ�������ݵĵ�ǰ���

	BYTE	arrRcvData[1100];//�洢���ν��յ�������
	UINT	uintRcvLen;//�洢���ν������ݵĸ���

	bool	blnOpened;//�˿��Ѿ���
	bool	blnSeted;//���ù����ڲ���

	bool	blnNoTimeout;//������ʱ��Ϣ��־

	BYTE	bytTimeoutCounter;//���Ͳ����У�����1̬ʱ����ENQ��
	                          //��Ҫ�ϳ�����ʱ���Ա�Է����д�������ļ�
						   	//�ñ����Գ�ʱʱ�����������ĳ��ֵ�����Ϊ��ʱ��

	BYTE	bytActStatus;   //����״̬��1������̬��10������̬
	BYTE	bytRcvStatus;   //���ղ�����ǰ״̬��0���ȴ�ENQ��1���ȴ�STX��ETX
	BYTE	bytSendStatus;  //���Ͳ����ĵ�ǰ״̬��0����ʼ״̬��1��������ENQ��2��������STX��3��������ETX
	BYTE	bytResendCount; //�ط�����
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
