// CBrowerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CBrower.h"
#include "CBrowerDlg.h"

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
// CCBrowerDlg dialog

CCBrowerDlg::CCBrowerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCBrowerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCBrowerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCBrowerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCBrowerDlg)
	DDX_Control(pDX, IDC_TREE, m_tree);
	DDX_Control(pDX, IDC_WEB, m_web);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCBrowerDlg, CDialog)
	//{{AFX_MSG_MAP(CCBrowerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FORWARD, OnForward)
	ON_BN_CLICKED(IDC_BACK, OnBack)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, OnSelchangedTree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCBrowerDlg message handlers

BOOL CCBrowerDlg::OnInitDialog()
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
	//显示首页
	m_web.Navigate("d:\\vc++\\CBrower\\head.htm",NULL,NULL,NULL,NULL);
	//初始化树控件
	TV_INSERTSTRUCT treeItem;
	HTREEITEM Item;
	treeItem.hInsertAfter=TVI_LAST;
	treeItem.item.mask=TVIF_TEXT|TVIF_PARAM;
	//第一层
	treeItem.hParent=TVI_ROOT;//根目录
	CString text="首页";
	treeItem.item.pszText=text.GetBuffer(30);
	treeItem.item.lParam=0;
	Item=m_tree.InsertItem(&treeItem);
	//第二层
	treeItem.hParent=Item;
	treeItem.item.lParam=1;
    strcpy(treeItem.item.pszText,"首页1");
	m_tree.InsertItem(&treeItem);
	
	treeItem.item.lParam=2;
    strcpy(treeItem.item.pszText,"首页2");
	m_tree.InsertItem(&treeItem);

	treeItem.item.lParam=3;
    strcpy(treeItem.item.pszText,"首页3");
	m_tree.InsertItem(&treeItem);

	treeItem.item.lParam=4;
    strcpy(treeItem.item.pszText,"首页4");
	m_tree.InsertItem(&treeItem);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCBrowerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCBrowerDlg::OnPaint() 
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
HCURSOR CCBrowerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCBrowerDlg::OnForward() 
{
 m_web.GoForward();	
}

void CCBrowerDlg::OnBack() 
{
	// TODO: Add your control notification handler code here
	m_web.GoBack();
}

void CCBrowerDlg::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	//根据得到选中的条目在树控件中的lParam值
    HTREEITEM item=m_tree.GetSelectedItem();
	TV_ITEM  tree;
	tree.hItem=item;
	m_tree.GetItem(&tree);
	TCHAR exeFullPath[1000];
	GetModuleFileName(NULL,exeFullPath,1000);
	CString strpath;
	strpath=exeFullPath;
	strpath=strpath.Mid(0,strpath.GetLength()-11);
	
	//判断选中的条目并显示相应的超文本文件
	switch(tree.lParam)
	{
	case 0:
		strpath=strpath+"\head.htm";
		m_web.Navigate(strpath,NULL,NULL,NULL,NULL);
		break;
	case 1:
		strpath=strpath+"\poem1.htm";
		m_web.Navigate(strpath,NULL,NULL,NULL,NULL);
		break;
	case 2:
		strpath=strpath+"\poem2.htm";
		m_web.Navigate(strpath,NULL,NULL,NULL,NULL);
		break;
	case 3:
		strpath=strpath+"\poem3.htm";
		m_web.Navigate(strpath,NULL,NULL,NULL,NULL);
		break;
    case 4:
		strpath=strpath+"\poem4.htm";
		m_web.Navigate(strpath,NULL,NULL,NULL,NULL);
		break;
	default:break;
	}
	*pResult = 0;
}
