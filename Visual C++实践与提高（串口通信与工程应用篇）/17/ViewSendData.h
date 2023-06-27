#if !defined(AFX_VIEWSENDDATA_H__E79F56CC_797D_48E0_B190_B71E1993AAF5__INCLUDED_)
#define AFX_VIEWSENDDATA_H__E79F56CC_797D_48E0_B190_B71E1993AAF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewSendData.h : header file
//

#include "ViewBase.h"

/////////////////////////////////////////////////////////////////////////////
// CViewSendData view

class CViewSendData : public CViewBase
{
protected:
	CViewSendData();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewSendData)

// Attributes
public:

// Operations
public:
	void InitColumns();
    void InsertSendLog(CString source, CString content);	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewSendData)
	public:
	
	protected:
	
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CViewSendData();
#ifdef _DEBUG
	
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CViewSendData)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWSENDDATA_H__E79F56CC_797D_48E0_B190_B71E1993AAF5__INCLUDED_)
