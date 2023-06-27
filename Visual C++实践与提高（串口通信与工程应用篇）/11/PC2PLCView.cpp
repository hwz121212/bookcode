// PC2PLCView.cpp : implementation of the CPC2PLCView class
//

#include "stdafx.h"
#include "PC2PLC.h"

#include "PC2PLCDoc.h"
#include "PC2PLCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//定义全局变量
HANDLE hCom;                               //串口句柄
DWORD ThreadProcWrite(LPVOID pParam);      //写线程函数
DWORD ThreadProcRead(LPVOID pParam);       //读线程函数
OVERLAPPED Wol={0};                        //写操作OVERLAPPED结构变量
OVERLAPPED Rol={0};                        //读操作OVERLAPPED结构变量
HANDLE hThreadWrite;                       //写线程句柄
HANDLE hThreadRead;                        //读线程句柄
HWND hWnd;                                 //窗口句柄

BYTE myRByte[300];                         //存放已读数据
BYTE myWByte[300];                         //存放欲写数据
 
long dataRLen;                             //接收数据的长度
long dataWLen;                             //发送数据的长度

bool blnError;                             //错误标志，在接收命令代码中使用
int	intWrite=0;                            //反映写操作的状态，0－无意义，1－写错误，2－写正确
int intRead=0;                             //反映读操作的状态，0－无意义，1－读错误，2－读正确


/////////////////////////////////////////////////////////////////////////////
// CPC2PLCView

IMPLEMENT_DYNCREATE(CPC2PLCView, CEditView)

BEGIN_MESSAGE_MAP(CPC2PLCView, CEditView)
	//{{AFX_MSG_MAP(CPC2PLCView)
	ON_COMMAND(ID_SETUP, OnSetup)
	ON_COMMAND(ID_RECEIVE, OnReceive)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_UPDATE_COMMAND_UI(ID_RECEIVE, OnUpdateReceive)
	ON_COMMAND(ID_OPENCOM, OnOpencom)
	ON_UPDATE_COMMAND_UI(ID_SETUP, OnUpdateSetup)
	ON_UPDATE_COMMAND_UI(ID_OPENCOM, OnUpdateOpencom)
	ON_UPDATE_COMMAND_UI(ID_CLOSECOM, OnUpdateClosecom)
	ON_COMMAND(ID_CLOSECOM, OnClosecom)
	ON_UPDATE_COMMAND_UI(ID_APP_EXIT, OnUpdateAppExit)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPC2PLCView construction/destruction

CPC2PLCView::CPC2PLCView()
{
	// TODO: add construction code here
	myCom="COM4";                      //默认设置
	myBaudRate=CBR_4800;
	myfParity=false;
	myParity=NOPARITY;

}

CPC2PLCView::~CPC2PLCView()
{
}

BOOL CPC2PLCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping


	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CPC2PLCView drawing

void CPC2PLCView::OnDraw(CDC* pDC)
{
	CPC2PLCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CPC2PLCView diagnostics

#ifdef _DEBUG
void CPC2PLCView::AssertValid() const
{
	CEditView::AssertValid();
}

void CPC2PLCView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CPC2PLCDoc* CPC2PLCView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPC2PLCDoc)));
	return (CPC2PLCDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPC2PLCView message handlers

void CPC2PLCView::OnSetup() 
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
			}
			break;
		case 5:
			{
			strStatus="COM6";
			strStatus+="  ";
			myCom="COM6";
			}
			break;
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
		m_pStatus->SetPaneText(1,strStatus);            //将通信参数显示在状态条上
		
	}
}
//*******************************************
//***接收操作代码*************************
//********************************************
void CPC2PLCView::OnReceive() 
{
	// TODO: Add your command handler code here
	int i,j;
	CString strDis,strTemp;
	char myChar[20];
	BYTE xorByte;                                     //存放奇偶校验和
	PurgeComm(hCom,PURGE_RXCLEAR);                    //清空接收和发送缓冲区
	PurgeComm(hCom,PURGE_TXCLEAR);
	myWByte[0]=5;
	dataWLen=1;
	CEdit& myEdit=this->GetEditCtrl( );
	myEdit.SetSel(1000000,1000000);

	strDis="";
	strDis+="<-- [ENQ] ";
	_strdate(myChar);
	strDis+=myChar;
	strDis+=" ";
	_strtime(myChar);
	strDis+=myChar;
	strDis+="\15\12";
	myEdit.ReplaceSel(strDis);
	intWrite=0;
	if (!myfuncWrite())                              //发出ENQ读数据请求
	{
		myEdit.SetSel(1000000,1000000);
		strDis="";
		strDis+="   通信错误\15\12\15\12";
		myEdit.ReplaceSel(strDis);
		Beep(1000,50);
		return;
	}

	dataRLen=3;
	intRead=0;
	if(myfuncRead(5))                                //读数据，应该为“ACK，长度，长度取反值”
	{
		strDis="--> ";
		for(i=0;i<=2;i++)
		{
			strTemp.Format("%02X",myRByte[i]);      //将16进制数格式化为2位形式
			strDis+=strTemp;
			strDis+="|";
		}
		myEdit.SetSel(1000000,1000000);
		strDis+="\15\12";
		strDis.MakeUpper();
		myEdit.ReplaceSel(strDis);                 //显示接收到的数据

	}
	else//若出错，说明通信故障，退出此次读数据操作
	{
		blnError=true;
		myEdit.SetSel(1000000,1000000);
		strDis="";
		strDis+="   通信错误\15\12\15\12";
		myEdit.ReplaceSel(strDis);
		Beep(1000,50);
		return;
	}
	for(i=0;i<3;i++)                               //对数据进行3次校验
	{
		if((myRByte[0]==6) && ((myRByte[1]+myRByte[2])==255))
		{
			blnError=false;
			break;
		}
		else
		{
			blnError=true;
		}
		myWByte[0]=21;
		dataWLen=1;
		intWrite=0;
		myEdit.SetSel(1000000,1000000);
		strDis="";
		strDis+="<-- [NAK]\15\12";
		myEdit.ReplaceSel(strDis);
		if(!myfuncWrite())                        //若校验未通过，则回应NAK，要求重发
		{
			blnError=true;
			break;
		}
		dataRLen=3;
		intRead=0;
		if(myfuncRead(21))//再次读取数据，应该为“ACK，长度，长度取反值”
		{
			strDis="--> ";
			strTemp.Format("%02X",myRByte[0]);
			strDis+=strTemp;
			strDis+="|";
			strTemp.Format("%02X",myRByte[1]);
			strDis+=strTemp;
			strDis+="|";
			strTemp.Format("%02X",myRByte[2]);
			strDis+=strTemp;
			myEdit.SetSel(1000000,1000000);
			strDis+="\15\12";
			strDis.MakeUpper();
			myEdit.ReplaceSel(strDis);//
		}
		else
		{
			blnError=true;
			myEdit.SetSel(1000000,1000000);
			strDis="";
			strDis+="   通信错误\15\12\15\12";
			strDis.MakeUpper();
			myEdit.ReplaceSel(strDis);
			Beep(1000,50);
			return;
		}

	}


	if (blnError)//若出错，说明通信存在故障，则退出本次操作
	{
		myEdit.SetSel(1000000,1000000);
		strDis="";
		strDis+="   通信错误\15\12\15\12";
		strDis.MakeUpper();
		myEdit.ReplaceSel(strDis);
		Beep(1000,50);
		blnError=false;
		return;
	}
	//正常通信，继续进行
	myWByte[0]=6;                                 //收到长度及其取反值，且校验正确，回应ACK
	dataWLen=1;
	myEdit.SetSel(1000000,1000000);
	strDis="";
	strDis+="<-- [ACK]\15\12";
	strDis.MakeUpper();
	myEdit.ReplaceSel(strDis);
	intWrite=0;
	if (!myfuncWrite())
	{
		myEdit.SetSel(1000000,1000000);
		strDis="";
		strDis+="   通信错误\15\12\15\12";
		strDis.MakeUpper();
		myEdit.ReplaceSel(strDis);
		Beep(1000,50);
		return;
	}

	//回应ACK成功，等待接收数据
	dataRLen=myRByte[1]+1;
	for(i=0;i<3;i++)                            //若1次未读出正确数据，则重新操作，共循环3次
	{
		intRead=0;
		if(myfuncRead(21))
		{

			strDis="--> ";
			xorByte=0;
			for(j=0;j<=dataRLen-2;j++)
			{
				strTemp.Format("%02X",myRByte[j]);
				strDis+=strTemp;
				strDis+="|";
				xorByte^=myRByte[j];
			}
			strTemp.Format("%02X",myRByte[dataRLen-1]);
			strDis+=strTemp;
			myEdit.SetSel(1000000,1000000);
			strDis+="\15\12";
			strDis.MakeUpper();
			myEdit.ReplaceSel(strDis);         //显示接收到的数据

			if(myRByte[dataRLen-1]==xorByte)   //校验数据
			{
				
				blnError=false;
				break;
			}
			else
			{
				blnError=true;
			}
		}
		else
		{
			blnError=true;
			break;
		}
		myWByte[0]=21;
		dataWLen=1;
		intWrite=0;
		myEdit.SetSel(1000000,1000000);
		strDis="";
		strDis+="<-- [NAK]\15\12";
		strDis.MakeUpper();
		myEdit.ReplaceSel(strDis);
		if(!myfuncWrite())                    //数据校验出错，响应NAK，要求重发
		{
			blnError=true;
			break;
		}

	}
	if (blnError)//若blnError被置1，说明通信存在故障，则退出本次操作
	{
		myEdit.SetSel(1000000,1000000);
		strDis="";
		strDis+="   通信错误\15\12\15\12";
		strDis.MakeUpper();
		myEdit.ReplaceSel(strDis);
		Beep(1000,50);
		blnError=false;
		return;
	}
	//数据已经读回，并且已经校验正确
	myWByte[0]=6;                          //回应ACK
	dataWLen=1;
	myEdit.SetSel(1000000,1000000);
	strDis="";
	strDis+="<-- [ACK]\15\12";
	strDis.MakeUpper();
	myEdit.ReplaceSel(strDis);
	intWrite=0;
	if (!myfuncWrite())
	{
		myEdit.SetSel(1000000,1000000);
		strDis="";
		strDis+="   通信错误\15\12\15\12";
		myEdit.ReplaceSel(strDis);
		Beep(1000,50);
		return;
	}
	myEdit.SetSel(1000000,1000000);
	strDis="";
	strDis+="   接收完毕！\15\12\15\12";
	myEdit.ReplaceSel(strDis);           //显示成功信息
	Beep(1000,50);
	
}

int CPC2PLCView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CEdit& myEdit=this->GetEditCtrl( );
	myEdit.SetReadOnly (true);          //将显示区域设为只读
	hWnd=GetSafeHwnd();                 //获取当前窗口的句柄
	blnOpened=false;
	return 0;
}

//*****************************
//****读线程函数****************
//*****************************
DWORD  ThreadProcRead(LPVOID pParam)
{
	
	CString myStr;
	DWORD dwRes;
	DWORD dwRead;                      //实际读出的字节数
	intRead=0;
	Rol.hEvent=CreateEvent(NULL,       //创建Rol的hEvent成员为无信号状态
			TRUE, 
			FALSE, 
			NULL);
	if (Rol.hEvent == NULL)
	{
		AfxMessageBox("hEvent空");
		intRead=1;
         return -1;
	}
	if (ReadFile(hCom,               //串口句柄
			&myRByte,                //存放读取数据
			dataRLen,                //欲读取的字节数
			NULL,
			&Rol))                   //指向创建hCom时的Rol的指针
	{
		intRead=2;

         //在这里加入处理已读取数据的代码，已读取数据存放在myRByte数组中。
	}
	else
	{
		dwRes = WaitForSingleObject(Rol.hEvent, 
				2000);              //设置2秒的超时
		switch(dwRes)
		{
		case WAIT_OBJECT_0:
			 if (!GetOverlappedResult(hCom, 
					&Rol, 
					&dwRead,        //实际读出的字节数
					TRUE))          //TRUE表示直到操作完成该函数才返回
			 {   
				 //操作失败，可以使用GetLastError（）函数获取错误信息。
				intRead=1;

			}
			else
			{
			    //操作成功完成，数据读出，并存放到myRByte数组中。
                //在这里加入处理数据的代码
				intRead=2;
			 }
			 break;
		case WAIT_TIMEOUT:
			//读操作失败，原因是读超时。
			intRead=1;
			break;
		default:
			 //这里可以加入默认情况下的处理代码。
			 intRead=1;
			 break;
		}
	}
	CloseHandle(Rol.hEvent);
	return 0;
}

//*****************************
//****写线程函数****************
//*****************************
DWORD  ThreadProcWrite(LPVOID pParam)
{
	CString myStr;
	DWORD dwRes;
	DWORD dwWrite;
	intWrite=0;
	Wol.Internal=0;                //设置OVERLAPPED结构Wol
	Wol.InternalHigh=0;
	Wol.Offset=0;
	Wol.OffsetHigh=0;
	Wol.hEvent=CreateEvent(NULL,   //创建Wol的hEvent成员为无信号状态
         TRUE,
         FALSE,
         NULL);
	if (Wol.hEvent == NULL)
	{
		AfxMessageBox("hEvent空");
		intWrite=1;
         return -1;
	}
	if (WriteFile(hCom,           //串口句柄
			&myWByte,             //存放待发送数据
			dataWLen,             //欲发送的字节数
			NULL,
			&Wol))                //指向创建hCom时的Wol的指针
	{
         //在这里加入成功发送的处理代码。
		intWrite=2;

	}
	else
	{
		dwRes = WaitForSingleObject(Wol.hEvent,
				 500);           //设置写超时500ms
		switch(dwRes)
		{
		case WAIT_OBJECT_0:
			 if (!GetOverlappedResult(hCom, 
					&Wol, 
					&dwWrite, 
					TRUE))
			 {   
				intWrite=1;
				//操作失败，可以使用GetLastError（）函数获取错误信息。
			 }
			 else
			 {
				//发送数据成功
				intWrite=2;
				//在这里加入发送成功的处理代码
			 }
			 break;
		case WAIT_TIMEOUT:
			//发送失败，原因是发送超时
			intWrite=1;
			break;
		default:
			//这里可以加入默认情况下的处理代码。
			intWrite=1;
			break;
		}
	}
	CloseHandle(Wol.hEvent);
	return 0;
}

void CPC2PLCView::OnDestroy() 
{
	CEditView::OnDestroy();
	if(!(hCom==NULL))
	{
		CloseHandle(hCom);           //关闭串口句柄
	}
	// TODO: Add your message handler code here
	
}

bool  CPC2PLCView::myfuncWrite()
{
	//写串口操作
	DWORD dwThreadID;//
	DWORD dwParam;
	int	 i;
	for(i=0;i<3;i++)
	{
		hThreadWrite=CreateThread(NULL,
			0,
			(LPTHREAD_START_ROUTINE )ThreadProcWrite, //写线程函数名称
			&dwParam,
			0,                                        //创建线程后，立即执行该线程
			&dwThreadID);
		if (hThreadWrite==NULL)
		{
			AfxMessageBox("写线程创建失败！");
			intWrite=1;
			return false;
		}
		while (intWrite==0)
		{
			Sleep(100);                              //等待写操作结果
		}
		if (intWrite==2)
		{
			return true;
		}
	}
	
	return false;
}

bool	CPC2PLCView::myfuncRead(BYTE ackChar)
{
	//读串口操作代码
	DWORD dwThreadID;
	DWORD dwParam;
	CString strDis;
	int i;
	for(i=0;i<3;i++)
	{
		hThreadRead=CreateThread(NULL,
				0,
				(LPTHREAD_START_ROUTINE )ThreadProcRead,//读线程函数名称
				&dwParam,
				0,                                      //创建线程后，立即执行该线程
				&dwThreadID);
		if (hThreadRead==NULL)
		{
			AfxMessageBox("读线程创建失败！");
			intRead=1;
			return false;
		}
		while (intRead==0)
		{
			Sleep(100);                                //等待读操作结果
		}
		if (intRead==2)
		{
			return true;
		}
		else
		{
			myWByte[0]=ackChar;                       //发送ENQ或NAK（ascii码为5或21）
			dataWLen=1;
			CEdit& myEdit=this->GetEditCtrl( );
			myEdit.SetSel(1000000,1000000);
			strDis="";
			switch(ackChar)
			{
			case 5:
				{
				strDis+="<-- [ENQ]\15\12";
				break;
				}
			case 21:
				{
				strDis+="<-- [NAK]\15\12";
				break;
				}
			}
			myEdit.ReplaceSel(strDis);
			if(!myfuncWrite())
			{
				return false;
			}
		}
	}
	return false;

}



void CPC2PLCView::OnUpdateReceive(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//根据串口是否打开，决定是否允许“接收”命令
	if (blnOpened)
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
}

void CPC2PLCView::OnOpencom() 
{
	// TODO: Add your command handler code here
	CString strDis;
	CEdit& myEdit=this->GetEditCtrl( );
	hCom=CreateFile(myCom,                            //创建串口COM2
		GENERIC_READ | GENERIC_WRITE, 
		0,
		NULL,
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL| FILE_FLAG_OVERLAPPED, //使用重叠方式
		 NULL );
	if( hCom !=INVALID_HANDLE_VALUE) 
	{
		SetupComm(hCom,1024,512);
		DCB myDCB;
		GetCommState( hCom, &myDCB );
		myDCB.BaudRate=myBaudRate;
		myDCB.fBinary=TRUE;
		myDCB.fParity=myfParity;
		myDCB.ByteSize=8;
		myDCB.Parity=myParity;
		myDCB.StopBits=ONESTOPBIT;
		SetCommState(hCom,&myDCB);

		//显示串口成功打开
		myEdit.SetReadOnly (true);
		myEdit.SetSel(1000000,1000000);
		strDis=myCom;
		strDis+="打开成功！\15\12\15\12";
		myEdit.ReplaceSel(strDis);
		blnOpened=true;
	}
	else
	{
		//显示串口打开失败
		myEdit.SetReadOnly (true);
		myEdit.SetSel(1000000,1000000);
		strDis=myCom;
		strDis+="打开失败！\15\12\15\12";
		myEdit.ReplaceSel(strDis);
		blnOpened=false;
	}
}

void CPC2PLCView::OnUpdateSetup(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//根据串口是否打开，决定是否允许“设置”命令
	if (!blnOpened)
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
}

void CPC2PLCView::OnUpdateOpencom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//根据串口是否打开，决定是否允许“打开”命令
	if (!blnOpened)
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
}

void CPC2PLCView::OnUpdateClosecom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//根据串口是否打开，决定是否允许“关闭”命令
	if (blnOpened)
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
	
}

void CPC2PLCView::OnClosecom() 
{
	// TODO: Add your command handler code here
	if ((blnOpened) && (hCom!=NULL))
	{
		CloseHandle(hCom);

		CString strDis;                         //显示串口成功关闭
		CEdit& myEdit=this->GetEditCtrl( );
		myEdit.SetReadOnly (true);
		myEdit.SetSel(1000000,1000000);
		strDis=myCom;
		strDis+="  已关闭！\15\12\15\12";
		myEdit.ReplaceSel(strDis);
		blnOpened=false;
	}
	
}

void CPC2PLCView::OnUpdateAppExit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//根据串口是否打开，决定是否允许“退出”命令
	if (blnOpened)
	{
		pCmdUI->Enable(false);
	}
	else
	{
		pCmdUI->Enable(true);
	}
}

void CPC2PLCView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CEditView::OnChar(nChar, nRepCnt, nFlags);
}
