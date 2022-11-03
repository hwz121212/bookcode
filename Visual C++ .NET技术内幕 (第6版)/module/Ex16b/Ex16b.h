// Ex16b.h : main header file for the Ex16b application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx16bApp:
// See Ex16b.cpp for the implementation of this class
//

class CEx16bApp : public CWinApp
{
public:
	CEx16bApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
public:
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
};

extern CEx16bApp theApp;