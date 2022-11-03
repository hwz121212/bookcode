// MyModeless.h : main header file for the MYMODELESS application
//

#if !defined(AFX_MYMODELESS_H__33D4FC39_C0DC_11D2_A71D_9648DA4D456A__INCLUDED_)
#define AFX_MYMODELESS_H__33D4FC39_C0DC_11D2_A71D_9648DA4D456A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyModelessApp:
// See MyModeless.cpp for the implementation of this class
//

class CMyModelessApp : public CWinApp
{
public:
	CMyModelessApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyModelessApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMyModelessApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYMODELESS_H__33D4FC39_C0DC_11D2_A71D_9648DA4D456A__INCLUDED_)
