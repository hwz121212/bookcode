// MidPlayer.h : main header file for the MIDPLAYER application
//

#if !defined(AFX_MIDPLAYER_H__68591833_CB2A_11D2_A71D_EC34D8292E66__INCLUDED_)
#define AFX_MIDPLAYER_H__68591833_CB2A_11D2_A71D_EC34D8292E66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMidPlayerApp:
// See MidPlayer.cpp for the implementation of this class
//

class CMidPlayerApp : public CWinApp
{
public:
	CMidPlayerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMidPlayerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMidPlayerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIDPLAYER_H__68591833_CB2A_11D2_A71D_EC34D8292E66__INCLUDED_)
