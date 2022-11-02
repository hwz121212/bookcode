// ntChatRoomServer.h : main header file for the ntChatRoomServer application
//

#if !defined(AFX_ntChatRoomServer_H__680EC642_E19B_4D55_88DF_2C9E9B1B30FD__INCLUDED_)
#define AFX_ntChatRoomServer_H__680EC642_E19B_4D55_88DF_2C9E9B1B30FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CntChatRoomServerApp:
// See ntChatRoomServer.cpp for the implementation of this class
//

class CntChatRoomServerApp : public CWinApp
{
public:
	CntChatRoomServerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CntChatRoomServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CntChatRoomServerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ntChatRoomServer_H__680EC642_E19B_4D55_88DF_2C9E9B1B30FD__INCLUDED_)
