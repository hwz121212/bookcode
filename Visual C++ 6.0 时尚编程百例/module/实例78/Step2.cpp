// Step2.cpp : implementation file
//

#include "stdafx.h"
#include "Wizard.h"
#include "Step2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStep2 property page

IMPLEMENT_DYNCREATE(CStep2, CPropertyPage)

CStep2::CStep2() : CPropertyPage(CStep2::IDD)
{
	//{{AFX_DATA_INIT(CStep2)
	m_check = FALSE;
	//}}AFX_DATA_INIT
}

CStep2::~CStep2()
{
}

void CStep2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStep2)
	DDX_Check(pDX, IDC_CHECK1, m_check);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStep2, CPropertyPage)
	//{{AFX_MSG_MAP(CStep2)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStep2 message handlers

BOOL CStep2::OnSetActive() 
{
	CPropertySheet *pSheet=(CPropertySheet *)GetParent();
	ASSERT_KINDOF(CPropertySheet,pSheet);
	pSheet->SetWizardButtons(PSWIZB_NEXT|PSWIZB_BACK);	
	return CPropertyPage::OnSetActive();

}

LRESULT CStep2::OnWizardNext() 
{
	UpdateData( );
	if(!m_check)
	{
		MessageBox("You must check the box.");
		return -1;
	}

	return CPropertyPage::OnWizardNext();
}
