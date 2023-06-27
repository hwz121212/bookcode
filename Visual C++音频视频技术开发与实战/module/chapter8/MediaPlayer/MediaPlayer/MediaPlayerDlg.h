// MediaPlayerDlg.h : ͷ�ļ�
//

#pragma once
#include "CDXGraph.h"
#include "afxwin.h"
#include "afxcmn.h"


#define SLIDER_TIMER 100

// CMediaPlayerDlg �Ի���
class CMediaPlayerDlg : public CDialog
{
// ����
public:
	CMediaPlayerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MEDIAPLAYER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnGraphNotify(WPARAM inWParam, LPARAM inLParam);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpen();

	virtual BOOL PreTranslateMessage(MSG* pMsg);

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
//	afx_msg void OnAskCbFormatName(UINT nMaxCount, LPTSTR lpszString);
	//////////////////////////////////////////////////////////////////////////////////// myself
	//tooltip��ʾ
	CToolTipCtrl m_tooltip;
	CDXGraph *m_pFilterGraph;
	//Դ�ļ�
	CString	m_sourceFile;
	CString m_mediaFileName;
	UINT_PTR m_playerTimer;
	void CreateGraph();
	void DestroyGraph();
	CString  GetFileTitleFromFileName(CString FileName, BOOL Ext);
	long m_volume;

//////////////////////////////////////////////////////////////////////////////////// ~myself
public:
	//CStatic fdgfdgfgfdg;
public:
	CStatic m_videoWindow;
public:
	afx_msg void OnBnClickedButtonPlay();
public:
	afx_msg void OnBnClickedButtonExit();
public:
	afx_msg void OnBnClickedButtonStop();
public:
	afx_msg void OnBnClickedButtonPause();
public:
	afx_msg void OnMenuOpenfile();
public:
	afx_msg void OnMenuHalfrate();
public:
	afx_msg void OnMenuNormalrate();
public:
	afx_msg void OnMenuDoublerate();
public:
	afx_msg void OnMenuFullscreen();
public:
	afx_msg void OnMenuAlwaysontop();
public:
	CSliderCtrl m_sliderPlayer;
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
public:
	CSliderCtrl m_sliderVolume;
public:
	afx_msg void OnMenuMute();
public:
	afx_msg void OnBnClickedButtonGrasp();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	afx_msg void OnMenuClosefile();
public:
	afx_msg void OnMenuPlay();
public:
	afx_msg void OnMenuStop();
public:
	afx_msg void OnMenuGrabimage();
public:
	afx_msg void OnMenuSavegraph();
public:
	afx_msg void OnMenuExit();
};
