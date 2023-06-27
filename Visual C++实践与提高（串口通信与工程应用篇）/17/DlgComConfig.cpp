// DlgComConfig.cpp : implementation file
//

#include "stdafx.h"
#include "GpsServer.h"
#include "DlgComConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgComConfig dialog


CDlgComConfig::CDlgComConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgComConfig::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgComConfig)	
	m_strCom = _T("");
	//}}AFX_DATA_INIT


}


void CDlgComConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgComConfig)
	DDX_Control(pDX, IDC_COMBO_COM, m_combCom);
	DDX_CBString(pDX, IDC_COMBO_COM, m_strCom);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgComConfig, CDialog)
	//{{AFX_MSG_MAP(CDlgComConfig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgComConfig message handlers



BOOL CDlgComConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();	
#define COMMAXLENGTH      4
	CString comlist[COMMAXLENGTH]={"COM1","COM2","COM3","COM4"};
	for (int i=0;i<3;i++)
	{
		m_combCom.AddString(comlist[i]);
	}
	m_combCom.SetCurSel(0);	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


