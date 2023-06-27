// TTYReceiveMSCommDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TTYReceiveMSComm.h"
#include "TTYReceiveMSCommDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTTYReceiveMSCommDlg dialog

CTTYReceiveMSCommDlg::CTTYReceiveMSCommDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTTYReceiveMSCommDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTTYReceiveMSCommDlg)
	m_Para = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTTYReceiveMSCommDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTTYReceiveMSCommDlg)
	DDX_Control(pDX, IDC_CLOSECOM, m_Closecom);
	DDX_Control(pDX, IDC_SETUPCOM, m_Setupcom);
	DDX_Control(pDX, IDC_OPENCOM, m_Opencom);
	DDX_Control(pDX, IDC_EXIT, m_Exit);
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	DDX_Text(pDX, IDC_PARA, m_Para);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTTYReceiveMSCommDlg, CDialog)
	//{{AFX_MSG_MAP(CTTYReceiveMSCommDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SETUPCOM, OnSetupcom)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDC_OPENCOM, OnOpencom)
	ON_BN_CLICKED(IDC_CLOSECOM, OnClosecom)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTTYReceiveMSCommDlg message handlers

BOOL CTTYReceiveMSCommDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//blnOpened=false;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTTYReceiveMSCommDlg::OnPaint() 
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
HCURSOR CTTYReceiveMSCommDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTTYReceiveMSCommDlg::OnSetupcom() 
{
	// TODO: Add your control notification handler code here
	CString strStatus,strTemp;
	double dblBaud;
	if(mySetupDlg.DoModal()==IDOK)
	{
		myCom=mySetupDlg.m_Com+1;                              //求取串口编号
		dblBaud=pow(2,(double)mySetupDlg.m_BaudRate);          //求取波特率
		dblBaud=19200/dblBaud;
		strStatus.Format("%.0f",dblBaud);
		myBaudRate=strStatus;

		switch(mySetupDlg.m_Parity)
		{
		case 0:
			{
			myParity="N";
			break;
			}
		case 1:
			{
			myParity="O";
			break;
			}
		case 2:
			{
			myParity="E";
			break;
			}
		}
	strStatus="COM";
	strTemp.Format("%d",myCom);
	strStatus+=strTemp;
	strStatus+=",";
	strStatus+=myBaudRate;
	strStatus+=",";
	strStatus+=myParity;
	strStatus+=",8,1";
	m_Para=strStatus;
	UpdateData(false);
	}

}

void CTTYReceiveMSCommDlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	this->EndDialog(IDOK);                     //关闭程序
	
}

void CTTYReceiveMSCommDlg::OnOpencom() 
{
	// TODO: Add your control notification handler code here
	//以下的初始化只是一个例子，根据实际程序要求的不同，
	//初始化代码可能与此有差别。斜体字代码是必须的。
	CString strPara;                          //串口参数
	myComm.SetCommPort(myCom);                //指定串口号myCom
	strPara=myBaudRate;
	strPara+=",";
	strPara+=myParity;
	strPara+=",8,1";
	myComm.SetSettings(strPara);             //通信参数设置
	myComm.SetInBufferSize(1024);            //指定接收缓冲区大小
	myComm.SetInBufferCount(0);              //清空接收缓冲区
	myComm.SetInputMode(1);                  //设置数据获取方式
	myComm.SetInputLen(0);                   //设置每次读取长度
	myComm.SetRThreshold(1);                 //设置接收OnComm事件门限值
	myComm.SetPortOpen(1);                   //打开串口
	m_Opencom.EnableWindow(false);           //使“打开串口”按钮无效
	m_Closecom.EnableWindow(true);           //使“关闭串口”按钮生效
	m_Setupcom.EnableWindow(false);          //使“设置”按钮无效
	m_Exit.EnableWindow(false);              //使“退出”按钮无效
	AfxMessageBox("串口打开成功！");
}

void CTTYReceiveMSCommDlg::OnClosecom() 
{
	// TODO: Add your control notification handler code here
	myComm.SetPortOpen(0);
	AfxMessageBox("串口关闭成功！");
	m_Opencom.EnableWindow(true);           //使打开串口按钮生效
	m_Closecom.EnableWindow(false);         //使关闭串口按钮无效
	m_Setupcom.EnableWindow(true);          //使设置按钮生效
	m_Exit.EnableWindow(true);              //使退出按钮生效
}

int CTTYReceiveMSCommDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	//创建控件的实例
	DWORD style=WS_VISIBLE|WS_CHILD;
	if (!myComm.Create(NULL,style,CRect(0,0,0,0),this,IDC_MSCOMM1))
	{
		AfxMessageBox("创建MSComm控件失败！");
		m_Opencom.EnableWindow(false);        //使打开串口按钮无效
		m_Closecom.EnableWindow(false);       //使关闭串口按钮无效
		m_Setupcom.EnableWindow(false);       //使设置按钮无效
		return -1;
	}
	m_Para="COM1,9600,N,8,1";
	return 0;
}

BEGIN_EVENTSINK_MAP(CTTYReceiveMSCommDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CTTYReceiveMSCommDlg)
	ON_EVENT(CTTYReceiveMSCommDlg, IDC_MSCOMM1, 1 /* OnComm */, OnOnCommMscomm1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CTTYReceiveMSCommDlg::OnOnCommMscomm1() 
{
	// TODO: Add your control notification handler code here
	VARIANT input1;                     //定义VARIANT类型变量
	BYTE rxdata[2048];                  //定义存放二进制数据的数组
	long len1,k;
	COleSafeArray safearray1;           //定义COleSafeArray类的实例
	CString strDis;
	switch(myComm.GetCommEvent())
	{
	case 2:
		//收到 RThreshold 个字符
		//添加接收处理代码
		input1=myComm.GetInput();
		//将VARAIANT变量赋值给COleSafeArray类的实例
		safearray1=input1;     
		//使用COleSafeArray类的成员函数获取数据长度
		len1=safearray1.GetOneDimSize();
		for(k=0;k<len1;k++)
		//使用COleSafeArray类的成员函数将数据写入数组
			safearray1.GetElement(&k,rxdata+k);

		for(k=0;k<1;k++)
		{
			if(rxdata[k]==13)
			{
				m_Edit1.SetSel(1000000,1000000);
				m_Edit1.ReplaceSel("\15\12");
				UpdateData(false);
			}
			else
			{
				if(rxdata[k]<=126 && rxdata[k]>=32)
				{
					strDis+=rxdata[k];
					m_Edit1.SetSel(1000000,1000000);
					m_Edit1.ReplaceSel(strDis);
					strDis="";
					UpdateData(false);
				}
			}
		}
	}
}
