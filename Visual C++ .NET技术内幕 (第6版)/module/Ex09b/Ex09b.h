// Ex09b.h : main header file for the Ex09b application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx09bApp:
// See Ex09b.cpp for the implementation of this class
//

class CEx09bApp : public CWinApp
{
public:
	CEx09bApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx09bApp theApp;