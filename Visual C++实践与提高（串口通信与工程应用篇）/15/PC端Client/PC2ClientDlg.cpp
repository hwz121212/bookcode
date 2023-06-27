// PC2ClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PC2Client.h"
#include "PC2ClientDlg.h"
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPC2ClientDlg dialog

CPC2ClientDlg::CPC2ClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPC2ClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPC2ClientDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPC2ClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPC2ClientDlg)
	DDX_Control(pDX, IDC_VOLUME4, m_Volume4);
	DDX_Control(pDX, IDC_VOLUME3, m_Volume3);
	DDX_Control(pDX, IDC_VOLUME2, m_Volume2);
	DDX_Control(pDX, IDC_VOLUME1, m_Volume1);
	DDX_Control(pDX, IDC_VALVE4, m_Valve4);
	DDX_Control(pDX, IDC_VALVE2, m_Valve2);
	DDX_Control(pDX, IDC_VALVE1, m_Valve1);
	DDX_Control(pDX, IDC_SETUPCOM, m_Setup);
	DDX_Control(pDX, IDC_OPENCOM, m_Open);
	DDX_Control(pDX, IDC_CLOSECOM, m_Close);
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	DDX_Control(pDX, IDC_VALVE3, m_Valve3);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPC2ClientDlg, CDialog)
	//{{AFX_MSG_MAP(CPC2ClientDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SETUPCOM, OnSetupcom)
	ON_BN_CLICKED(IDC_OPENCOM, OnOpencom)
	ON_BN_CLICKED(IDC_CLOSECOM, OnClosecom)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPC2ClientDlg message handlers

BOOL CPC2ClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	int i,k;
	this->SetWindowText("PC->KingComClient:19200  COM4 O-8-1");
	DWORD style=WS_VISIBLE|WS_CHILD;
	if (!myComm.Create(NULL,style,CRect(0,0,0,0),this,IDC_MSCOMM1))
	{
		AfxMessageBox("创建MSComm控件失败！");
		return -1;
	}
	m_Open.EnableWindow(false);
	m_Close.EnableWindow(false);
	bytCount=0;
	bytSum=0;
	k=1;
    for(i=22;i>=0;i--)
	{
		arrMantissa[i] =(float)(1 /pow(2,k));
        k++;
	}
    for(i=0;i<=7;i++)
	{
        arrCompare[i] =(BYTE) pow(2,i);

	}
    for(i=0;i<=4;i++)
	{
        arrB[i]=0;
        arrF[i]=0;
	}
    arrTypeLong[1]=1;              //byte型占1字节
    arrTypeLong[2]=2;              //int型占2字节
    arrTypeLong[3]=4;              //float型占4字节
    arrTypeLong[4]=2;              //uint型占2字节
	dblIncStep=0.1;
	dblVarible=-1;
	m_Edit1.SetReadOnly(true);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPC2ClientDlg::OnPaint() 
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
HCURSOR CPC2ClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPC2ClientDlg::OnSetupcom() 
{
	// TODO: Add your control notification handler code here
	CString myStr,myStr1;
	
	if (mySetupDlg.DoModal()==IDOK)
	{
		myStr="PC->KingComClient:";
		switch (mySetupDlg.m_Com )
		{
		case 0:
			{
			myStr+="COM1 ";
			break;
			}
		case 1:
			{
			myStr+="COM2 ";
			break;
			}
		case 2:
			{
			myStr+="COM3 ";
			break;
			}
		case 3:
			{
			myStr+="COM4 ";
			break;
			}
		case 4:
			{
			myStr+="COM5 ";
			break;
			}
		case 5:
			{
			myStr+="COM6 ";
			break;
			}
		}
		switch (mySetupDlg.m_BaudRate)
		{
		case 0:
			{
			myStr+="19200 ";
			break;
			}
		case 1:
			{
			myStr+="9600 ";
			break;
			}
		case 2:
			{
			myStr+="4800 ";
			break;
			}
		case 3:
			{
			myStr+="2400 ";
			break;
			}
		}
		switch (mySetupDlg.m_Parity)
		{
		case 0:
			{
			myStr+="N-8-1";
			break;
			}
		case 1:
			{
			myStr+="O-8-1";
			break;
			}
		case 2:
			{
			myStr+="E-8-1";
			break;
			}
		}
		this->SetWindowText(myStr);
		m_Open.EnableWindow(true);
		m_Close.EnableWindow(false);
	}
}

BEGIN_EVENTSINK_MAP(CPC2ClientDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CPC2ClientDlg)
	ON_EVENT(CPC2ClientDlg, IDC_MSCOMM1, 1 /* OnComm */, OnOnCommMscomm1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CPC2ClientDlg::OnOnCommMscomm1() 
{
	// TODO: Add your control notification handler code here

	int intDimension;//每次进入OnComm事件后，读出数据的个数.一帧读完后，是一帧数据的个数
	int i;           //循环计数用
	bool bFlag;      //调用函数时返回值，成功与否，
	BYTE arrTemp[4]; //临时存放字节型数组
	BYTE bytTemp;    //临时存放字节型变量
	float fTemp;     //临时使用的浮点数
	BYTE bytActFlag; //操作标志，读还是写
	BYTE bytType;    //数据类型
	int intOffset;   //寄存器偏移地址
	BYTE bytNumber;  //读请求中要读的数据个数
	BYTE bytDataLong;          //回应读请求时，回应串行字符的总个数
	CString myStr,myStr1;      //显示信息时使用

	VARIANT input1;            //定义VARIANT类型变量
	BYTE rxdata[2048];         //定义存放二进制数据的数组,rxdata[]临时存放每次接收到的串行信号原始值，并非完整帧
	long k;
	COleSafeArray safearray1;  //定义COleSafeArray类的实例
	CByteArray Array1;         //创建存放二进制数据的CByteArray类实例


	input1=myComm.GetInput();
	//将VARAIANT变量赋值给COleSafeArray类的实例
	safearray1=input1;          
	//使用COleSafeArray类的成员函数获取数据长度
	intDimension=safearray1.GetOneDimSize();
	for(k=0;k<intDimension;k++)
	//使用COleSafeArray类的成员函数将数据写入数组
	{
		safearray1.GetElement(&k,rxdata+k);
		arrReceive[bytCount+k]=rxdata[k];   //传数
	}

    switch(bytCount)                        // '区别是否首次读一帧数据，0为首次读
	{
	case 0:
		{
            switch(arrReceive[2])
			{
			case 0x52:                     //若为读操作
				{
                    bytCount = intDimension;
                    bytSum = 9;           //应该接收到的数据个数为9个
					break;
				}
			case 0x57:                    //若为写操作
				{
					switch(arrReceive[3]) //区别byte类型1还是float类型3
					{
					case 1:
						{
                            bytCount = intDimension;
                            bytSum = 10;  //应该接收到的数据个数为10个
							break;
						}
					case 3:
						{
                            bytCount = intDimension;
                            bytSum = 12;  //应该接收到的数据个数为12个
							break;
						}
					}
				}
			}
			break;
		}
	default:
		{
            bytCount+=intDimension;     //累计已接收到的数据个数
		}
    }
    if (bytCount == bytSum)             //已经收到要求数量的字符
	{
		myStr1="收到:";
        for(k=0;k<bytCount;k++)
		{
			myStr.Format("%02X",arrReceive[k]);
			myStr1+=myStr;
			myStr1+="-";
		}
		m_Edit1.SetSel(1000000,1000000);
		myStr1.TrimRight('-');
		m_Edit1.ReplaceSel(myStr1);
		UpdateData(false);
		intDimension = bytCount;
        bytCount = 0;
        bytSum = 0;
	}
	else
	{
		if(bytCount>20)                //传输出现错误，重新开始进行接收计数
		{
			bytCount = 0;
			bytSum = 0;
		}
		return;
	}
	//已经收到要求数量的字符，并且存放在arrReceive[]中

    //判校验CRC正确否?正确继续，否则跳出oncomm过程
	bytTemp = 0;
	for(k=0;k<=intDimension-3;k++)
	{
        bytTemp=bytTemp^arrReceive[k];
	}
    if (bytTemp!=arrReceive[intDimension-2])
	{
        bFlag=AckError(0x83);
        return;
	}
    //判结束符0D？
    if( arrReceive[intDimension - 1] != 0x0D)
	{
        bFlag = AckError(0x82);
        return;
    }
    //判STX起始位是否为02？
    if( arrReceive[0] != 0x2)
	{
        bFlag = AckError(0x82);
        return;
	}
    //判Sta起始位是否为27？
    if( arrReceive[1] != 0x27)
	{
        bFlag = AckError(0x82);
        return;
	}
    switch(arrReceive[2])                //确定操作类型
	{
	case 0x52:
	case 0x57:
		{
            bytActFlag = arrReceive[2];
			break;
		}
	default:
		{
            bFlag = AckError(0x82);
			return;
		}
	}
    switch(arrReceive[3])              //确定数据类型
	{
	case 1:
	case 3:
		{
            bytType = arrReceive[3];
			break;
		}
	default:
		{
            bFlag = AckError(0x80);
			return;
		}
	}
    intOffset = arrReceive[4] + arrReceive[5] * 256;//变量偏移地址
	switch(bytActFlag)
	{
	case 0x57:                       //写操作
		{
            switch(bytType)
			{
			case 1:
				{
                    arrB[intOffset]= arrReceive[7];
					myStr1=" 写B";
					myStr.Format("%d=%02X",intOffset,arrB[intOffset]);
					myStr1+=myStr;
					myStr1+="\15\12";
					m_Edit1.SetSel(1000000,1000000);
					m_Edit1.ReplaceSel(myStr1);
                    if( arrB[intOffset] == 255)
					{
						switch(intOffset)
						{
						case 1:
							{
							   m_Valve1.SetWindowText("已打开");

								break;
							}
						case 2:
							{
							   m_Valve2.SetWindowText("已打开");
								break;
							}
						case 3:
							{
							   m_Valve3.SetWindowText("已打开");
								break;
							}
						case 4:
							{
							   m_Valve4.SetWindowText("已打开");
								break;
							}
						}
					}
                    else
					{
						switch(intOffset)
						{
						case 1:
							{
							   m_Valve1.SetWindowText("已关闭");
								break;
							}
						case 2:
							{
							   m_Valve2.SetWindowText("已关闭");
								break;
							}
						case 3:
							{
							   m_Valve3.SetWindowText("已关闭");
								break;
							}
						case 4:
							{
							   m_Valve4.SetWindowText("已关闭");
								break;
							}
						}

					}
					break;
				}
			case 3:
				{
                    for(i=0;i<=3;i++)
                        arrTemp[i]=arrReceive[i+6];
					if(Bin2Float(arrTemp,&fTemp)) arrF[intOffset]=fTemp;

					myStr1=" 写F";
					myStr.Format("%d=%f",intOffset,arrF[intOffset]);
					myStr1+=myStr;
					myStr1+="\15\12";
					m_Edit1.SetSel(1000000,1000000);
					m_Edit1.ReplaceSel(myStr1);

					break;
				}
			}
            bFlag = AckCorrect();
			break;
		}
	case 0x52:                             //读操作
		{
            bytNumber = arrReceive[6];     //读取欲传送数据个数到bytNumber
 			Array1.RemoveAll();
			bytDataLong=5 + bytNumber * arrTypeLong[bytType];
			Array1.SetSize(bytDataLong);
			Array1.SetAt(0,6);
			Array1.SetAt(1,0x27);
			Array1.SetAt(2,bytNumber * arrTypeLong[bytType]);
            switch(bytType)
			{
			case 1:
				{
                    for(i=0;i<=(bytNumber - 1);i++)
						Array1.SetAt(i+3,arrB[i + intOffset]);

					myStr1=" 读B";
					if(bytNumber==1)
							myStr.Format("%d",intOffset);
						else
							myStr.Format("%d～B%d",intOffset,intOffset+bytNumber-1);

					myStr1+=myStr;
					myStr1+="\15\12";
					m_Edit1.SetSel(1000000,1000000);
					m_Edit1.ReplaceSel(myStr1);
					break;
				}
			case 3:
				{
                    for(i=0;i<=(bytNumber - 1);i++)
					{
                        fTemp = arrF[i + intOffset];
						if(Float2Bin(fTemp,arrTemp))
						{
							Array1.SetAt(4*i+3,arrTemp[0]);
							Array1.SetAt(4*i+4,arrTemp[1]);
							Array1.SetAt(4*i+5,arrTemp[2]);
							Array1.SetAt(4*i+6,arrTemp[3]);
						}
					}
					myStr1=" 读F";
					if(bytNumber==1)
							myStr.Format("%d",intOffset);
						else
							myStr.Format("%d～F%d",intOffset,intOffset+bytNumber-1);

					myStr1+=myStr;
					myStr1+="\15\12";
					m_Edit1.SetSel(1000000,1000000);
					m_Edit1.ReplaceSel(myStr1);
					break;

				}
			}
			bytTemp = 0;
            for(i=0;i<=(bytDataLong - 3);i++)
                bytTemp^=Array1.GetAt(i);
			Array1.SetAt(bytDataLong-2,bytTemp);
			Array1.SetAt(bytDataLong-1,0x0d);
			myComm.SetOutput(COleVariant(Array1)); 
			myStr1="  回应: ";
			for(i=0;i<=bytDataLong-1;i++)
			{
				myStr.Format("%02X",Array1.GetAt(i));
				myStr1+=myStr;
				myStr1+="-";
			}
			myStr1.TrimRight('-');
			myStr1+="\15\12\15\12";
			m_Edit1.SetSel(1000000,1000000);
			m_Edit1.ReplaceSel(myStr1);
			
			break;
		}
	}
}

void CPC2ClientDlg::OnOpencom() 
{
	// TODO: Add your control notification handler code here
	CString myStr;
	if (!myComm.GetPortOpen())                  //若串口尚未打开
	{
		myComm.SetCommPort(mySetupDlg.m_Com+1); //指定串口号
		switch (mySetupDlg.m_BaudRate)
		{
		case 0:
			{
			myStr="19200,";
			break;
			}
		case 1:
			{
			myStr="9600,";
			break;
			}
		case 2:
			{
			myStr="4800,";
			break;
			}
		case 3:
			{
			myStr="2400,";
			break;
			}
		}
		switch (mySetupDlg.m_Parity)
		{
		case 0:
			{
			myStr+="N,8,1";
			break;
			}
		case 1:
			{
			myStr+="O,8,1";
			break;
			}
		case 2:
			{
			myStr+="E,8,1";
			break;
			}
		}		
		myComm.SetSettings(myStr);          //通信参数设置
		myComm.SetInBufferSize(1024);       //指定接收缓冲区大小
		myComm.SetInBufferCount(0);         //清空接收缓冲区
		myComm.SetInputMode(1);             //设置数据获取方式
		myComm.SetInputLen(0);              //设置每次读取长度
		myComm.SetRThreshold(3);            //设置接收OnComm事件门限值
		myComm.SetPortOpen(1);              //打开串口
		myComm.SetInBufferCount(0);         //清除输入缓冲区
		m_Close.EnableWindow(true);
		m_Open.EnableWindow(false);
		m_Setup.EnableWindow(false);
		SetTimer(1,1000,NULL);
	}
	else                                   //串口已经打开
	{
		AfxMessageBox("串口已经打开!");
	}

}

void CPC2ClientDlg::OnClosecom() 
{
	// TODO: Add your control notification handler code here
	if (myComm.GetPortOpen())             //串口若打开
	{
		myComm.SetPortOpen(false);
		m_Close.EnableWindow(false);
		m_Open.EnableWindow(true);
		m_Setup.EnableWindow(true);
		KillTimer(1);
	}
}


void CPC2ClientDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if (myComm.GetPortOpen())             //串口若打开
	{
		myComm.SetPortOpen(false);
		m_Close.EnableWindow(false);
		m_Open.EnableWindow(true);
		m_Setup.EnableWindow(true);

	}
	
	CDialog::OnClose();
}

//32位二进制数转浮点数程序
bool  CPC2ClientDlg::Bin2Float(BYTE arrBin[],float *fOutput)
{
    int Power;                         //Power存放阶码,
	int i,j;                           //i,j计数
    float fMantissa;                   //存放尾数十进制数值
    BYTE arrBits[32];                  //存放32位1或0值
    long lTemp;
    lTemp = 0;
    for(i=0;i<=3;i++)
        lTemp = lTemp + arrBin[i];
    if(lTemp != 0)
	{
        Power = 0;
        for(i=3;i>=0;i--)
		{
            for(j=7;j>=0;j--)
			{
                if(arrBin[i] >= arrCompare[j])
				{
                    arrBits[i * 8 + j] = 1;
                    arrBin[i]=arrBin[i] - arrCompare[j];
				}
				else
                    arrBits[i * 8 + j]=0;
			}
		}
        for(i=0;i<=7;i++)
            Power = Power + arrBits[i + 23] * (int)pow(2,i);
        Power = Power - 127;             //阶码采用过余127码格式，故需减去127
        fMantissa = 0;
        for(i=22;i>=0;i--)
            fMantissa = fMantissa + arrMantissa[i] * arrBits[i];
        fMantissa = fMantissa + 1;       //规格化浮点数隐含整数1，故需加入
        //浮点数＝-1位符次幂*2阶码次幂*尾数
        *fOutput =(float)(pow(-1,arrBits[31])* pow(2,Power) * fMantissa);
	}
	else
		*fOutput=0;
	return true;
}

//浮点数转32位二进制数程序
bool  CPC2ClientDlg::Float2Bin(float fInput,BYTE *arrBin)
{
    BYTE Power;                        //浮点数的阶码
	BYTE *tmpBin;
	int j;
    BYTE arrBits[23];                  //23位尾数各位的取值情况，1或0
    BYTE bytBit23;                     //第23位的取值情况，1或0
    for(j=0;j<=22;j++)
        arrBits[j] = 0;
	tmpBin=arrBin;                     //将字节数组地址保存起来
    for(j=0;j<=3;j++)                  //四字节数初始化为0
	{
        *arrBin=0;
		arrBin++;
	}
	arrBin=tmpBin;                    //恢复数组地址
    if(fInput!=0)                     //若fInput为0，则arrBin（0~3）都为0
	{
        Power=127;                    //设置基值，以恢复过余127码的原值
        if(fInput < 1)
		{
            for(j=1;j<=127;j++)       //此处的127只是大概数值，更准确的上限值应考察浮点数的可用范围
			{
                Power--;
                if((fInput * pow(2,j)) >= 1)
				{
                    fInput = fInput * (float)pow(2,j);
                    break;
				}
			}
		}
		else
		{
            while ( fInput >= 2)
			{
                fInput = fInput / 2;
                Power++;
			}
		}
        if((Power%2)!=0)
		{
            bytBit23 = 1;
		}
		arrBin=arrBin+3;
        *arrBin=(BYTE)Power/2;              //求arrBin[3]
		arrBin=tmpBin;
        fInput--;                           //消除规格化浮点数的隐含整数1
        for(j=22;j>=0;j--)
		{
            if(fInput >= arrMantissa[j])
			{
                arrBits[j] = 1;
                fInput-=arrMantissa[j];
			}
			else
			{
                arrBits[j] = 0;
            }

		}
        for(j=7;j>=0;j--)
            *arrBin+=(BYTE)pow(2,j) * arrBits[j];       //求arrBin[0]
		arrBin++;
        for(j=15;j>=8;j--)
            *arrBin+=(BYTE)pow(2,(j - 8))* arrBits[j];  //求arrBin[1]
		arrBin++;
        for(j=22;j>=16;j--)
            *arrBin+=(BYTE)pow(2,(j - 16))* arrBits[j]; //求arrBin[2]
        *arrBin+=(BYTE)pow(2,7)* bytBit23;
		arrBin=tmpBin;

	}
	return true;
}

//返回错误响应程序
bool	CPC2ClientDlg::AckError(BYTE errCode)
{
	CByteArray Array1;              //创建存放二进制数据的CByteArray类实例
	CString myStr1,myStr;           //显示信息时使用的字符串
	int i;
	Array1.RemoveAll();
	Array1.SetSize(4);
	Array1.SetAt(0,0xf);
	Array1.SetAt(1,errCode);
	Array1.SetAt(2,errCode^0xf);
	Array1.SetAt(3,0x0d);
	myComm.SetOutput(COleVariant(Array1)); 
	myStr1="  回应: ";
	for(i=0;i<=3;i++)
	{
		myStr.Format("%02X",Array1.GetAt(i));
		myStr1+=myStr;
		myStr1+="-";
	}
	myStr1.TrimRight('-');
	myStr1+="\15\12\15\12";
	m_Edit1.SetSel(1000000,1000000);
	m_Edit1.ReplaceSel(myStr1);
	return true;
}

//返回正确响应程序
bool	CPC2ClientDlg::AckCorrect()
{

	CByteArray Array1;            //创建存放二进制数据的CByteArray类实例
	CString myStr1,myStr;         //显示信息时使用的字符串
	int i;
	Array1.RemoveAll();
	Array1.SetSize(4);
	Array1.SetAt(0,6);
	Array1.SetAt(1,0x27);
	Array1.SetAt(2,0x21);
	Array1.SetAt(3,0x0d);
	myComm.SetOutput(COleVariant(Array1)); 
	myStr1="  回应: ";
	for(i=0;i<=3;i++)
	{
		myStr.Format("%02X",Array1.GetAt(i));
		myStr1+=myStr;
		myStr1+="-";
	}
	myStr1.TrimRight('-');
	myStr1+="\15\12\15\12";
	m_Edit1.SetSel(1000000,1000000);
	m_Edit1.ReplaceSel(myStr1);
	if(m_Edit1.GetLineCount()>=1000)
	{
		m_Edit1.SetReadOnly(false);
		m_Edit1.SetSel(0,-1);
		m_Edit1.Clear();
		m_Edit1.SetReadOnly(true);
	}
    return true;
}

void CPC2ClientDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CString myStr;
	if(dblVarible>2)
	{
		dblIncStep=-0.1;
	}
	if(dblVarible<-1)
	{
		dblIncStep=0.1;
	}
	dblVarible+=dblIncStep;
	arrF[1]=(float)dblVarible*10+12;
	arrF[2]=(float)dblVarible*10+32;
	arrF[3]=(float)dblVarible*10+62;
	arrF[4]=(float)dblVarible*10+82;

	myStr.Format("%.2f",arrF[1]);
	m_Volume1.SetWindowText(myStr);
	myStr.Format("%.2f",arrF[2]);
	m_Volume2.SetWindowText(myStr);
	myStr.Format("%.2f",arrF[3]);
	m_Volume3.SetWindowText(myStr);
	myStr.Format("%.2f",arrF[4]);
	m_Volume4.SetWindowText(myStr);

	CDialog::OnTimer(nIDEvent);
}
