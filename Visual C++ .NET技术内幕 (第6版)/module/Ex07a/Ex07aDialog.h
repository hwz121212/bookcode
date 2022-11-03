#pragma once


// CEx07aDialog dialog

class CEx07aDialog : public CDialog
{
	DECLARE_DYNAMIC(CEx07aDialog)

public:
	CEx07aDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEx07aDialog();

    enum { nMin = 0 };
    enum { nMax = 100 };

	// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// Enter Bio info here...
	CString m_strBio;
	int m_nCat;
	CString m_strDept;
	BOOL m_bInsDis;
	CString m_strEduc;
	int m_nLang;
	BOOL m_bInsLife;
	int m_nLoyal;
	BOOL m_bInsMed;
	CString m_strName;
	int m_nRely;
	CString m_strSkill;
	int m_nSsn;
	afx_msg void OnBnClickedSpecial();
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
