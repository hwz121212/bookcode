// Ex07a.h : main header file for the Ex07a application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx07aApp:
// See Ex07a.cpp for the implementation of this class
//

class CEx07aApp : public CWinApp
{
public:
	CEx07aApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx07aApp theApp;