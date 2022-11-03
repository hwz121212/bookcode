// UseSpaceshipDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UseSpaceship.h"
#include "UseSpaceshipDlg.h"
#include "_attributedatlspaceshipsvr.h"
#include "atlspaceshipsvr.h"
#include "_attributedatlspaceshipsvr_i.c"
#include "atlspaceshipsvr_i.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CUseSpaceshipDlg dialog



CUseSpaceshipDlg::CUseSpaceshipDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUseSpaceshipDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUseSpaceshipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUseSpaceshipDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_USEATTRIBUTEDATLSPACESHIP, OnBnClickedUseattributedatlspaceship)
    ON_BN_CLICKED(IDC_USECLASSICATLSPACESHIP, OnBnClickedUseclassicatlspaceship)
END_MESSAGE_MAP()


// CUseSpaceshipDlg message handlers

BOOL CUseSpaceshipDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUseSpaceshipDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUseSpaceshipDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUseSpaceshipDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CUseSpaceshipDlg::OnBnClickedUseattributedatlspaceship()
{
	//Call CoCreateInstance on the CLSID	

	IAttributedATLSpaceShip* pSpaceShip = NULL;
	IMotion* pMotion = NULL;
	IVisual* pVisual = NULL;

	HRESULT hr;
	hr = CoCreateInstance(CLSID_CAttributedATLSpaceShip, 
		             NULL, 
					 CLSCTX_INPROC_SERVER, 
					 IID_IAttributedATLSpaceShip, 
					 (void**)&pSpaceShip);

	if(pSpaceShip) {
		pSpaceShip->QueryInterface(IID_IVisual, (void**)&pVisual);

		if(pVisual) {
			pVisual->Display();
			pVisual->Release();
		}

		pSpaceShip->QueryInterface(IID_IMotion, (void**)&pMotion);
		if(pMotion) {
			long lPosition;

			pMotion->Fly();
			pMotion->GetPosition(&lPosition);
			pMotion->Release();
		}

		pSpaceShip->Release();
	}
}

void CUseSpaceshipDlg::OnBnClickedUseclassicatlspaceship()
{
	//Call CoCreateInstance on the CLSID	

	IClassicATLSpaceship* pSpaceShip = NULL;
	IMotion* pMotion = NULL;
	IVisual* pVisual = NULL;

	HRESULT hr;
	hr = CoCreateInstance(CLSID_ClassicATLSpaceship, 
		             NULL, 
					 CLSCTX_INPROC_SERVER, 
					 IID_IClassicATLSpaceship, 
					 (void**)&pSpaceShip);

	if(pSpaceShip) {
		pSpaceShip->QueryInterface(IID_IVisual, (void**)&pVisual);

		if(pVisual) {
			pVisual->Display();
			pVisual->Release();
		}

		pSpaceShip->QueryInterface(IID_IMotion, (void**)&pMotion);
		if(pMotion) {
			long lPosition;

			pMotion->Fly();
			pMotion->GetPosition(&lPosition);
			pMotion->Release();
		}

		pSpaceShip->Release();
	}
}
