// Ex18a.h : main header file for the Ex18a application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx18aApp:
// See Ex18a.cpp for the implementation of this class
//

class CEx18aApp : public CWinApp
{
public:
	CEx18aApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx18aApp theApp;