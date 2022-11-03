// SoundDlg.h : header file
//

#if !defined(AFX_SOUNDDLG_H__1DD1AAE8_271A_11D4_B0E6_00001A012804__INCLUDED_)
#define AFX_SOUNDDLG_H__1DD1AAE8_271A_11D4_B0E6_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CSoundDlg dialog

class CSoundDlg : public CDialog
{
// Construction
public:
	CSoundDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSoundDlg)
	enum { IDD = IDD_SOUND_DIALOG };
	CButton	m_stop;
	CButton	m_play;
	CButton	m_pause;
	CButton	m_open;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoundDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	private:
		void ShowError(DWORD dwError);

// Implementation
protected:
	HICON m_hIcon;
    BOOL m_bPlay;//是否在播放文件
	BOOL m_bPause;//是否已暂停播放文件
	int  Iscda;  //判断是否为播放CD文件
	MCIDEVICEID m_MCIDeviceID;

	// Generated message map functions
	//{{AFX_MSG(CSoundDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPlay();
	afx_msg void OnOpen();
	afx_msg void OnPause();
	afx_msg void OnStop();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	//}}AFX_MSG
	afx_msg LRESULT OnMciNotify(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOUNDDLG_H__1DD1AAE8_271A_11D4_B0E6_00001A012804__INCLUDED_)
