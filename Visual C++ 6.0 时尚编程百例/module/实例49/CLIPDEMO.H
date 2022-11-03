// ClipDemo.h : main header file for the CLIPDEMO application
//

#if !defined(AFX_CLIPDEMO_H__63253C04_3758_11D2_BB89_000629EE2C0F__INCLUDED_)
#define AFX_CLIPDEMO_H__63253C04_3758_11D2_BB89_000629EE2C0F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CClipDemoApp:
// See ClipDemo.cpp for the implementation of this class
//

class CClipDemoApp : public CWinApp
{
public:
	CClipDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClipDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CClipDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIPDEMO_H__63253C04_3758_11D2_BB89_000629EE2C0F__INCLUDED_)
