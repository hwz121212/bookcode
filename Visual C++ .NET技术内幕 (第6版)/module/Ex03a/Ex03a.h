// Ex03a.h : main header file for the Ex03a application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx03aApp:
// See Ex03a.cpp for the implementation of this class
//

class CEx03aApp : public CWinApp
{
public:
	CEx03aApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx03aApp theApp;