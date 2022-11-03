// DlgToolbarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DlgToolbar.h"
#include "DlgToolbarDlg.h"

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
// CDlgToolbarDlg dialog

CDlgToolbarDlg::CDlgToolbarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgToolbarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgToolbarDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDlgToolbarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgToolbarDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgToolbarDlg, CDialog)
	//{{AFX_MSG_MAP(CDlgToolbarDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND_RANGE(ID_BUTTONRED,ID_BUTTONBLUE,OnButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgToolbarDlg message handlers

BOOL CDlgToolbarDlg::OnInitDialog()
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
	btn[0].iBitmap = 0 ;
	btn[0].idCommand = ID_BUTTONRED ;
	btn[0].fsState = TBSTATE_ENABLED  ;
	btn[0].fsStyle = TBSTYLE_BUTTON  ;
	btn[0].dwData = 0 ;
	btn[0].iString = 0;

	btn[1].iBitmap = 1 ;
	btn[1].idCommand = ID_BUTTONGREEN;
	btn[1].fsState = TBSTATE_ENABLED  ;
	btn[1].fsStyle = TBSTYLE_BUTTON ;
	btn[1].dwData = 0 ;
	btn[1].iString = 1;

	btn[2].iBitmap = 2 ;
	btn[2].idCommand = ID_BUTTONBLUE ;
	btn[2].fsState = TBSTATE_ENABLED  ;
	btn[2].fsStyle = TBSTYLE_BUTTON ;
	btn[2].dwData = 0 ;
	btn[2].iString = 2;

	m_toolbarCtrl = NULL ;
	VERIFY(m_toolbarCtrl == NULL );
	m_toolbarCtrl = new CToolBarCtrl() ;

	CRect wndRect ;
	GetWindowRect(&wndRect);
	CRect rc(0,0,wndRect.right , 50);
	if ( 0 == 0 )
		m_toolbarCtrl->Create(TBSTYLE_TOOLTIPS |WS_CHILD | WS_VISIBLE | CCS_TOP | CCS_NODIVIDER, rc ,this , 0 );
	else
		m_toolbarCtrl->Create(TBSTYLE_TOOLTIPS |WS_CHILD | WS_VISIBLE | CCS_BOTTOM  | CCS_NODIVIDER , rc ,this , 0 );

	m_toolbarCtrl->AddButtons(3, btn);
	m_toolbarCtrl->AddBitmap(1, IDR_MYTOOLBAR);
/*
	CSize sz_btn(100,100);
	m_toolbarCtrl->SetButtonSize(sz_btn);
	
	CSize sz_img(100,100);
	m_toolbarCtrl->SetBitmapSize(sz_img);
*/
	m_toolbarCtrl->AutoSize();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDlgToolbarDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDlgToolbarDlg::OnPaint() 
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
void CDlgToolbarDlg::OnButton(UINT nID)
{
	switch(nID)
	{
	case ID_BUTTONRED:MessageBox("你选择红色");break;
	case ID_BUTTONGREEN:MessageBox("你选择绿色");break;
	case ID_BUTTONBLUE:MessageBox("你选择兰色");break;
	}
}
// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDlgToolbarDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
