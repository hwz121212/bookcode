// TapiNew.h : main header file for the TAPINEW application
//

#if !defined(AFX_TAPINEW_H__975A99F0_EF5B_410A_9F7B_43FD1B454959__INCLUDED_)
#define AFX_TAPINEW_H__975A99F0_EF5B_410A_9F7B_43FD1B454959__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTapiNewApp:
// See TapiNew.cpp for the implementation of this class
//

class CTapiNewApp : public CWinApp
{
public:
	CTapiNewApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTapiNewApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTapiNewApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TAPINEW_H__975A99F0_EF5B_410A_9F7B_43FD1B454959__INCLUDED_)
