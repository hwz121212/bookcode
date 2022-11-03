// MyDlgBar.h : main header file for the MYDLGBAR application
//

#if !defined(AFX_MYDLGBAR_H__3F1C89E5_C384_11D2_A71D_D06875665969__INCLUDED_)
#define AFX_MYDLGBAR_H__3F1C89E5_C384_11D2_A71D_D06875665969__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyDlgBarApp:
// See MyDlgBar.cpp for the implementation of this class
//

class CMyDlgBarApp : public CWinApp
{
public:
	CMyDlgBarApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlgBarApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMyDlgBarApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDLGBAR_H__3F1C89E5_C384_11D2_A71D_D06875665969__INCLUDED_)
