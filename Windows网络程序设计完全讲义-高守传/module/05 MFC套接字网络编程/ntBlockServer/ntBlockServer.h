// ntBlockServer.h : main header file for the ntBlockServer application
//

#if !defined(AFX_ntBlockServer_H__AD1C696A_8379_43CF_9C17_AA99AD05A61A__INCLUDED_)
#define AFX_ntBlockServer_H__AD1C696A_8379_43CF_9C17_AA99AD05A61A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CntBlockServerApp:
// See ntBlockServer.cpp for the implementation of this class
//

class CntBlockServerApp : public CWinApp
{
public:
	CntBlockServerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CntBlockServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CntBlockServerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ntBlockServer_H__AD1C696A_8379_43CF_9C17_AA99AD05A61A__INCLUDED_)
