#pragma once


// CPromptDlg dialog

class CPromptDlg : public CDialog
{
	DECLARE_DYNCREATE(CPromptDlg)

public:
	CPromptDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPromptDlg();
// Overrides

// Dialog Data
	enum { IDD = IDD_PROMPTDLG, IDH = IDR_HTML_PROMPTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
    long m_lData;
    CString m_strData;
};
