// Print1.h : main header file for the PRINT1 application
//

#if !defined(AFX_PRINT1_H__DC72DC26_29C8_11D4_9E64_00001A012804__INCLUDED_)
#define AFX_PRINT1_H__DC72DC26_29C8_11D4_9E64_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPrint1App:
// See Print1.cpp for the implementation of this class
//

class CPrint1App : public CWinApp
{
public:
	CPrint1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrint1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPrint1App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINT1_H__DC72DC26_29C8_11D4_9E64_00001A012804__INCLUDED_)
