// Ex06d.h : main header file for the Ex06d application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx06dApp:
// See Ex06d.cpp for the implementation of this class
//

class CEx06dApp : public CWinApp
{
public:
	CEx06dApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx06dApp theApp;