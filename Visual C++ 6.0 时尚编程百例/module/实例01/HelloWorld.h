// HelloWorld.h : main header file for the HELLOWORLD application
//

#if !defined(AFX_HELLOWORLD_H__A1700790_E3C2_11D2_A71D_ED13154A5A4B__INCLUDED_)
#define AFX_HELLOWORLD_H__A1700790_E3C2_11D2_A71D_ED13154A5A4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHelloWorldApp:
// See HelloWorld.cpp for the implementation of this class
//

class CHelloWorldApp : public CWinApp
{
public:
	CHelloWorldApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHelloWorldApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CHelloWorldApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELLOWORLD_H__A1700790_E3C2_11D2_A71D_ED13154A5A4B__INCLUDED_)
