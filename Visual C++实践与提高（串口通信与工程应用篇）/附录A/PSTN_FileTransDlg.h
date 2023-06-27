// PSTN_FileTransDlg.h : header file
//

#if !defined(AFX_PSTN_FILETRANSDLG_H__974EC735_A1A6_4D9D_849C_079A8994F2E2__INCLUDED_)
#define AFX_PSTN_FILETRANSDLG_H__974EC735_A1A6_4D9D_849C_079A8994F2E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mscomm.h"
//#include "SetupDlg.h"
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// CPSTN_FileTransDlg dialog

class CPSTN_FileTransDlg : public CDialog
{
// Construction
public:
	CPSTN_FileTransDlg(CWnd* pParent = NULL);	// standard constructor

	CMSComm myComm;	                    	//����myComm����ΪCMSComm����
	int		iRelay;							//��ʱ����
	int		iRcvStatus;						//����״̬
	int		iSendStatus;					//����״̬
	int		iActStatus;                     //����״̬��0����Ч��1������̬��2������̬
	int		iSendCur;                       //��ǰ���ʹ���
	int		iRcvCur;						//��ǰ���մ���
	long	lFileLen;                       //�ļ�����
	char	charSendData[10240];            //���ļ��ж���������
	char	charRcvData[10240];             //���յ�����������
	char	charSendNow[132];               //���η�������
	int		iAgain;                         //���Դ���
	BYTE	bytSendNow;                     //����ʱ������֡�е����
	BYTE	bytRcvNow;                      //����ʱ������֡��Ӧ�õ����
	CByteArray ArraySend;                   //������Ŷ��������ݵ�CByteArray��ʵ�����շ��͵�����


// Dialog Data
	//{{AFX_DATA(CPSTN_FileTransDlg)
	enum { IDD = IDD_PSTN_FILETRANS_DIALOG };
	CEdit	m_Dis;
	CButton	m_Exit;
	CButton	m_Closecom;
	CButton	m_Sendfile;
	CButton	m_Rcvfile;
	CButton	m_Opencom;
	int		m_Com;
	int		m_BaudRate;
	int		m_Parity;
	CString	m_Number;
	CString	m_Again;
	CString	m_Phone;
	//}}AFX_DATA


	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSTN_FileTransDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPSTN_FileTransDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnExit();
	afx_msg void OnOpencom();
	afx_msg void OnClosecom();
	afx_msg void OnSendfile();
	afx_msg void OnOnCommMscomm1();
	afx_msg void OnRcvfile();
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSTN_FILETRANSDLG_H__974EC735_A1A6_4D9D_849C_079A8994F2E2__INCLUDED_)
