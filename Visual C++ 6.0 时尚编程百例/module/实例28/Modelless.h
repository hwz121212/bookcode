// Modelless.h : main header file for the MODELLESS application
//

#if !defined(AFX_MODELLESS_H__7F0ECE58_1C5D_11D4_B0E6_00001A012804__INCLUDED_)
#define AFX_MODELLESS_H__7F0ECE58_1C5D_11D4_B0E6_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CModellessApp:
// See Modelless.cpp for the implementation of this class
//

class CModellessApp : public CWinApp
{
public:
	CModellessApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModellessApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CModellessApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODELLESS_H__7F0ECE58_1C5D_11D4_B0E6_00001A012804__INCLUDED_)
