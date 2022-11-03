// Ex19c.h : main header file for the Ex19c application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx19cApp:
// See Ex19c.cpp for the implementation of this class
//

class CEx19cApp : public CWinApp
{
public:
	CEx19cApp();
public:
    CMultiDocTemplate* m_pTemplateHex;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CEx19cApp theApp;