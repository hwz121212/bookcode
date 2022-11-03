// Ex11a.h : main header file for the Ex11a application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx11aApp:
// See Ex11a.cpp for the implementation of this class
//

class CEx11aApp : public CWinApp
{
public:
	CEx11aApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx11aApp theApp;