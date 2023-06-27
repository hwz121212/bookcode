// MoniControl.h : main header file for the MONICONTROL application
//

#if !defined(AFX_MONICONTROL_H__93B5B8FE_09E1_4289_8B4A_4C5EF9A63689__INCLUDED_)
#define AFX_MONICONTROL_H__93B5B8FE_09E1_4289_8B4A_4C5EF9A63689__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMoniControlApp:
// See MoniControl.cpp for the implementation of this class
//

class CMoniControlApp : public CWinApp
{
public:
	CMoniControlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMoniControlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMoniControlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONICONTROL_H__93B5B8FE_09E1_4289_8B4A_4C5EF9A63689__INCLUDED_)
