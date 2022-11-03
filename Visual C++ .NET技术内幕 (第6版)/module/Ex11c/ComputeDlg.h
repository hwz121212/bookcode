#pragma once

#define WM_THREADFINISHED		WM_USER + 5
UINT ComputeThreadProc(LPVOID pParam);


// CComputeDlg dialog

class CComputeDlg : public CDialog
{
	LRESULT OnThreadFinished(WPARAM wParam, LPARAM lParam);

private:
    int m_nTimer;
public:
    enum { nMaxCount = 50000 };

	DECLARE_DYNAMIC(CComputeDlg)

public:
	CComputeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CComputeDlg();

// Dialog Data
	enum { IDD = IDD_COMPUTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
