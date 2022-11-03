// Ex17b.h : main header file for the Ex17b application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx17bApp:
// See Ex17b.cpp for the implementation of this class
//

class CEx17bApp : public CWinApp
{
public:
	CEx17bApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx17bApp theApp;