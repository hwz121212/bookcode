// Listbox.h : main header file for the LISTBOX application
//

#if !defined(AFX_LISTBOX_H__9859BEB8_C5B0_11D2_A71D_E1F8995C8269__INCLUDED_)
#define AFX_LISTBOX_H__9859BEB8_C5B0_11D2_A71D_E1F8995C8269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CListboxApp:
// See Listbox.cpp for the implementation of this class
//

class CListboxApp : public CWinApp
{
public:
	CListboxApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListboxApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CListboxApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTBOX_H__9859BEB8_C5B0_11D2_A71D_E1F8995C8269__INCLUDED_)
