#pragma once
#include "afxdtctl.h"
#include "afxcmn.h"


// CEx08bDialog dialog

class CEx08bDialog : public CDialog
{
	DECLARE_DYNAMIC(CEx08bDialog)

public:
	CEx08bDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEx08bDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };
    CImageList m_imageList;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CDateTimeCtrl m_MonthCal1;
	CDateTimeCtrl m_MonthCal2;
	CDateTimeCtrl m_MonthCal3;
	CDateTimeCtrl m_MonthCal4;
	CIPAddressCtrl m_ptrIPCtrl;
	CMonthCalCtrl m_MonthCal5;
	CString m_strDate1;
	CString m_strDate2;
	CString m_strDate3;
	CString m_strDate4;
	CString m_strDate5;
	CString m_strIPValue;
	CString m_strComboEx1;
	CString m_strComboEx2;
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeDatetimepicker2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeDatetimepicker3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeDatetimepicker4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMcnSelchangeMonthcalendar1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboboxex1();
	afx_msg void OnCbnSelchangeComboboxex2();
};
