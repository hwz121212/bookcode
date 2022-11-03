// Ex21b.h : main header file for the Ex21b application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx21bApp:
// See Ex21b.cpp for the implementation of this class
//

class CEx21bApp : public CWinApp
{
public:
	CEx21bApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx21bApp theApp;