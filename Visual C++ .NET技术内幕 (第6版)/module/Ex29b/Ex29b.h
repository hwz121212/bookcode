// Ex29b.h : main header file for the Ex29b application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx29bApp:
// See Ex29b.cpp for the implementation of this class
//

class CEx29bApp : public CWinApp
{
public:
	CEx29bApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx29bApp theApp;