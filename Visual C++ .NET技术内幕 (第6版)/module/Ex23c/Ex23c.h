// Ex23c.h : main header file for the Ex23c application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx23cApp:
// See Ex23c.cpp for the implementation of this class
//

class CEx23cApp : public CWinApp
{
public:
	CEx23cApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx23cApp theApp;