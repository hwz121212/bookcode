// MyIe.h : main header file for the MYIE application
//

#if !defined(AFX_MYIE_H__BD651585_C472_11D2_A71D_AFFC5B955368__INCLUDED_)
#define AFX_MYIE_H__BD651585_C472_11D2_A71D_AFFC5B955368__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyIeApp:
// See MyIe.cpp for the implementation of this class
//

class CMyIeApp : public CWinApp
{
public:
	CMyIeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyIeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMyIeApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYIE_H__BD651585_C472_11D2_A71D_AFFC5B955368__INCLUDED_)
