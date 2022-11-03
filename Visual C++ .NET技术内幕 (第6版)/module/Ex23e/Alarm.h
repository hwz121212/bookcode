#pragma once


// CAlarm dialog

class CAlarmDlg : public CDialog
{
	DECLARE_DYNAMIC(CAlarmDlg)

public:
	CAlarmDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAlarmDlg();

// Dialog Data
	enum { IDD = IDD_ALARMDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    int m_nHours;
    int m_nMinutes;
    int m_nSeconds;
};
