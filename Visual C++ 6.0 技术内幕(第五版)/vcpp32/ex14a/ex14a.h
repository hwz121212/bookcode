// ex14a.h : main header file for the EX14A application
//

#if !defined(AFX_EX14A_H__361E2147_B1BB_11D1_8ED7_0080C7360DC1__INCLUDED_)
#define AFX_EX14A_H__361E2147_B1BB_11D1_8ED7_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx14aApp:
// See ex14a.cpp for the implementation of this class
//

class CEx14aApp : public CWinApp
{
public:
	CEx14aApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx14aApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CEx14aApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX14A_H__361E2147_B1BB_11D1_8ED7_0080C7360DC1__INCLUDED_)
