// PC2MCU.h : main header file for the PC2MCU application
//

#if !defined(AFX_PC2MCU_H__2C42A11A_5A8B_4DEE_9DC4_F6247D8DB992__INCLUDED_)
#define AFX_PC2MCU_H__2C42A11A_5A8B_4DEE_9DC4_F6247D8DB992__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPC2MCUApp:
// See PC2MCU.cpp for the implementation of this class
//

class CPC2MCUApp : public CWinApp
{
public:
	CPC2MCUApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPC2MCUApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPC2MCUApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PC2MCU_H__2C42A11A_5A8B_4DEE_9DC4_F6247D8DB992__INCLUDED_)
