// AviPlay.h : main header file for the AVIPLAY application
//

#if !defined(AFX_AVIPLAY_H__BA12C5A5_CD17_11D2_A71D_94D5089BEA62__INCLUDED_)
#define AFX_AVIPLAY_H__BA12C5A5_CD17_11D2_A71D_94D5089BEA62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAviPlayApp:
// See AviPlay.cpp for the implementation of this class
//

class CAviPlayApp : public CWinApp
{
public:
	CAviPlayApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAviPlayApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAviPlayApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AVIPLAY_H__BA12C5A5_CD17_11D2_A71D_94D5089BEA62__INCLUDED_)
