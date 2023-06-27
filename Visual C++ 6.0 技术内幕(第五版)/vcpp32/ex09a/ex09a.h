// ex09a.h : main header file for the EX09A application
//

#if !defined(AFX_EX09A_H__E0A2E3D7_D7BF_11D1_B2A3_FB06F1BF1F48__INCLUDED_)
#define AFX_EX09A_H__E0A2E3D7_D7BF_11D1_B2A3_FB06F1BF1F48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx09aApp:
// See ex09a.cpp for the implementation of this class
//

class CEx09aApp : public CWinApp
{
public:
	CEx09aApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx09aApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CEx09aApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX09A_H__E0A2E3D7_D7BF_11D1_B2A3_FB06F1BF1F48__INCLUDED_)
