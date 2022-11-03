// DlgBar.h : main header file for the DLGBAR application
//

#if !defined(AFX_DLGBAR_H__958A2893_DB28_11D2_A71D_D12047679B5A__INCLUDED_)
#define AFX_DLGBAR_H__958A2893_DB28_11D2_A71D_D12047679B5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDlgBarApp:
// See DlgBar.cpp for the implementation of this class
//

class CDlgBarApp : public CWinApp
{
public:
	CDlgBarApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBarApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDlgBarApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBAR_H__958A2893_DB28_11D2_A71D_D12047679B5A__INCLUDED_)
