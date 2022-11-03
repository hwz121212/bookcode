// Step3.cpp : implementation file
//

#include "stdafx.h"
#include "Wizard.h"
#include "Step3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStep3 property page

IMPLEMENT_DYNCREATE(CStep3, CPropertyPage)

CStep3::CStep3() : CPropertyPage(CStep3::IDD)
{
	//{{AFX_DATA_INIT(CStep3)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CStep3::~CStep3()
{
}

void CStep3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStep3)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStep3, CPropertyPage)
	//{{AFX_MSG_MAP(CStep3)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStep3 message handlers

BOOL CStep3::OnSetActive() 
{
// TODO: Add your specialized code here and/or call the base class
	CPropertySheet *pSheet=(CPropertySheet *)GetParent();
	ASSERT_KINDOF(CPropertySheet,pSheet);
	pSheet->SetWizardButtons(PSWIZB_FINISH|PSWIZB_BACK);
	return CPropertyPage::OnSetActive();
}
