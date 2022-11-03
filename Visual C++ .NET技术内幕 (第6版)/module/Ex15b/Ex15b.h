// Ex15b.h : main header file for the Ex15b application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx15bApp:
// See Ex15b.cpp for the implementation of this class
//

class CEx15bApp : public CWinApp
{
public:
	CEx15bApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx15bApp theApp;