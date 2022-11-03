// Ex07c.h : main header file for the Ex07c application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx07cApp:
// See Ex07c.cpp for the implementation of this class
//

class CEx07cApp : public CWinApp
{
public:
	CEx07cApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx07cApp theApp;