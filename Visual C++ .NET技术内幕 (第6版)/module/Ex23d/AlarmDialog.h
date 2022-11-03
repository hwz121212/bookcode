#pragma once


// CAlarmDialog dialog

class CAlarmDialog : public CDialog
{
	DECLARE_DYNAMIC(CAlarmDialog)

public:
	CAlarmDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAlarmDialog();

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
