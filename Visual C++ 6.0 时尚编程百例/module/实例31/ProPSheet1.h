#if !defined(AFX_PROPSHEET1_H__682A1ED6_1396_11D4_A927_00001A012804__INCLUDED_)
#define AFX_PROPSHEET1_H__682A1ED6_1396_11D4_A927_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Page1.h"
#include "Page2.h"

// ProPSheet1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProPSheet

class CProPSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CProPSheet)

// Construction
public:
	CProPSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CProPSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProPSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	CPage2 m_page2;
	CPage1 m_page1;
	virtual ~CProPSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CProPSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPSHEET1_H__682A1ED6_1396_11D4_A927_00001A012804__INCLUDED_)
