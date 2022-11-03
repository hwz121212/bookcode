// DbdemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Dbdemo.h"
#include "DbdemoDlg.h"

#include "PersonInfo.h"
#define PERSON_INFO 20

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
// CDbdemoDlg dialog

CDbdemoDlg::CDbdemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDbdemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDbdemoDlg)
	m_age = 0;
	m_sex = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDbdemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDbdemoDlg)
	DDX_Control(pDX, IDC_LIST3, m_MyListBox);
	DDX_Text(pDX, IDC_EDIT1, m_age);
	DDX_Text(pDX, IDC_EDIT2, m_sex);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDbdemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDbdemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_LIST3, OnSelchangeList3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDbdemoDlg message handlers

BOOL CDbdemoDlg::OnInitDialog()
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
	FillMyListBox();
	return TRUE;  // return TRUE  unless you set the focus to a control
}
void CDbdemoDlg::FillMyListBox()
{
     BOOL bSuccess = FALSE;

     CString strFunction;

     SQLHENV henv = NULL;
     SQLHDBC hdbc = NULL;
     BOOL bIsConnected = FALSE;
     SQLHSTMT hstmt = NULL;

     SQLRETURN rc;

     SWORD    sMsgNum = 0;
     char     szState[7]="";
     SDWORD   pfNative=0;
if (SQL_SUCCESS == (rc =
 ::SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE,
 &henv)))
{
  if (SQL_SUCCESS == (rc = ::SQLSetEnvAttr(henv,
  SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3,
  SQL_IS_INTEGER)))
  {
	  if (SQL_SUCCESS == (rc =
   ::SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc)))
   {
		   rc = ::SQLConnect(hdbc, 
     (SQLCHAR*)"Mydb",
     SQL_NTS,
     (SQLCHAR*)"", SQL_NTS, (SQLCHAR*)"", SQL_NTS);
	  if ((SQL_SUCCESS == rc)
    || (SQL_SUCCESS_WITH_INFO == rc))
    {
     bIsConnected = TRUE;

     if (SQL_SUCCESS == (rc =
     ::SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt)))
      {
      LPCSTR szSQL = "SELECT * FROM PersonInfo";
      if (SQL_SUCCESS == (rc = ::SQLPrepare(hstmt,
      (unsigned char*)szSQL, SQL_NTS)))
      {
       if (SQL_SUCCESS == (rc = ::SQLExecute(hstmt)))
       {
		   SDWORD cb;
		   char szName[PERSON_INFO];
		   long personage;
		   char personsex[PERSON_INFO];
           SQLBindCol(hstmt,1,SQL_C_CHAR,szName,PERSON_INFO,&cb);
		   SQLBindCol(hstmt,2,SQL_C_LONG,&personage,0,&cb);
		   SQLBindCol(hstmt,3,SQL_C_CHAR,personsex,PERSON_INFO,&cb);
		   
        int iIndex;

        rc = SQLFetch(hstmt);
        while (SQL_SUCCESS == rc)
        {
			PersonInfo *MyInfo=new PersonInfo();
			MyInfo->personName=szName;
			MyInfo->PersonAge=personage;
			MyInfo->PersonSex=personsex;
			iIndex=m_MyListBox.AddString(szName);
			m_MyListBox.SetItemData(iIndex,(DWORD)MyInfo);

			  rc = SQLFetch(hstmt);
        }
       }
      }
     }
    }
   }
  }
 }

 if (henv)
 {
  if (hdbc)
  {
   if (bIsConnected)
   {
    if (hstmt)
    {
     ::SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    }
    ::SQLDisconnect(hdbc);
    bIsConnected = FALSE;
   }
   ::SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
   hdbc = NULL;
  }
  ::SQLFreeHandle(SQL_HANDLE_ENV, henv);
  henv = NULL;
 }
}
void CDbdemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDbdemoDlg::OnPaint() 
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
HCURSOR CDbdemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDbdemoDlg::OnSelchangeList3() 
{
     int iIndex=m_MyListBox.GetCurSel();
	 if (LB_ERR != iIndex)
 {
     PersonInfo *MyInfo=(PersonInfo*)m_MyListBox.GetItemData(iIndex);
	 if(PersonInfo)
	 {
        m_age=MyInfo->PersonAge;
		m_sex=MyInfo->PersonSex;

		UpdateData(FALSE);
	 }
}
}
