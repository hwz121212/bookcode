// TTYSendApi.h : main header file for the TTYSENDAPI application
//

#if !defined(AFX_TTYSENDAPI_H__5F7928EE_3561_4A7C_945E_2CE0F75A0619__INCLUDED_)
#define AFX_TTYSENDAPI_H__5F7928EE_3561_4A7C_945E_2CE0F75A0619__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTTYSendApiApp:
// See TTYSendApi.cpp for the implementation of this class
//

class CTTYSendApiApp : public CWinApp
{
public:
	CTTYSendApiApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTTYSendApiApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTTYSendApiApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TTYSENDAPI_H__5F7928EE_3561_4A7C_945E_2CE0F75A0619__INCLUDED_)
