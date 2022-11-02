// ServerSocket.cpp : implementation file
//

#include "stdafx.h"
#include "ntChatRoomClient.h"
#include "ServerSocket.h"
#include "ntChatRoomClientDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerSocket

CServerSocket::CServerSocket()
{
	UserName="";
	myDlg=0;
}

CServerSocket::~CServerSocket()
{
}

BOOL CServerSocket::SetDlg(CntChatRoomClientDlg *tmp)
{
	myDlg=tmp;
	return true;
}
// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CServerSocket, CSocket)
	//{{AFX_MSG_MAP(CServerSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CServerSocket member functions

void CServerSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	myDlg->GetMessage();//接收服务器信息
	CSocket::OnReceive(nErrorCode);	
}
