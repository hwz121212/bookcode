// Ex05b.h : main header file for the Ex05b application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx05bApp:
// See Ex05b.cpp for the implementation of this class
//

class CEx05bApp : public CWinApp
{
public:
	CEx05bApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx05bApp theApp;