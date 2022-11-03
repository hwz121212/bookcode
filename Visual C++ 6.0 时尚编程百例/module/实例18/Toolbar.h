// Toolbar.h : main header file for the TOOLBAR application
//

#if !defined(AFX_TOOLBAR_H__30B15B9B_0300_11D4_876D_00001CD613F0__INCLUDED_)
#define AFX_TOOLBAR_H__30B15B9B_0300_11D4_876D_00001CD613F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CToolbarApp:
// See Toolbar.cpp for the implementation of this class
//

class CToolbarApp : public CWinApp
{
public:
	CToolbarApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolbarApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CToolbarApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLBAR_H__30B15B9B_0300_11D4_876D_00001CD613F0__INCLUDED_)
