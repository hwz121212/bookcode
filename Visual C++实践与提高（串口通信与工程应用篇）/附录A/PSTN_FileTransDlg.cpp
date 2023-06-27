// PSTN_FileTransDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PSTN_FileTrans.h"
#include "PSTN_FileTransDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSTN_FileTransDlg dialog

CPSTN_FileTransDlg::CPSTN_FileTransDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPSTN_FileTransDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPSTN_FileTransDlg)
	m_Com = 0;
	m_BaudRate =0;
	m_Parity = 0;
	m_Number = _T("0");
	m_Again = _T("0");
	m_Phone = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPSTN_FileTransDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPSTN_FileTransDlg)
	DDX_Control(pDX, IDC_DIS, m_Dis);
	DDX_Control(pDX, IDC_EXIT, m_Exit);
	DDX_Control(pDX, IDC_CLOSECOM, m_Closecom);
	DDX_Control(pDX, IDC_SENDFILE, m_Sendfile);
	DDX_Control(pDX, IDC_RCVFILE, m_Rcvfile);
	DDX_Control(pDX, IDC_OPENCOM, m_Opencom);
	DDX_CBIndex(pDX, IDC_COMBO_COM, m_Com);
	DDX_CBIndex(pDX, IDC_COMBO_B, m_BaudRate);
	DDX_CBIndex(pDX, IDC_COMBO_P, m_Parity);
	DDX_Text(pDX, IDC_NUMBER, m_Number);
	DDX_Text(pDX, IDC_AGAIN, m_Again);
	DDX_Text(pDX, IDC_PHONE, m_Phone);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPSTN_FileTransDlg, CDialog)
	//{{AFX_MSG_MAP(CPSTN_FileTransDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDC_OPENCOM, OnOpencom)
	ON_BN_CLICKED(IDC_CLOSECOM, OnClosecom)
	ON_BN_CLICKED(IDC_SENDFILE, OnSendfile)
	ON_BN_CLICKED(IDC_RCVFILE, OnRcvfile)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSTN_FileTransDlg message handlers

BOOL CPSTN_FileTransDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//创建控件的实例
	DWORD style=WS_VISIBLE|WS_CHILD;
	if (!myComm.Create(NULL,style,CRect(0,0,0,0),this,IDC_MSCOMM1))
	{
		AfxMessageBox("创建MSComm控件失败！");
		m_Opencom.EnableWindow(false);        //使“打开串口”按钮无效
		m_Closecom.EnableWindow(false);       //使“关闭串口”按钮无效
		return -1;
	}	
	m_Closecom.EnableWindow(false);
	bytSendNow=1;
	//bytSendLast=1;
	iSendCur=1;
	iSendStatus=100;
	iRcvStatus=200;
	iRelay=0;
	iActStatus=0;
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPSTN_FileTransDlg::OnPaint() 
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
HCURSOR CPSTN_FileTransDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPSTN_FileTransDlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	this->EndDialog(IDOK);
}

void CPSTN_FileTransDlg::OnOpencom() 
{
	// TODO: Add your control notification handler code here

	CString strPara,strTemp;
	double dblBaud;
	UpdateData(true);
	dblBaud=pow(2,(double)m_BaudRate);          //求取波特率
	dblBaud=19200/dblBaud;
	strTemp.Format("%.0f",dblBaud);
	strPara=strTemp;
	strPara+=",";

	switch(m_Parity)
	{
	case 0:
		{
		strTemp="N";
		break;
		}
	case 1:
		{
		strTemp="O";
		break;
		}
	case 2:
		{
		strTemp="E";
		break;
		}
	}
	strPara+=strTemp;
	strPara+=",8,1";
	//AfxMessageBox(strPara);
	myComm.SetCommPort(m_Com+1);             //指定串口号myCom
	myComm.SetSettings(strPara);             //通信参数设置
	myComm.SetInBufferSize(1024);            //指定接收缓冲区大小
	myComm.SetInBufferCount(0);              //清空接收缓冲区
	myComm.SetInputMode(1);                  //设置数据获取方式
	myComm.SetInputLen(0);                   //设置每次读取长度
	myComm.SetRThreshold(1);                 //设置接收OnComm事件门限值
	myComm.SetPortOpen(1);                   //打开串口
	m_Opencom.EnableWindow(false);           //使打开串口按钮无效
	m_Closecom.EnableWindow(true);           //使关闭串口按钮生效
	m_Exit.EnableWindow(false);              //使退出按钮无效
	GetDlgItem(IDC_COMBO_COM)->EnableWindow(false);
	GetDlgItem(IDC_COMBO_B)->EnableWindow(false);
	GetDlgItem(IDC_COMBO_P)->EnableWindow(false);
	m_Dis.SetSel(100000,100000);
	m_Dis.ReplaceSel("串口打开成功！\12\15");
	m_Dis.SetSel(100000,100000);
	m_Dis.ReplaceSel("\12\15");
	UpdateData(false);
}

void CPSTN_FileTransDlg::OnClosecom() 
{
	// TODO: Add your control notification handler code here
	myComm.SetPortOpen(0);
	m_Dis.SetSel(100000,100000);
	m_Dis.ReplaceSel("串口关闭成功！\12\15");
	m_Dis.SetSel(100000,100000);
	m_Dis.ReplaceSel("\12\15");
	UpdateData(false);
	m_Opencom.EnableWindow(true);           //使打开串口按钮生效
	m_Closecom.EnableWindow(false);         //使关闭串口按钮无效
	m_Exit.EnableWindow(true);              //使退出按钮生效
	GetDlgItem(IDC_COMBO_COM)->EnableWindow(true);
	GetDlgItem(IDC_COMBO_B)->EnableWindow(true);
	GetDlgItem(IDC_COMBO_P)->EnableWindow(true);

}

void CPSTN_FileTransDlg::OnSendfile() 
{
	// TODO: Add your control notification handler code here
	CFileDialog myFileDlg(true);          //打开文件对话框
	CFile myFile;
	CString myStr,myFileName,myPathName;
	CFileException e;                     //文件异常变量
	myFileDlg.m_ofn.lpstrFilter="*.TXT";
	myFileDlg.m_ofn.lpstrTitle="打开文本文件";
	if(myFileDlg.DoModal()==IDOK)         //调出文件选择对话框，选择传送的文件
	{
		myPathName=myFileDlg.GetPathName();
		myFileName=myFileDlg.GetFileName();
	}
	else
	{
		return;
	}
	myPathName.Replace("\\","\\\\");    //将文件名中的单“\”替换成双“\\”

	//打开选定的文件
	if(!myFile.Open(myPathName,CFile::modeRead,&e))
	{
		myStr.Format("%02X",e.m_cause); //文件打开错误处理，错误代码为m_cause
		myStr+="error";
		AfxMessageBox(myStr);
		return;
	}
	lFileLen=myFile.GetLength();
	if(lFileLen>=10240)                //检查文件尺寸<10K
	{
		m_Dis.SetSel(100000,100000);
		m_Dis.ReplaceSel("文件必须小于10K！\12\15");
		m_Dis.SetSel(100000,100000);
		m_Dis.ReplaceSel("\12\15");
		UpdateData(false);
		return;
	}
	myFile.Read(charSendData,lFileLen);
	myFile.Close();

	//正常使用时，应将该段程序取消注释，共8行代码。
	/*myStr="ATDT";
	UpdateData(true);
	myStr+=m_Phone;
	myStr+="\12\15";
	myComm.SetOutput(COleVariant(myStr));//发出拨号
	iActStatus=1;                        //进入发送态
	iSendStatus=101;                     //切换发送状态
	SetTimer(1,2000,NULL);               //启动超时定时器
	*/ //正常代码结束行

	//当无Modem测试程序时，使用该段代码，共4行。
	iActStatus=1;
	iSendStatus=102;
	iRcvStatus=200;
	SetTimer(1,2000,NULL);
	//无Modem测试代码结束行

	this->SetWindowText("发送文件");
	Beep(400,30);
}

BEGIN_EVENTSINK_MAP(CPSTN_FileTransDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CPSTN_FileTransDlg)
	ON_EVENT(CPSTN_FileTransDlg, IDC_MSCOMM1, 1 /* OnComm */, OnOnCommMscomm1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CPSTN_FileTransDlg::OnOnCommMscomm1() 
{
	// TODO: Add your control notification handler code here
	VARIANT input1;                          //定义一个VARIANT结构的变量
	BYTE rxdata[2048];                       //定义存放二进制数据的数组
	long len1,k;
	COleSafeArray safearray1;                //定义COleSafeArray类的实例
	int counts,i;
	CString input2;
	int	iParityTemp;
	CFileDialog myFileDlg(false);            //保存文件对话框
	CFile myFile;
	CString myStr,myFileName,myPathName;
	CFileException e;                        //文件异常变量

	KillTimer(1);                            //关闭超时定时器

	switch(myComm.GetCommEvent())
	{
	case 2://收到字符
		{
			switch(iActStatus)
			{
			case 1:                                           //发送操作状态
				{
					for(i=0;i<10;i++)                         //最大延时2秒钟
					{
						Sleep(200);                           //延时200ms
						counts=myComm.GetInBufferCount();     //获取接收缓冲区中的字符数
						if(iSendStatus==101)     //iSendStatus为101态时至少要接收2个字符
						{
							if (counts>=2)
								break;
						}
						else//iSendStatus为102～105态时只需要接收1个字符
						{
							if (counts>=1)
								break;

						}
						
					}
					if(i==10)
					{
						m_Dis.SetSel(100000,100000);
						m_Dis.ReplaceSel("超时错误！\12\15");
						m_Dis.SetSel(100000,100000);
						m_Dis.ReplaceSel("\12\15");
						UpdateData(false);
						return;
					}
					input1=myComm.GetInput();
					//将VARAIANT变量赋值给COleSafeArray类的实例
					safearray1=input1;            
					len1=safearray1.GetOneDimSize();//使用COleSafeArray类的成员函数获取数据长度
					for(k=0;k<len1;k++)
					//使用COleSafeArray类的成员函数将数据写入数组
						safearray1.GetElement(&k,rxdata+k);
					//AfxMessageBox(input2);
					switch(iSendStatus)
					{
					case 101:                                 //等待CONNECT ...
						{

							rxdata[len1]='\0';
							input2=rxdata;                    //得到接收的字符串
							input2.MakeUpper();               //接收字符串变为大写
							m_Dis.SetSel(100000,100000);      //更新显示内容
							m_Dis.ReplaceSel(input2);
							UpdateData(false);				
							if(input2.Find("CO")>=0)          //收到CONNECT 
							{
								iSendStatus=102;              //更改状态
							}
							break;
						}
					case 102:                                 //等待NAK ,然后发第1帧数据
						{
							
							if(rxdata[0]==21)                 //收到NAK 
							{
								m_Dis.SetSel(100000,100000);
								m_Dis.ReplaceSel("开始发送文件！\12\15");
								m_Dis.SetSel(100000,100000);
								m_Dis.ReplaceSel("\12\15");
								UpdateData(false);
								iSendCur=1;
								bytSendNow=1;
								charSendNow[0]=01;
								charSendNow[1]=01;
								charSendNow[2]=(char)0xFE;
								if(lFileLen<128)               //文件长度小于128字节，需补空格
								{
									for(i=0;i<lFileLen;i++)
									{
										charSendNow[i+3]=charSendData[i];
									}
									for(i=lFileLen;i<128;i++)
									{
										charSendNow[i+3]=32;   //补齐空格

									}
									iParityTemp=0;
									for(i=3;i<131;i++)
									{
										iParityTemp+=charSendNow[i];
									}
									iParityTemp=iParityTemp%256;
									charSendNow[131]=(char)iParityTemp;//求出校验位CheckSum
									ArraySend.RemoveAll();
									ArraySend.SetSize(132);
									for(i=0;i<132;i++)
									{
										ArraySend.SetAt(i,charSendNow[i]);
									}
									myComm.SetOutput(COleVariant(ArraySend)); 
									iSendStatus=104;

								}
								else
								{
									for(i=0;i<128;i++)              //直接获取完整的128字节内容
									{
										charSendNow[i+3]=charSendData[i];
									}
									iParityTemp=0;
									for(i=3;i<131;i++)
									{
										iParityTemp+=charSendNow[i];
									}
									iParityTemp=iParityTemp%256;
									charSendNow[131]=(char)iParityTemp;//求出校验位CheckSum
									ArraySend.RemoveAll();
									ArraySend.SetSize(132);
									for(i=0;i<132;i++)
									{
										ArraySend.SetAt(i,charSendNow[i]);
									}
									myComm.SetOutput(COleVariant(ArraySend)); //发送数据帧
									iSendStatus=103;                      //更改状态

								}

							} 
							SetTimer(1,2000,NULL);                //启动超时定时器
							break;
						}

					case 103:                                     //等待ACK，
						{

							switch(rxdata[0])
							{
							case 6:                               //响应是ACK
								{
									iSendCur++;
									myStr.Format("%d",iSendCur);
									m_Number=myStr;
									UpdateData(false);
									if(bytSendNow==255)
									{
										bytSendNow=0;
									}
									else
									{
										bytSendNow++;
									}

									if((iSendCur*128)>lFileLen)          //剩余数据不足128
									{
										charSendNow[0]=1;
										charSendNow[1]=bytSendNow;
										charSendNow[2]=255-charSendNow[1];

										for(i=0;i<(lFileLen%128);i++)
										{
											charSendNow[i+3]=charSendData[i+(iSendCur-1)*128];
										}
										for(i=(lFileLen%128);i<128;i++)
										{
											charSendNow[i+3]=32;         //补齐空格

										}
										iParityTemp=0;
										for(i=3;i<131;i++)
										{
											iParityTemp+=charSendNow[i];
										}
										iParityTemp=iParityTemp%256;
										charSendNow[131]=(char)iParityTemp;//求出校验位CheckSum
										ArraySend.RemoveAll();
										ArraySend.SetSize(132);
										for(i=0;i<132;i++)
										{
											ArraySend.SetAt(i,charSendNow[i]);
										}
										myComm.SetOutput(COleVariant(ArraySend)); 
										iSendStatus=104;
									}
									else//剩余数据不小于128
									{
										charSendNow[0]=1;
										charSendNow[1]=bytSendNow;
										charSendNow[2]=255-charSendNow[1];
										for(i=0;i<128;i++)              //直接获取完整的128字节内容
										{
											charSendNow[i+3]=charSendData[i+(iSendCur-1)*128];
										}
										iParityTemp=0;
										for(i=3;i<131;i++)
										{
											iParityTemp+=charSendNow[i];
										}
										iParityTemp=iParityTemp%256;
										charSendNow[131]=(char)iParityTemp;//求出校验位CheckSum
										ArraySend.RemoveAll();
										ArraySend.SetSize(132);
										for(i=0;i<132;i++)
										{
											ArraySend.SetAt(i,charSendNow[i]);
										}
										myComm.SetOutput(COleVariant(ArraySend)); //发送数据帧

									}
									break;
								}
							case 21://响应是NAK
								{
									//重发上次的数据帧
									myComm.SetOutput(COleVariant(ArraySend)); 
									break;

								}
							default:
								{
									m_Dis.SetSel(100000,100000);
									m_Dis.ReplaceSel("接收到无效的字符");
									UpdateData(false);
									iSendStatus=100;              //恢复初始状态
									iRcvStatus=200;
									iActStatus=0;
									return;                       //直接退出接收处理程序
									break;
								}
							}
							SetTimer(1,2000,NULL);                //启动超时定时器
							break;
						}
					case 104:                                    //等待ACK，发EOT
						{

							switch(rxdata[0])
							{
							case 6:                              //响应是ACK
								{

									ArraySend.RemoveAll();
									ArraySend.SetSize(1);
									ArraySend.SetAt(0,4);
									myComm.SetOutput(COleVariant(ArraySend)); 
									iSendStatus=105;

									break;
								}
							case 21:                             //响应是NAK
								{
									//重发上次的数据帧
									myComm.SetOutput(COleVariant(ArraySend)); 
									break;

								}
							default:
								{
									m_Dis.SetSel(100000,100000);
									m_Dis.ReplaceSel("接收到无效的字符！\12\15");
									m_Dis.SetSel(100000,100000);
									m_Dis.ReplaceSel("\12\15");
									UpdateData(false);
									iSendStatus=100;              //恢复初始状态
									iRcvStatus=200;
									iActStatus=0;
									return;                       //直接退出接收处理程序
									break;
								}
							}
							SetTimer(1,2000,NULL);                //启动超时定时器

							break;
						}
					case 105:                                     //等待ACK,结束通信
						{

							switch(rxdata[0])
							{
							case 6:                               //响应是ACK
								{

									m_Dis.SetSel(100000,100000);
									m_Dis.ReplaceSel("发送完毕！\12\15");
									m_Dis.SetSel(100000,100000);
									m_Dis.ReplaceSel("\12\15");
									UpdateData(false);

									//无Modem测试时，使用这段程序，共5行。
									iSendStatus=100;
									iSendCur=1;
									iActStatus=0;
									bytSendNow=1;
									Beep(400,30);
									//无Modem测试程序段结束

									//正常，有Modem时，使用这段程序，共9行。
									/*Sleep(1000);
									ArraySend.RemoveAll();
									ArraySend.SetSize(3);
									ArraySend.SetAt(0,43);                //发+++
									ArraySend.SetAt(1,43);                
									ArraySend.SetAt(2,43);                
									myComm.SetOutput(COleVariant(ArraySend)); 
									iSendStatus=106;                //切换状态至106
									SetTimer(1,2000,NULL);          //启动超时定时器
									*/
									//有Modem测试程序段结束

									break;
								}
							case 21:   //响应是NAK
								{
									//重发上次的数据帧
									myComm.SetOutput(COleVariant(ArraySend)); 
									SetTimer(1,2000,NULL);                //启动超时定时器							
									break;

								}
							default:
								{
									m_Dis.SetSel(100000,100000);
									m_Dis.ReplaceSel("接收到无效的字符！\12\15");
									m_Dis.SetSel(100000,100000);
									m_Dis.ReplaceSel("\12\15");
									UpdateData(false);
									iSendStatus=100;                     //恢复初始状态
									iRcvStatus=200;
									iActStatus=0;
									return;                              //直接退出接收处理程序
									break;
								}
							}
							break;
						}
					case 106:                                           //等待Modem回应，发挂机命令
						{
							//只要收到Modem的响应就执行挂机命令
							ArraySend.RemoveAll();
							ArraySend.SetSize(5);
							ArraySend.SetAt(0,65);                //发"ATH\12\15"
							ArraySend.SetAt(1,84);                //
							ArraySend.SetAt(2,72);                //
							ArraySend.SetAt(3,10);                //
							ArraySend.SetAt(4,13);                //
							myComm.SetOutput(COleVariant(ArraySend)); 

							iSendStatus=100;                      //恢复为初始状态
							iSendCur=1;
							iActStatus=0;
							bytSendNow=1;
							Beep(400,30);
							break;
						}
					}

					break;
				}
			case 2:                                               //接收操作状态
				{
					switch(iRcvStatus)
					{
					case 201:                                     //等待CONNECT...
						{

							for(i=0;i<10;i++)                     //最大延时2秒钟
							{
								Sleep(200);                       //延时200ms
								counts=myComm.GetInBufferCount(); //获取接收缓冲区中的字符数
								if (counts>=2)
								{
									break;
								}
							}
							if(i==10)
							{
								m_Dis.SetSel(100000,100000);
								m_Dis.ReplaceSel("超时错误！\12\15");
								m_Dis.SetSel(100000,100000);
								m_Dis.ReplaceSel("\12\15");
								UpdateData(false);
								iActStatus=0;
								iSendStatus=100;                   //恢复初始状态
								iRcvStatus=200;
								return;
							}
							input1=myComm.GetInput();
							//将VARAIANT变量赋值给COleSafeArray类的实例
							safearray1=input1;            
							len1=safearray1.GetOneDimSize();      //使用COleSafeArray类的成员函数获取数据长度
							for(k=0;k<len1;k++)
							//使用COleSafeArray类的成员函数将数据写入数组
								safearray1.GetElement(&k,rxdata+k);

							rxdata[len1]='\0';
							input2=rxdata;                           //得到接收的字符串
							input2.MakeUpper();                      //接收字符串变为大写
							m_Dis.SetSel(100000,100000);             //更新显示内容
							m_Dis.ReplaceSel(input2);
							UpdateData(false);				
							if(input2.Find("CO")>=0)                 //若收到CONNECT 
							{
								iRcvStatus=202;                      //更改状态
								ArraySend.RemoveAll();
								ArraySend.SetSize(1);
								ArraySend.SetAt(0,21);                //发NAK
								myComm.SetOutput(COleVariant(ArraySend)); 
							}

							SetTimer(1,2000,NULL);
							break;
						}
					case 202:                                         //等待第一帧数据
						{

							for(i=0;i<10;i++)                         //最大延时2秒钟
							{
								Sleep(200);                           //延时200ms
								counts=myComm.GetInBufferCount();     //获取接收缓冲区中的字符数
								if (counts>=132)
								{
									break;
								}
							}
							if(i==10)
							{
								m_Dis.SetSel(100000,100000);
								m_Dis.ReplaceSel("超时错误！\12\15");
								m_Dis.SetSel(100000,100000);
								m_Dis.ReplaceSel("\12\15");
								UpdateData(false);
								iActStatus=0;
								iSendStatus=100;               //恢复初始状态
								iRcvStatus=200;
								return;
							}
							input1=myComm.GetInput();
							//将VARAIANT变量赋值给COleSafeArray类的实例
							safearray1=input1;            
							len1=safearray1.GetOneDimSize();//使用COleSafeArray类的成员函数获取数据长度
							for(k=0;k<len1;k++)
							{
							//使用COleSafeArray类的成员函数将数据写入数组
								safearray1.GetElement(&k,rxdata+k);	

							}
							if(!(rxdata[0]==1 && rxdata[1]==1 && rxdata[2]==(BYTE)0xFE))
							{
								iAgain++;
								myStr.Format("%d",iAgain);
								m_Again=myStr;
								UpdateData(false);
								if (iAgain>10)
								{
									m_Dis.SetSel(100000,100000);
									m_Dis.ReplaceSel("重试次数超限！\12\15");
									m_Dis.SetSel(100000,100000);
									m_Dis.ReplaceSel("\12\15");
									UpdateData(false);
									iRcvStatus=200;                       //恢复初始状态
									iAgain=0;
									iActStatus=0;
									bytRcvNow=1;
									return;
								}
								else
								{
									ArraySend.RemoveAll();
									ArraySend.SetSize(1);
									ArraySend.SetAt(0,21);                //发NAK
									myComm.SetOutput(COleVariant(ArraySend)); 
								}

							}
							iParityTemp=0;
							for(i=3;i<131;i++)
							{
								iParityTemp+=rxdata[i];
							}
							iParityTemp=iParityTemp%256;
							if(rxdata[131]!=(BYTE)iParityTemp)            //若校验未通过
							{
								iAgain++;
								myStr.Format("%d",iAgain);
								m_Again=myStr;
								UpdateData(false);
								if (iAgain>10)
								{
									m_Dis.SetSel(100000,100000);
									m_Dis.ReplaceSel("重试次数超限！\12\15");
									m_Dis.SetSel(100000,100000);
									m_Dis.ReplaceSel("\12\15");
									UpdateData(false);
									iActStatus=0;
									iRcvStatus=200;                      //恢复初始状态
									iAgain=0;
									return;
								}
								else
								{
									ArraySend.RemoveAll();
									ArraySend.SetSize(1);
									ArraySend.SetAt(0,21);               //发NAK
									myComm.SetOutput(COleVariant(ArraySend)); 
								}

							}
							m_Dis.SetSel(100000,100000);
							m_Dis.ReplaceSel("开始接收文件！\12\15");
							m_Dis.SetSel(100000,100000);
							m_Dis.ReplaceSel("\12\15");
							UpdateData(false);
							iRcvCur=1;                                   //接收次数为1
							bytRcvNow=1;                                 //帧序号为1
							for(i=0;i<128;i++)
							{
								charRcvData[i]=rxdata[i+3];
							}
							iRcvStatus=203;
							ArraySend.RemoveAll();
							ArraySend.SetSize(1); 
							ArraySend.SetAt(0,6);                       //发ACK
							myComm.SetOutput(COleVariant(ArraySend)); 

							SetTimer(1,2000,NULL);
							break;
						}

					case 203:                                          //等待数据，包括完整帧和EOT帧
						{

							myComm.SetInputLen(1);                     //设置只读一个字符
							input1=myComm.GetInput();
							myComm.SetInputLen(0);                     //设置读全部缓冲区
							//将VARAIANT变量赋值给COleSafeArray类的实例
							safearray1=input1;    
							k=0;
							safearray1.GetElement(&k,rxdata);
							switch(rxdata[0])
							{
							case 4:                                    //收到EOT
								{

									//myStr="txt";
									myFileDlg.m_ofn.lpstrFilter="*.TXT";
									myFileDlg.m_ofn.lpstrDefExt="txt";
									myFileDlg.m_ofn.lpstrTitle="保存文本文件";
									//调出文件选择对话框，选择保存文件
									if(myFileDlg.DoModal()==IDOK)     
										
									{
										myPathName=myFileDlg.GetPathName();
										myFileName=myFileDlg.GetFileName();
									}
									else
									{
										iRcvStatus=200;
										iRcvCur=1;
										iAgain=0;
										bytRcvNow=1;
										m_Dis.SetSel(100000,100000);
										m_Dis.ReplaceSel("取消保存文件！\12\15");
										m_Dis.SetSel(100000,100000);
										m_Dis.ReplaceSel("\12\15");
										UpdateData(false);
										return;
									}
									myPathName.Replace("\\","\\\\");  //将文件名中的单“\”替换成双“\\”

									//打开选定的文件
									if(!myFile.Open(myPathName,CFile::modeWrite|CFile::modeCreate,&e))//
									{
										myStr.Format("%02X",e.m_cause);//文件打开错误处理，错误代码为m_cause
										myStr+="error";
										AfxMessageBox(myStr);
										return;
									}
									myFile.SetLength(0);//iRcvCur*128);
									myFile.Write(charRcvData,iRcvCur*128);
									myFile.Close();	
									m_Dis.SetSel(100000,100000);
									m_Dis.ReplaceSel("文件已保存！\12\15");
									m_Dis.SetSel(100000,100000);
									m_Dis.ReplaceSel("\12\15");
									UpdateData(false);

									ArraySend.RemoveAll();
									ArraySend.SetSize(1);
									ArraySend.SetAt(0,6);                //发ACK
									myComm.SetOutput(COleVariant(ArraySend)); 

									//无Modem测试时，使用这段代码，共6行。
									iRcvStatus=200;                     //恢复为初始状态
									iRcvCur=1;
									iActStatus=0;
									iAgain=0;
									bytRcvNow=1;
									Beep(400,30);
									//无Modem测试代码结束行

									//正常使用时，使用这段代码，共9行。
									/*Sleep(1000);
									ArraySend.RemoveAll();
									ArraySend.SetSize(3);
									ArraySend.SetAt(0,43);                //发+++
									ArraySend.SetAt(1,43);                //
									ArraySend.SetAt(2,43);                //
									myComm.SetOutput(COleVariant(ArraySend)); 
									iRcvStatus=204;                       //切换状态至204
									SetTimer(1,2000,NULL);                //启动超时定时器*/
									//正常使用代码结束行
									
									break;
								}
							case 1://收到SOH
								{
									
									for(i=0;i<10;i++)                         //最大延时2秒钟
									{
										Sleep(200);                           //延时200ms
										counts=myComm.GetInBufferCount();     //获取接收缓冲区中的字符数
										if (counts>=131)
										{
											break;
										}
									}
									if(i==10)
									{
										m_Dis.SetSel(100000,100000);
										m_Dis.ReplaceSel("超时错误！\12\15");
										m_Dis.SetSel(100000,100000);
										m_Dis.ReplaceSel("\12\15");
										UpdateData(false);
										iActStatus=0;
										iSendStatus=100;               //恢复初始状态
										iRcvStatus=200;
										return;
									}
									input1=myComm.GetInput();
									//将VARAIANT变量赋值给COleSafeArray类的实例
									safearray1=input1;            
									len1=safearray1.GetOneDimSize();//使用COleSafeArray类的成员函数获取数据长度
									for(k=0;k<len1;k++)
									{
									//使用COleSafeArray类的成员函数将数据写入数组
										safearray1.GetElement(&k,rxdata+k+1);
									}

									if(!(rxdata[0]==1 && (rxdata[1]+rxdata[2])==255))
									{
										
										iAgain++;
										myStr.Format("%d",iAgain);
										m_Again=myStr;
										UpdateData(false);
										if (iAgain>10)
										{
											m_Dis.SetSel(100000,100000);
											m_Dis.ReplaceSel("重试次数超限！\12\15");
											m_Dis.SetSel(100000,100000);
											m_Dis.ReplaceSel("\12\15");
											UpdateData(false);
											iRcvStatus=200;                 //恢复初始状态
											iAgain=0;
											iRcvCur=1;
											iActStatus=0;
											iSendStatus=100;               //恢复初始状态
											bytRcvNow=1;
											return;
										}
										else
										{
											ArraySend.RemoveAll();
											ArraySend.SetSize(1);
											ArraySend.SetAt(0,21);                //发NAK
											myComm.SetOutput(COleVariant(ArraySend)); 
										}

									}
									iParityTemp=0;
									for(i=3;i<131;i++)
									{
										iParityTemp+=rxdata[i];
									}
									iParityTemp=iParityTemp%256;
									if(rxdata[131]!=(BYTE)iParityTemp)  //若校验未通过
									{
										iAgain++;
										myStr.Format("%d",iAgain);
										m_Again=myStr;
										UpdateData(false);
										if (iAgain>10)
										{
											m_Dis.SetSel(100000,100000);
											m_Dis.ReplaceSel("重试次数超限！\12\15");
											m_Dis.SetSel(100000,100000);
											m_Dis.ReplaceSel("\12\15");
											UpdateData(false);
											iRcvStatus=200;                 //恢复初始状态
											iAgain=0;
											iRcvCur=1;
											iActStatus=0;
											bytRcvNow=1;
											return;
										}
										else
										{
											ArraySend.RemoveAll();
											ArraySend.SetSize(1);
											ArraySend.SetAt(0,21);                //发NAK
											myComm.SetOutput(COleVariant(ArraySend)); 
										}

									}

									if(rxdata[1]==bytRcvNow+1 ||(rxdata[1]==0 && bytRcvNow==255))
									{
										iRcvCur++;               //接收次数加1
										myStr.Format("%d",iRcvCur);
										m_Number=myStr;
										UpdateData(false);
										if(bytRcvNow<255)//帧序号加1
										{
											bytRcvNow++;
										}
										else
										{
											bytRcvNow=0;
										}

										for(i=0;i<128;i++)
										{
											charRcvData[i+(iRcvCur-1)*128]=rxdata[i+3];
										}
										ArraySend.RemoveAll();
										ArraySend.SetSize(1);
										ArraySend.SetAt(0,6);                //发ACK
										myComm.SetOutput(COleVariant(ArraySend)); 
										SetTimer(1,2000,NULL);											

									}
									else
									{
										if(rxdata[1]==bytRcvNow)
										{
											for(i=0;i<128;i++)
											{
												charRcvData[i+(iRcvCur-1)*128]=rxdata[i+3];
											}
											ArraySend.RemoveAll();
											ArraySend.SetSize(1);
											ArraySend.SetAt(0,6);                //发ACK
											myComm.SetOutput(COleVariant(ArraySend)); 
											SetTimer(1,2000,NULL);											
										}
									}

									break;

								}
							default:
								{
									SetTimer(1,2000,NULL);
									break;
								}
							}
							break;
						}
					case 204:
						{
							//只要收到Modem的响应就执行挂机命令
							ArraySend.RemoveAll();
							ArraySend.SetSize(5);
							ArraySend.SetAt(0,65);                //发"ATH\12\15"
							ArraySend.SetAt(1,84);                //
							ArraySend.SetAt(2,72);                //
							ArraySend.SetAt(3,10);                //
							ArraySend.SetAt(4,13);                //
							myComm.SetOutput(COleVariant(ArraySend)); 

							iRcvStatus=200;                        //恢复为初始状态
							iRcvCur=1;
							iAgain=0;
							bytRcvNow=1;
							Beep(400,30);

							break;

						}
					}

					break;
				}
			}
		}
	}

}

void CPSTN_FileTransDlg::OnRcvfile() 
{
	// TODO: Add your control notification handler code here
	//正常使用的代码，共9行。
	/*
	CString	myStr;
	myStr="ats0=1\12\15";              //自动应答
	myComm.SetOutput(COleVariant(myStr));
	m_Dis.SetSel(100000,100000);
	m_Dis.ReplaceSel("等待与对方联机...");
	UpdateData(false);
	iActStatus=2;
	iRcvStatus=201;                   //切换状态为201
	SetTimer(1,2000,NULL);            //启动超时定时器
	*/
	//正常使用代码结束行

	//无Modem测试使用的代码段，共8行。
	iActStatus=2;
	iRcvStatus=202;
	iSendStatus=100;
	ArraySend.RemoveAll();
	ArraySend.SetSize(1);
	ArraySend.SetAt(0,21);            //发NAK
	myComm.SetOutput(COleVariant(ArraySend)); 
	SetTimer(1,2000,NULL);
	//无Modem测试代码结束行-

	this->SetWindowText("接收文件");
	Beep(400,30);

}

void CPSTN_FileTransDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CString myStr;
	switch(iActStatus)
	{
	case 1:
		{
			switch(iSendStatus)
			{
				case 100:
					{
						break;
					}
				default:
					{
						iRelay++;
						if(iRelay>10)
						{
							m_Dis.SetSel(100000,100000);
							m_Dis.ReplaceSel("发送出错！\12\15");
							m_Dis.SetSel(100000,100000);
							m_Dis.ReplaceSel("\12\15");
							UpdateData(false);
							iSendStatus=100;
							iRelay=0;
							KillTimer(1);
						}
					}
			}
			break;
		}
	case 2:
		{
			switch(iRcvStatus)
			{
				case 200:
					{
						break;
					}
				case 202:
					{
						ArraySend.RemoveAll();
						ArraySend.SetSize(1);
						ArraySend.SetAt(0,21);
						myComm.SetOutput(COleVariant(ArraySend)); 
						iRelay++;
						if(iRelay>10)
						{
							m_Dis.SetSel(100000,100000);
							m_Dis.ReplaceSel("接收出错！\12\15");
							m_Dis.SetSel(100000,100000);
							m_Dis.ReplaceSel("\12\15");
							UpdateData(false);
							iSendStatus=200;
							iRelay=0;
							KillTimer(1);
						}

						break;
					}
				default:
					{
						iRelay++;
						if(iRelay>10)
						{
							m_Dis.SetSel(100000,100000);
							m_Dis.ReplaceSel("接收出错！\12\15");
							m_Dis.SetSel(100000,100000);
							m_Dis.ReplaceSel("\12\15");
							UpdateData(false);
							iSendStatus=200;
							iRelay=0;
							KillTimer(1);
						}
					}
			}
			break;
		}
	}
	CDialog::OnTimer(nIDEvent);
}
