// Dsound3DPlayDemoDlg.h : ͷ�ļ�
//

#pragma once


// CDsound3DPlayDemoDlg �Ի���
class CDsound3DPlayDemoDlg : public CDialog
{
// ����
public:
	CDsound3DPlayDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DSOUND3DPLAYDEMO_DIALOG };

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
	afx_msg void OnSelectFile();
	afx_msg void OnBnClickedPlay();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT nIDEvent ); 
	void SafeRealse();
	void UpdateGrid(  FLOAT x, FLOAT y );
};
