// Ex06b.h : main header file for the Ex06b application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx06bApp:
// See Ex06b.cpp for the implementation of this class
//

class CEx06bApp : public CWinApp
{
public:
	CEx06bApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx06bApp theApp;