// SaveRead.h : main header file for the SAVEREAD application
//

#if !defined(AFX_SAVEREAD_H__70B4B526_1DEE_11D4_B0E6_00001A012804__INCLUDED_)
#define AFX_SAVEREAD_H__70B4B526_1DEE_11D4_B0E6_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSaveReadApp:
// See SaveRead.cpp for the implementation of this class
//

class CSaveReadApp : public CWinApp
{
public:
	CSaveReadApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveReadApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSaveReadApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVEREAD_H__70B4B526_1DEE_11D4_B0E6_00001A012804__INCLUDED_)
