// TestLead.h : main header file for the TESTLEAD application
//

#if !defined(AFX_TESTLEAD_H__BA0EE526_E514_11D1_A2B6_0000B4810C13__INCLUDED_)
#define AFX_TESTLEAD_H__BA0EE526_E514_11D1_A2B6_0000B4810C13__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestLeadApp:
// See TestLead.cpp for the implementation of this class
//

class CTestLeadApp : public CWinApp
{
public:
	CTestLeadApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestLeadApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestLeadApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTLEAD_H__BA0EE526_E514_11D1_A2B6_0000B4810C13__INCLUDED_)
