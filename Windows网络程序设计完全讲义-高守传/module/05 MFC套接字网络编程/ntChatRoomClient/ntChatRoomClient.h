// ntChatRoomClient.h : main header file for the ntChatRoomClient application
//

#if !defined(AFX_ntChatRoomClient_H__4503F0DD_CA95_4F24_B6EE_3183B64B095B__INCLUDED_)
#define AFX_ntChatRoomClient_H__4503F0DD_CA95_4F24_B6EE_3183B64B095B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CntChatRoomClientApp:
// See ntChatRoomClient.cpp for the implementation of this class
//

class CntChatRoomClientApp : public CWinApp
{
public:
	CntChatRoomClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CntChatRoomClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CntChatRoomClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ntChatRoomClient_H__4503F0DD_CA95_4F24_B6EE_3183B64B095B__INCLUDED_)
