// ManyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Many.h"
#include "ManyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
    CEvent m_begin;      //启动线程事件
 	CEvent m_end;        //终止线程事件
	int m_count;         //计数变量

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
// CManyDlg dialog

CManyDlg::CManyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CManyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CManyDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CManyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CManyDlg)
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
	DDX_Control(pDX, IDC_ANIMATE, m_animate);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CManyDlg, CDialog)
	//{{AFX_MSG_MAP(CManyDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_FINISHED,OnFinished)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManyDlg message handlers

BOOL CManyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_animate.Open("Filecopy.avi");//打开AVI文件
	m_count=0;                      //初始化计数变量
	m_progress.SetPos(m_count);      //设置进度条初始为位置
	AfxBeginThread(CThreadProc,GetSafeHwnd());  //启动一个线程

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

void CManyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CManyDlg::OnPaint() 
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
HCURSOR CManyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CManyDlg::OnStart() 
{
   SetTimer(1,100,NULL);      //启动记时器
   GetDlgItem(IDC_START)->EnableWindow(FALSE); //禁用开始按钮
   m_begin.SetEvent();     //设置开始事件信号
   m_animate.Play(0,-1,-1);  //开始播放AVI 
 }

void CManyDlg::OnStop() 
{
	if(m_count==0)
	{
		m_begin.SetEvent();
	}
	m_end.SetEvent();  //设置停止事件信号
}
UINT CThreadProc(LPVOID pParam)
{
	volatile int nNum;
	//调用等待启动事件,如果没有启动事件信号将一直等待下去
	::WaitForSingleObject(m_begin,INFINITE);
	    //开始计数
		for(m_count=0;m_count<10000;m_count++)
		{
			for(nNum=0;nNum<10000;nNum++)
			{
			}
			//调用等待停止事件,由于超时值为0,所以只进行简单的判别作用
			if(::WaitForSingleObject(m_end,0)==WAIT_OBJECT_0)
				break;
		}
		//告诉主窗口线程已经结束
		::PostMessage((HWND)pParam,WM_FINISHED,0,0);
		m_count=0;
	return 0;
}


void CManyDlg::OnTimer(UINT_PTR nIDEvent) 
{
	//设置进度条位置显示计数进度
    m_progress.SetPos(m_count*100/10000);  	
	CDialog::OnTimer(nIDEvent);
}
LRESULT CManyDlg::OnFinished(WPARAM wParam,LPARAM lParam)
{
	CManyDlg::OnOK();   //结束对话框应用程序
	m_animate.Stop();  //停止播放AVI
	return 0;
}
