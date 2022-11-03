// Ex06a.h : main header file for the Ex06a application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx06aApp:
// See Ex06a.cpp for the implementation of this class
//

class CEx06aApp : public CWinApp
{
public:
	CEx06aApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx06aApp theApp;