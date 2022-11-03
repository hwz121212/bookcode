#pragma once


// CTest20dDialog dialog

extern "C" __declspec(dllimport) void Ex20dEntry(); // dummy function
#define RYG_SETSTATE WM_USER + 0
#define RYG_GETSTATE WM_USER + 1

class CTest20dDialog : public CDialog
{
	enum { OFF, RED, YELLOW, GREEN } m_nState;
	DECLARE_DYNAMIC(CTest20dDialog)

public:
	CTest20dDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTest20dDialog();

// Dialog Data
	enum { IDD = IDD_EX20D };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	afx_msg void OnClickedRyg();
};
