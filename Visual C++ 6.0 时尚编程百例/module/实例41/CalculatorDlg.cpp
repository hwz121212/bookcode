// CalculatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorDlg.h"

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
// CCalculatorDlg dialog

CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalculatorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalculatorDlg)
	m_number = 0.0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	NumberState=1;
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalculatorDlg)
	DDX_Text(pDX, IDC_EDIT_PUTOUT, m_number);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialog)
	//{{AFX_MSG_MAP(CCalculatorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND_RANGE(IDC_NUMBER1,IDC_NUMBER10,OnNumberKey)
	ON_COMMAND_RANGE(IDC_NUMBER11,IDC_NUMBER20,OnOperationKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalculatorDlg message handlers

BOOL CCalculatorDlg::OnInitDialog()

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

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
void CCalculatorDlg::OnNumberKey(UINT nID)
{
	int n=0;
	switch(nID)
	{
	case IDC_NUMBER1:n=1;break;
	case IDC_NUMBER2:n=2;break;
	case IDC_NUMBER3:n=3;break;
	case IDC_NUMBER4:n=4;break;
	case IDC_NUMBER5:n=5;break;
	case IDC_NUMBER6:n=6;break;
	case IDC_NUMBER7:n=7;break;
	case IDC_NUMBER8:n=8;break;
	case IDC_NUMBER9:n=9;break;
	case IDC_NUMBER10:n=0;break;
	}
	if(NumberState==1)
	{
		m_number=m_number*10+n;
        number1=m_number;
		UpdateData(FALSE);
	}
	else
	{
		m_number=m_number*10+n;
		number2=m_number;
		UpdateData(FALSE);
	}
}
void CCalculatorDlg::OnOperationKey(UINT nID)
{
	switch(nID)
	{
	case IDC_NUMBER11:m_number=-m_number;
		              if(NumberState==1)
					  number1=m_number;
                      else number2=m_number;
					  UpdateData(FALSE);
					  break;                 
	case IDC_NUMBER12:m_number=(int)m_number/10;
		              if(NumberState==1)
					  number1=m_number;
                      else number2=m_number;
					  UpdateData(FALSE);
					  break;       
	case IDC_NUMBER13:OperationState=1;m_number=0;UpdateData(FALSE);NumberState=2;break;
	case IDC_NUMBER14:OperationState=2;m_number=0;UpdateData(FALSE);NumberState=2;break;
	case IDC_NUMBER15:OperationState=3;m_number=0;UpdateData(FALSE);NumberState=2;break;
	case IDC_NUMBER16:OperationState=4;m_number=0;UpdateData(FALSE);NumberState=2;break;
	case IDC_NUMBER17:number1=number2=m_number=0;UpdateData(FALSE);NumberState=1;break;
	case IDC_NUMBER18:number1=m_number=sqrt(number1);UpdateData(FALSE);break;
	case IDC_NUMBER19:number1=m_number=(double)1/number1;UpdateData(FALSE);break;
	case IDC_NUMBER20:cal();break;
	}
}
void CCalculatorDlg::cal()
{
	switch(OperationState)
	{
	case 1:m_number=(double)number1/number2;NumberState=1;UpdateData(FALSE);break;
	case 2:m_number=number1*number2;NumberState=1;UpdateData(FALSE);break;
	case 3:m_number=number1+number2;NumberState=1;UpdateData(FALSE);break;
	case 4:m_number=number1-number2;NumberState=1;UpdateData(FALSE);break;
	}
	OperationState=0;
}
void CCalculatorDlg::OnPaint() 
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
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
