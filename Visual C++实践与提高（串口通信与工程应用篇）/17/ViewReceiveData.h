#if !defined(AFX_RECEIVEVIEW_H__E79F56CC_797D_48E0_B190_B71E1993AAF5__INCLUDED_)
#define AFX_RECEIVEVIEW_H__E79F56CC_797D_48E0_B190_B71E1993AAF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CViewReceiveData.h : header file
//

#include "ViewBase.h"

/////////////////////////////////////////////////////////////////////////////
// CViewReceiveData view


class CViewReceiveData : public CViewBase
{
protected:
	CViewReceiveData();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewReceiveData)

// Attributes
public:

// Operations
public:
	void InitColumns();
    void InsertReceiveLog(CString source, CString content);
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewReceiveData)
	public:	
	protected:	
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CViewReceiveData();
#ifdef _DEBUG	
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CViewReceiveData)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECEIVEVIEW_H__E79F56CC_797D_48E0_B190_B71E1993AAF5__INCLUDED_)
