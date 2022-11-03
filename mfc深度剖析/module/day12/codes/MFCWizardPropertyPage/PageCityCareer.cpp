// PageCityCareer.cpp : implementation file
//

#include "stdafx.h"
#include "MFCWizardPropertyPage.h"
#include "PageCityCareer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageCityCareer property page

IMPLEMENT_DYNCREATE(CPageCityCareer, CPropertyPage)

CPageCityCareer::CPageCityCareer() : CPropertyPage(CPageCityCareer::IDD)
{
	//{{AFX_DATA_INIT(CPageCityCareer)
	m_strCity = _T("");
	m_nCareer = -1;
	//}}AFX_DATA_INIT
}

CPageCityCareer::~CPageCityCareer()
{
}

void CPageCityCareer::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageCityCareer)
	DDX_Control(pDX, IDC_LIST_CITY, m_wndCity);
	DDX_LBString(pDX, IDC_LIST_CITY, m_strCity);
	DDX_Radio(pDX, IDC_RADIO_PROGRAMER, m_nCareer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageCityCareer, CPropertyPage)
	//{{AFX_MSG_MAP(CPageCityCareer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageCityCareer message handlers

BOOL CPageCityCareer::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	//�����򵼰�ť��	CPropertySheet::SetWizardButtons
	//�Ȼ�ȡ��
	((CPropertySheet*)GetParent())->SetWizardButtons(
		PSWIZB_NEXT   
		);
	return CPropertyPage::OnSetActive();
}

BOOL CPageCityCareer::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	//���б������ӳ�����Ϣ
	m_wndCity.AddString("����");
	m_wndCity.AddString("�Ϻ�");
	m_wndCity.AddString("���");
	m_wndCity.AddString("����");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CPageCityCareer::OnWizardNext() 
{
	// TODO: Add your specialized code here and/or call the base class
		UpdateData(TRUE);
	if(-1==m_nCareer){
		MessageBox("��ѡ������ְҵ!");
		return -1;
	}
	if(m_strCity.IsEmpty()){
		MessageBox("��ѡ�������ڵĳ���!");
		return -1;
	}
	return CPropertyPage::OnWizardNext();
}

void CPageCityCareer::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType) 
{
	// TODO: Add your specialized code here and/or call the base class

	CPropertyPage::CalcWindowRect(lpClientRect, nAdjustType);
}
