// ex19a.h : main header file for the EX19A application
//

#if !defined(AFX_EX19A_H__EF919B45_C406_11D1_B30A_0080C7360DC1__INCLUDED_)
#define AFX_EX19A_H__EF919B45_C406_11D1_B30A_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx19aApp:
// See ex19a.cpp for the implementation of this class
//

class CEx19aApp : public CWinApp
{
public:
	CEx19aApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx19aApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CEx19aApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX19A_H__EF919B45_C406_11D1_B30A_0080C7360DC1__INCLUDED_)
