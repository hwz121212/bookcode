// capaudioDlg.h : ͷ�ļ�
//
#include <dshow.h>

#pragma once


// CcapaudioDlg �Ի���
class CcapaudioDlg : public CDialog
{
// ����
public:
	CcapaudioDlg(CWnd* pParent = NULL);	// ��׼���캯��
	
	//myself
	IGraphBuilder *pGraph;
	ICaptureGraphBuilder2 * pBuilder;
	IMediaControl *pMC;
	IMoniker *pMoniker;
	IBaseFilter *pSrc,*pWaveDest,*pWriter;
	IFileSinkFilter2 *pSink;
	IPin * FindPin(IBaseFilter *pFilter, PIN_DIRECTION dir);
	//~myself

// �Ի�������
	enum { IDD = IDD_CAPAUDIO_DIALOG };

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
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRecord();
public:
	afx_msg void OnBnClickedCancel();
public:
	afx_msg void OnBnClickedStop();
public:
	afx_msg void OnBnClickedButtonFileName();
public:
	// �����ļ���
	CString m_PathName;
public:
//	afx_msg void OnDestroy();
public:
	afx_msg void OnClose();
};
