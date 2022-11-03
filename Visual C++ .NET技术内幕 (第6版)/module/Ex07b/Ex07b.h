// Ex07b.h : main header file for the Ex07b application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx07bApp:
// See Ex07b.cpp for the implementation of this class
//

class CEx07bApp : public CWinApp
{
public:
	CEx07bApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx07bApp theApp;