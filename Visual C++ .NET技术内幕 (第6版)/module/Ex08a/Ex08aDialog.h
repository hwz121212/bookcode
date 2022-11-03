#pragma once


// CEx08aDialog dialog

class CEx08aDialog : public CDialog
{
	DECLARE_DYNAMIC(CEx08aDialog)

public:
	CEx08aDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEx08aDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	int m_nProgress;
	int m_nSlider1;
	int m_nSlider2;
    static double dValue[5];
    CImageList m_imageList;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	double m_dSpin;
	afx_msg void OnLvnItemchangedListview1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedTreeview1(NMHDR *pNMHDR, LRESULT *pResult);
};
