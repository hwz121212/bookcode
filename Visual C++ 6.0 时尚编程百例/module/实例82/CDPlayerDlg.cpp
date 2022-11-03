// CDPlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CDPlayer.h"
#include "CDPlayerDlg.h"

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
// CCDPlayerDlg dialog

CCDPlayerDlg::CCDPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCDPlayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCDPlayerDlg)
	m_count = _T("");
	m_current = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	MyPlayer.Open();
}

void CCDPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCDPlayerDlg)
	DDX_Text(pDX, IDC_STATIC_COUNT, m_count);
	DDX_Text(pDX, IDC_STATIC_CURRENT, m_current);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCDPlayerDlg, CDialog)
	//{{AFX_MSG_MAP(CCDPlayerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BACK, OnButtonBack)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, OnButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCDPlayerDlg message handlers

BOOL CCDPlayerDlg::OnInitDialog()
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
	GetTotalCDCount();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCDPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCDPlayerDlg::OnPaint() 
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
HCURSOR CCDPlayerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCDPlayerDlg::OnButtonBack() 
{
     int nTrack=MyPlayer.GetCurrentTrack();
	 --nTrack;
	 MyPlayer.SeekTo(nTrack,0,0,0);
	 CString str;
	str.Format("%s %d %s","第",MyPlayer.GetCurrentTrack(),"首");
	 m_current=str;
	 UpdateData(FALSE);
}

void CCDPlayerDlg::OnButtonNext() 
{
	int nTrack=MyPlayer.GetCurrentTrack();
	++nTrack;
	MyPlayer.SeekTo(nTrack,0,0,0);
   CString str;
	str.Format("%s %d %s","第",MyPlayer.GetCurrentTrack(),"首");
	 m_current=str;
	 UpdateData(FALSE);
}

void CCDPlayerDlg::OnButtonPlay() 
{
CString str;
	 str.Format("%s %d %s","第",MyPlayer.GetCurrentTrack(),"首");
	 m_current=str;
	 UpdateData(FALSE);
    MyPlayer.Play();	
}

void CCDPlayerDlg::OnButtonStop() 
{
	MyPlayer.Stop();
}
void CCDPlayerDlg::GetTotalCDCount()
{
	CString str;
	str.Format("%d %s",MyPlayer.GetTotalTracks(),"首");
	m_count=str;
	UpdateData(FALSE);
}
