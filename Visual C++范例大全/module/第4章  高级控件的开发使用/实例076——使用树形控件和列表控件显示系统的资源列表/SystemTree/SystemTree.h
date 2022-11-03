// SystemTree.h : main header file for the SYSTEMTREE application
//

#if !defined(AFX_SYSTEMTREE_H__08DD9B15_B57A_4116_B799_CCCBE26C9D84__INCLUDED_)
#define AFX_SYSTEMTREE_H__08DD9B15_B57A_4116_B799_CCCBE26C9D84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSystemTreeApp:
// See SystemTree.cpp for the implementation of this class
//

class CSystemTreeApp : public CWinApp
{
public:
	CSystemTreeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSystemTreeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSystemTreeApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSTEMTREE_H__08DD9B15_B57A_4116_B799_CCCBE26C9D84__INCLUDED_)
