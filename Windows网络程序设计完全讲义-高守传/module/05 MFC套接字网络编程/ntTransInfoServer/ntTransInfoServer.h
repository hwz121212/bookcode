// ntTransInfoServer.h : main header file for the ntTransInfoServer application
//

#if !defined(AFX_ntTransInfoServer_H__61FF12CC_2510_4A3F_A8C3_516B993EE5F1__INCLUDED_)
#define AFX_ntTransInfoServer_H__61FF12CC_2510_4A3F_A8C3_516B993EE5F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CntTransInfoServerApp:
// See ntTransInfoServer.cpp for the implementation of this class
//

class CntTransInfoServerApp : public CWinApp
{
public:
	CntTransInfoServerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CntTransInfoServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CntTransInfoServerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ntTransInfoServer_H__61FF12CC_2510_4A3F_A8C3_516B993EE5F1__INCLUDED_)
