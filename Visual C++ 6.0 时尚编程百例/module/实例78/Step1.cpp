// Step1.cpp : implementation file
//

#include "stdafx.h"
#include "Wizard.h"
#include "Step1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStep1 property page

IMPLEMENT_DYNCREATE(CStep1, CPropertyPage)

CStep1::CStep1() : CPropertyPage(CStep1::IDD)
{
	//{{AFX_DATA_INIT(CStep1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CStep1::~CStep1()
{
}

void CStep1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStep1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStep1, CPropertyPage)
	//{{AFX_MSG_MAP(CStep1)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStep1 message handlers

BOOL CStep1::OnSetActive() 
{	
	CPropertySheet *pSheet=(CPropertySheet *)GetParent();
	ASSERT_KINDOF(CPropertySheet,pSheet);
	pSheet->SetWizardButtons(PSWIZB_NEXT);
	return CPropertyPage::OnSetActive();
}
