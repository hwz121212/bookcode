#if !defined(AFX_RECETEXTVIEW_H__E20EB6A2_3D99_45B2_ABF4_5D3E34C2E253__INCLUDED_)
#define AFX_RECETEXTVIEW_H__E20EB6A2_3D99_45B2_ABF4_5D3E34C2E253__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewLog.h : header file
//

#include "ViewBase.h"
/////////////////////////////////////////////////////////////////////////////
// CViewLog view

class CViewLog : public CViewBase
{
protected:
	CViewLog();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewLog)

// Attributes
public:

// Operations
public:
	void InitColumns();
	void InsertLog(CString level, CString log);	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewLog)
	public:	
	protected:	
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CViewLog();
#ifdef _DEBUG	
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CViewLog)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECETEXTVIEW_H__E20EB6A2_3D99_45B2_ABF4_5D3E34C2E253__INCLUDED_)
