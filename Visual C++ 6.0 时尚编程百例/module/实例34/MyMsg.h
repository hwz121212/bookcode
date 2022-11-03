// MyMsg.h : main header file for the MYMSG application
//

#if !defined(AFX_MYMSG_H__0E3CAD25_C3FF_11D2_A71D_F9BCAFDAF169__INCLUDED_)
#define AFX_MYMSG_H__0E3CAD25_C3FF_11D2_A71D_F9BCAFDAF169__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyMsgApp:
// See MyMsg.cpp for the implementation of this class
//

class CMyMsgApp : public CWinApp
{
public:
	CMyMsgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyMsgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMyMsgApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYMSG_H__0E3CAD25_C3FF_11D2_A71D_F9BCAFDAF169__INCLUDED_)
