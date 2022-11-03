#if !defined(AFX_WIZARDSHEET_H__E07A234B_3998_11D4_9E64_00001A012804__INCLUDED_)
#define AFX_WIZARDSHEET_H__E07A234B_3998_11D4_9E64_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WizardSheet.h : header file
//
#include "step1.h"
#include "step2.h"
#include "step3.h"
/////////////////////////////////////////////////////////////////////////////
// CWizardSheet

class CWizardSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CWizardSheet)

// Construction
public:
	CWizardSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CWizardSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
public:
        CStep1 m_step1;
		CStep2 m_step2;
		CStep3 m_step3;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizardSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWizardSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWizardSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZARDSHEET_H__E07A234B_3998_11D4_9E64_00001A012804__INCLUDED_)
