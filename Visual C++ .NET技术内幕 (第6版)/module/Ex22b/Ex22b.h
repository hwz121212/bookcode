// Ex22b.h : main header file for the Ex22b DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CEx22bApp
// See Ex22b.cpp for the implementation of this class
//

class CEx22bApp : public CWinApp
{
public:
	CEx22bApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
