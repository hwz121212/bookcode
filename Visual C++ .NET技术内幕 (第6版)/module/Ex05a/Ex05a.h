// Ex05a.h : main header file for the Ex05a application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx05aApp:
// See Ex05a.cpp for the implementation of this class
//

class CEx05aApp : public CWinApp
{
public:
	CEx05aApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx05aApp theApp;