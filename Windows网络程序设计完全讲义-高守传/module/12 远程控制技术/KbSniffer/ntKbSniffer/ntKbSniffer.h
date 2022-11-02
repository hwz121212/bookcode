/*
  This project was created and edited using the MFC SelfBanner AppWizard.

  Comment: 键盘记录工具－系统钩子.

  Project: ntKbSniffer.
  Author : dhyao
  Date   : 星期三, 二月 04, 2009
*/
/////////////////////////////////////////////////////////////////////

// ntKbSniffer.h : main header file for the NTKBSNIFFER application
//

#if !defined(AFX_NTKBSNIFFER_H__6A6FA67A_C0F7_4C93_A724_85DEE47B92E0__INCLUDED_)
#define AFX_NTKBSNIFFER_H__6A6FA67A_C0F7_4C93_A724_85DEE47B92E0__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNtKbSnifferApp:
// See ntKbSniffer.cpp for the implementation of this class
//

class CNtKbSnifferApp : public CWinApp
{
public:
	CNtKbSnifferApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNtKbSnifferApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNtKbSnifferApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NTKBSNIFFER_H__6A6FA67A_C0F7_4C93_A724_85DEE47B92E0__INCLUDED_)
