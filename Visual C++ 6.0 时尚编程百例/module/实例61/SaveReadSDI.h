// SaveReadSDI.h : main header file for the SAVEREADSDI application
//

#if !defined(AFX_SAVEREADSDI_H__51C3F704_1EB8_11D4_B0E6_00001A012804__INCLUDED_)
#define AFX_SAVEREADSDI_H__51C3F704_1EB8_11D4_B0E6_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSaveReadSDIApp:
// See SaveReadSDI.cpp for the implementation of this class
//

class CSaveReadSDIApp : public CWinApp
{
public:
	CSaveReadSDIApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveReadSDIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSaveReadSDIApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVEREADSDI_H__51C3F704_1EB8_11D4_B0E6_00001A012804__INCLUDED_)
