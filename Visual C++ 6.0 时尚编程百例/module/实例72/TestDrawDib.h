// TestDrawDib.h : main header file for the TESTDRAWDIB application
//

#if !defined(AFX_TESTDRAWDIB_H__C37FFDE4_726A_11D1_9606_444553540000__INCLUDED_)
#define AFX_TESTDRAWDIB_H__C37FFDE4_726A_11D1_9606_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestDrawDibApp:
// See TestDrawDib.cpp for the implementation of this class
//

class CTestDrawDibApp : public CWinApp
{
public:
	CTestDrawDibApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDrawDibApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestDrawDibApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDRAWDIB_H__C37FFDE4_726A_11D1_9606_444553540000__INCLUDED_)
