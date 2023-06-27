// SetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PC2PC.h"
#include "SetupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg dialog


CSetupDlg::CSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetupDlg)
	m_BaudRate = 0;
	m_Com = 3;
	m_Parity = 0;
	//}}AFX_DATA_INIT
}


void CSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupDlg)
	DDX_CBIndex(pDX, IDC_COMBO_B, m_BaudRate);
	DDX_CBIndex(pDX, IDC_COMBO_COM, m_Com);
	DDX_CBIndex(pDX, IDC_COMBO_P, m_Parity);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CSetupDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg message handlers

BOOL CSetupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	CString strStatus;
	switch (m_Com)
	{
	case 0:
		{
		strStatus="COM1";
		strStatus+="  ";
		//myCom="COM1";
		break;
		}
	case 1:
		{
		strStatus="COM2";
		strStatus+="  ";
		//myCom="COM2";
		break;
		}

	case 2:
		{
		strStatus="COM3";
		strStatus+="  ";
		//myCom="COM3";
		break;
		}

	case 3:
		{
		strStatus="COM4";
		strStatus+="  ";
		//myCom="COM4";
		break;
		}

	case 4:
		{
		strStatus="COM5";
		strStatus+="  ";
		//myCom="COM5";
		}
		break;
	case 5:
		{
		strStatus="COM6";
		strStatus+="  ";
		//myCom="COM6";
		}
		break;
	}
	switch(m_BaudRate)
	{

	case 0:
		{
		strStatus+="19200";
		strStatus+="  ";
		//myBaudRate=CBR_19200;
		break;
		}
	case 1:
		{
		strStatus+="9600";
		strStatus+="  ";
		//myBaudRate=CBR_9600;
		break;
		}
	case 2:
		{
		strStatus+="4800";
		strStatus+="  ";
		//myBaudRate=CBR_4800;
		break;
		}
	case 3:
		{
		strStatus+="2400";
		strStatus+="  ";
		//myBaudRate=CBR_2400;
		break;
		}
	}
	switch(m_Parity)
	{
	case 0:
		{
		//myfParity=false;
		//myParity=NOPARITY;
		strStatus+="N";
		strStatus+="-8-1";
		break;
		}
	case 1:
		{
		//myfParity=TRUE;
		//myParity=ODDPARITY;
		strStatus+="O";
		strStatus+="-8-1";
		break;
		}
	case 2:
		{
		//myfParity=true;
		//myParity=EVENPARITY;
		strStatus+="E";
		strStatus+="-8-1";
		break;
		}
	}

	CMainFrame* m_pGetFrame=(CMainFrame*) AfxGetApp()->m_pMainWnd ;
	CStatusBar* m_pStatus=&m_pGetFrame->m_wndStatusBar;
	m_pStatus->SetPaneText(1,strStatus);     //将通信参数显示在状态条上
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
