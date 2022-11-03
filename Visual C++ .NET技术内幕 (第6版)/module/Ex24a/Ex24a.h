// Ex24a.h : main header file for the Ex24a application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx24aApp:
// See Ex24a.cpp for the implementation of this class
//

class CEx24aApp : public CWinApp
{
public:
	CEx24aApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx24aApp theApp;