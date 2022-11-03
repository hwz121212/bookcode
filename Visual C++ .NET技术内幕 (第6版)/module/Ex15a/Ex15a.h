// Ex15a.h : main header file for the Ex15a application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx15aApp:
// See Ex15a.cpp for the implementation of this class
//

class CEx15aApp : public CWinApp
{
public:
	CEx15aApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx15aApp theApp;