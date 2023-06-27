// RSComConfig.cpp : implementation file
//

#include "stdafx.h"
#include "GpsServer.h"
#include "RSComConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSComConfig

IMPLEMENT_DYNAMIC(CRSComConfig, CRecordset)

CRSComConfig::CRSComConfig(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSComConfig)
	m_id = 0;
	m_Name = _T("");
	m_BoundRate = 0;
	m_ByteSize = 0;
	m_Parity = 0;
	m_StopBits = 0;
	m_IsValid = FALSE;
	m_nFields = 8;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CRSComConfig::GetDefaultConnect()
{
	return _T("ODBC;DSN=GPSCOMDB");
}

CString CRSComConfig::GetDefaultSQL()
{
	return _T("[ComConfig]");
}

void CRSComConfig::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSComConfig)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[id]"), m_id);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[BoundRate]"), m_BoundRate);
	RFX_Long(pFX, _T("[ByteSize]"), m_ByteSize);
	RFX_Long(pFX, _T("[Parity]"), m_Parity);
	RFX_Long(pFX, _T("[StopBits]"), m_StopBits);
	RFX_Date(pFX, _T("[RegTime]"), m_RegTime);
	RFX_Bool(pFX, _T("[IsValid]"), m_IsValid);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSComConfig diagnostics

#ifdef _DEBUG
void CRSComConfig::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSComConfig::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
