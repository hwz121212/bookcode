// Ex28aView.cpp : implementation of the CEx28aView class
//

#include "stdafx.h"
#include "Ex28a.h"
#include "mainfrm.h"

#include "Ex28aDoc.h"
#include "Ex28aView.h"
#include "Utility.h"
#include "SheetConfig.h"
#include "BlockSock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern CBlockingSocket g_sListen;

// CEx28aView

IMPLEMENT_DYNCREATE(CEx28aView, CEditView)

BEGIN_MESSAGE_MAP(CEx28aView, CEditView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
    ON_COMMAND(ID_INTERNET_START_SERVER, OnInternetStartServer)
    ON_UPDATE_COMMAND_UI(ID_INTERNET_START_SERVER, OnUpdateInternetStartServer)
    ON_COMMAND(ID_INTERNET_REQUEST_SOCK, OnInternetRequestSock)
    ON_COMMAND(ID_INTERNET_REQUEST_INET, OnInternetRequestInet)
    ON_COMMAND(ID_INTERNET_STOP_SERVER, OnInternetStopServer)
    ON_UPDATE_COMMAND_UI(ID_INTERNET_STOP_SERVER, OnUpdateInternetStopServer)
    ON_COMMAND(ID_INTERNET_CONFIGURATION, OnInternetConfiguration)
    ON_UPDATE_COMMAND_UI(ID_INTERNET_CONFIGURATION, OnUpdateInternetConfiguration)
    ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearAll)
	ON_COMMAND(IDC_REQUEST, OnRequest)
    ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

// CEx28aView construction/destruction

CEx28aView::CEx28aView()
{
	// TODO: add construction code here

}

CEx28aView::~CEx28aView()
{
}

BOOL CEx28aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}


// CEx28aView printing

BOOL CEx28aView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CEx28aView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CEx28aView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}


// CEx28aView diagnostics

#ifdef _DEBUG
void CEx28aView::AssertValid() const
{
	CEditView::AssertValid();
}

void CEx28aView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CEx28aDoc* CEx28aView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx28aDoc)));
	return (CEx28aDoc*)m_pDocument;
}
#endif //_DEBUG


// CEx28aView message handlers

void CEx28aView::OnInternetStartServer()
{
	try {
		CSockAddr saServer;
		if(g_strIPServer.IsEmpty()) { // first or only IP
			saServer = CSockAddr(INADDR_ANY, (USHORT) g_nPortServer);
		}
		else {	// if our computer has multiple IP addresses...
			saServer = CSockAddr(g_strIPServer, (USHORT) g_nPortServer);
		}
		g_sListen.Create();
		g_sListen.Bind(saServer);
		g_sListen.Listen();// start listening
		g_bListening = TRUE;
		g_nConnection = 0;
		AfxBeginThread(ServerThreadProc, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
	}
	catch(CBlockingSocketException* e) {
		g_sListen.Cleanup();
		LogBlockingSocketException(GetSafeHwnd(), "VIEW:", e);
		e->Delete();
	}
}

void CEx28aView::OnUpdateInternetStartServer(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!g_bListening);
}

void CEx28aView::OnInternetRequestSock()
{
	AfxBeginThread(ClientSocketThreadProc, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}

void CEx28aView::OnInternetRequestInet()
{
	AfxBeginThread(ClientWinInetThreadProc, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}

void CEx28aView::OnInternetStopServer()
{	
    try {
		if(g_bListening) {
			g_sListen.Close();
		}
	}
	catch(CBlockingSocketException* e) {
		LogBlockingSocketException(GetSafeHwnd(), "VIEW:", e);
		e->Delete();
	}
}

void CEx28aView::OnUpdateInternetStopServer(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(g_bListening);
}

void CEx28aView::OnInternetConfiguration()
{
	CSheetConfig sh("Configuration");
	sh.m_pageServer.m_strDirect = g_strDirect;
	sh.m_pageServer.m_strDefault = g_strDefault;
	sh.m_pageServer.m_nPortServer = g_nPortServer;
	sh.m_pageClient.m_strServerIP = g_strServerIP;
	sh.m_pageClient.m_nPort = g_nPort;
	sh.m_pageClient.m_strServerName = g_strServerName;
	sh.m_pageClient.m_strFile = g_strFile;
	sh.m_pageClient.m_strProxy = g_strProxy;
	sh.m_pageClient.m_bUseProxy = g_bUseProxy;
	sh.m_pageAdv.m_strIPClient = g_strIPClient;
	sh.m_pageAdv.m_strIPServer = g_strIPServer;
	if(sh.DoModal() == IDOK) {
		g_strDirect = sh.m_pageServer.m_strDirect;
		g_strDefault = sh.m_pageServer.m_strDefault;
		g_nPortServer = sh.m_pageServer.m_nPortServer;
		g_strServerIP = sh.m_pageClient.m_strServerIP;
		g_nPort = sh.m_pageClient.m_nPort;
		g_strServerName = sh.m_pageClient.m_strServerName;
		if(sh.m_pageClient.m_strFile.IsEmpty()) {
			g_strFile = "/";
		}
		else {
			g_strFile = sh.m_pageClient.m_strFile;
		}
		g_strProxy = sh.m_pageClient.m_strProxy;
		g_bUseProxy = sh.m_pageClient.m_bUseProxy;
		g_strIPClient = sh.m_pageAdv.m_strIPClient;
		g_strIPServer = sh.m_pageAdv.m_strIPServer;
		if(!g_strIPClient.IsEmpty() && g_bUseProxy) {
			AfxMessageBox("Warning: you can't assign a client IP address if "
				"you are using a proxy server");
		}
		if(!g_strServerIP.IsEmpty() && g_bUseProxy) {
			AfxMessageBox("Warning: you must specify the server by name if "
				"you are using a proxy server");
		}
		if(g_strServerIP.IsEmpty() && g_strServerName.IsEmpty()) {
			AfxMessageBox("Warning: you must specify either a server name or "
				"a server IP address");
		}
		if(!g_strServerIP.IsEmpty() && !g_strServerName.IsEmpty()) {
			AfxMessageBox("Warning: you cannot specify both a server name "
				"and a server IP address");
		}
		::SetCurrentDirectory(g_strDirect);
	}
}

void CEx28aView::OnUpdateInternetConfiguration(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!g_bListening);
}

void CEx28aView::OnEditClearAll()
{
	SetWindowText("");
}

void CEx28aView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// clear-all menu activated on right button
	CMenu menu;
	menu.LoadMenu(IDR_CONTEXT_MENU);
	menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		point.x, point.y, this);
}

void CEx28aView::OnRequest() 
{
	CWnd& rBar = ((CMainFrame*) AfxGetApp()->m_pMainWnd)->m_wndDialogBar;
	// g_strURL: thread sync?
	rBar.GetDlgItemText(IDC_URL, g_strURL);
	TRACE("CEx28aView::OnRequest -- URL = %s\n", (const char*) g_strURL);
	AfxBeginThread(ClientUrlThreadProc, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}