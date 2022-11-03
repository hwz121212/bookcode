// SheetConfig.cpp : implementation file
//

#include "stdafx.h"
#include "Ex28a.h"
#include "SheetConfig.h"


// CSheetConfig

IMPLEMENT_DYNAMIC(CSheetConfig, CPropertySheet)
CSheetConfig::CSheetConfig(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CSheetConfig::CSheetConfig(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_pageClient);
	AddPage(&m_pageServer);
	AddPage(&m_pageAdv);
}

CSheetConfig::~CSheetConfig()
{
}


BEGIN_MESSAGE_MAP(CSheetConfig, CPropertySheet)
END_MESSAGE_MAP()


// CSheetConfig message handlers
// SheetConfig.cpp : implementation file
//

#include "stdafx.h"
#include "Ex28a.h"
#include "SheetConfig.h"


// CPageServer dialog

IMPLEMENT_DYNAMIC(CPageServer, CPropertyPage)
CPageServer::CPageServer()
	: CPropertyPage(CPageServer::IDD)
{
	m_strDirect = _T("");
	m_nPortServer = 0;
	m_strDefault = _T("");
}

CPageServer::~CPageServer()
{
}

void CPageServer::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DIRECT, m_strDirect);
	DDX_Text(pDX, IDC_PORTSERVER, m_nPortServer);
	DDX_Text(pDX, IDC_DEFAULT, m_strDefault);
}


BEGIN_MESSAGE_MAP(CPageServer, CPropertyPage)
END_MESSAGE_MAP()


// CPageServer message handlers
// SheetConfig.cpp : implementation file
//

#include "stdafx.h"
#include "Ex28a.h"
#include "SheetConfig.h"


// CPageAdv dialog

IMPLEMENT_DYNAMIC(CPageAdv, CPropertyPage)
CPageAdv::CPageAdv()
	: CPropertyPage(CPageAdv::IDD)
{
	m_strIPServer = _T("");
	m_strIPClient = _T("");
}

CPageAdv::~CPageAdv()
{
}

void CPageAdv::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_IPSERVER, m_strIPServer);
	DDX_Text(pDX, IDC_IPCLIENT, m_strIPClient);
}


BEGIN_MESSAGE_MAP(CPageAdv, CPropertyPage)
END_MESSAGE_MAP()


// CPageAdv message handlers
// SheetConfig.cpp : implementation file
//

#include "stdafx.h"
#include "Ex28a.h"
#include "SheetConfig.h"


// CPageClient dialog

IMPLEMENT_DYNAMIC(CPageClient, CPropertyPage)
CPageClient::CPageClient()
	: CPropertyPage(CPageClient::IDD)
{
	m_strProxy = _T("");
	m_strServerIP = _T("");
	m_strServerName = _T("");
	m_bUseProxy = FALSE;
	m_strFile = _T("");
	m_nPort = 0;
}

CPageClient::~CPageClient()
{
}

void CPageClient::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PROXY, m_strProxy);
	DDX_Text(pDX, IDC_IPADDR, m_strServerIP);
	DDX_Text(pDX, IDC_SERVER, m_strServerName);
	DDX_Check(pDX, IDC_USEPROXY, m_bUseProxy);
	DDX_Text(pDX, IDC_FILE, m_strFile);
	DDX_Text(pDX, IDC_PORT, m_nPort);
}


BEGIN_MESSAGE_MAP(CPageClient, CPropertyPage)
END_MESSAGE_MAP()


// CPageClient message handlers
