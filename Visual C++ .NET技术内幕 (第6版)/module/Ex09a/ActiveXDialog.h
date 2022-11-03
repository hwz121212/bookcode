#pragma once
#include "ccalendar.h"


// CActiveXDialog dialog

class CActiveXDialog : public CDialog
{
	DECLARE_DYNAMIC(CActiveXDialog)

public:
	CActiveXDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CActiveXDialog();

// Dialog Data
	enum { IDD = IDD_ACTIVEXDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void NewMonthCalendar1();
	afx_msg void OnBnClickedNextweek();
	afx_msg void OnBnClickedSelectdate();
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
public:
	CCalendar m_calendar;
	short m_sDay;
	short m_sMonth;
	short m_sYear;
	COleVariant m_varValue;
	unsigned long m_BackColor;
protected:
	virtual void OnOK();
};
