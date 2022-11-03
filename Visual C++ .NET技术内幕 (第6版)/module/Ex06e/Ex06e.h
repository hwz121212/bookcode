// Ex06e.h : main header file for the Ex06e application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx06eApp:
// See Ex06e.cpp for the implementation of this class
//

class CEx06eApp : public CWinApp
{
public:
	CEx06eApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx06eApp theApp;