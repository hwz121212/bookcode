// Ex17a.h : main header file for the Ex17a application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx17aApp:
// See Ex17a.cpp for the implementation of this class
//

class CEx17aApp : public CWinApp
{
public:
	CEx17aApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx17aApp theApp;