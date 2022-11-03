// Ex18c.h : main header file for the Ex18c application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx18cApp:
// See Ex18c.cpp for the implementation of this class
//

class CEx18cApp : public CWinApp
{
public:
	CEx18cApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx18cApp theApp;