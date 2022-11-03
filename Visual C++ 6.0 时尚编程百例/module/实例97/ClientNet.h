// ClientNet.h : main header file for the CLIENTNET application
//

#if !defined(AFX_CLIENTNET_H__55800FA4_28B3_11D4_9E64_00001A012804__INCLUDED_)
#define AFX_CLIENTNET_H__55800FA4_28B3_11D4_9E64_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CClientNetApp:
// See ClientNet.cpp for the implementation of this class
//

class CClientNetApp : public CWinApp
{
public:
	CClientNetApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientNetApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CClientNetApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTNET_H__55800FA4_28B3_11D4_9E64_00001A012804__INCLUDED_)
