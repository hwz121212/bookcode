// FaxMachine.h : main header file for the FAXMACHINE application
//

#if !defined(AFX_FAXMACHINE_H__56DB66C8_D624_475E_90FE_154B9C7C7249__INCLUDED_)
#define AFX_FAXMACHINE_H__56DB66C8_D624_475E_90FE_154B9C7C7249__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFaxMachineApp:
// See FaxMachine.cpp for the implementation of this class
//

class CFaxMachineApp : public CWinApp
{
public:
	CFaxMachineApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFaxMachineApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFaxMachineApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FAXMACHINE_H__56DB66C8_D624_475E_90FE_154B9C7C7249__INCLUDED_)
