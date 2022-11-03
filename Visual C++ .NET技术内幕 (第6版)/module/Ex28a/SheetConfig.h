
#pragma once


// CPageServer dialog

class CPageServer : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageServer)

public:
	CPageServer();
	virtual ~CPageServer();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_SERVER };
	CString	m_strDirect;
	UINT	m_nPortServer;
	CString	m_strDefault;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
#pragma once


// CPageAdv dialog

class CPageAdv : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageAdv)

public:
	CPageAdv();
	virtual ~CPageAdv();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_ADV };
	CString	m_strIPServer;
	CString	m_strIPClient;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
#pragma once


// CPageClient dialog

class CPageClient : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageClient)

public:
	CPageClient();
	virtual ~CPageClient();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_CLIENT };
	CString	m_strProxy;
	CString	m_strServerIP;
	CString	m_strServerName;
	BOOL	m_bUseProxy;
	CString	m_strFile;
	UINT	m_nPort;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};

#pragma once



// CSheetConfig

class CSheetConfig : public CPropertySheet
{
	DECLARE_DYNAMIC(CSheetConfig)

public:
	CSheetConfig(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CSheetConfig(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CSheetConfig();

	CPageAdv m_pageAdv;
	CPageClient m_pageClient;
	CPageServer m_pageServer;

protected:
	DECLARE_MESSAGE_MAP()
};

