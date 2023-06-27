#if !defined(AFX_SPACESHIP1_H__9D4F0919_EA79_11D1_B30A_0080C7360DC1__INCLUDED_)
#define AFX_SPACESHIP1_H__9D4F0919_EA79_11D1_B30A_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Spaceship1.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CSpaceship command target

class CSpaceship : public CCmdTarget
{
	DECLARE_DYNCREATE(CSpaceship)

	CSpaceship();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpaceship)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSpaceship();

	// Generated message map functions
	//{{AFX_MSG(CSpaceship)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CSpaceship)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CSpaceship)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPACESHIP1_H__9D4F0919_EA79_11D1_B30A_0080C7360DC1__INCLUDED_)
