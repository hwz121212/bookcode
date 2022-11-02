// ntCmdCliennt.h : main header file for the ntCmdCliennt application
//

#if !defined(AFX_ntCmdCliennt_H__D2A0DC44_712D_4A0C_AC98_BE538804E293__INCLUDED_)
#define AFX_ntCmdCliennt_H__D2A0DC44_712D_4A0C_AC98_BE538804E293__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*
  This project was created and edited using the MFC SelfBanner AppWizard.

  Comment: 远程控制－远程Cmd客户端.

  Project: ntCmdCliennt.
  Author : dhyao
  Date   : 星期一, 二月 02, 2009
*/
/////////////////////////////////////////////////////////////////////
#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CntCmdClienntApp:
// See ntCmdCliennt.cpp for the implementation of this class
//

class CntCmdClienntApp : public CWinApp
{
public:
	CntCmdClienntApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CntCmdClienntApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CntCmdClienntApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ntCmdCliennt_H__D2A0DC44_712D_4A0C_AC98_BE538804E293__INCLUDED_)
