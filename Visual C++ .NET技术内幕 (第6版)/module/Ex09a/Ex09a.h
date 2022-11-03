// Ex09a.h : main header file for the Ex09a application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx09aApp:
// See Ex09a.cpp for the implementation of this class
//

class CEx09aApp : public CWinApp
{
public:
	CEx09aApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx09aApp theApp;