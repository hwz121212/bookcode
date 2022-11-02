// ConnectedDlg1.cpp : implementation file
//

#include "stdafx.h"
#include "ntChatRoomClient.h"
#include "ConnectedDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConnectedDlg dialog


CConnectedDlg::CConnectedDlg(CServerSocket * tmp,CWnd* pParent /*=NULL*/)
	: CDialog(CConnectedDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConnectedDlg)
	m_strAddress = _T("");
	m_strUserName = _T("");
	//}}AFX_DATA_INIT
	myServerSocket=tmp;
}


void CConnectedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnectedDlg)
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_strAddress);
	DDX_Text(pDX, IDC_EDIT_NIKENAME, m_strUserName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConnectedDlg, CDialog)
	//{{AFX_MSG_MAP(CConnectedDlg)
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnectedDlg message handlers

void CConnectedDlg::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();//�˳�����

}

void CConnectedDlg::OnConnect() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char*address;
	int n;
	if (!myServerSocket->Create())//���������׽���
	{
		myServerSocket->Close();
		AfxMessageBox("Socket�������󣡣�");
		return;
	}
	n=m_strAddress.GetLength();
	address=new char(n+1);//��ȡ��������IP��ַ
	sprintf(address,"%s",m_strAddress.GetBuffer(n));
	address[n]=0;
	if (!myServerSocket->Connect(address,4611))//���ӷ�����
	{
		myServerSocket->Close();
		AfxMessageBox("�������Ӵ��������¼���������ַ����д�Ƿ���ȷ��");
		return;
	}
	myServerSocket->UserName=m_strUserName;
	CDialog::OnOK();//�˳�����
	
}
