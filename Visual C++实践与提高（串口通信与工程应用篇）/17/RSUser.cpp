// RSUser.cpp : implementation file
//

#include "stdafx.h"
#include "GpsServer.h"
#include "RSUser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSUser

IMPLEMENT_DYNAMIC(CRSUser, CRecordset)

CRSUser::CRSUser(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSUser)
	m_ID = 0;
	m_pass = _T("");
	m_username = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CRSUser::GetDefaultConnect()
{
	return _T("ODBC;DSN=GPSCOMDB");
}

CString CRSUser::GetDefaultSQL()
{
	return _T("[dbo].[User]");
}

void CRSUser::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSUser)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[pass]"), m_pass);
	RFX_Text(pFX, _T("[username]"), m_username);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSUser diagnostics

#ifdef _DEBUG
void CRSUser::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSUser::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

