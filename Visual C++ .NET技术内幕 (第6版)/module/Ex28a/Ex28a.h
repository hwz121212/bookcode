// Ex28a.h : main header file for the Ex28a application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx28aApp:
// See Ex28a.cpp for the implementation of this class
//

class CEx28aApp : public CWinApp
{
public:
	CEx28aApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx28aApp theApp;