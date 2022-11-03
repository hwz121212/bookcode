// Ex13a.h : main header file for the Ex13a application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx13aApp:
// See Ex13a.cpp for the implementation of this class
//

class CEx13aApp : public CWinApp
{
public:
	CEx13aApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx13aApp theApp;