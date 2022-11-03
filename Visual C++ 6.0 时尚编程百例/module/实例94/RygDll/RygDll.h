// RygDll.h : main header file for the RYGDLL DLL
//

#if !defined(AFX_RYGDLL_H__04BA5A05_2CA3_11D4_9E64_00001A012804__INCLUDED_)
#define AFX_RYGDLL_H__04BA5A05_2CA3_11D4_9E64_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRygDllApp
// See RygDll.cpp for the implementation of this class
//

class CRygDllApp : public CWinApp
{
public:
	CRygDllApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRygDllApp)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CRygDllApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RYGDLL_H__04BA5A05_2CA3_11D4_9E64_00001A012804__INCLUDED_)
