// Alarm.cpp : implementation file
//

#include "stdafx.h"
#include "Ex23e.h"
#include "Alarm.h"


// CAlarm dialog

IMPLEMENT_DYNAMIC(CAlarmDlg, CDialog)
CAlarmDlg::CAlarmDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAlarmDlg::IDD, pParent)
    , m_nHours(0)
    , m_nMinutes(0)
    , m_nSeconds(0)
{
}

CAlarmDlg::~CAlarmDlg()
{
}

void CAlarmDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_HOURS, m_nHours);
    DDX_Text(pDX, IDC_MINUTES, m_nMinutes);
    DDX_Text(pDX, IDC_SECONDS, m_nSeconds);
}


BEGIN_MESSAGE_MAP(CAlarmDlg, CDialog)
END_MESSAGE_MAP()


// CAlarm message handlers
