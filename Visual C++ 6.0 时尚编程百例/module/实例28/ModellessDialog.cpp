// ModellessDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Modelless.h"
#include "ModellessDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModellessDialog dialog


CModellessDialog::CModellessDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CModellessDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModellessDialog)
	m_add = -1;
	m_first = 0.0f;
	m_second = 0.0f;
	m_result = 0.0f;
	//}}AFX_DATA_INIT
}


void CModellessDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModellessDialog)
	DDX_Radio(pDX, IDC_ADD, m_add);
	DDX_Text(pDX, IDC_FIRST, m_first);
	DDX_Text(pDX, IDC_SECOND, m_second);
	DDX_Text(pDX, IDC_RESULT, m_result);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModellessDialog, CDialog)
	//{{AFX_MSG_MAP(CModellessDialog)
	ON_BN_CLICKED(IDC_COMPUTER, OnComputer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModellessDialog message handlers

void CModellessDialog::OnComputer() 
{
   UpdateData();
   if(m_add==0)
	   m_result=m_first+m_second;
   if(m_add==1)
	   m_result=m_first-m_second;
   if(m_add==2)
	   m_result=m_first*m_second;
   if(m_add==3)
	   m_result=m_first/m_second;
   UpdateData(FALSE);
	// TODO: Add your control notification handler code here
	
}
