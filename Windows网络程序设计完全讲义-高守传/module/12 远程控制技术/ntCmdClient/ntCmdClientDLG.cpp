/*
  This project was created and edited using the MFC SelfBanner AppWizard.

  Comment: 远程控制－远程Cmd客户端.

  Project: ntCmdClient.
  Author : dhyao
  Date   : 星期一, 二月 02, 2009
*/
/////////////////////////////////////////////////////////////////////
// ntCmdClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ntCmdClient.h"
#include "ntCmdClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CntCmdClientDlg dialog

CntCmdClientDlg::CntCmdClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CntCmdClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CntCmdClientDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	msInfor.dwIP=inet_addr("127.0.0.1");
	msInfor.uPort=htons(830);
	IsFullScreen=FALSE;
	
	TitleBar=NULL;
}


CntCmdClientDlg::~CntCmdClientDlg()
{
	if(TitleBar!=NULL)
	{
		delete TitleBar;
		TitleBar=NULL;
	}
}


void CntCmdClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CntCmdClientDlg)
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CntCmdClientDlg, CDialog)
	//{{AFX_MSG_MAP(CntCmdClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(tbWM_CLOSE, OnTbClose)
	ON_MESSAGE(tbWM_MINIMIZE, OnTbMinimize)
	ON_MESSAGE(tbWM_MAXIMIZE, OnTbMaximize)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CntCmdClientDlg message handlers

BOOL CntCmdClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	StartNewConnet(NULL);
//	SetTimer(0,100, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CntCmdClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
		
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CntCmdClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CntCmdClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

DWORD CntCmdClientDlg::StartNewConnet(LPVOID lpvoid)
{
	
	WSADATA ws;
	//初始化wsa
	WSAStartup(MAKEWORD(2,2),&ws);
	//建立socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM , IPPROTO_TCP);
	SOCKADDR_IN addr_in = {0};
	addr_in.sin_family = AF_INET;
	addr_in.sin_addr.S_un.S_addr = msInfor.dwIP;
	addr_in.sin_port =msInfor.uPort;

	int ret = SOCKET_ERROR;
	HANDLE  hp = NULL;
	//连接指定的ip和端口
		ret=connect(sock, (struct sockaddr*)&addr_in,sizeof(addr_in));
		if ( ret == 0 )
		{
			m_edit.StartCmdEditor(sock);
			SetWindowText("连接到：127.0.0.1");
		}
		
	return 1;
}

void CntCmdClientDlg::SetFullScreen(BOOL OnOff)
{

	LONG style = GetWindowLong(m_hWnd, GWL_STYLE);
	
	if(OnOff==TRUE)
	{
		ShowWindow(SW_MAXIMIZE);
		//调整控件
		m_edit.ShowWindow(SW_MAXIMIZE);
		style = ::GetWindowLong(m_hWnd, GWL_STYLE);
		style &= ~(WS_DLGFRAME | WS_THICKFRAME);
		::SetWindowLong(m_hWnd, GWL_STYLE, style);
		int cx = GetSystemMetrics(SM_CXSCREEN);
		int cy = GetSystemMetrics(SM_CYSCREEN);
		::SetWindowPos(m_hWnd,HWND_TOPMOST, -1, -1, cx+3, cy+3, SWP_FRAMECHANGED);
		IsFullScreen=TRUE;
		TitleBar->DisplayWindow(TRUE, TRUE);
		InvalidateRect(NULL,TRUE);		
	}
	else //OFF!
	{
		style |= WS_DLGFRAME | WS_THICKFRAME;
		SetWindowLong(m_hWnd, GWL_STYLE, style);
		::SetWindowPos(m_hWnd, HWND_NOTOPMOST, 0,0,100,100, SWP_NOMOVE | SWP_NOSIZE);
		ShowWindow( SW_NORMAL);
		//调整控件
		m_edit.ShowWindow(SW_NORMAL);
		IsFullScreen=FALSE;
		TitleBar->DisplayWindow(FALSE, TRUE);
		InvalidateRect(NULL,TRUE);
	}
}

void CntCmdClientDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(TitleBar==NULL)
	{
		TitleBar=new CTitleBar(AfxGetInstanceHandle(),m_hWnd);
		TitleBar->SetText("连接到：127.0.0.1");
	}
	
	if(IsFullScreen==FALSE)
		SetFullScreen(TRUE); //Set fullscreen on!
	else
		SetFullScreen(FALSE); //Set fullscreen off!

	CDialog::OnLButtonDown(nFlags, point);
}

void CntCmdClientDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}

LRESULT CntCmdClientDlg::OnTbClose(WPARAM wParam, LPARAM lParam)
{
	DestroyWindow();
	PostQuitMessage(0);
	return 0;
}



LRESULT CntCmdClientDlg::OnTbMinimize(WPARAM wParam, LPARAM lParam)
{
	ShowWindow(SW_MINIMIZE);
	return 0;
}



LRESULT CntCmdClientDlg::OnTbMaximize(WPARAM wParam, LPARAM lParam)
{
	if(IsFullScreen==FALSE)
		SetFullScreen(TRUE); //Set fullscreen on!
	else
		SetFullScreen(FALSE); //Set fullscreen on!

	return 0;
}

