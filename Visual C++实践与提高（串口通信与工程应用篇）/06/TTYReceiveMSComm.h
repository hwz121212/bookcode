// TTYReceiveMSComm.h : main header file for the TTYRECEIVEMSCOMM application
//

#if !defined(AFX_TTYRECEIVEMSCOMM_H__BBE9C711_AB29_42ED_B99C_A54C0BDB9592__INCLUDED_)
#define AFX_TTYRECEIVEMSCOMM_H__BBE9C711_AB29_42ED_B99C_A54C0BDB9592__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTTYReceiveMSCommApp:
// See TTYReceiveMSComm.cpp for the implementation of this class
//

class CTTYReceiveMSCommApp : public CWinApp
{
public:
	CTTYReceiveMSCommApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTTYReceiveMSCommApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTTYReceiveMSCommApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TTYRECEIVEMSCOMM_H__BBE9C711_AB29_42ED_B99C_A54C0BDB9592__INCLUDED_)
