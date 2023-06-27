// ex23b.h : main header file for the EX23B application
//

#if !defined(AFX_EX23B_H__D20D2FA5_EE57_11D1_B30A_0080C7360DC1__INCLUDED_)
#define AFX_EX23B_H__D20D2FA5_EE57_11D1_B30A_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx23bApp:
// See ex23b.cpp for the implementation of this class
//

class CEx23bApp : public CWinApp
{
public:
	CEx23bApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx23bApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CEx23bApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX23B_H__D20D2FA5_EE57_11D1_B30A_0080C7360DC1__INCLUDED_)
