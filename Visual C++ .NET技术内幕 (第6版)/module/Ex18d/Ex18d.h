// Ex18d.h : main header file for the Ex18d application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx18dApp:
// See Ex18d.cpp for the implementation of this class
//

class CEx18dApp : public CWinApp
{
public:
	CEx18dApp();

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

extern CEx18dApp theApp;