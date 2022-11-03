// Ex13c.h : main header file for the Ex13c application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx13cApp:
// See Ex13c.cpp for the implementation of this class
//

class CEx13cApp : public CWinApp
{
public:
	CEx13cApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx13cApp theApp;