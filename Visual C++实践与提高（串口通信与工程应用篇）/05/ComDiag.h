// ComDiag.h : main header file for the COMDIAG application
//

#if !defined(AFX_COMDIAG_H__424DF0EF_F092_42C1_9F4E_68BE29D16397__INCLUDED_)
#define AFX_COMDIAG_H__424DF0EF_F092_42C1_9F4E_68BE29D16397__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CComDiagApp:
// See ComDiag.cpp for the implementation of this class
//

class CComDiagApp : public CWinApp
{
public:
	CComDiagApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComDiagApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CComDiagApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMDIAG_H__424DF0EF_F092_42C1_9F4E_68BE29D16397__INCLUDED_)
