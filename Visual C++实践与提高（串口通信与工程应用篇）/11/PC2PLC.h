// PC2PLC.h : main header file for the PC2PLC application
//

#if !defined(AFX_PC2PLC_H__20638DFD_9868_4B9D_ACB8_8CF693493943__INCLUDED_)
#define AFX_PC2PLC_H__20638DFD_9868_4B9D_ACB8_8CF693493943__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPC2PLCApp:
// See PC2PLC.cpp for the implementation of this class
//

class CPC2PLCApp : public CWinApp
{
public:
	CPC2PLCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPC2PLCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPC2PLCApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PC2PLC_H__20638DFD_9868_4B9D_ACB8_8CF693493943__INCLUDED_)
