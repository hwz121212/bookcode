// ActiveXDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Ex09a.h"
#include "ActiveXDialog.h"


// CActiveXDialog dialog

IMPLEMENT_DYNAMIC(CActiveXDialog, CDialog)
CActiveXDialog::CActiveXDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CActiveXDialog::IDD, pParent)
	
{
	m_sDay = 0;
    m_sMonth = 0;
    m_sYear = 0;
	m_BackColor = 0x8000000F;
}

CActiveXDialog::~CActiveXDialog()
{
}

void CActiveXDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CALENDAR1, m_calendar);
	DDX_Text(pDX, IDC_DAY, m_sDay);
	DDX_Text(pDX, IDC_MONTH, m_sMonth);
    DDX_Text(pDX, IDC_YEAR, m_sYear);
    DDX_OCColor(pDX, IDC_CALENDAR1, DISPID_BACKCOLOR, m_BackColor);
}


BEGIN_MESSAGE_MAP(CActiveXDialog, CDialog)
	ON_BN_CLICKED(IDC_NEXTWEEK, OnBnClickedNextweek)
	ON_BN_CLICKED(IDC_SELECTDATE, OnBnClickedSelectdate)
	
END_MESSAGE_MAP()


// CActiveXDialog message handlers
BEGIN_EVENTSINK_MAP(CActiveXDialog, CDialog)
	ON_EVENT(CActiveXDialog, IDC_CALENDAR1, 3, NewMonthCalendar1, VTS_NONE)
END_EVENTSINK_MAP()

BOOL CActiveXDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_calendar.put_Value(m_varValue); // no DDX for VARIANTs

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CActiveXDialog::OnOK()
{
	CDialog::OnOK();
	m_varValue = m_calendar.get_Value(); // no DDX for VARIANTs
}
void CActiveXDialog::NewMonthCalendar1()
{
	AfxMessageBox("EVENT:  CActiveXDialog::NewMonthCalendar1");
}

void CActiveXDialog::OnBnClickedSelectdate()
{
	CDataExchange dx(this, TRUE);
    DDX_Text(&dx, IDC_DAY, m_sDay);
    DDX_Text(&dx, IDC_MONTH, m_sMonth);
    DDX_Text(&dx, IDC_YEAR, m_sYear);
    m_calendar.put_Day(m_sDay);
    m_calendar.put_Month(m_sMonth);
    m_calendar.put_Year(m_sYear);

}

void CActiveXDialog::OnBnClickedNextweek()
{
	m_calendar.NextWeek();    
}



