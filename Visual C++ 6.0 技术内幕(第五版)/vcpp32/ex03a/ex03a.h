// ex03a.h : main header file for the EX03A application
//

#if !defined(AFX_EX03A_H__8BD53F05_B293_11D1_8ED7_0080C7360DC1__INCLUDED_)
#define AFX_EX03A_H__8BD53F05_B293_11D1_8ED7_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx03aApp:
// See ex03a.cpp for the implementation of this class
//

class CEx03aApp : public CWinApp
{
public:
	CEx03aApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx03aApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CEx03aApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX03A_H__8BD53F05_B293_11D1_8ED7_0080C7360DC1__INCLUDED_)
