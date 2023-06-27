#if !defined(AFX_DIALOG1_H__E0A2E3E7_D7BF_11D1_B2A3_FB06F1BF1F48__INCLUDED_)
#define AFX_DIALOG1_H__E0A2E3E7_D7BF_11D1_B2A3_FB06F1BF1F48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialog1 dialog

class CDialog1 : public CDialog
{
// Construction
public:
	CDialog1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog1)
	enum { IDD = IDD_DIALOG1 };
	CMonthCalCtrl	m_MonthCal5;
	CDateTimeCtrl	m_MonthCal4;
	CDateTimeCtrl	m_MonthCal3;
	CDateTimeCtrl	m_MonthCal2;
	CDateTimeCtrl	m_MonthCal1;
	CIPAddressCtrl	m_ptrIPCtrl;
	CImageList m_imageList;
	CString	m_strDate1;
	CString	m_strDate2;
	CString	m_strDate3;
	CString	m_strDate4;
	CString	m_strDate5;
	CString	m_strIPValue;
	CString	m_strComboEx1;
	CString	m_strComboEx2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog1)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboboxex1();
	afx_msg void OnSelchangeComboboxex2();
	afx_msg void OnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeDatetimepicker2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeDatetimepicker3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeDatetimepicker4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFieldchangedIpaddress1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG1_H__E0A2E3E7_D7BF_11D1_B2A3_FB06F1BF1F48__INCLUDED_)
