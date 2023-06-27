// ex14c.h : main header file for the EX14C application
//

#if !defined(AFX_EX14C_H__C7C85805_E3B0_11D1_8524_A6295F36C950__INCLUDED_)
#define AFX_EX14C_H__C7C85805_E3B0_11D1_8524_A6295F36C950__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx14cApp:
// See ex14c.cpp for the implementation of this class
//

class CEx14cApp : public CWinApp
{
public:
	CEx14cApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx14cApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CEx14cApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX14C_H__C7C85805_E3B0_11D1_8524_A6295F36C950__INCLUDED_)
