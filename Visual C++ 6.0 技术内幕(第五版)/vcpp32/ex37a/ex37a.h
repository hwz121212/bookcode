// ex37a.h : main header file for the EX37A application
//

#if !defined(AFX_EX37A_H__97DB1245_0651_11D2_8524_444553540000__INCLUDED_)
#define AFX_EX37A_H__97DB1245_0651_11D2_8524_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx37aApp:
// See ex37a.cpp for the implementation of this class
//

class CEx37aApp : public CWinApp
{
public:
	CEx37aApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx37aApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CEx37aApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX37A_H__97DB1245_0651_11D2_8524_444553540000__INCLUDED_)
