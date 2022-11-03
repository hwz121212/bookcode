// DrawBottun.h : main header file for the DRAWBOTTUN application
//

#if !defined(AFX_DRAWBOTTUN_H__4AF533E5_C125_11D2_A71D_A0815CB6AA6A__INCLUDED_)
#define AFX_DRAWBOTTUN_H__4AF533E5_C125_11D2_A71D_A0815CB6AA6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDrawBottunApp:
// See DrawBottun.cpp for the implementation of this class
//

class CDrawBottunApp : public CWinApp
{
public:
	CDrawBottunApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawBottunApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDrawBottunApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWBOTTUN_H__4AF533E5_C125_11D2_A71D_A0815CB6AA6A__INCLUDED_)
