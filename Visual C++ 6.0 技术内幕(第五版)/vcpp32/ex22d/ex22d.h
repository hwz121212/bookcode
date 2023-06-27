// ex22d.h : main header file for the EX22D DLL
//

#if !defined(AFX_EX22D_H__B030BA55_C874_11D1_B30A_E985A96A8907__INCLUDED_)
#define AFX_EX22D_H__B030BA55_C874_11D1_B30A_E985A96A8907__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx22dApp
// See ex22d.cpp for the implementation of this class
//

class CEx22dApp : public CWinApp
{
public:
	CEx22dApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx22dApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CEx22dApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX22D_H__B030BA55_C874_11D1_B30A_E985A96A8907__INCLUDED_)
