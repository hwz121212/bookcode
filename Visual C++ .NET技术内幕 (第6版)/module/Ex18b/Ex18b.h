// Ex18b.h : main header file for the Ex18b application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx18bApp:
// See Ex18b.cpp for the implementation of this class
//

class CEx18bApp : public CWinApp
{
public:
	CEx18bApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx18bApp theApp;