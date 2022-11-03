// RoundRect.h : main header file for the ROUNDRECT application
//

#if !defined(AFX_ROUNDRECT_H__5824351E_B188_443D_9DC5_B84F4D80048D__INCLUDED_)
#define AFX_ROUNDRECT_H__5824351E_B188_443D_9DC5_B84F4D80048D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRoundRectApp:
// See RoundRect.cpp for the implementation of this class
//

class CRoundRectApp : public CWinApp
{
public:
	CRoundRectApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoundRectApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRoundRectApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROUNDRECT_H__5824351E_B188_443D_9DC5_B84F4D80048D__INCLUDED_)
