#if !defined(AFX_RSCOMCONFIG_H__BF086982_20CC_4FCF_ABA4_7F35D9DC8749__INCLUDED_)
#define AFX_RSCOMCONFIG_H__BF086982_20CC_4FCF_ABA4_7F35D9DC8749__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSComConfig.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSComConfig recordset

class CRSComConfig : public CRecordset
{
public:
	CRSComConfig(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSComConfig)

// Field/Param Data
	//{{AFX_FIELD(CRSComConfig, CRecordset)
	long	m_id;
	CString	m_Name;
	long	m_BoundRate;
	long	m_ByteSize;
	long	m_Parity;
	long	m_StopBits;
	CTime	m_RegTime;
	BOOL	m_IsValid;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSComConfig)
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

#endif // !defined(AFX_RSCOMCONFIG_H__BF086982_20CC_4FCF_ABA4_7F35D9DC8749__INCLUDED_)
