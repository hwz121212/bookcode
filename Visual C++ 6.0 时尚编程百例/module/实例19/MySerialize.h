// MySerialize.h : main header file for the MYSERIALIZE application
//

#if !defined(AFX_MYSERIALIZE_H__DFC8F825_10B2_11D4_876D_00001CD613F0__INCLUDED_)
#define AFX_MYSERIALIZE_H__DFC8F825_10B2_11D4_876D_00001CD613F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMySerializeApp:
// See MySerialize.cpp for the implementation of this class
//

class CMySerializeApp : public CWinApp
{
public:
	CMySerializeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySerializeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMySerializeApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSERIALIZE_H__DFC8F825_10B2_11D4_876D_00001CD613F0__INCLUDED_)
