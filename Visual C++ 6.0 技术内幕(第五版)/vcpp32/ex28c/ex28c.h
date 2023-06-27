// ex28c.h : main header file for the EX28C application
//

#if !defined(AFX_EX28C_H__1EAAB6EE_6011_11D0_848F_00400526305B__INCLUDED_)
#define AFX_EX28C_H__1EAAB6EE_6011_11D0_848F_00400526305B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx28cApp:
// See ex28c.cpp for the implementation of this class
//

class CEx28cApp : public CWinApp
{
	friend class CEx28cDoc;
public:
	CEx28cApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx28cApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation

	//{{AFX_MSG(CEx28cApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX28C_H__1EAAB6EE_6011_11D0_848F_00400526305B__INCLUDED_)
