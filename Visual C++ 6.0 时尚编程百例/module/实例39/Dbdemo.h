// Dbdemo.h : main header file for the DBDEMO application
//

#if !defined(AFX_DBDEMO_H__9859BEA5_C5B0_11D2_A71D_E1F8995C8269__INCLUDED_)
#define AFX_DBDEMO_H__9859BEA5_C5B0_11D2_A71D_E1F8995C8269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDbdemoApp:
// See Dbdemo.cpp for the implementation of this class
//

class CDbdemoApp : public CWinApp
{
public:
	CDbdemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDbdemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDbdemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBDEMO_H__9859BEA5_C5B0_11D2_A71D_E1F8995C8269__INCLUDED_)
