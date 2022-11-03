// FormColor.h : main header file for the FORMCOLOR application
//

#if !defined(AFX_FORMCOLOR_H__B7C92250_E459_11D2_A71D_A44E1A83F14B__INCLUDED_)
#define AFX_FORMCOLOR_H__B7C92250_E459_11D2_A71D_A44E1A83F14B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFormColorApp:
// See FormColor.cpp for the implementation of this class
//

class CFormColorApp : public CWinApp
{
public:
	CFormColorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormColorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFormColorApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMCOLOR_H__B7C92250_E459_11D2_A71D_A44E1A83F14B__INCLUDED_)
