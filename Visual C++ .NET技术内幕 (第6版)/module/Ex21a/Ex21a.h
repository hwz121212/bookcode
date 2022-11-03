// Ex21a.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CEx21aApp:
// See Ex21a.cpp for the implementation of this class
//

class CEx21aApp : public CWinApp
{
public:
	CEx21aApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CEx21aApp theApp;