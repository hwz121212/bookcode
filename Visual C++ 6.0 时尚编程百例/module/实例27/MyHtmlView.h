// MyHtmlView.h : main header file for the MYHTMLVIEW application
//

#if !defined(AFX_MYHTMLVIEW_H__38E95ED4_CCB9_11D2_A71D_D9D3A9F7FE66__INCLUDED_)
#define AFX_MYHTMLVIEW_H__38E95ED4_CCB9_11D2_A71D_D9D3A9F7FE66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyHtmlViewApp:
// See MyHtmlView.cpp for the implementation of this class
//

class CMyHtmlViewApp : public CWinApp
{
public:
	CMyHtmlViewApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyHtmlViewApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMyHtmlViewApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYHTMLVIEW_H__38E95ED4_CCB9_11D2_A71D_D9D3A9F7FE66__INCLUDED_)
