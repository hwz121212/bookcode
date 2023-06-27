#if !defined(AFX_VIEWRECEIVEPOSITION_H__25B9CAFF_E7C1_472E_BCB2_3512B6850466__INCLUDED_)
#define AFX_VIEWRECEIVEPOSITION_H__25B9CAFF_E7C1_472E_BCB2_3512B6850466__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewReceivePosition.h : header file
//

#include "ViewBase.h"
/////////////////////////////////////////////////////////////////////////////
// CViewReceivePosition view

class CViewReceivePosition : public CViewBase
{
protected:
	CViewReceivePosition();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewReceivePosition)

// Attributes
public:

// Operations
public:
	void InitColumns();
	void InsertPosition(CString source, GPSPack *pack);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewReceivePosition)
	public:	
	protected:	
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CViewReceivePosition();
#ifdef _DEBUG
	
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CViewReceivePosition)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWRECEIVEPOSITION_H__25B9CAFF_E7C1_472E_BCB2_3512B6850466__INCLUDED_)
