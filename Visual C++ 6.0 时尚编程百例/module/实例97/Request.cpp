// Request.cpp : implementation file
//

#include "stdafx.h"
#include "ClientNet.h"
#include "Request.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRequest

CRequest::CRequest(CMainFrame *pMainFrame)
{
	m_pMainFrame=pMainFrame;
}

CRequest::~CRequest()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CRequest, CSocket)
	//{{AFX_MSG_MAP(CRequest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CRequest member functions

//利用ClassWizard生成下面的函数

void CRequest::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pMainFrame->FetchMsg(this);
	
	CSocket::OnReceive(nErrorCode);
}
