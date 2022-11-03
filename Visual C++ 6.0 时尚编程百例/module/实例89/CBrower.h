// CBrower.h : main header file for the CBROWER application
//

#if !defined(AFX_CBROWER_H__A9AEDC06_25E3_11D4_B0E6_00001A012804__INCLUDED_)
#define AFX_CBROWER_H__A9AEDC06_25E3_11D4_B0E6_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCBrowerApp:
// See CBrower.cpp for the implementation of this class
//

class CCBrowerApp : public CWinApp
{
public:
	CCBrowerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCBrowerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCBrowerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CBROWER_H__A9AEDC06_25E3_11D4_B0E6_00001A012804__INCLUDED_)
