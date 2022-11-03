// switch.h : main header file for the SWITCH application
//

#if !defined(AFX_SWITCH_H__B21A70F4_7F31_11D2_BE4E_0000216A06C9__INCLUDED_)
#define AFX_SWITCH_H__B21A70F4_7F31_11D2_BE4E_0000216A06C9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#include "SwitchDoc.h"
/////////////////////////////////////////////////////////////////////////////
// CSwitchApp:
// See switch.cpp for the implementation of this class
//

class CSwitchApp : public CWinApp
{
public:
	CSwitchApp();

   CSwitchDoc* m_pDoc;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSwitchApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSwitchApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SWITCH_H__B21A70F4_7F31_11D2_BE4E_0000216A06C9__INCLUDED_)
