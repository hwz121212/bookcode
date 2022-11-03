// DynMenu.h : main header file for the DYNMENU application
//

#if !defined(AFX_DYNMENU_H__6ABF34E5_E453_11D2_A71D_A44E1A83F14B__INCLUDED_)
#define AFX_DYNMENU_H__6ABF34E5_E453_11D2_A71D_A44E1A83F14B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDynMenuApp:
// See DynMenu.cpp for the implementation of this class
//

class CDynMenuApp : public CWinApp
{
public:
	CDynMenuApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDynMenuApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDynMenuApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DYNMENU_H__6ABF34E5_E453_11D2_A71D_A44E1A83F14B__INCLUDED_)
