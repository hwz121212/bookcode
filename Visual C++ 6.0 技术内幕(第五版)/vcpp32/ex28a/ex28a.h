// ex28a.h : main header file for the EX28A application
//

#if !defined(AFX_EX28A_H__D4B8ACC6_FA2D_11D1_B30A_0080C7360DC1__INCLUDED_)
#define AFX_EX28A_H__D4B8ACC6_FA2D_11D1_B30A_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx28aApp:
// See ex28a.cpp for the implementation of this class
//

class CEx28aApp : public CWinApp
{
public:
	CEx28aApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx28aApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(CEx28aApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX28A_H__D4B8ACC6_FA2D_11D1_B30A_0080C7360DC1__INCLUDED_)
