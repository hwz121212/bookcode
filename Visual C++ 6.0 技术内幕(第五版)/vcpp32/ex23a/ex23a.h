// ex23a.h : main header file for the EX23A application
//

#if !defined(AFX_EX23A_H__591DC947_C89D_11D1_B30A_E985A96A8907__INCLUDED_)
#define AFX_EX23A_H__591DC947_C89D_11D1_B30A_E985A96A8907__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx23aApp:
// See ex23a.cpp for the implementation of this class
//

class CEx23aApp : public CWinApp
{
public:
	CEx23aApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx23aApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx23aApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX23A_H__591DC947_C89D_11D1_B30A_E985A96A8907__INCLUDED_)
