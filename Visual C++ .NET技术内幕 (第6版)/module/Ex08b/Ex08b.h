// Ex08b.h : main header file for the Ex08b application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx08bApp:
// See Ex08b.cpp for the implementation of this class
//

class CEx08bApp : public CWinApp
{
public:
	CEx08bApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx08bApp theApp;