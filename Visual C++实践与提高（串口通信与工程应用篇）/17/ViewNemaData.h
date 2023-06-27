#if !defined(AFX_VIEWNEMADATA_H__E79F56CC_797D_48E0_B190_B71E1993AAF5__INCLUDED_)
#define AFX_VIEWNEMADATA_H__E79F56CC_797D_48E0_B190_B71E1993AAF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CViewNemaData.h : header file
//

#include "ViewBase.h"

/////////////////////////////////////////////////////////////////////////////
// CViewNemaData view


class CViewNemaData : public CViewBase
{
protected:
	CViewNemaData();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewNemaData)

// Attributes
public:

// Operations
public:
	void InitColumns();
    void InsertNema(CString source, GPSPack* pack);
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewNemaData)
	public:	
	protected:	
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CViewNemaData();
#ifdef _DEBUG	
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CViewNemaData)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWNEMADATA_H__E79F56CC_797D_48E0_B190_B71E1993AAF5__INCLUDED_)
