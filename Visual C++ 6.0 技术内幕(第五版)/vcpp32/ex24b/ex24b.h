// ex24b.h : main header file for the EX24B DLL
//

#if !defined(AFX_EX24B_H__E16369D3_EA5A_11D1_B30A_0080C7360DC1__INCLUDED_)
#define AFX_EX24B_H__E16369D3_EA5A_11D1_B30A_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx24bApp
// See ex24b.cpp for the implementation of this class
//

class CEx24bApp : public CWinApp
{
public:
	CEx24bApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx24bApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CEx24bApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX24B_H__E16369D3_EA5A_11D1_B30A_0080C7360DC1__INCLUDED_)
