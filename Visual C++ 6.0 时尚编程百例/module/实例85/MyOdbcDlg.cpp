// MyOdbcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyOdbc.h"
#include "MyOdbcDlg.h"

#include "MyRecordSet.h"

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
// CMyOdbcDlg dialog

CMyOdbcDlg::CMyOdbcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyOdbcDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyOdbcDlg)
	m_age = 0;
	m_sex = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyOdbcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyOdbcDlg)
	DDX_Control(pDX, IDC_LIST1, m_listbox);
	DDX_Text(pDX, IDC_EDIT1, m_age);
	DDX_Text(pDX, IDC_EDIT2, m_sex);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyOdbcDlg, CDialog)
	//{{AFX_MSG_MAP(CMyOdbcDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyOdbcDlg message handlers

BOOL CMyOdbcDlg::OnInitDialog()
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
	FillPersonInfo();
	return TRUE;  // return TRUE  unless you set the focus to a control
}
void CMyOdbcDlg::FillPersonInfo()
{
	CDatabase db;
	int iIndex;
	MyRecordSet *PersonRecord=NULL;
	if(db.Open("Mydb"))
	{
		PersonRecord=new MyRecordSet();
		PersonRecord->Open();
		while(!PersonRecord->IsEOF())
		{
			PersonInfo *Info=new PersonInfo();
			Info->personName=PersonRecord->m_Name;
			Info->PersonAge=PersonRecord->m_Age;
			Info->PersonSex=PersonRecord->m_Sex;
			iIndex=m_listbox.AddString(Info->personName);
			m_listbox.SetItemData(iIndex,(DWORD)Info);
			PersonRecord->MoveNext();
		}
	}
	else MessageBox("Can't open Database");
	PersonRecord->Close();
	delete PersonRecord;
	db.Close();
}
void CMyOdbcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMyOdbcDlg::OnPaint() 
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
HCURSOR CMyOdbcDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMyOdbcDlg::OnSelchangeList() 
{
	int iIndex=m_listbox.GetCurSel();
	if (LB_ERR != iIndex)
 {
     PersonInfo *Info=(PersonInfo*)m_listbox.GetItemData(iIndex);
	 if(Info != NULL)
	 {
        m_age=Info->PersonAge;
		m_sex=Info->PersonSex;

		UpdateData(FALSE);
	 }
}
	
}
