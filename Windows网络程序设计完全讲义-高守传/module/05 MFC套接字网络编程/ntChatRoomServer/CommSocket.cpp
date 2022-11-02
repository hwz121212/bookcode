// CommSocket.cpp : implementation file
//

#include "stdafx.h"
#include "ntChatRoomServer.h"
#include "CommSocket.h"
#include "CommSocketList.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommSocket

CCommSocket::CCommSocket(CCommSocketList *temp)
{
	Front=Next=0;
	List=temp;
}

CCommSocket::~CCommSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CCommSocket, CSocket)
	//{{AFX_MSG_MAP(CCommSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CCommSocket member functions

void CCommSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	List->Sends(this);//调用CCommSocketList的send函数
	CSocket::OnClose(nErrorCode);
}

void CCommSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	List->Sends(this);//调用CCommSocketList的send函数
	CSocket::OnReceive(nErrorCode);
}
