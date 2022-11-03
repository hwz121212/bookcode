#if !defined(AFX_SHEET_H__682A1ED7_1396_11D4_A927_00001A012804__INCLUDED_)
#define AFX_SHEET_H__682A1ED7_1396_11D4_A927_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "page1.h"
#include "page2.h"
// Sheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSheet

class CSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CSheet)

// Construction
public:
	CSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	CPage2 m_page2;
	CPage1 m_page1;
	virtual ~CSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHEET_H__682A1ED7_1396_11D4_A927_00001A012804__INCLUDED_)
