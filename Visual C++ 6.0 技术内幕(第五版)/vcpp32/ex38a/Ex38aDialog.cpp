// Ex38aDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ex38a.h"
#include "Ex38aDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx38aDialog dialog


CEx38aDialog::CEx38aDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEx38aDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEx38aDialog)
	m_bCheck1 = FALSE;
	//}}AFX_DATA_INIT
}


void CEx38aDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEx38aDialog)
	DDX_Control(pDX, IDC_PROGRESS1, m_pProgressCtrl);
	DDX_Control(pDX, IDC_COMBO1, m_pComboBox);
	DDX_Check(pDX, IDC_CHECK1, m_bCheck1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEx38aDialog, CDialog)
	//{{AFX_MSG_MAP(CEx38aDialog)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx38aDialog message handlers

BOOL CEx38aDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_pComboBox.AddString(_T("Travel"));
	m_pComboBox.AddString(_T("Meal"));
	m_pComboBox.AddString(_T("Cab Fare"));
	m_pComboBox.AddString(_T("Entertainment"));
	m_pComboBox.AddString(_T("Other"));

	m_pProgressCtrl.SetPos(50);

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEx38aDialog::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	
}

void CEx38aDialog::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	
}
