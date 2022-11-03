// MyPen.h : main header file for the MYPEN application
//

#if !defined(AFX_MYPEN_H__BD6FCC88_CD89_11D2_A71D_F9904D517C61__INCLUDED_)
#define AFX_MYPEN_H__BD6FCC88_CD89_11D2_A71D_F9904D517C61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyPenApp:
// See MyPen.cpp for the implementation of this class
//

class CMyPenApp : public CWinApp
{
public:
	CMyPenApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyPenApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMyPenApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPEN_H__BD6FCC88_CD89_11D2_A71D_F9904D517C61__INCLUDED_)
