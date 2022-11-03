// Ex23b.h : main header file for the Ex23b DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CEx23bApp
// See Ex23b.cpp for the implementation of this class
//

class CEx23bApp : public CWinApp
{
public:
	CEx23bApp();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	DECLARE_MESSAGE_MAP()
};
