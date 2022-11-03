// Ex20c.h : main header file for the Ex20c DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CEx20cApp
// See Ex20c.cpp for the implementation of this class
//

class CEx20cApp : public CWinApp
{
public:
	CEx20cApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern "C" __declspec(dllexport) double Ex20cSquareRoot(double d);