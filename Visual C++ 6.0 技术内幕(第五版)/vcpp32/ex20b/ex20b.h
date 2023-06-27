// ex20b.h : main header file for the EX20B application
//

#if !defined(AFX_EX20B_H__806617BD_C4C9_11D1_B30A_0080C7360DC1__INCLUDED_)
#define AFX_EX20B_H__806617BD_C4C9_11D1_B30A_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx20bApp:
// See ex20b.cpp for the implementation of this class
//

class CEx20bApp : public CWinApp
{
public:
	CEx20bApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx20bApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CEx20bApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX20B_H__806617BD_C4C9_11D1_B30A_0080C7360DC1__INCLUDED_)
