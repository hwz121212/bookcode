// MyRecordSet.cpp : implementation file
//

#include "stdafx.h"
#include "MyOdbc.h"
#include "MyRecordSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MyRecordSet

IMPLEMENT_DYNAMIC(MyRecordSet, CRecordset)

MyRecordSet::MyRecordSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(MyRecordSet)
	m_Name = _T("");
	m_Age = 0;
	m_Sex = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString MyRecordSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=Mydb");
}

CString MyRecordSet::GetDefaultSQL()
{
	return _T("[PersonInfo]");
}

void MyRecordSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(MyRecordSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[Age]"), m_Age);
	RFX_Text(pFX, _T("[Sex]"), m_Sex);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// MyRecordSet diagnostics

#ifdef _DEBUG
void MyRecordSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void MyRecordSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
