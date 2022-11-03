#pragma once

#define WM_THREADFINISHED		WM_USER + 5
UINT ComputeThreadProc(LPVOID pParam);

// CComputeDlg dialog

class CComputeDlg : public CDialog
{
	LRESULT OnThreadFinished(WPARAM wParam, LPARAM lParam);
	DECLARE_DYNAMIC(CComputeDlg)
    int m_nTimer;

public:
	CComputeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CComputeDlg();

// Dialog Data
	enum { IDD = IDD_COMPUTE };

	enum { nMaxCount = 50000 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedStart();
};
