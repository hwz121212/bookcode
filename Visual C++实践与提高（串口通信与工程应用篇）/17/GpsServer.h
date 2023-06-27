// GpsServer.h : main header file for the GPSSERVER application
//

#if !defined(AFX_GPSSERVER_H__7EDC80AF_A1C7_4CA9_96AA_4CE7DEA76B3E__INCLUDED_)
#define AFX_GPSSERVER_H__7EDC80AF_A1C7_4CA9_96AA_4CE7DEA76B3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGpsServerApp:
// See GpsServer.cpp for the implementation of this class
//


class CGpsServerApp : public CWinApp
{
public:	
	CGpsServerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGpsServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CGpsServerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPSSERVER_H__7EDC80AF_A1C7_4CA9_96AA_4CE7DEA76B3E__INCLUDED_)
