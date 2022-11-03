// Ex24b.h : main header file for the Ex24b application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx24bApp:
// See Ex24b.cpp for the implementation of this class
//

class CEx24bApp : public CWinApp
{
public:
	CEx24bApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx24bApp theApp;