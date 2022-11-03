// Ex23e.h : main header file for the Ex23e application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx23eApp:
// See Ex23e.cpp for the implementation of this class
//

class CEx23eApp : public CWinApp
{
public:
	CEx23eApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx23eApp theApp;