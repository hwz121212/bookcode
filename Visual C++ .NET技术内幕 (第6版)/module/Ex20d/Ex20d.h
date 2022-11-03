// Ex20d.h : main header file for the Ex20d DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CEx20dApp
// See Ex20d.cpp for the implementation of this class
//

class CEx20dApp : public CWinApp
{
public:
	CEx20dApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
