// PC2PC.h : main header file for the PC2PC application
//

#if !defined(AFX_PC2PC_H__151F7E24_2EAB_429B_93B8_CC9A04ED35DE__INCLUDED_)
#define AFX_PC2PC_H__151F7E24_2EAB_429B_93B8_CC9A04ED35DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPC2PCApp:
// See PC2PC.cpp for the implementation of this class
//

class CPC2PCApp : public CWinApp
{
public:
	CPC2PCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPC2PCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPC2PCApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PC2PC_H__151F7E24_2EAB_429B_93B8_CC9A04ED35DE__INCLUDED_)
