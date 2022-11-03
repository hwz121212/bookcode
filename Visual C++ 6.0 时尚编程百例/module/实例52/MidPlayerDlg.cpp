// MidPlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MidPlayer.h"
#include "MidPlayerDlg.h"


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
// CMidPlayerDlg dialog

CMidPlayerDlg::CMidPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMidPlayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMidPlayerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMidPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMidPlayerDlg)
	DDX_Control(pDX, IDC_LIST1, m_midbox);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMidPlayerDlg, CDialog)
	//{{AFX_MSG_MAP(CMidPlayerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMidPlayerDlg message handlers

BOOL CMidPlayerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
    nIndex=0;
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMidPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMidPlayerDlg::OnPaint() 
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
HCURSOR CMidPlayerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMidPlayerDlg::OnOpen() 
{
 CString szFilter="MID Files(*.MID)|*.MID||";
	CFileDialog Dlg( TRUE, NULL, NULL,
		OFN_HIDEREADONLY, szFilter );
CString MidName;

		 if(Dlg.DoModal()==IDOK)
		 {
          MidName=Dlg.GetFileName();
		  m_midbox.AddString(MidName);
	
		 }

	  
	
}

void CMidPlayerDlg::OnPlay() 
{
	CString GetMidName;
 	m_midbox.GetText(nIndex,GetMidName);
    Mymid.Open(GetMidName);
	Mymid.Play();
}

void CMidPlayerDlg::OnSelchangeList() 
{
nIndex=m_midbox.GetCurSel();
	
}

void CMidPlayerDlg::OnStop() 
{
Mymid.Stop();
Mymid.Close();
}

void CMidPlayerDlg::OnNext() 
{
int count=m_midbox.GetCount()-1;
if(nIndex<count){++nIndex;
m_midbox.SetCurSel(nIndex);	
OnStop();
OnPlay();}
}

void CMidPlayerDlg::OnDblclkList() 
{
    nIndex=m_midbox.GetCurSel();
	OnStop();
    OnPlay();
}
