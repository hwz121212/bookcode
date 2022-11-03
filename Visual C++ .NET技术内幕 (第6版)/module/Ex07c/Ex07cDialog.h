#pragma once

#define WM_GOODBYE     WM_USER + 5

// CEx07cDialog dialog

class CEx07cDialog : public CDialog
{
	DECLARE_DYNAMIC(CEx07cDialog)

public:
	CEx07cDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEx07cDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

    CEx07cDialog(CView* pView);
	BOOL Create();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
    CView* m_pView;

public:
	CString m_strEdit1;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};
