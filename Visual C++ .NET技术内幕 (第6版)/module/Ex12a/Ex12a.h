// Ex12a.h : main header file for the Ex12a application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx12aApp:
// See Ex12a.cpp for the implementation of this class
//

class CEx12aApp : public CWinApp
{
public:
	CEx12aApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx12aApp theApp;