#if !defined(AFX_MYRECORDSET_H__AF8F15E0_C5DD_11D2_A71D_A175F8619D69__INCLUDED_)
#define AFX_MYRECORDSET_H__AF8F15E0_C5DD_11D2_A71D_A175F8619D69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyRecordSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MyRecordSet recordset

class MyRecordSet : public CRecordset
{
public:
	MyRecordSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(MyRecordSet)

// Field/Param Data
	//{{AFX_FIELD(MyRecordSet, CRecordset)
	CString	m_Name;
	long	m_Age;
	CString	m_Sex;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MyRecordSet)
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

#endif // !defined(AFX_MYRECORDSET_H__AF8F15E0_C5DD_11D2_A71D_A175F8619D69__INCLUDED_)
