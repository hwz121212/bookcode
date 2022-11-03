// novel.h : main header file for the NOVEL application
//

#if !defined(AFX_NOVEL_H__68D9F565_B317_11D2_8B4D_00A0C92E6E9E__INCLUDED_)
#define AFX_NOVEL_H__68D9F565_B317_11D2_8B4D_00A0C92E6E9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CNovelApp:
// See novel.cpp for the implementation of this class
//

class CNovelApp : public CWinApp
{
public:
	CNovelApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNovelApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CNovelApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOVEL_H__68D9F565_B317_11D2_8B4D_00A0C92E6E9E__INCLUDED_)
