// Ex22c.h : main header file for the Ex22c application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx22cApp:
// See Ex22c.cpp for the implementation of this class
//

class CEx22cApp : public CWinApp
{
public:
	CEx22cApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx22cApp theApp;