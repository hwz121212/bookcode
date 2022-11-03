// CCalendar.cpp  : Definition of ActiveX Control wrapper class(es) created by Microsoft Visual C++


#include "stdafx.h"
#include "CCalendar.h"

/////////////////////////////////////////////////////////////////////////////
// CCalendar


IMPLEMENT_DYNCREATE(CCalendar, CWnd)

BEGIN_MESSAGE_MAP(CCalendar, CWnd)
    ON_WM_HELPINFO()
END_MESSAGE_MAP()



BOOL CCalendar::OnHelpInfo(HELPINFO* pHelpInfo) 
{    
    // Edit the following string for your system
    ::WinHelp(GetSafeHwnd(), "c:\\winnt\\system32\\mscal.hlp",
              HELP_FINDER, 0);
    return FALSE;
}


