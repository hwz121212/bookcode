// Ex19b.h : main header file for the Ex19b application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx19bApp:
// See Ex19b.cpp for the implementation of this class
//

class CEx19bApp : public CWinApp
{
public:
	CEx19bApp();

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

extern CEx19bApp theApp;