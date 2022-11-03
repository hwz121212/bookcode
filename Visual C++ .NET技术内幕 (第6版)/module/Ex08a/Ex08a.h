// Ex08a.h : main header file for the Ex08a application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx08aApp:
// See Ex08a.cpp for the implementation of this class
//

class CEx08aApp : public CWinApp
{
public:
	CEx08aApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx08aApp theApp;