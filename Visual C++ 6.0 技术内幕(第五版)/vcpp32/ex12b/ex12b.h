// ex12b.h : main header file for the EX12B application
//

#if !defined(AFX_EX12B_H__7D12C13C_6C0B_12D0_8FD6_00C04FC2A0C2__INCLUDED_)
#define AFX_EX12B_H__7D12C13C_6C0B_12D0_8FD6_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx12bApp:
// See ex12b.cpp for the implementation of this class
//

class CEx12bApp : public CWinApp
{
public:
	CEx12bApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx12bApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx12bApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX12B_H__7D12C13C_6C0B_12D0_8FD6_00C04FC2A0C2__INCLUDED_)
