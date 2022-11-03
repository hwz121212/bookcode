//********************************************************************************
//* A Cartoon Timer
//*
//* (C) 2002 by ÍõÅô
//*
//* Write to me:	mailwp@21cn.com
//********************************************************************************


#if !defined(AFX_WISER_H)
#define AFX_WISER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWiserApp:
// See Wiser.cpp for the implementation of this class
//

class CWiserApp : public CWinApp
{
public:
	CWiserApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWiserApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWiserApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WISER_H__98909AF7_6175_48D8_9274_710E3789AC65__INCLUDED_)

