// Ex14a.h : main header file for the Ex14a application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx14aApp:
// See Ex14a.cpp for the implementation of this class
//

class CEx14aApp : public CWinApp
{
public:
	CEx14aApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx14aApp theApp;