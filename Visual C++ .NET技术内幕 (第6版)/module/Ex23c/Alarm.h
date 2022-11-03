
#pragma once


// CAlarm command target

class CAlarm : public CCmdTarget
{
	DECLARE_DYNAMIC(CAlarm)

public:
	CAlarm(DATE time);
	virtual ~CAlarm();

	virtual void OnFinalRelease();

    DATE m_time;

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
    void OnTimeChanged(void);

    enum 
    {
        dispidTime = 1
    };
};


