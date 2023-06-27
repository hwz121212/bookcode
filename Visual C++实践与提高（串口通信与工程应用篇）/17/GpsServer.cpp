// GpsServer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "GpsServer.h"

#include "MainFrm.h"
#include "GpsServerDoc.h"
#include "GpsServerView.h"
#include "DlgLogin.h"
#include "ViewNemaData.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CGpsServerApp

BEGIN_MESSAGE_MAP(CGpsServerApp, CWinApp)
	//{{AFX_MSG_MAP(CGpsServerApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGpsServerApp construction

CGpsServerApp::CGpsServerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance	
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGpsServerApp object

CGpsServerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CGpsServerApp initialization

BOOL CGpsServerApp::InitInstance()
{		
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CGpsServerDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CGpsServerView));
	AddDocTemplate(pDocTemplate);
		

	// Parse command line for standard shell commands, DDE, file open

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Don't display a new MDI child window during startup
   

	// Dispatch commands specified on the command line
    if (!ProcessShellCommand(cmdInfo))
		return FALSE;


	// 定义是否可以成功启动的变量
	BOOL success=FALSE;		
	
	// 获取程序主框架变量和程序文档变量	
	CMainFrame* pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	if (pFrame == NULL) return FALSE;
	CGpsServerDoc* pDoc=(CGpsServerDoc*)pFrame->GetCurrentDoc();
	if (pDoc == NULL) return FALSE;

	// 询问用户是否使用数据库，
	// 如果使用数据库，询问用户登录用户名和密码，来判断用户的有效性
	// 如果不使用数据库，则不需要验证，但是不会保存数据，也不可以自定义配置
	
	while (!success)
	{
		CDlgLogin dlgLogin;
		if (dlgLogin.DoModal()!=IDOK)
		{
			PostQuitMessage(0);
		    return FALSE;
		}

		if (dlgLogin.m_bUseDB)
		{
			success = pDoc->IsUserValid(dlgLogin.m_user, dlgLogin.m_pass);
			if (!success)
			{
				AfxMessageBox("用户名或密码错误，请重新输入！");
			}
			else
			{
				pDoc->m_bUseDB = TRUE;
			}
		}
		else
		{
			success = TRUE;
			pDoc->m_bUseDB = FALSE;
		}
	}
	
	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->SetWindowText("GPS测试机");
	m_pMainWnd->UpdateWindow();	

	// 2、初始化串口的工作变量
	success = pDoc->ReadComConfigs();
	success = pDoc->OpenAllComWorkFlow();
	

	return success;
}


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
		// No message handlers
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

// App command to run the dialog
void CGpsServerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CGpsServerApp message handlers





