// Lisent.cpp : implementation file
//

#include "stdafx.h"
#include "ServerNet.h"
#include "Lisent.h"

#include "Client.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLisent

CLisent::CLisent(CMainFrame *pMainFrame)
{
	m_pMainFrame=pMainFrame;
}

CLisent::~CLisent()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CLisent, CSocket)
	//{{AFX_MSG_MAP(CLisent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CLisent member functions

//利用ClassWizar生成下面的消息响应函数

void CLisent::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CClient *pSocket=new CClient(m_pMainFrame);
	if(m_pMainFrame->m_pListening->Accept(*pSocket))
	{
		m_pMainFrame->m_pList.AddTail(pSocket);
	}
	else 
		delete pSocket;
	CSocket::OnAccept(nErrorCode);
}
