// Ex23d.h : main header file for the Ex23d application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx23dApp:
// See Ex23d.cpp for the implementation of this class
//

class CEx23dApp : public CWinApp
{
public:
	CEx23dApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx23dApp theApp;