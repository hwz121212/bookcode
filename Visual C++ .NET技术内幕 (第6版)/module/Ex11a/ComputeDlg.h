#pragma once


// CComputeDlg dialog

class CComputeDlg : public CDialog
{
	DECLARE_DYNAMIC(CComputeDlg)

public:
	CComputeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CComputeDlg();

// Dialog Data
	enum { IDD = IDD_COMPUTE };

protected:
    int m_nTimer;
    int m_nCount;
    enum { nMaxCount = 50000 };

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedCancel();
};
