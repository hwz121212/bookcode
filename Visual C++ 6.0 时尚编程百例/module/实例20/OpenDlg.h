// OpenDlg.h : main header file for the OPENDLG application
//

#if !defined(AFX_OPENDLG_H__D049029E_DB09_11D2_A71D_B295A824025F__INCLUDED_)
#define AFX_OPENDLG_H__D049029E_DB09_11D2_A71D_B295A824025F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// COpenDlgApp:
// See OpenDlg.cpp for the implementation of this class
//

class COpenDlgApp : public CWinApp
{
public:
	COpenDlgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenDlgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(COpenDlgApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENDLG_H__D049029E_DB09_11D2_A71D_B295A824025F__INCLUDED_)
