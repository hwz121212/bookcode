// Ex05c.h : main header file for the Ex05c application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx05cApp:
// See Ex05c.cpp for the implementation of this class
//

class CEx05cApp : public CWinApp
{
public:
	CEx05cApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx05cApp theApp;