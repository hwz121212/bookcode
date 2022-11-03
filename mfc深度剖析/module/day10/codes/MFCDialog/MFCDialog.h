// MFCDialog.h : main header file for the MFCDIALOG application
//

#if !defined(AFX_MFCDIALOG_H__DE4C309D_B3E7_48DE_B270_2C141CF13BEF__INCLUDED_)
#define AFX_MFCDIALOG_H__DE4C309D_B3E7_48DE_B270_2C141CF13BEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMFCDialogApp:
// See MFCDialog.cpp for the implementation of this class
//

class CMFCDialogApp : public CWinApp
{
public:
	CMFCDialogApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCDialogApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMFCDialogApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCDIALOG_H__DE4C309D_B3E7_48DE_B270_2C141CF13BEF__INCLUDED_)
