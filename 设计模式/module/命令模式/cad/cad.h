// cad.h : main header file for the CAD application
//

#if !defined(AFX_CAD_H__528BD64F_9567_4BEE_8090_677549CC76DC__INCLUDED_)
#define AFX_CAD_H__528BD64F_9567_4BEE_8090_677549CC76DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCadApp:
// See cad.cpp for the implementation of this class
//

class CCadApp : public CWinApp
{
public:
	ULONG_PTR m_gdiplusToken;
	CCadApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCadApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCadApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAD_H__528BD64F_9567_4BEE_8090_677549CC76DC__INCLUDED_)
