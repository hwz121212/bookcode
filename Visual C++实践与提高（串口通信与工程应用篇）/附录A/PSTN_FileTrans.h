// PSTN_FileTrans.h : main header file for the PSTN_FILETRANS application
//

#if !defined(AFX_PSTN_FILETRANS_H__56D6F1AA_41CD_4023_B3BB_6C673DCD90D2__INCLUDED_)
#define AFX_PSTN_FILETRANS_H__56D6F1AA_41CD_4023_B3BB_6C673DCD90D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPSTN_FileTransApp:
// See PSTN_FileTrans.cpp for the implementation of this class
//

class CPSTN_FileTransApp : public CWinApp
{
public:
	CPSTN_FileTransApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSTN_FileTransApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPSTN_FileTransApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSTN_FILETRANS_H__56D6F1AA_41CD_4023_B3BB_6C673DCD90D2__INCLUDED_)
