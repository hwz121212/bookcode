// 9-2Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "VMR_Capture.h"
#include "Convert.h"

// CMy92Dlg �Ի���
class CMy92Dlg : public CDialog
{
// ����
public:
	CMy92Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY92_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	virtual BOOL PreTranslateMessage(MSG* pMsg);
// user dta
	//CToolTipCtrl m_toolTip;
	CToolTipCtrl m_tooltip;

	CVMR_Capture m_VMRCap;
	ColorSpaceConversions conv;
	UINT m_timerID;
	CString m_yuvFileName;
	CFile m_pFile;
	BOOL m_fileState;
	int m_imageWidth;
	int m_imageHeight;
	BYTE *p_yuv420;

//

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
	// display video data
	CStatic m_videoWindow;
public:
	CComboBox m_listCtrl;
public:
	afx_msg void OnBnClickedPreview();
public:
	afx_msg void OnBnClickedCapture();
public:
	afx_msg void OnBnClickedPauseplay();
public:
	afx_msg void OnBnClickedSavegraph();
public:
	afx_msg void OnBnClickedExitapp();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	afx_msg void OnBnClickedStopcap();
};
