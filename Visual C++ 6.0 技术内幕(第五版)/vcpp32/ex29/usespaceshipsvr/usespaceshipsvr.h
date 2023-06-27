// usespaceshipsvr.h : main header file for the USESPACESHIPSVR application
//

#if !defined(AFX_USESPACESHIPSVR_H__FACE88FC_06C8_11D2_B77D_0060081EE21C__INCLUDED_)
#define AFX_USESPACESHIPSVR_H__FACE88FC_06C8_11D2_B77D_0060081EE21C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUsespaceshipsvrApp:
// See usespaceshipsvr.cpp for the implementation of this class
//

class CUsespaceshipsvrApp : public CWinApp
{
public:
	CUsespaceshipsvrApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUsespaceshipsvrApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUsespaceshipsvrApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USESPACESHIPSVR_H__FACE88FC_06C8_11D2_B77D_0060081EE21C__INCLUDED_)
