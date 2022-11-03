// AlarmDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Ex23d.h"
#include "AlarmDialog.h"


// CAlarmDialog dialog

IMPLEMENT_DYNAMIC(CAlarmDialog, CDialog)
CAlarmDialog::CAlarmDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CAlarmDialog::IDD, pParent)
    , m_nHours(0)
    , m_nMinutes(0)
    , m_nSeconds(0)
{
}

CAlarmDialog::~CAlarmDialog()
{
}

void CAlarmDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_HOURS, m_nHours);
    DDX_Text(pDX, IDC_MINUTES, m_nMinutes);
    DDX_Text(pDX, IDC_SECONDS, m_nSeconds);
}


BEGIN_MESSAGE_MAP(CAlarmDialog, CDialog)
END_MESSAGE_MAP()


// CAlarmDialog message handlers
