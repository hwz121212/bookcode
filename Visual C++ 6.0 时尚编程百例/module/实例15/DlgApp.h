// DlgApp.h : main header file for the DLGAPP application
//

#if !defined(AFX_DLGAPP_H__2D2A2C6A_E2F1_11D2_A71D_F998D259734B__INCLUDED_)
#define AFX_DLGAPP_H__2D2A2C6A_E2F1_11D2_A71D_F998D259734B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDlgAppApp:
// See DlgApp.cpp for the implementation of this class
//

class CDlgAppApp : public CWinApp
{
public:
	CDlgAppApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAppApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDlgAppApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAPP_H__2D2A2C6A_E2F1_11D2_A71D_F998D259734B__INCLUDED_)
