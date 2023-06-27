#if !defined(AFX_USERRECORDSET_H__0632BF3D_8E31_4B90_B1BD_483551603B00__INCLUDED_)
#define AFX_USERRECORDSET_H__0632BF3D_8E31_4B90_B1BD_483551603B00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CRSUser.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSUser recordset

class CRSUser : public CRecordset
{
public:
	
	CRSUser(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSUser)

// Field/Param Data
	//{{AFX_FIELD(CRSUser, CRecordset)
	int		m_ID;
	CString	m_pass;
	CString	m_username;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSUser)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERRECORDSET_H__0632BF3D_8E31_4B90_B1BD_483551603B00__INCLUDED_)
