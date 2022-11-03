// Client.cpp : implementation file
//

#include "stdafx.h"
#include "ServerNet.h"
#include "Client.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClient

CClient::CClient(CMainFrame *pMainFrame)
{
		m_pMainFrame=pMainFrame;
}

CClient::~CClient()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClient, CSocket)
	//{{AFX_MSG_MAP(CClient)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClient member functions

void CClient::OnReceive(int nErrorCode) 
{
	m_pMainFrame->FetchMsg(this);	
	CSocket::OnReceive(nErrorCode);
}
