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
		AfxMessageBox("����MSComm�ؼ�ʧ�ܣ�");
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
    arrTypeLong[1]=1;              //byte��ռ1�ֽ�
    arrTypeLong[2]=2;              //int��ռ2�ֽ�
    arrTypeLong[3]=4;              //float��ռ4�ֽ�
    arrTypeLong[4]=2;              //uint��ռ2�ֽ�
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

	int intDimension;//ÿ�ν���OnComm�¼��󣬶������ݵĸ���.һ֡�������һ֡���ݵĸ���
	int i;           //ѭ��������
	bool bFlag;      //���ú���ʱ����ֵ���ɹ����
	BYTE arrTemp[4]; //��ʱ����ֽ�������
	BYTE bytTemp;    //��ʱ����ֽ��ͱ���
	float fTemp;     //��ʱʹ�õĸ�����
	BYTE bytActFlag; //������־��������д
	BYTE bytType;    //��������
	int intOffset;   //�Ĵ���ƫ�Ƶ�ַ
	BYTE bytNumber;  //��������Ҫ�������ݸ���
	BYTE bytDataLong;          //��Ӧ������ʱ����Ӧ�����ַ����ܸ���
	CString myStr,myStr1;      //��ʾ��Ϣʱʹ��

	VARIANT input1;            //����VARIANT���ͱ���
	BYTE rxdata[2048];         //�����Ŷ��������ݵ�����,rxdata[]��ʱ���ÿ�ν��յ��Ĵ����ź�ԭʼֵ����������֡
	long k;
	COleSafeArray safearray1;  //����COleSafeArray���ʵ��
	CByteArray Array1;         //������Ŷ��������ݵ�CByteArray��ʵ��


	input1=myComm.GetInput();
	//��VARAIANT������ֵ��COleSafeArray���ʵ��
	safearray1=input1;          
	//ʹ��COleSafeArray��ĳ�Ա������ȡ���ݳ���
	intDimension=safearray1.GetOneDimSize();
	for(k=0;k<intDimension;k++)
	//ʹ��COleSafeArray��ĳ�Ա����������д������
	{
		safearray1.GetElement(&k,rxdata+k);
		arrReceive[bytCount+k]=rxdata[k];   //����
	}

    switch(bytCount)                        // '�����Ƿ��״ζ�һ֡���ݣ�0Ϊ�״ζ�
	{
	case 0:
		{
            switch(arrReceive[2])
			{
			case 0x52:                     //��Ϊ������
				{
                    bytCount = intDimension;
                    bytSum = 9;           //Ӧ�ý��յ������ݸ���Ϊ9��
					break;
				}
			case 0x57:                    //��Ϊд����
				{
					switch(arrReceive[3]) //����byte����1����float����3
					{
					case 1:
						{
                            bytCount = intDimension;
                            bytSum = 10;  //Ӧ�ý��յ������ݸ���Ϊ10��
							break;
						}
					case 3:
						{
                            bytCount = intDimension;
                            bytSum = 12;  //Ӧ�ý��յ������ݸ���Ϊ12��
							break;
						}
					}
				}
			}
			break;
		}
	default:
		{
            bytCount+=intDimension;     //�ۼ��ѽ��յ������ݸ���
		}
    }
    if (bytCount == bytSum)             //�Ѿ��յ�Ҫ���������ַ�
	{
		myStr1="�յ�:";
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
		if(bytCount>20)                //������ִ������¿�ʼ���н��ռ���
		{
			bytCount = 0;
			bytSum = 0;
		}
		return;
	}
	//�Ѿ��յ�Ҫ���������ַ������Ҵ����arrReceive[]��

    //��У��CRC��ȷ��?��ȷ��������������oncomm����
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
    //�н�����0D��
    if( arrReceive[intDimension - 1] != 0x0D)
	{
        bFlag = AckError(0x82);
        return;
    }
    //��STX��ʼλ�Ƿ�Ϊ02��
    if( arrReceive[0] != 0x2)
	{
        bFlag = AckError(0x82);
        return;
	}
    //��Sta��ʼλ�Ƿ�Ϊ27��
    if( arrReceive[1] != 0x27)
	{
        bFlag = AckError(0x82);
        return;
	}
    switch(arrReceive[2])                //ȷ����������
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
    switch(arrReceive[3])              //ȷ����������
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
    intOffset = arrReceive[4] + arrReceive[5] * 256;//����ƫ�Ƶ�ַ
	switch(bytActFlag)
	{
	case 0x57:                       //д����
		{
            switch(bytType)
			{
			case 1:
				{
                    arrB[intOffset]= arrReceive[7];
					myStr1=" дB";
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
							   m_Valve1.SetWindowText("�Ѵ�");

								break;
							}
						case 2:
							{
							   m_Valve2.SetWindowText("�Ѵ�");
								break;
							}
						case 3:
							{
							   m_Valve3.SetWindowText("�Ѵ�");
								break;
							}
						case 4:
							{
							   m_Valve4.SetWindowText("�Ѵ�");
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
							   m_Valve1.SetWindowText("�ѹر�");
								break;
							}
						case 2:
							{
							   m_Valve2.SetWindowText("�ѹر�");
								break;
							}
						case 3:
							{
							   m_Valve3.SetWindowText("�ѹر�");
								break;
							}
						case 4:
							{
							   m_Valve4.SetWindowText("�ѹر�");
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

					myStr1=" дF";
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
	case 0x52:                             //������
		{
            bytNumber = arrReceive[6];     //��ȡ���������ݸ�����bytNumber
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

					myStr1=" ��B";
					if(bytNumber==1)
							myStr.Format("%d",intOffset);
						else
							myStr.Format("%d��B%d",intOffset,intOffset+bytNumber-1);

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
					myStr1=" ��F";
					if(bytNumber==1)
							myStr.Format("%d",intOffset);
						else
							myStr.Format("%d��F%d",intOffset,intOffset+bytNumber-1);

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
			myStr1="  ��Ӧ: ";
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
	if (!myComm.GetPortOpen())                  //��������δ��
	{
		myComm.SetCommPort(mySetupDlg.m_Com+1); //ָ�����ں�
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
		myComm.SetSettings(myStr);          //ͨ�Ų�������
		myComm.SetInBufferSize(1024);       //ָ�����ջ�������С
		myComm.SetInBufferCount(0);         //��ս��ջ�����
		myComm.SetInputMode(1);             //�������ݻ�ȡ��ʽ
		myComm.SetInputLen(0);              //����ÿ�ζ�ȡ����
		myComm.SetRThreshold(3);            //���ý���OnComm�¼�����ֵ
		myComm.SetPortOpen(1);              //�򿪴���
		myComm.SetInBufferCount(0);         //������뻺����
		m_Close.EnableWindow(true);
		m_Open.EnableWindow(false);
		m_Setup.EnableWindow(false);
		SetTimer(1,1000,NULL);
	}
	else                                   //�����Ѿ���
	{
		AfxMessageBox("�����Ѿ���!");
	}

}

void CPC2ClientDlg::OnClosecom() 
{
	// TODO: Add your control notification handler code here
	if (myComm.GetPortOpen())             //��������
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
	if (myComm.GetPortOpen())             //��������
	{
		myComm.SetPortOpen(false);
		m_Close.EnableWindow(false);
		m_Open.EnableWindow(true);
		m_Setup.EnableWindow(true);

	}
	
	CDialog::OnClose();
}

//32λ��������ת����������
bool  CPC2ClientDlg::Bin2Float(BYTE arrBin[],float *fOutput)
{
    int Power;                         //Power��Ž���,
	int i,j;                           //i,j����
    float fMantissa;                   //���β��ʮ������ֵ
    BYTE arrBits[32];                  //���32λ1��0ֵ
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
        Power = Power - 127;             //������ù���127���ʽ�������ȥ127
        fMantissa = 0;
        for(i=22;i>=0;i--)
            fMantissa = fMantissa + arrMantissa[i] * arrBits[i];
        fMantissa = fMantissa + 1;       //��񻯸�������������1���������
        //��������-1λ������*2�������*β��
        *fOutput =(float)(pow(-1,arrBits[31])* pow(2,Power) * fMantissa);
	}
	else
		*fOutput=0;
	return true;
}

//������ת32λ������������
bool  CPC2ClientDlg::Float2Bin(float fInput,BYTE *arrBin)
{
    BYTE Power;                        //�������Ľ���
	BYTE *tmpBin;
	int j;
    BYTE arrBits[23];                  //23λβ����λ��ȡֵ�����1��0
    BYTE bytBit23;                     //��23λ��ȡֵ�����1��0
    for(j=0;j<=22;j++)
        arrBits[j] = 0;
	tmpBin=arrBin;                     //���ֽ������ַ��������
    for(j=0;j<=3;j++)                  //���ֽ�����ʼ��Ϊ0
	{
        *arrBin=0;
		arrBin++;
	}
	arrBin=tmpBin;                    //�ָ������ַ
    if(fInput!=0)                     //��fInputΪ0����arrBin��0~3����Ϊ0
	{
        Power=127;                    //���û�ֵ���Իָ�����127���ԭֵ
        if(fInput < 1)
		{
            for(j=1;j<=127;j++)       //�˴���127ֻ�Ǵ����ֵ����׼ȷ������ֵӦ���측�����Ŀ��÷�Χ
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
        *arrBin=(BYTE)Power/2;              //��arrBin[3]
		arrBin=tmpBin;
        fInput--;                           //������񻯸���������������1
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
            *arrBin+=(BYTE)pow(2,j) * arrBits[j];       //��arrBin[0]
		arrBin++;
        for(j=15;j>=8;j--)
            *arrBin+=(BYTE)pow(2,(j - 8))* arrBits[j];  //��arrBin[1]
		arrBin++;
        for(j=22;j>=16;j--)
            *arrBin+=(BYTE)pow(2,(j - 16))* arrBits[j]; //��arrBin[2]
        *arrBin+=(BYTE)pow(2,7)* bytBit23;
		arrBin=tmpBin;

	}
	return true;
}

//���ش�����Ӧ����
bool	CPC2ClientDlg::AckError(BYTE errCode)
{
	CByteArray Array1;              //������Ŷ��������ݵ�CByteArray��ʵ��
	CString myStr1,myStr;           //��ʾ��Ϣʱʹ�õ��ַ���
	int i;
	Array1.RemoveAll();
	Array1.SetSize(4);
	Array1.SetAt(0,0xf);
	Array1.SetAt(1,errCode);
	Array1.SetAt(2,errCode^0xf);
	Array1.SetAt(3,0x0d);
	myComm.SetOutput(COleVariant(Array1)); 
	myStr1="  ��Ӧ: ";
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

//������ȷ��Ӧ����
bool	CPC2ClientDlg::AckCorrect()
{

	CByteArray Array1;            //������Ŷ��������ݵ�CByteArray��ʵ��
	CString myStr1,myStr;         //��ʾ��Ϣʱʹ�õ��ַ���
	int i;
	Array1.RemoveAll();
	Array1.SetSize(4);
	Array1.SetAt(0,6);
	Array1.SetAt(1,0x27);
	Array1.SetAt(2,0x21);
	Array1.SetAt(3,0x0d);
	myComm.SetOutput(COleVariant(Array1)); 
	myStr1="  ��Ӧ: ";
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
