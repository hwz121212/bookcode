#if !defined(AFX_STEP3_H__E07A234A_3998_11D4_9E64_00001A012804__INCLUDED_)
#define AFX_STEP3_H__E07A234A_3998_11D4_9E64_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Step3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStep3 dialog

class CStep3 : public CPropertyPage
{
	DECLARE_DYNCREATE(CStep3)

// Construction
public:
	CStep3();
	~CStep3();


// Dialog Data
	//{{AFX_DATA(CStep3)
	enum { IDD = IDD_STEP3 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CStep3)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CStep3)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STEP3_H__E07A234A_3998_11D4_9E64_00001A012804__INCLUDED_)
