// ex05c.h : main header file for the EX05C application
//

#if !defined(AFX_EX05C_H__B6B0A125_9C84_11D1_8ED7_0080C7360DC1__INCLUDED_)
#define AFX_EX05C_H__B6B0A125_9C84_11D1_8ED7_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx05cApp:
// See ex05c.cpp for the implementation of this class
//

class CEx05cApp : public CWinApp
{
public:
	CEx05cApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx05cApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CEx05cApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX05C_H__B6B0A125_9C84_11D1_8ED7_0080C7360DC1__INCLUDED_)
