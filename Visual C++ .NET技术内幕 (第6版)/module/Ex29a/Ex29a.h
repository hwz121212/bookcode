// Ex29a.h : main header file for the Ex29a application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx29aApp:
// See Ex29a.cpp for the implementation of this class
//

class CEx29aApp : public CWinApp
{
public:
	CEx29aApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx29aApp theApp;