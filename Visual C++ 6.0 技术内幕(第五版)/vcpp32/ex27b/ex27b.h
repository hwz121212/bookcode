// ex27b.h : main header file for the EX27B DLL
//

#if !defined(AFX_EX27B_H__62451995_F64F_11D1_B30A_D09549C10710__INCLUDED_)
#define AFX_EX27B_H__62451995_F64F_11D1_B30A_D09549C10710__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx27bApp
// See ex27b.cpp for the implementation of this class
//

class CEx27bApp : public CWinApp
{
public:
	CEx27bApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx27bApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CEx27bApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX27B_H__62451995_F64F_11D1_B30A_D09549C10710__INCLUDED_)
