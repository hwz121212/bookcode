// ex38a.h : main header file for the EX38A application
//

#if !defined(AFX_EX38A_H__25B52AE6_0533_11D2_8B47_00104B881C94__INCLUDED_)
#define AFX_EX38A_H__25B52AE6_0533_11D2_8B47_00104B881C94__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx38aApp:
// See ex38a.cpp for the implementation of this class
//

class CEx38aApp : public CWinApp
{
public:
	CEx38aApp(LPCTSTR lpszAppName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx38aApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx38aApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX38A_H__25B52AE6_0533_11D2_8B47_00104B881C94__INCLUDED_)
