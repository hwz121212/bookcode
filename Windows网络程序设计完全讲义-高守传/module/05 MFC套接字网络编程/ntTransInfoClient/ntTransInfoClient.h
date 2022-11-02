// ntTransInfoClient.h : main header file for the ntTransInfoClient application
//

#if !defined(AFX_ntTransInfoClient_H__DA38275E_81E9_458E_B28B_80E9B5CF1173__INCLUDED_)
#define AFX_ntTransInfoClient_H__DA38275E_81E9_458E_B28B_80E9B5CF1173__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CntTransInfoClientApp:
// See ntTransInfoClient.cpp for the implementation of this class
//

class CntTransInfoClientApp : public CWinApp
{
public:
	CntTransInfoClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CntTransInfoClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CntTransInfoClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ntTransInfoClient_H__DA38275E_81E9_458E_B28B_80E9B5CF1173__INCLUDED_)
