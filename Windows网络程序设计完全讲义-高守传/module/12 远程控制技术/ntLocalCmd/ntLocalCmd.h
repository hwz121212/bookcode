/*
  This project was created and edited using the MFC SelfBanner AppWizard.

  Comment: 管道编程－本地CMD.

  Project: ntLocalCmd.
  Author : dhyao
  Date   : 星期一, 二月 02, 2009
*/
/////////////////////////////////////////////////////////////////////

// ntLocalCmd.h : main header file for the NTLOCALCMD application
//

#if !defined(AFX_NTLOCALCMD_H__E5D874CA_6FC8_4B0C_8760_01BA33BB1B0C__INCLUDED_)
#define AFX_NTLOCALCMD_H__E5D874CA_6FC8_4B0C_8760_01BA33BB1B0C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CNtLocalCmdApp:
// See ntLocalCmd.cpp for the implementation of this class
//

class CNtLocalCmdApp : public CWinApp
{
public:
	CNtLocalCmdApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNtLocalCmdApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNtLocalCmdApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NTLOCALCMD_H__E5D874CA_6FC8_4B0C_8760_01BA33BB1B0C__INCLUDED_)
