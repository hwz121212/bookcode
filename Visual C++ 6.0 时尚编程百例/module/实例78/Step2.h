#if !defined(AFX_STEP2_H__E07A2349_3998_11D4_9E64_00001A012804__INCLUDED_)
#define AFX_STEP2_H__E07A2349_3998_11D4_9E64_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Step2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStep2 dialog

class CStep2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CStep2)

// Construction
public:
	CStep2();
	~CStep2();

// Dialog Data
	//{{AFX_DATA(CStep2)
	enum { IDD = IDD_STEP2 };
	BOOL	m_check;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CStep2)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CStep2)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STEP2_H__E07A2349_3998_11D4_9E64_00001A012804__INCLUDED_)
