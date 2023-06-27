// PC2Client.h : main header file for the PC2CLIENT application
//

#if !defined(AFX_PC2CLIENT_H__C90385D5_B5C9_4FF8_8CB2_D2FA8C9CA6DE__INCLUDED_)
#define AFX_PC2CLIENT_H__C90385D5_B5C9_4FF8_8CB2_D2FA8C9CA6DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPC2ClientApp:
// See PC2Client.cpp for the implementation of this class
//

class CPC2ClientApp : public CWinApp
{
public:
	CPC2ClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPC2ClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPC2ClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PC2CLIENT_H__C90385D5_B5C9_4FF8_8CB2_D2FA8C9CA6DE__INCLUDED_)
