// CaptureVideoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "CaptureClass.h"

// CCaptureVideoDlg �Ի���
class CCaptureVideoDlg : public CDialog
{
// ����
public:
	CCaptureVideoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CAPTUREVIDEO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	virtual BOOL PreTranslateMessage(MSG* pMsg);
// user data
	CCaptureClass m_cap;
	CToolTipCtrl m_tooltip;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// ��ʾ�����ͼ��
	CStatic m_videoWindow;
public:
	afx_msg void OnBnClickedPreview();
public:
	afx_msg void OnBnClickedCapture();
public:
	afx_msg void OnBnClickedVideoFormat();
public:
	afx_msg void OnBnClickedImageParameter();
public:
	afx_msg void OnBnClickedSavegraph();
public:
	afx_msg void OnBnClickedExit();
public:
	// ��Ͽ��б���ʾ�豸����
	CComboBox m_listCtrl;
};
