// Alarm.cpp : implementation file
//

#include "stdafx.h"
#include "Ex23c.h"
#include "Alarm.h"


// CAlarm

IMPLEMENT_DYNAMIC(CAlarm, CCmdTarget)
CAlarm::CAlarm(DATE time)
{
    CString str;

    str.Format("Entering CAlarm ctor -- vaTime = %f\n", (double) time);
	TRACE(str);
	m_time = time;
	EnableAutomation();
}

CAlarm::~CAlarm()
{
}


void CAlarm::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CAlarm, CCmdTarget)
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CAlarm, CCmdTarget)
    DISP_PROPERTY_NOTIFY_ID(CAlarm, "Time", dispidTime, m_time, OnTimeChanged, VT_DATE)
END_DISPATCH_MAP()

// Note: we add support for IID_IAlarm to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {8DB7D0FB-355F-464B-BBD5-0F17553E71C8}
static const IID IID_IAlarm =
{ 0x8DB7D0FB, 0x355F, 0x464B, { 0xBB, 0xD5, 0xF, 0x17, 0x55, 0x3E, 0x71, 0xC8 } };

BEGIN_INTERFACE_MAP(CAlarm, CCmdTarget)
	INTERFACE_PART(CAlarm, IID_IAlarm, Dispatch)
END_INTERFACE_MAP()


// CAlarm message handlers

void CAlarm::OnTimeChanged(void)
{
    AFX_MANAGE_STATE(AfxGetAppModuleState());

    // TODO: Add your property handler code here
}
