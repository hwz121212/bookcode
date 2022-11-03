// Ex11b.h : main header file for the Ex11b application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx11bApp:
// See Ex11b.cpp for the implementation of this class
//

class CEx11bApp : public CWinApp
{
public:
	CEx11bApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx11bApp theApp;