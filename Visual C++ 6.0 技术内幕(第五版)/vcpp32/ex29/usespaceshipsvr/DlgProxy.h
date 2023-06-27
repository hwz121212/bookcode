// DlgProxy.h : header file
//

#if !defined(AFX_DLGPROXY_H__FACE8900_06C8_11D2_B77D_0060081EE21C__INCLUDED_)
#define AFX_DLGPROXY_H__FACE8900_06C8_11D2_B77D_0060081EE21C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUsespaceshipsvrDlg;

/////////////////////////////////////////////////////////////////////////////
// CUsespaceshipsvrDlgAutoProxy command target

class CUsespaceshipsvrDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CUsespaceshipsvrDlgAutoProxy)

	CUsespaceshipsvrDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CUsespaceshipsvrDlg* m_pDialog;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUsespaceshipsvrDlgAutoProxy)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CUsespaceshipsvrDlgAutoProxy();

	// Generated message map functions
	//{{AFX_MSG(CUsespaceshipsvrDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CUsespaceshipsvrDlgAutoProxy)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CUsespaceshipsvrDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROXY_H__FACE8900_06C8_11D2_B77D_0060081EE21C__INCLUDED_)
