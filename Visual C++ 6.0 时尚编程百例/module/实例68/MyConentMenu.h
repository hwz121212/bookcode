#if !defined(AFX_MYCONENTMENU_H__5DE021A2_D970_11D2_A71D_FE8D80131C58__INCLUDED_)
#define AFX_MYCONENTMENU_H__5DE021A2_D970_11D2_A71D_FE8D80131C58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyConentMenu.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MyConentMenu window
typedef struct{
	UINT nID;
}*pICON_ID,ICON_ID;
class MyConentMenu : public CListBox
{
// Construction
public:
	MyConentMenu();
    int State;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MyConentMenu)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~MyConentMenu();

	// Generated message map functions
protected:
	//{{AFX_MSG(MyConentMenu)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCONENTMENU_H__5DE021A2_D970_11D2_A71D_FE8D80131C58__INCLUDED_)
