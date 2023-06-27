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

	CSetupDlg mySetupDlg;            //���öԻ����������
	CMSComm myComm;                  //MSComm�ؼ���������

	float arrMantissa[23];           //���0.5��0.25��0.125��0.0625��0.01325...
	BYTE arrCompare[8];              //���128��64��32��16��8...
	BYTE arrTypeLong[5];             //���4������������ռ�ֽ���
	BYTE arrB[5];                    //�����ֽ������ݣ���ӦB0~B4
	float arrF[5];                   //���帡�������ݣ���ӦF0~F4
	BYTE arrReceive[1024];           //��Ž��յ��Ĵ����ź�ԭʼֵ
	BYTE bytCount;                   //�ѽ��յ��ֽ���
	BYTE bytSum;                     //Ӧ���յ��ֽ�����
	double	dblIncStep;              //ģ���ֳ�����ʱʹ�õĲ���
	double	dblVarible;              //ģ���ֳ��ı���
	//32λ��������ת����������
	bool  Bin2Float(BYTE arrBin[],float *fOutput); 
	//������ת32λ������������
	bool  Float2Bin(float fInput,BYTE *arrBin);
	bool	AckError(BYTE errCode); //���ش�����Ӧ����
	bool	AckCorrect();           //������ȷ��Ӧ����








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
