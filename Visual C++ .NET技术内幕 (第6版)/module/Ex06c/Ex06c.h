// Ex06c.h : main header file for the Ex06c application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx06cApp:
// See Ex06c.cpp for the implementation of this class
//

class CEx06cApp : public CWinApp
{
public:
	CEx06cApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx06cApp theApp;