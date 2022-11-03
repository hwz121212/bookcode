// Ex20b.h : main header file for the Ex20b application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx20bApp:
// See Ex20b.cpp for the implementation of this class
//

class CEx20bApp : public CWinApp
{
public:
	CEx20bApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx20bApp theApp;