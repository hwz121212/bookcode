// PC2PCView.cpp : implementation of the CPC2PCView class
//

#include "stdafx.h"
#include "PC2PC.h"

#include "PC2PCDoc.h"
#include "PC2PCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


HANDLE hCom;                                //串口的句柄
HANDLE hThreadEvent;                      //事件线程句柄
DWORD ThreadProcEvent(LPVOID pParam);      //事件响应函数
bool fEventRun;                            //事件线程函数执行标志
HWND hWnd;                                  //窗口句柄
DWORD dwThreadID;                          //事件线程ID
OVERLAPPED Eol={0};                       //事件线程使用的OVERLAPPED结构Eol
OVERLAPPED Wol={0};                       //写操作使用的OVERLAPPED结构Wol
OVERLAPPED Rol={0};                       //读操作使用的OVERLAPPED结构Rol
DWORD	dwTimeoutValue;					//定义接收超时时间，ms为单位,在事件线程中使用


/////////////////////////////////////////////////////////////////////////////
// CPC2PCView

IMPLEMENT_DYNCREATE(CPC2PCView, CEditView)

BEGIN_MESSAGE_MAP(CPC2PCView, CEditView)
	//{{AFX_MSG_MAP(CPC2PCView)
	ON_COMMAND(ID_SETUPCOM, OnSetupcom)
	ON_COMMAND(ID_SENDFILE, OnSendfile)
	ON_COMMAND(ID_OPENCOM, OnOpencom)
	ON_COMMAND(ID_CLOSECOM, OnClosecom)
	ON_UPDATE_COMMAND_UI(ID_SENDFILE, OnUpdateSendfile)
	ON_UPDATE_COMMAND_UI(ID_SETUPCOM, OnUpdateSetupcom)
	ON_UPDATE_COMMAND_UI(ID_OPENCOM, OnUpdateOpencom)
	ON_UPDATE_COMMAND_UI(ID_CLOSECOM, OnUpdateClosecom)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_UPDATE_COMMAND_UI(ID_APP_EXIT, OnUpdateAppExit)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MYMSG,OnReceiveEvent)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPC2PCView construction/destruction

CPC2PCView::CPC2PCView()
{
	// TODO: add construction code here
	myCom="COM4";            //默认设置
	myBaudRate=CBR_4800;
	myfParity=false;
	myParity=NOPARITY;
}

CPC2PCView::~CPC2PCView()
{
}

BOOL CPC2PCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CPC2PCView drawing

void CPC2PCView::OnDraw(CDC* pDC)
{
	CPC2PCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CPC2PCView diagnostics

#ifdef _DEBUG
void CPC2PCView::AssertValid() const
{
	CEditView::AssertValid();
}

void CPC2PCView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CPC2PCDoc* CPC2PCView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPC2PCDoc)));
	return (CPC2PCDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPC2PCView message handlers

void CPC2PCView::OnSetupcom() 
{
	// TODO: Add your command handler code here
	CString strStatus;
	if(mySetupDlg.DoModal()==IDOK)
	{
		switch (mySetupDlg.m_Com)
		{
		case 0:
			{
			strStatus="COM1";
			strStatus+="  ";
			myCom="COM1";
			break;
			}
		case 1:
			{
			strStatus="COM2";
			strStatus+="  ";
			myCom="COM2";
			break;
			}

		case 2:
			{
			strStatus="COM3";
			strStatus+="  ";
			myCom="COM3";
			break;
			}

		case 3:
			{
			strStatus="COM4";
			strStatus+="  ";
			myCom="COM4";
			break;
			}

		case 4:
			{
			strStatus="COM5";
			strStatus+="  ";
			myCom="COM5";
			break;
			}
		case 5:
			{
			strStatus="COM6";
			strStatus+="  ";
			myCom="COM6";
			break;
			}
		}
		switch(mySetupDlg.m_BaudRate)
		{

		case 0:
			{
			strStatus+="19200";
			strStatus+="  ";
			myBaudRate=CBR_19200;
			break;
			}
		case 1:
			{
			strStatus+="9600";
			strStatus+="  ";
			myBaudRate=CBR_9600;
			break;
			}
		case 2:
			{
			strStatus+="4800";
			strStatus+="  ";
			myBaudRate=CBR_4800;
			break;
			}
		case 3:
			{
			strStatus+="2400";
			strStatus+="  ";
			myBaudRate=CBR_2400;
			break;
			}
		}
		switch(mySetupDlg.m_Parity)
		{
		case 0:
			{
			myfParity=false;
			myParity=NOPARITY;
			strStatus+="N";
			strStatus+="-8-1";
			break;
			}
		case 1:
			{
			myfParity=TRUE;
			myParity=ODDPARITY;
			strStatus+="O";
			strStatus+="-8-1";
			break;
			}
		case 2:
			{
			myfParity=true;
			myParity=EVENPARITY;
			strStatus+="E";
			strStatus+="-8-1";
			break;
			}
		}

		CMainFrame* m_pGetFrame=(CMainFrame*) AfxGetApp()->m_pMainWnd ;
		CStatusBar* m_pStatus=&m_pGetFrame->m_wndStatusBar;
		m_pStatus->SetPaneText(1,strStatus);     //将通信参数显示在状态条上
		blnSeted=true;
		
	}
}

void CPC2PCView::OnSendfile() 
{
	// TODO: Add your command handler code here
	
	CFileDialog myFileDlg(true);      //打开文件对话框
	CEdit& myEdit=this->GetEditCtrl();
	BYTE bytFileNameLen;              //文件名字符串的长度
	BYTE bytTemp;
	DWORD dwTemp1,dwTemp2;
	int i;
	CString myStr,myFileName,myPathName;
	CFileException e;                 //文件异常变量
	bytActStatus=1;                   //置为发送态
	if(myFileDlg.DoModal()==IDOK)     //调出文件选择对话框，选择传送的文件
	{
		myPathName=myFileDlg.GetPathName();
		myFileName=myFileDlg.GetFileName();
		if(myFileName.GetLength()>100)
		{
			AfxMessageBox("文件名长度应小于100!");	
			bytActStatus=10;          //恢复为接收态
			return;
		}
		else
		{
			bytFileNameLen=(BYTE)myFileName.GetLength();
		}
	}
	else
	{
		bytActStatus=10;              //恢复为接收态

		return;
	}
	myPathName.Replace("\\","\\\\");  //将文件名中的单“\”替换成双“\\”

	//打开选定的文件
	if(!myFile.Open(myPathName,CFile::modeRead|CFile::typeBinary|CFile::shareDenyWrite,&e))
	{
		myStr.Format("%02X",e.m_cause);//文件打开错误处理，错误代码为m_cause
		myStr+="error";
		AfxMessageBox(myStr);
		bytActStatus=10;               //恢复为接收态
		return;
	}
	dwFileLen=myFile.GetLength();
	if(dwFileLen>=67108864)
	{
		AfxMessageBox("文件必须小于64M！");//检查文件尺寸<64兆
		bytActStatus=10;                //恢复为接收态
		return;
	}
	arrSendData[0]=05;                  //ENQ
	arrSendData[4]=(BYTE)(dwFileLen/16777216);
	dwTemp1=dwFileLen%16777216;
	arrSendData[3]=(BYTE)(dwTemp1/65536);
	dwTemp2=dwTemp1%65536;
	arrSendData[2]=(BYTE)(dwTemp2/256);
	arrSendData[1]=(BYTE)(dwTemp2%256);
	arrSendData[5]=bytFileNameLen;
	
	for(i=6;i<=bytFileNameLen+5;i++)    //存文件名称
	{
		arrSendData[i]=myFileName.GetAt(i-6);
	}
	
	bytTemp=0;

	for(i=0;i<=bytFileNameLen+5;i++)
	{
		bytTemp^=arrSendData[i];
	}
	arrSendData[bytFileNameLen+6]=bytTemp;//计算出校验位

	bytSendStatus=1;
	bytResendCount=0;

	Write(arrSendData,bytFileNameLen+7);
	myEdit.SetSel(1000000,1000000);
	myEdit.ReplaceSel("发出传输请求。\15\12");

	blnNoTimeout=false;

}

void CPC2PCView::OnOpencom() 
{
	// TODO: Add your command handler code here
	//打开串口操作
	hCom=CreateFile(myCom,              //打开串口COM2
		GENERIC_READ | GENERIC_WRITE, //使用读写方式
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, //使用重叠方式
		NULL);
	if( hCom !=INVALID_HANDLE_VALUE) 
	{
		SetupComm(hCom,1500,1500);      //设置发送缓冲512，接收缓冲区1500
		DCB myDCB;
		GetCommState( hCom, &myDCB ); //获取当前串口参数
		myDCB.BaudRate=myBaudRate;
		myDCB.fBinary=TRUE;
		myDCB.fParity=myfParity;
		myDCB.ByteSize=8;
		myDCB.Parity=myParity;
		myDCB.StopBits=ONESTOPBIT;
		SetCommState(hCom,&myDCB);     //设置串口通讯参数
		blnOpened=true;

		//创建并立即执行线程函数
		DWORD dwParam;
		if (!SetCommMask(hCom,EV_RXCHAR))// | EV_TXEMPTY))//设置允许的事件类型
		{
			AfxMessageBox("建立事件掩码失败！");
		}
		hThreadEvent=CreateThread(NULL,                 //创建事件线程
			0,
			(LPTHREAD_START_ROUTINE )ThreadProcEvent,   //指定线程函数名称
			&dwParam,
			0,                                               //创建线程函数后，立即执行
			&dwThreadID);
		if (hThreadEvent==INVALID_HANDLE_VALUE)
		{
			AfxMessageBox("事件线程创建失败！");
		}
		fEventRun=true;                                    //允许事件函数执行循环体
		bytActStatus=10;
		bytSendStatus=0;
		bytRcvStatus=0;
		bytResendCount=0;
		uintStxCurNo=0;
	}
	else
	{
		AfxMessageBox("创建串口失败！");
	}
	
}

void CPC2PCView::OnClosecom() 
{
	// TODO: Add your command handler code here
	fEventRun=false;                     //停止事件线程循环体的操作
	WaitForSingleObject(hThreadEvent,    //等待事件线程函数退出
		INFINITE);                        //无限时地等待，直到事件线程函数退出
	CloseHandle(hThreadEvent);        //关闭事件线程句柄
	CloseHandle(hCom);                  //关闭串口句柄
	blnOpened=false;
}

//事件线程函数
DWORD ThreadProcEvent(LPVOID pParam)
{
	DWORD dwErrors;
	COMSTAT Rcs;
	DWORD dwEvtMask,dwRes;
	Eol.hEvent=CreateEvent(NULL, //设置Eol.hEvent成员为无信号状态
		TRUE, 
		FALSE, 
		NULL);
	while(fEventRun)
	{
		WaitCommEvent(hCom,                            //监视串口事件
			&dwEvtMask,                                 //存放事件掩码组合值
			&Eol);                                       //OVERLAPPED结构
		dwRes=WaitForSingleObject(Eol.hEvent,        //等待的事件对象句柄
			dwTimeoutValue);                       //超时时间（ms）
		
		switch (dwRes)
		{
			case  WAIT_OBJECT_0:                      //成功得到事件监视结果
				{
					switch (dwEvtMask)
					{
					case EV_RXCHAR:                      //接收到数据
						{
							//向主线程发送消息，接收到数据
							ClearCommError(hCom,                //串口句柄
								&dwErrors,                        //存放出错信息的掩码组合
								&Rcs);                             //COMSTAT类型结构变量
							if(Rcs.cbInQue!=0)
							{
							::PostMessage(hWnd,         //目的窗口句柄
								WM_MYMSG,              //消息名称
								0,                      //传递的参数1
								(LPARAM)EV_RXCHAR );    //传递的参数2
							}
							break;
						}
					case EV_TXEMPTY:                    //发送缓冲区已空
						{
							   //这里可加入发送缓冲区空的处理代码，或向主线程发送消息
							break;
						}
					}
					break;
				}

			case WAIT_TIMEOUT:
				{
					//传递超时消息给主线程
					::PostMessage(hWnd,         //目的窗口句柄
						WM_MYMSG,              //消息名称
						0,                      //传递的参数1
						(LPARAM)100 );         //传递的参数100
					break;
				}
		}
	}
	return true;
}

//消息响应函数
LONG CPC2PCView::OnReceiveEvent(WPARAM wParam,LPARAM lParam)
{
	CFileDialog myFileDlg(false);         //保存文件对话框
	BYTE myByte[1100];
	BYTE bytTemp;
	CString strDis,strDis1;
	char *myChar;                       //获取文件名时使用
	char myName[300];
	char myExt[5];
	int i;
	CEdit& myEdit=this->GetEditCtrl();
	CMainFrame* m_pGetFrame=(CMainFrame*) AfxGetApp()->m_pMainWnd ;
	CStatusBar* m_pStatus=&m_pGetFrame->m_wndStatusBar;
	CFileException e;

	switch(bytActStatus)
	{
	case 1://发送操作
		{
			switch(bytSendStatus)//发送的不同状态
			{
			case 1://发送操作的1态
				{
					switch(lParam)
					{
					case EV_RXCHAR://lParam＝EV_RXCHAR即1，说明读线程收到数据
						{
							blnNoTimeout=true;
							bytTimeoutCounter=0;
							switch(Detect(1))
							{
							case 0://收到指定数量的字符
								{
									break;
								}
							case 4://超时错误
								{
									DisSend(4);
									blnNoTimeout=false;
									return -1;
									break;
								}

							case 8://无效，输入缓冲区中字符数量为0
								{
									blnNoTimeout=false;
									return 0;
									break;
								}

							}
							switch(Read(myByte,1))
							{
							case 0:
								{
									//继续后面的操作
									break;
								}
							case 4://超时错误
								{
									DisSend(4);
									return -1;
									break;
								}
							case 16://读操作失败
								{
									DisSend(16);
									return -1;
									break;
								}
							}
							switch(myByte[0])
							{
							case 6://响应是ACK吗？
								{
									//发送当前序号的数据
									uintStxCurNo=1;

									myEdit.SetSel(1000000,1000000);
									myEdit.ReplaceSel("正在传送数据...\15\12");

									if((uintStxCurNo*1024)<dwFileLen)
									{
										//
										arrSendData[0]=02;//STX，对应02
										arrSendData[1]=(BYTE)(uintStxCurNo%256);
										arrSendData[2]=(BYTE)(uintStxCurNo/256);
										uintSendLen=1+2+1024+1;
										myFile.Seek((uintStxCurNo-1)*1024,CFile::begin);
										myFile.Read(&arrSendData[3],1024);
										bytTemp=0;
										for(i=0;i<=1026;i++)
										{
											bytTemp^=arrSendData[i];
											arrSendDataLast[i]=arrSendData[i];
										}
										arrSendData[1027]=bytTemp;
										arrSendDataLast[1027]=arrSendData[1027];//保存本次发送的数据和数据个数
										uintSendLenLast=uintSendLen;
										Write(arrSendData,1028);
										bytSendStatus=2;
										bytResendCount=0;

									}
									else
									{
										arrSendData[0]=03;//ETX，对应03
										uintSendLen=1+2+2+(dwFileLen-(uintStxCurNo-1)*1024)+1;
										arrSendData[1]=(BYTE)((dwFileLen-(uintStxCurNo-1)*1024)%256);
										arrSendData[2]=(BYTE)((dwFileLen-(uintStxCurNo-1)*1024)/256);
										arrSendData[3]=(BYTE)(uintStxCurNo%256);
										arrSendData[4]=(BYTE)(uintStxCurNo/256);
										myFile.Read(&arrSendData[5],(dwFileLen-(uintStxCurNo-1)*1024));
										bytTemp=0;
										for(i=0;(UINT)i<=uintSendLen-2;i++)
										{
											bytTemp^=arrSendData[i];
											arrSendDataLast[i]=arrSendData[i];
										}
										arrSendData[uintSendLen-1]=bytTemp;
										arrSendDataLast[uintSendLen-1]=arrSendData[uintSendLen-1];//保存本次发送的数据和数据个数
										uintSendLenLast=uintSendLen;
										blnNoTimeout=false;
										bytSendStatus=3;
										Write(arrSendData,uintSendLen);
										bytResendCount=0;
									}
									break;
								}
							case 21://响应是NAK吗？
								{
									
									break;
								}
							case 24://响应是CAN吗？
								{
									DisSend(1);
									break;
								}
							default:
								{
									DisSend(2);//收到无效字符
									return -1;
									break;

								}
							}

							blnNoTimeout=false;      //允许超时
							break;
						}
					case 100://lParam=100，表示事件线程读超时
						{
							if((!blnNoTimeout)&&(bytTimeoutCounter>20))
							{
								DisSend(4);
								bytTimeoutCounter=0;
							}
							else
							{
								if(bytTimeoutCounter<255)//发送传输请求后，延时时间应该长些，
									bytTimeoutCounter++;//以留出让接收端选择保存文件位置需要的时间。

							}
							break;
						}
					}
					break;
				}
			case 2://发送操作的2态
				{
					switch(lParam)
					{
					case EV_RXCHAR://lParam＝EV_RXCHAR即1，说明读线程收到数据
						{
							blnNoTimeout=true;
							switch(Detect(1))
							{
							case 0://收到指定数量的字符
								{
									break;
								}
							case 4://超时错误
								{
									DisSend(4);
									blnNoTimeout=false;
									return -1;
									break;
								}

							case 8://无效，输入缓冲区中字符数量为0
								{
									blnNoTimeout=false;
									return 0;
									break;
								}

							}		
							switch(Read(myByte,1))
							{
							case 0:
								{
									//继续后面的操作
									break;
								}
							case 4://超时错误
								{
									DisSend(4);
									blnNoTimeout=false;
									return -1;
									break;
								}
							case 16://读操作失败
								{
									DisSend(16);
									blnNoTimeout=false;
									return -1;
									break;
								}
							}
							switch(myByte[0])
							{
							case 6://响应是ACK
								{
									//发送当前序号的数据

									uintStxCurNo++;//将发送序号加1

									if((uintStxCurNo*1024)<dwFileLen)//能组成完整的1024长的帧,以STX作为数据的起始位
									{
										
										arrSendData[0]=02;
										arrSendData[1]=(BYTE)(uintStxCurNo%256);
										arrSendData[2]=(BYTE)(uintStxCurNo/256);
										uintSendLen=1+2+1024+1;
										myFile.Seek((uintStxCurNo-1)*1024,CFile::begin);
										myFile.Read(&arrSendData[3],1024);
										bytTemp=0;
										for(i=0;i<=1026;i++)
										{
											bytTemp^=arrSendData[i];
											arrSendDataLast[i]=arrSendData[i];
										}
										arrSendData[1027]=bytTemp;
										arrSendDataLast[1027]=arrSendData[1027];//保存本次发送的数据和数据个数
										uintSendLenLast=uintSendLen;
										Write(arrSendData,uintSendLen);
										blnNoTimeout=false;
										bytSendStatus=2;
										bytResendCount=0;

										strDis.Format("已传送(%.0f%%)",(float)((uintStxCurNo+1)*1024)/dwFileLen*100);
										m_pStatus->SetPaneText(0,strDis);     //将传输进度显示在状态条上

									}
									else//不能组成完整的1024长的帧，以ETX作为数据的起始位。
									{
										
										arrSendData[0]=03;//ETX，对应03
										uintSendLen=1+2+2+(dwFileLen-(uintStxCurNo-1)*1024)+1;
										arrSendData[1]=(BYTE)((dwFileLen-(uintStxCurNo-1)*1024)%256);
										arrSendData[2]=(BYTE)((dwFileLen-(uintStxCurNo-1)*1024)/256);
										arrSendData[3]=(BYTE)(uintStxCurNo%256);
										arrSendData[4]=(BYTE)(uintStxCurNo/256);
										myFile.Read(&arrSendData[5],(dwFileLen-(uintStxCurNo-1)*1024));
										bytTemp=0;
										for(i=0;(UINT)i<=uintSendLen-2;i++)
										{
											bytTemp^=arrSendData[i];
											arrSendDataLast[i]=arrSendData[i];
										}
										arrSendData[uintSendLen-1]=bytTemp;
										arrSendDataLast[uintSendLen-1]=arrSendData[uintSendLen-1];//保存本次发送的数据和数据个数
										uintSendLenLast=uintSendLen;
										bytSendStatus=3;
										Write(arrSendData,uintSendLen);

										strDis="已传送(100%)";
										m_pStatus->SetPaneText(0,strDis);     //将传输进度显示在状态条上
										blnNoTimeout=false;
										bytResendCount=0;

									}
									break;
								}
							case 21://响应是NAK
								{
									
								
									break;
								}
							case 24://响应是CAN
								{
									
								
									break;
								}
							default:
								{
								
									break;
								}
							}

							blnNoTimeout=false;      //允许超时
							break;
						}
					case 100://lParam=100，表示事件线程读超时
						{
							//AfxMessageBox("time out");
							if(!blnNoTimeout)
							{
								DisSend(4);
							}
							break;
						}
					}
					break;
				}
			case 3://发送操作的3态
				{
					
					switch(lParam)
					{
					case EV_RXCHAR://lParam＝EV_RXCHAR即1，说明读线程收到数据
						{
							blnNoTimeout=true;
							switch(Detect(1))
							{
							case 0://收到指定数量的字符
								{
									break;
								}
							case 4://超时错误
								{
									DisSend(4);
									blnNoTimeout=false;
									return -1;
									break;
								}

							case 8://无效，输入缓冲区中字符数量为0
								{
									blnNoTimeout=false;
									return 0;
									break;
								}

							}		
							switch(Read(myByte,1))
							{
							case 0:
								{
									//继续后面的操作
									break;
								}
							case 4://超时错误
								{
									DisSend(4);
									blnNoTimeout=false;
									return -1;
									break;
								}
							case 16://读操作失败
								{
									DisSend(16);
									blnNoTimeout=false;
									return -1;
									break;
								}
							}
							if(myByte[0]==6)//响应是ACK吗？
							{

								myEdit.SetSel(1000000,1000000);
								myEdit.ReplaceSel("传送完毕！\15\12\15\12");

								strDis="已传送完毕";
								m_pStatus->SetPaneText(0,strDis);//将传输进度显示在状态条上
								if(myFile.m_pStream!=NULL)
								{
									myFile.Close();     //关闭打开的文件
								}
								uintStxCurNo=0;      //将发送序号清0
								bytSendStatus=0;
								bytResendCount=0;
								bytRcvStatus=0;
								bytActStatus=10;


							}
							else//响应不是ACK
							{
								if(myByte[0]==21)//响应是NAK吗？
								{
									bytResendCount++;
									if(bytResendCount>3)
									{
										DisSend(8);
										uintStxCurNo=0;//将发送序号清0
										bytActStatus=10;
										bytSendStatus=0;
										bytResendCount=0;

									}
									else
									{
										Write(arrSendDataLast,uintSendLenLast);

										strDis.Format("重发%d次！\15\12",bytResendCount);
										myEdit.SetSel(1000000,1000000);
										myEdit.ReplaceSel(strDis);
									}
								}
								else
								{
									DisSend(2);
									uintStxCurNo=0;//将发送序号清0
									bytActStatus=10;
									bytSendStatus=0;
									bytResendCount=0;
								}

							}

							blnNoTimeout=false;      //允许超时
							break;
						}
					case 100://lParam=100，表示事件线程读超时
						{
							if(!blnNoTimeout)
							{
								DisSend(4);
							}
							break;
						}
					}
					break;
				}
			}

			
			break;
		}
	case 10://接收状态
		{
			switch(bytRcvStatus)
			{
			case 0:
				{
					switch(lParam)
					{
					case EV_RXCHAR://收到数据
						{
							switch(Detect(6))
							{
							case 0://收到指定数量的字符
								{
									break;
								}
							case 4://超时错误
								{
									DisRcv(4);
									return -1;
									break;
								}

							case 8://无效，输入缓冲区中字符数量为0
								{
									return 0;
									break;
								}

							}

							switch(Read(myByte,6))
							{
							case 0://成功读出数据
								{
									//直接跳出switch，继续后面操作
									break;
								}
							case 4://超时错误
								{
									DisRcv(4);
									return -1;
									break;
								}
							case 16://读操作失败
								{
									DisRcv(16);
									return -1;
									break;
								}
							}
							//在这里处理读数据操作，数据存放在myByte中
							for(i=0;i<=5;i++)
							{
								arrRcvData[i]=myByte[i];
							}
							if(arrRcvData[0]==5)
							{
								//计算数据总长度
								uintRcvLen=arrRcvData[5]+7;
							}
							else
							{
								DisRcv(2);
								return -1;
							}
							switch(Read(myByte,arrRcvData[5]+1))
							{
							case 0:
								{
									//直接跳出switch，继续后面操作
									break;
								}
							case 4: 
								{
									DisRcv(4);
									return -1;
									break;
								}
							case 16:
								{
									DisRcv(16);
									return -1;
									break;
								}
							}
							for(i=0;i<=arrRcvData[5];i++)
							{
								arrRcvData[i+6]=myByte[i];//存储数据
							}

							//校验操作
							bytTemp=0;
							for(i=0;(UINT)i<=(uintRcvLen-2);i++)
							{
								bytTemp^=arrRcvData[i];
							}
							if(bytTemp!=arrRcvData[uintRcvLen-1])//若校验出错
							{
								bytResendCount++;
								if (bytResendCount>3)//重试次数大于3
								{
									DisRcv(8);
									return -1;
								}
								else
								{
									arrSendData[0]=21;
									Write(arrSendData,1);
									return -1;

								}
							}
							//至此，经过校验后，完整的数据已经存在arrRcvData[]数组中了
							myEdit.SetSel(1000000,1000000);
							myEdit.ReplaceSel("收到传输请求。\15\12");
							//获取文件名称
							if((myChar=new char[arrRcvData[5]+1])==NULL)
							{
								AfxMessageBox("分配堆内存时出错！");
								//向发送方回应CAN，以取消本次传送
								arrSendData[0]=24;
								Write(arrSendData,1);
								DisRcv(1);
								return -1;
							}

							for(i=0;i<=arrRcvData[5]-1;i++)
							{
								myChar[i]=arrRcvData[i+6];
							}
							myChar[arrRcvData[5]]='\0';
							strDis1=myChar;

							strcpy(myName,myChar);
							strDis="."+strDis1.Right(3);
							strDis+="\0\0";
							strcpy(myExt,strDis);
							delete []myChar;
							//打开对话框，提示用户保存文件	
							
							myFileDlg.m_ofn.lpstrFile=myName;
							myFileDlg.m_ofn.lpstrFilter=myExt;
							if(myFileDlg.DoModal()==IDOK)
							{
								strDis=myFileDlg.GetPathName();
							}
							else
							{
								//向发送方回应CAN，以取消本次传送
								arrSendData[0]=24;
								Write(arrSendData,1);
								DisRcv(1);
								return -1;
							}
							strDis.Replace("\\","\\\\");
							strDis+=myExt;
							if(!myFile.Open(strDis,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary,&e))
							{
								strDis.Format("文件打开时发生异常！错误代码为：%d。",e.m_cause);//文件打开错误处理，错误代码为m_cause
								//strDis+="error";
								AfxMessageBox(strDis);
								bytActStatus=10;                //恢复为接收态
								bytRcvStatus=0;
								bytSendStatus=0;
								return -1;
							}
							dwFileLen=arrRcvData[1]+arrRcvData[2]*256+arrRcvData[3]*65536+arrRcvData[4]*16777216;
							myFile.SetLength(dwFileLen);
							uintStxCurNo=1;
							bytRcvStatus=1;
							bytResendCount=0;

							arrSendData[0]=6;
							Write(arrSendData,1);

							break;
						}
					case 100://超时错误
						{
							//接收0态时，对超时不作处理
							break;
						}
					
					}
					break;
				}
			case 1:
				{
					switch(lParam)
					{
					case EV_RXCHAR://收到字符
						{
							switch(Detect(1))
							{
							case 0://收到指定数量的字符
								{
									break;
								}
							case 4://超时错误
								{
									DisRcv(4);
									return -1;
									break;
								}

							case 8://无效，输入缓冲区中字符数量为0
								{
									return 0;
									break;
								}

							}
							switch(Read(myByte,1))
							{
							case 0:
								{
									break;
								}
							case 4:
								{
									DisRcv(4);
									return -1;
									break;
								}
							case 16:
								{
									DisRcv(16);
									return -1;
									break;
								}
							}
							switch(myByte[0])//判断是STX还是ETX
							{
							case 2://首字符是STX
								{
									//读取数据
									arrRcvData[0]=myByte[0];
									uintRcvLen=1028;
									switch(Detect(1027))
									{
									case 0://收到指定数量的字符
										{
											//跳出switch，继续下面的操作
											break;
										}
									case 4://超时错误
										{
											DisRcv(4);
											return -1;
											break;
										}

									case 8://无效，输入缓冲区中字符数量为0
										{
											return 0;
											break;
										}
									}///
									switch(Read(myByte,1027))
									{
									case 0:
										{
											break;
										}
									case 4:
										{
											DisRcv(4);
											return -1;
											break;
										}
									case 16:
										{
											DisRcv(16);
											return -1;
											break;
										}
									}
									for(i=0;i<=1026;i++)
									{
										arrRcvData[i+1]=myByte[i];//保存数据至arrRcvData[]数组中
									}
									
									uintStxCurNo=arrRcvData[1]+arrRcvData[2]*256;
									if(uintStxCurNo==1)
									{
										myEdit.SetSel(1000000,1000000);
										myEdit.ReplaceSel("正在接收数据...\15\12");
									}
									strDis.Format("已接收(%.0f%%)",(float)((uintStxCurNo+1)*1024)/dwFileLen*100);
									m_pStatus->SetPaneText(0,strDis);     //将传输进度显示在状态条上
									myFile.Seek((uintStxCurNo-1)*1024,CFile::begin);
									myFile.Write(&arrRcvData[3],1024);

									bytResendCount=0;
									arrSendData[0]=6;
									Write(arrSendData,1);
									
									break;
								}

							case 3://首字符是ETX
								{
									//读取数据
									arrRcvData[0]=myByte[0];
									switch(Read(myByte,2))
									{
									case 0:
										{
											break;
										}
									case 4:
										{
											DisRcv(4);
											return -1;
											break;
										}
									case 16:
										{
											DisRcv(16);
											return -1;
											break;
										}
									}
									arrRcvData[1]=myByte[0];
									arrRcvData[2]=myByte[1];
									uintRcvLen=1+2+2+(arrRcvData[1]+arrRcvData[2]*256)+1;//数据总长度

									switch(Read(myByte,uintRcvLen-3))
									{
									case 0:
										{
											break;
										}
									case 4:
										{
											DisRcv(4);
											return -1;
											break;
										}
									case 16:
										{
											DisRcv(16);
											return -1;
											break;
										}
									}
									for(i=0;(UINT)i<=uintRcvLen-2;i++)
									{
										arrRcvData[i+3]=myByte[i];
									}
									//至此，完整数据已经读入arrRcvData[]中。
									uintStxCurNo=arrRcvData[3]+arrRcvData[4]*256;
									if(uintStxCurNo==1)
									{
										myEdit.SetSel(1000000,1000000);
										myEdit.ReplaceSel("正在接收数据...\15\12");
									}
									myFile.Seek((uintStxCurNo-1)*1024,CFile::begin);
									myFile.Write(&arrRcvData[5],arrRcvData[1]+arrRcvData[2]*256);

									myEdit.SetSel(1000000,1000000);
									myEdit.ReplaceSel("接收完毕！\15\12\15\12");
									strDis="已接收完毕";
									m_pStatus->SetPaneText(0,strDis);     //将传输进度显示在状态条上
									bytRcvStatus=0;
									bytActStatus=10;
									bytSendStatus=0;
									bytResendCount=0;
									arrSendData[0]=6;
									Write(arrSendData,1);
									if(myFile.m_pStream!=NULL)
									{
										myFile.Close();//关闭打开的文件
									}
									break;
								}
							}
							break;
						}
					case 100://超时错误
						{
							break;
						}
					}
					break;
				}
			}
			break;
		}//


	}
	return 0;
}

void CPC2PCView::OnUpdateSendfile(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (blnOpened)//根据串口是否打开，决定是否允许“发送文件”命令
	{
		if(!((bytSendStatus+bytRcvStatus)>0))//当前既没开始发送，也没开始接收
		{
			pCmdUI->Enable(true);
		}
		else
		{
			pCmdUI->Enable(false);
		}
	}
	else
	{
		pCmdUI->Enable(false);
	}
}

void CPC2PCView::OnUpdateSetupcom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (!blnOpened)//根据串口是否打开，决定是否允许“设置”命令
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
}

void CPC2PCView::OnUpdateOpencom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (!blnOpened && blnSeted)//根据串口是否打开，决定是否允许“打开”命令
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
}

void CPC2PCView::OnUpdateClosecom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (blnOpened)//根据串口是否打开，决定是否允许“关闭”命令
	{
		if(!((bytSendStatus+bytRcvStatus)>0))//当前既没开始发送，也没开始接收
		{
			pCmdUI->Enable(true);
		}
		else
		{
			pCmdUI->Enable(false);
		}
	}
	else
	{
		pCmdUI->Enable(false);
	}
}

int CPC2PCView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CEdit& myEdit=this->GetEditCtrl( );
	myEdit.SetReadOnly (true);                         //将显示区域设为只读
	hWnd=GetSafeHwnd();                                    //获取当前窗口的句柄

	blnOpened=false;     //串口已经打开标志
	blnSeted=false;      //已经设置过通信参数
	bytRcvStatus=0;      //初始化时，接收状态为等待ENQ
	dwTimeoutValue=1500; //初始化事件线程超时时间
	bytActStatus=10;     //初始化为接收态
	blnNoTimeout=true;
	uintStxCurNo=0;
	bytTimeoutCounter=0;
	return 0;
}
bool CPC2PCView::DisSend(BYTE bytType)//发送态显示信息函数，bytType决定显示信息的内容
{
	CString strDis;
	CEdit& myEdit=this->GetEditCtrl();
	myEdit.SetReadOnly(true);
	myEdit.SetSel(1000000,1000000);
	switch(bytType)
	{
	case 1:
		{
			strDis="取消操作！\15\12";
			break;
		}
	case 2:
		{
			strDis="收到无效的命令！\15\12";
			break;
		}
	case 4:
		{
			strDis="对方无响应，超时错误！\15\12";
			break;
		}
	case 8:
		{
			strDis="重试次数多于3次！\15\12";
			break;
		}
	}
		
	myEdit.ReplaceSel(strDis);
	bytSendStatus=0;//恢复发送0态
	bytActStatus=10;//恢复为接收态
	bytRcvStatus=0;
	bytResendCount=0;//重试次数初始化为0
	if(myFile.m_pStream!=NULL)
	{
		myFile.Close();//关闭打开的文件
	}
	Beep(1000,50);
	return true;

}
bool CPC2PCView::DisRcv(BYTE bytType)//接收态显示信息函数，bytType决定显示信息的内容
{
	CString strDis;
	CEdit& myEdit=this->GetEditCtrl();
	myEdit.SetReadOnly(true);
	myEdit.SetSel(1000000,1000000);
	switch(bytType)
	{
	case 1:
		{
			strDis="取消操作！\15\12";
			break;
		}
	case 2:
		{
			strDis="收到无效的命令！\15\12";
			break;
		}
	case 4:
		{
			strDis="对方无响应，超时错误！\15\12";
			break;
		}
	case 8:
		{
			strDis="重试次数多于3次！\15\12";
			break;
		}
	}
		
	myEdit.ReplaceSel(strDis);
	bytRcvStatus=0;           //恢复接收0态
	bytActStatus=10;          //恢复为接收态
	bytSendStatus=0;          //发送态恢复为0态
	bytResendCount=0;         //重试次数初始化为0
	if(myFile.m_pStream!=NULL)
	{
		myFile.Close();       //关闭打开的文件
	}
	return true;
}
BYTE CPC2PCView::Read(BYTE arrBin[],int count)//读数据函数，arrBin[]存放数据，count是读的个数
{									//成功返回0，读失败返回16，超时错误返回4
	DWORD dwRes;
	DWORD dwRead;
	Rol.hEvent=CreateEvent(NULL, //创建Rol.hEvent为无信号状态
		TRUE,                 
		FALSE, 
		NULL);
	if (ReadFile(hCom,
		arrBin,
		count,                     //读取count个字节
		NULL,
		&Rol))
	{
		 //串口接收的数据已经成功读出，并存放在arrBin[]数组中
		return 0;
	}
	else
	{
		dwRes = WaitForSingleObject(Rol.hEvent, 
			2000);                      //设置2秒的读超时
		switch(dwRes)
		{
		case WAIT_OBJECT_0:
			{
				 if (!GetOverlappedResult(hCom, 
						&Rol, 
						&dwRead,             //实际读取字节数存放在dwRead中
						TRUE))
				 {   
					 //读操作失败。使用GetLastError（）函数可以获取错误消息
						return 16;
				 }
				 else
				 {
					   //串口接收的数据已经成功读出，并存放在arrBin[]数组中
					 return 0;
				 }
				 break;
			}
		case WAIT_TIMEOUT:
			{
				//读操作出现超时错误。
				return 4;
			}
		}
	}
	return 0;
}



//发送数据函数，arrBin[]存放数据，count是发送个数
//发送态时，发送数据调用这个函数
//接收态时，响应时调用这个函数发送响应代码ACK、NAK或CAN
bool CPC2PCView::Write(BYTE arrBin[],int count)
{
	DWORD	dwWrite;
	Wol.hEvent=CreateEvent(NULL, //创建Wol.hEvent事件句柄，并设置为无信号状态
		TRUE, 
		FALSE, 
		NULL);
	WriteFile(hCom,                //写数据，通过Wol结构获取操作结果
		arrBin,
		count,
		NULL,
		&Wol);
	if(GetOverlappedResult(hCom,&Wol,&dwWrite,true))
	{
		return true;
	}
	return false;

}
//检测串口输入缓冲区中是否有指定个数的数据
//返回0－有，4－超时错误,8-无效
BYTE CPC2PCView::Detect(int count)
{
	DWORD dwErrors;
	COMSTAT Rcs;
	CString strDis,strDis1;
	BYTE bytTimeCount;
	ClearCommError(hCom,                  //串口句柄
		&dwErrors,                        //存放出错信息的掩码组合
		&Rcs);                             //COMSTAT类型结构变量
	if(Rcs.cbInQue==0)
		return 8;
	bytTimeCount=0;
	while(bytTimeCount<4)
	{
		ClearCommError(hCom,                //串口句柄
			&dwErrors,                        //存放出错信息的掩码组合
			&Rcs);                             //COMSTAT类型结构变量
		if(Rcs.cbInQue>=(UINT)count)
		{
			return 0;//在输入缓冲区中找到指定数量的字符
		}
		Sleep(500);
		bytTimeCount++;
	}
	if((bytTimeCount>=4)&&(Rcs.cbInQue>0))//超时错误
	{
		return 4;//未找到
	}
	return 8;//无效状态，输入缓冲区中为0个字符
}

void CPC2PCView::OnDestroy() 
{
	
	CEditView::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CPC2PCView::OnUpdateAppExit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (!blnOpened)          //根据串口是否打开，决定是否允许“退出”命令
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
}
