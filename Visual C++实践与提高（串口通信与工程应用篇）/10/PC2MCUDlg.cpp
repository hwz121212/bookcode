// PC2MCUDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PC2MCU.h"
#include "PC2MCUDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int iStatus;         //表征当前操作状态，0－无操作，1－等待接收长度，2－等待接收数据
short dataLen,count; //数据的长度,重发的次数

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
// CPC2MCUDlg dialog

CPC2MCUDlg::CPC2MCUDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPC2MCUDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPC2MCUDlg)
	m_Edit1 = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPC2MCUDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPC2MCUDlg)
	DDX_Control(pDX, READ, m_Read);
	DDX_Text(pDX, IDC_EDIT1, m_Edit1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPC2MCUDlg, CDialog)
	//{{AFX_MSG_MAP(CPC2MCUDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(READ, OnREAD)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPC2MCUDlg message handlers

BOOL CPC2MCUDlg::OnInitDialog()
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
	DWORD style=WS_VISIBLE|WS_CHILD;
	if (!myComm.Create(NULL,style,CRect(0,0,0,0),this,IDC_MSCOMM1))
	{
		AfxMessageBox("创建MSComm控件失败！");
		return FALSE;
	}
	else//创建成功则执行初始化及打开串口操作
	{
		myComm.SetCommPort(4);            //指定串口号
		myComm.SetSettings("4800,N,8,1"); //通信参数设置
		myComm.SetInBufferSize(1024);     //指定接收缓冲区大小
		myComm.SetInBufferCount(0);       //清空接收缓冲区
		myComm.SetInputMode(1);           //设置数据获取方式
		myComm.SetInputLen(0);            //设置每次读取长度
		myComm.SetRThreshold(1);          //设置接收OnComm事件门限值
		myComm.SetPortOpen(1);            //打开串口

	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPC2MCUDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPC2MCUDlg::OnPaint() 
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
HCURSOR CPC2MCUDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BEGIN_EVENTSINK_MAP(CPC2MCUDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CPC2MCUDlg)
	ON_EVENT(CPC2MCUDlg, IDC_MSCOMM1, 1 /* OnComm */, OnOnCommMscomm1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CPC2MCUDlg::OnOnCommMscomm1() 
{
	// TODO: Add your control notification handler code here
	int inCount,overCount;
	char myChar[20];
	CString myStr;
	VARIANT input1;                    //定义VARIANT类型变量
	BYTE rxdata[2048];                 //定义存放二进制数据的数组
	long len1,k,i,sum;
	COleSafeArray safearray1;          //定义COleSafeArray类的实例
	CByteArray Array1;                 //创建存放二进制数据的CByteArray类实例

	switch(myComm.GetCommEvent())
	{
	case 2:                           //收到 RThreshold 个字符
		//添加接收处理代码
		switch(iStatus)               //根据不同状态采取不同操作
		{
		case 1:
			//接收ACK及长度和长度的取反值
			{
				KillTimer(1);
				overCount=0;
				while(overCount<=10)
				{
					inCount=myComm.GetInBufferCount();
					if (inCount>=3) break;
					Sleep(200);
					overCount++;
				}
				if (overCount>=11)
				{
					m_Edit1+="   超时错误！";
					m_Edit1+="\15\12";
					UpdateData(false);
					Beep(1000,50);
					CEdit*pEdit1=(CEdit*)GetDlgItem(IDC_EDIT1);
					pEdit1->LineScroll(pEdit1->GetLineCount());
					iStatus=0;
					m_Read.EnableWindow(true);
					myComm.SetInBufferCount(0);
					myComm.SetOutBufferCount(0);
					break;
				}
				else
				{
					input1=myComm.GetInput();
					//将VARAIANT变量赋值给COleSafeArray类的实例
					safearray1=input1;            
					len1=safearray1.GetOneDimSize();//使用COleSafeArray类的成员函数获取数据长度
					for(k=0;k<len1;k++)
					//使用COleSafeArray类的成员函数将数据写入数组
					safearray1.GetElement(&k,rxdata+k);
					m_Edit1+="-->";
					for (i=0;i<=2;i++)
					{
						_itoa(rxdata[i],myChar,10);
						myStr+=myChar;
						myStr+="|";
					}
					m_Edit1+=myStr;
					UpdateData(false);
					m_Edit1+="\15\12";
					if((rxdata[0]==6) && ((rxdata[1]+rxdata[2])==255))
					{
						dataLen=rxdata[1];        //保存数据的长度值
						//发出正确回应ACK（06）
						count=0;
						Array1.RemoveAll();
						Array1.SetSize(1);
						Array1.SetAt(0,06);
						myComm.SetOutput(COleVariant(Array1)); 
						m_Edit1+="<--ACK";
						UpdateData(false);
						m_Edit1=m_Edit1+"\15\12";
						iStatus=2;
						SetTimer(1,1000,NULL);
					}
					else
					{
						//发出重发回应NAK（31）
						count++;
						if (count>=3)
						{
							m_Edit1+="   重发次数超过3次！";
							UpdateData(false);
							Beep(1000,50);
							CEdit*pEdit1=(CEdit*)GetDlgItem(IDC_EDIT1);
							pEdit1->LineScroll(pEdit1->GetLineCount());
							m_Edit1=m_Edit1+"\15\12";
							iStatus=0;
							m_Read.EnableWindow(true);
							myComm.SetInBufferCount(0);
							myComm.SetOutBufferCount(0);
							count=0;
							break;
						}
						Array1.RemoveAll();
						Array1.SetSize(1);
						Array1.SetAt(0,31);
						myComm.SetOutput(COleVariant(Array1)); 
						m_Edit1+="<--NAK";
						UpdateData(false);
						m_Edit1=m_Edit1+"\15\12";
						iStatus=1;
						SetTimer(1,1000,NULL);
					}

				}
				break;
				}
		case 2:
			{
				KillTimer(1);
				overCount=0;
				while(overCount<=10)
				{
					inCount=myComm.GetInBufferCount();
					if (inCount>=dataLen+1) break;
					Sleep(200);
					overCount++;
				}
				if (overCount>=11)
				{
					m_Edit1+="   超时错误！";
					m_Edit1+="\15\12";
					UpdateData(false);
					Beep(1000,50);
					CEdit*pEdit1=(CEdit*)GetDlgItem(IDC_EDIT1);
					pEdit1->LineScroll(pEdit1->GetLineCount());
					iStatus=0;
					m_Read.EnableWindow(true);
					myComm.SetInBufferCount(0);
					myComm.SetOutBufferCount(0);
					break;
				}
				else
				{
					input1=myComm.GetInput();
					//将VARAIANT变量赋值给COleSafeArray类的实例
					safearray1=input1;            
					len1=safearray1.GetOneDimSize();//使用COleSafeArray类的成员函数获取数据长度
					for(k=0;k<len1;k++)
					//使用COleSafeArray类的成员函数将数据写入数组
					safearray1.GetElement(&k,rxdata+k);
					m_Edit1+="--> ";
					sum=0;
					for (i=0;i<=dataLen;i++)
					{
						_itoa(rxdata[i],myChar,10);
						myStr+=myChar;
						myStr+="|";
						sum+=rxdata[i];
					}
					sum-=rxdata[dataLen];
					sum%=256;
					m_Edit1+=myStr;
					UpdateData(false);
					m_Edit1+="\15\12";
					if(sum==rxdata[dataLen])
					{
						//发出正确回应ACK（06）
						count=0;
						Array1.RemoveAll();
						Array1.SetSize(1);
						Array1.SetAt(0,06);
						myComm.SetOutput(COleVariant(Array1)); 
						m_Edit1+="<--ACK";
						UpdateData(false);
						m_Edit1=m_Edit1+"\15\12";
						iStatus=0;
						m_Read.EnableWindow(true);
						m_Edit1=m_Edit1+"\15\12";
						UpdateData(false);
						CEdit*pEdit1=(CEdit*)GetDlgItem(IDC_EDIT1);
						pEdit1->LineScroll(pEdit1->GetLineCount());
					}
					else
					{
						//发出重发回应NAK（31）
						count++;
						if (count>=3)
						{
							m_Edit1+="   重发次数超过3次！";
							UpdateData(false);
							Beep(1000,50);
							CEdit*pEdit1=(CEdit*)GetDlgItem(IDC_EDIT1);
							pEdit1->LineScroll(pEdit1->GetLineCount());
							m_Edit1=m_Edit1+"\15\12";
							iStatus=0;
							m_Read.EnableWindow(true);
							myComm.SetInBufferCount(0);
							myComm.SetOutBufferCount(0);
							count=0;
							break;
						}
						Array1.RemoveAll();
						Array1.SetSize(1);
						Array1.SetAt(0,31);
						myComm.SetOutput(COleVariant(Array1)); 
						m_Edit1+="<--NAK";
						UpdateData(false);
						CEdit*pEdit1=(CEdit*)GetDlgItem(IDC_EDIT1);
						pEdit1->LineScroll(pEdit1->GetLineCount());
						m_Edit1=m_Edit1+"\15\12";
						iStatus=2;
						SetTimer(1,1000,NULL);
					}
				}			
				break;
			}
		}
		break;
	//若需要处理其它事件，在这里加入其它的case语句
	}
}

void CPC2MCUDlg::OnREAD() 
{
	// TODO: Add your control notification handler code here
	//iStatus=0;
	char myChar[20];
	CByteArray Array1;                 //创建存放二进制数据的CByteArray类实例
	if (iStatus==0)
	{
		Array1.RemoveAll();
		Array1.SetSize(1);
		Array1.SetAt(0,05);
		myComm.SetOutput(COleVariant(Array1)); 
		m_Edit1+="<--ENQ  ";
		_strdate(myChar);
		m_Edit1+=myChar;
		m_Edit1+="  ";
		_strtime(myChar);
		m_Edit1+=myChar;
		m_Edit1=m_Edit1+"\15\12";
		UpdateData(false);
		CEdit*pEdit1=(CEdit*)GetDlgItem(IDC_EDIT1);
		pEdit1->LineScroll(pEdit1->GetLineCount());
		m_Read.EnableWindow(false); //使按钮无效
		SetTimer(1,1000,NULL);
		iStatus=1;
	}
}

void CPC2MCUDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	m_Edit1+="   超时错误！";
	m_Edit1=m_Edit1+"\15\12";
	UpdateData(false);
	CEdit*pEdit1=(CEdit*)GetDlgItem(IDC_EDIT1);
	pEdit1->LineScroll(pEdit1->GetLineCount());
	m_Read.EnableWindow(true);    //使按钮有效
	KillTimer(1);
	iStatus=0;
	Beep(1000,50);
	CDialog::OnTimer(nIDEvent);
}

void CPC2MCUDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if (myComm.GetPortOpen()) 	
		myComm.SetPortOpen(0);              //关闭串口
	CDialog::OnClose();
}




