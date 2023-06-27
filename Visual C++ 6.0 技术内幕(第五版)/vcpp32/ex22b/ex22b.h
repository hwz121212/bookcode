// ex22b.h : main header file for the EX22B application
//

#if !defined(AFX_EX22B_H__7C620ED2_C7EE_11D1_B30A_0080C7360DC1__INCLUDED_)
#define AFX_EX22B_H__7C620ED2_C7EE_11D1_B30A_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx22bApp:
// See ex22b.cpp for the implementation of this class
//

class CEx22bApp : public CWinApp
{
public:
	CEx22bApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx22bApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CEx22bApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX22B_H__7C620ED2_C7EE_11D1_B30A_0080C7360DC1__INCLUDED_)
