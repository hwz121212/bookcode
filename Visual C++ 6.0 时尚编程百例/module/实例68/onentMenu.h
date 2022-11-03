#if !defined(AFX_ONENTMENU_H__5DE021A1_D970_11D2_A71D_FE8D80131C58__INCLUDED_)
#define AFX_ONENTMENU_H__5DE021A1_D970_11D2_A71D_FE8D80131C58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// onentMenu.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ConentMenu window

class ConentMenu : public CListBox
{
// Construction
public:
	ConentMenu();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ConentMenu)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ConentMenu();

	// Generated message map functions
protected:
	//{{AFX_MSG(ConentMenu)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONENTMENU_H__5DE021A1_D970_11D2_A71D_FE8D80131C58__INCLUDED_)
