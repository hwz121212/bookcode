// Ex13b.h : main header file for the Ex13b application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx13bApp:
// See Ex13b.cpp for the implementation of this class
//

class CEx13bApp : public CWinApp
{
public:
	CEx13bApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx13bApp theApp;