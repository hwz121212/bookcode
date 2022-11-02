// ntBlockClient.h : main header file for the ntBlockClient application
//

#if !defined(AFX_ntBlockClient_H__F8568D98_5744_4D87_8F3E_92F9754C0ABC__INCLUDED_)
#define AFX_ntBlockClient_H__F8568D98_5744_4D87_8F3E_92F9754C0ABC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CntBlockClientApp:
// See ntBlockClient.cpp for the implementation of this class
//

class CntBlockClientApp : public CWinApp
{
public:
	CntBlockClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CntBlockClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CntBlockClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ntBlockClient_H__F8568D98_5744_4D87_8F3E_92F9754C0ABC__INCLUDED_)
