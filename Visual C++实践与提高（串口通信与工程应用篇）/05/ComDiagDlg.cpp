// ComDiagDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ComDiag.h"
#include "ComDiagDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComDiagDlg dialog

CComDiagDlg::CComDiagDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CComDiagDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CComDiagDlg)
	m_Delay1 = 100;                         //设置超时时间1
	m_Delay2 = 100;                         //设置超时时间2
	m_Delay3 = 100;                         //设置超时时间3
	m_Delay4 = 100;                         //设置超时时间4
	m_Delay5 = 100;                         //设置超时时间5
	m_Delay6 = 100;                         //设置超时时间6
	m_Delay7 = 100;                         //设置超时时间7
	m_Senddata1 = _T("");
	m_Senddata2 = _T("");
	m_Senddata3 = _T("");
	m_Senddata4 = _T("");
	m_Senddata5 = _T("");
	m_Senddata6 = _T("");
	m_Senddata7 = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CComDiagDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComDiagDlg)
	DDX_Control(pDX, IDC_SEND7, m_Send7);
	DDX_Control(pDX, IDC_SEND6, m_Send6);
	DDX_Control(pDX, IDC_SEND5, m_Send5);
	DDX_Control(pDX, IDC_SEND4, m_Send4);
	DDX_Control(pDX, IDC_SEND3, m_Send3);
	DDX_Control(pDX, IDC_SEND2, m_Send2);
	DDX_Control(pDX, IDC_SEND1, m_Send1);
	DDX_Control(pDX, IDC_SETUPCOM, m_Setupcom);
	DDX_Control(pDX, IDC_CLOSECOM, m_Closecom);
	DDX_Control(pDX, IDC_OPENCOM, m_Opencom);
	DDX_Control(pDX, IDC_EXIT, m_Exit);
	DDX_Control(pDX, IDC_Dis, m_Dis);
	DDX_Text(pDX, IDC_DELAY1, m_Delay1);
	DDV_MinMaxInt(pDX, m_Delay1, 100, 100000);
	DDX_Text(pDX, IDC_DELAY2, m_Delay2);
	DDV_MinMaxInt(pDX, m_Delay2, 100, 100000);
	DDX_Text(pDX, IDC_DELAY3, m_Delay3);
	DDV_MinMaxInt(pDX, m_Delay3, 100, 100000);
	DDX_Text(pDX, IDC_DELAY4, m_Delay4);
	DDV_MinMaxInt(pDX, m_Delay4, 100, 100000);
	DDX_Text(pDX, IDC_DELAY5, m_Delay5);
	DDV_MinMaxInt(pDX, m_Delay5, 100, 100000);
	DDX_Text(pDX, IDC_DELAY6, m_Delay6);
	DDV_MinMaxInt(pDX, m_Delay6, 100, 100000);
	DDX_Text(pDX, IDC_DELAY7, m_Delay7);
	DDV_MinMaxInt(pDX, m_Delay7, 100, 100000);
	DDX_Text(pDX, IDC_SENDDATA1, m_Senddata1);
	DDX_Text(pDX, IDC_SENDDATA2, m_Senddata2);
	DDX_Text(pDX, IDC_SENDDATA3, m_Senddata3);
	DDX_Text(pDX, IDC_SENDDATA4, m_Senddata4);
	DDX_Text(pDX, IDC_SENDDATA5, m_Senddata5);
	DDX_Text(pDX, IDC_SENDDATA6, m_Senddata6);
	DDX_Text(pDX, IDC_SENDDATA7, m_Senddata7);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CComDiagDlg, CDialog)
	//{{AFX_MSG_MAP(CComDiagDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDC_SETUPCOM, OnSetupcom)
	ON_BN_CLICKED(IDC_OPENCOM, OnOpencom)
	ON_BN_CLICKED(IDC_CLOSECOM, OnClosecom)
	ON_BN_CLICKED(IDC_SEND1, OnSend1)
	ON_BN_CLICKED(IDC_SEND2, OnSend2)
	ON_BN_CLICKED(IDC_SEND3, OnSend3)
	ON_BN_CLICKED(IDC_SEND4, OnSend4)
	ON_BN_CLICKED(IDC_SEND5, OnSend5)
	ON_BN_CLICKED(IDC_SEND6, OnSend6)
	ON_BN_CLICKED(IDC_SEND7, OnSend7)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComDiagDlg message handlers

BOOL CComDiagDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
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
	m_Send1.EnableWindow(false);
	m_Send2.EnableWindow(false);
	m_Send3.EnableWindow(false);
	m_Send4.EnableWindow(false);
	m_Send5.EnableWindow(false);
	m_Send6.EnableWindow(false);
	m_Send7.EnableWindow(false);
	//m_Para="COM1,9600,N,8,1";
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CComDiagDlg::OnPaint() 
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
HCURSOR CComDiagDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CComDiagDlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	this->EndDialog(true);
}

void CComDiagDlg::OnSetupcom() 
{
	// TODO: Add your control notification handler code here
	CString strStatus,strTemp;
	double dblBaud;
	if(mySetupDlg.DoModal()==IDOK)
	{
		UpdateData(true);
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
		//m_Para=strStatus;
		//this->GetWindowText(strTemp);
		strTemp="ComDiag___";
		strTemp+=strStatus;
		this->SetWindowText(strTemp);                           //修改窗口标题
		UpdateData(false);
	}
	
}

void CComDiagDlg::OnOpencom() 
{
	// TODO: Add your control notification handler code here
	CString strPara;                          //串口参数
	myComm.SetCommPort(myCom);                //指定串口号
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
	m_Opencom.EnableWindow(false);           //使打开串口按钮无效
	m_Closecom.EnableWindow(true);           //使关闭串口按钮生效
	m_Setupcom.EnableWindow(false);          //使设置按钮无效
	m_Exit.EnableWindow(false);              //使退出按钮无效
	m_Send1.EnableWindow(true);              //使发送1按钮无效
	m_Send2.EnableWindow(true);              //使发送2按钮无效
	m_Send3.EnableWindow(true);              //使发送3按钮无效
	m_Send4.EnableWindow(true);              //使发送4按钮无效
	m_Send5.EnableWindow(true);              //使发送5按钮无效
	m_Send6.EnableWindow(true);              //使发送6按钮无效
	m_Send7.EnableWindow(true);              //使发送7按钮无效
	AfxMessageBox("串口打开成功！");
}

void CComDiagDlg::OnClosecom() 
{
	// TODO: Add your control notification handler code here
	myComm.SetPortOpen(0);
	AfxMessageBox("串口关闭成功！");
	m_Opencom.EnableWindow(true);             //使打开串口按钮生效
	m_Closecom.EnableWindow(false);           //使关闭串口按钮无效
	m_Setupcom.EnableWindow(true);            //使设置按钮生效
	m_Exit.EnableWindow(true);                //使退出按钮生效
	m_Send1.EnableWindow(false);              //使发送1按钮无效
	m_Send2.EnableWindow(false);              //使发送2按钮无效
	m_Send3.EnableWindow(false);              //使发送3按钮无效
	m_Send4.EnableWindow(false);              //使发送4按钮无效
	m_Send5.EnableWindow(false);              //使发送5按钮无效
	m_Send6.EnableWindow(false);              //使发送6按钮无效
	m_Send7.EnableWindow(false);              //使发送7按钮无效
}

BEGIN_EVENTSINK_MAP(CComDiagDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CComDiagDlg)
	ON_EVENT(CComDiagDlg, IDC_MSCOMM1, 1 /* OnComm */, OnOnCommMscomm1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CComDiagDlg::OnOnCommMscomm1() 
{
	// TODO: Add your control notification handler code here
	int		iLast=0;                                 //接收字符个数
	CString strDis,strTemp;
	VARIANT input1;                                  //定义VARIANT类型变量
	BYTE rxdata[2048];                               //定义存放二进制数据的数组
	COleSafeArray safearray1;                        //定义COleSafeArray类的实例
	long len1,k;
	UpdateData(true);
	KillTimer(1);                                    //关闭超时定时器
	switch(myComm.GetCommEvent())
	{
	case 2:
		{
			m_Send1.EnableWindow(true);              //使发送1按钮有效
			m_Send2.EnableWindow(true);              //使发送2按钮有效
			m_Send3.EnableWindow(true);              //使发送3按钮有效
			m_Send4.EnableWindow(true);              //使发送4按钮有效
			m_Send5.EnableWindow(true);              //使发送5按钮有效
			m_Send6.EnableWindow(true);              //使发送6按钮有效
			m_Send7.EnableWindow(true);              //使发送7按钮有效
			while((myComm.GetInBufferCount())>iLast)
			{
				iLast=myComm.GetInBufferCount();
				Sleep(100);
			}
			//收到iLast个字符
			//读取输入缓冲区数据
			input1=myComm.GetInput();
			//将VARAIANT变量赋值给COleSafeArray类的实例
			safearray1=input1;     
			//使用COleSafeArray类的成员函数获取数据长度
			len1=safearray1.GetOneDimSize();
			strDis="收到:";
			for(k=0;k<len1;k++)
			//使用COleSafeArray类的成员函数将数据写入数组
			{
				safearray1.GetElement(&k,rxdata+k);
				strTemp.Format("%02X-",rxdata[k]);
				strDis+=strTemp;
			}
			strDis+="\12\15\12\15";
			m_Dis.SetSel(100000,100000);
			m_Dis.ReplaceSel(strDis);               //更新显示
			UpdateData(false);
				
			break;
		}
	default:
		{

		}
	}


}

void CComDiagDlg::OnSend1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_Senddata1!="")
	{
		SendData(m_Senddata1);
		SetTimer(1,m_Delay1,NULL);
		m_Send1.EnableWindow(false);
	}
}

void CComDiagDlg::OnSend2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_Senddata2!="")
	{
		SendData(m_Senddata2);
		SetTimer(1,m_Delay2,NULL);
		m_Send2.EnableWindow(false);
	}
}

void CComDiagDlg::OnSend3() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_Senddata3!="")
	{
		SendData(m_Senddata3);
		SetTimer(1,m_Delay3,NULL);
		m_Send3.EnableWindow(false);
	}
}

void CComDiagDlg::OnSend4() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_Senddata4!="")
	{
		SendData(m_Senddata4);
		SetTimer(1,m_Delay4,NULL);
		m_Send4.EnableWindow(false);
	}
	
}

void CComDiagDlg::OnSend5() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_Senddata5!="")
	{
		SendData(m_Senddata5);
		SetTimer(1,m_Delay5,NULL);
		m_Send5.EnableWindow(false);
	}
	
}

void CComDiagDlg::OnSend6() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_Senddata6!="")
	{
		SendData(m_Senddata6);
		SetTimer(1,m_Delay6,NULL);
		m_Send6.EnableWindow(false);
	}
}

void CComDiagDlg::OnSend7() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_Senddata7!="")
	{
		SendData(m_Senddata7);
		SetTimer(1,m_Delay7,NULL);
		m_Send7.EnableWindow(false);
	}
}

//串口发送数据函数
void CComDiagDlg::SendData(CString strInput)
{
	CString strTemp,strClip,strTemp1;
	int		iLen,i,iCount;
	char	charInput[100];
	BYTE	arrSendData[100];
	CByteArray Array1;

	strInput+=",";
	strcpy(charInput,strInput);
	iLen=strInput.GetLength();
	iCount=0;
	for(i=0;i<iLen;i++)
	{
		switch(charInput[i])
		{
		case 48:               //字符0
		case 49:               //字符1
		case 50:               //字符2
		case 51:               //字符3
		case 52:               //字符4
		case 53:               //字符5
		case 54:               //字符6
		case 55:               //字符7
		case 56:               //字符8
		case 57:               //字符9
		case 65:               //字符A
		case 66:               //字符B
		case 67:               //字符C
		case 68:               //字符D
		case 69:               //字符E
		case 70:               //字符F
			{
				
				strTemp+=charInput[i];
				break;
			}
		default:               //其它字符
			{
				if(strTemp!="")
				{
					//将字符串转换为数值
					arrSendData[iCount]=(BYTE)strtol(strTemp,0,16);
					iCount++;
					strTemp="";
				}
				break;
			}
		}

	}
	Array1.RemoveAll();
	Array1.SetSize(iCount);
	for(i=0;i<iCount;i++)
	{
		Array1.SetAt(i,arrSendData[i]);
	}
	if(Array1.GetSize()>0)
	{
		myComm.SetOutput(COleVariant(Array1));          //发送数据
	}

}

void CComDiagDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(nIDEvent);                     //关闭超时定时器
	AfxMessageBox("超时！");
	m_Send1.EnableWindow(true);              //使发送1按钮有效
	m_Send2.EnableWindow(true);              //使发送2按钮有效
	m_Send3.EnableWindow(true);              //使发送3按钮有效
	m_Send4.EnableWindow(true);              //使发送4按钮有效
	m_Send5.EnableWindow(true);              //使发送5按钮有效
	m_Send6.EnableWindow(true);              //使发送6按钮有效
	m_Send7.EnableWindow(true);              //使发送7按钮有效

	CDialog::OnTimer(nIDEvent);
}
