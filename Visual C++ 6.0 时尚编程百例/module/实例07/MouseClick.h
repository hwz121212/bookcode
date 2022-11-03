// MouseClick.h : main header file for the MOUSECLICK application
//

#if !defined(AFX_MOUSECLICK_H__34D8A459_0B96_11D4_876D_00001CD613F0__INCLUDED_)
#define AFX_MOUSECLICK_H__34D8A459_0B96_11D4_876D_00001CD613F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMouseClickApp:
// See MouseClick.cpp for the implementation of this class
//

class CMouseClickApp : public CWinApp
{
public:
	CMouseClickApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMouseClickApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMouseClickApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOUSECLICK_H__34D8A459_0B96_11D4_876D_00001CD613F0__INCLUDED_)
