// Ex16c.h : main header file for the Ex16c application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEx16cApp:
// See Ex16c.cpp for the implementation of this class
//

class CEx16cApp : public CWinApp
{
public:
	CEx16cApp();

protected:
	CMultiDocTemplate* m_pDocTemplate;
public:

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	afx_msg void OnFileNewFrame();
	afx_msg void OnFileNew();
	DECLARE_MESSAGE_MAP()
};

extern CEx16cApp theApp;