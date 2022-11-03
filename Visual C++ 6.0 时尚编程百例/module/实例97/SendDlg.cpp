// SendDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientNet.h"
#include "SendDlg.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSendDlg dialog


CSendDlg::CSendDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSendDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSendDlg)
	m_sendedit = _T("");
	m_acceptedit = _T("");
	//}}AFX_DATA_INIT
}


void CSendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSendDlg)
	DDX_Text(pDX, IDC_SENDEDIT, m_sendedit);
	DDX_Text(pDX, IDC_ACCEPTEDIT, m_acceptedit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSendDlg, CDialog)
	//{{AFX_MSG_MAP(CSendDlg)
	ON_BN_CLICKED(IDC_ACCEPT, OnAccept)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendDlg message handlers

void CSendDlg::OnAccept() 
{
	
	UpdateData(FALSE);	

          
}

void CSendDlg::OnSend() 
{
	// TODO: Add your control notification handler code here
    	UpdateData();
    	CMainFrame *pFrame=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	    UpdateData(FALSE);	
		if(pFrame->m_pSocket)
	{
		char pMsg[10000];
		sprintf(pMsg,"%s",m_sendedit.GetBuffer(10000));
		pFrame->SendMsg(pFrame->m_pSocket,pMsg);
	}
}
