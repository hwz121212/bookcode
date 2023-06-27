// ex38b.h : main header file for the EX38B application
//

#if !defined(AFX_EX38B_H__25B52AFA_0533_11D2_8B47_00104B881C94__INCLUDED_)
#define AFX_EX38B_H__25B52AFA_0533_11D2_8B47_00104B881C94__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx38bApp:
// See ex38b.cpp for the implementation of this class
//

class CEx38bApp : public CWinApp
{
public:
	CEx38bApp(LPCTSTR lpszAppName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx38bApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx38bApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX38B_H__25B52AFA_0533_11D2_8B47_00104B881C94__INCLUDED_)
