// ex12c.h : main header file for the EX12C application
//

#if !defined(AFX_EX12C_H__7D12C151_6C0B_12D0_8FD6_00C04FC2A0C2__INCLUDED_)
#define AFX_EX12C_H__7D12C151_6C0B_12D0_8FD6_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx12cApp:
// See ex12c.cpp for the implementation of this class
//

class CEx12cApp : public CWinApp
{
public:
	CEx12cApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx12cApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx12cApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX12C_H__7D12C151_6C0B_12D0_8FD6_00C04FC2A0C2__INCLUDED_)
