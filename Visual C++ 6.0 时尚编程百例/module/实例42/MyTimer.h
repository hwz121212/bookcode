// MyTimer.h : main header file for the MYTIMER application
//

#if !defined(AFX_MYTIMER_H__5862DF05_DB10_11D2_A71D_B295A824025F__INCLUDED_)
#define AFX_MYTIMER_H__5862DF05_DB10_11D2_A71D_B295A824025F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyTimerApp:
// See MyTimer.cpp for the implementation of this class
//

class CMyTimerApp : public CWinApp
{
public:
	CMyTimerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTimerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMyTimerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTIMER_H__5862DF05_DB10_11D2_A71D_B295A824025F__INCLUDED_)
