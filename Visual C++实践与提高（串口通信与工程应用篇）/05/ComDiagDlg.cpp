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
	m_Delay1 = 100;                         //���ó�ʱʱ��1
	m_Delay2 = 100;                         //���ó�ʱʱ��2
	m_Delay3 = 100;                         //���ó�ʱʱ��3
	m_Delay4 = 100;                         //���ó�ʱʱ��4
	m_Delay5 = 100;                         //���ó�ʱʱ��5
	m_Delay6 = 100;                         //���ó�ʱʱ��6
	m_Delay7 = 100;                         //���ó�ʱʱ��7
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
	//�����ؼ���ʵ��
	DWORD style=WS_VISIBLE|WS_CHILD;
	if (!myComm.Create(NULL,style,CRect(0,0,0,0),this,IDC_MSCOMM1))
	{
		AfxMessageBox("����MSComm�ؼ�ʧ�ܣ�");
		m_Opencom.EnableWindow(false);        //ʹ�򿪴��ڰ�ť��Ч
		m_Closecom.EnableWindow(false);       //ʹ�رմ��ڰ�ť��Ч
		m_Setupcom.EnableWindow(false);       //ʹ���ð�ť��Ч
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
		myCom=mySetupDlg.m_Com+1;                              //��ȡ���ڱ��
		dblBaud=pow(2,(double)mySetupDlg.m_BaudRate);          //��ȡ������
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
		this->SetWindowText(strTemp);                           //�޸Ĵ��ڱ���
		UpdateData(false);
	}
	
}

void CComDiagDlg::OnOpencom() 
{
	// TODO: Add your control notification handler code here
	CString strPara;                          //���ڲ���
	myComm.SetCommPort(myCom);                //ָ�����ں�
	strPara=myBaudRate;
	strPara+=",";
	strPara+=myParity;
	strPara+=",8,1";
	myComm.SetSettings(strPara);             //ͨ�Ų�������
	myComm.SetInBufferSize(1024);            //ָ�����ջ�������С
	myComm.SetInBufferCount(0);              //��ս��ջ�����
	myComm.SetInputMode(1);                  //�������ݻ�ȡ��ʽ
	myComm.SetInputLen(0);                   //����ÿ�ζ�ȡ����
	myComm.SetRThreshold(1);                 //���ý���OnComm�¼�����ֵ
	myComm.SetPortOpen(1);                   //�򿪴���
	m_Opencom.EnableWindow(false);           //ʹ�򿪴��ڰ�ť��Ч
	m_Closecom.EnableWindow(true);           //ʹ�رմ��ڰ�ť��Ч
	m_Setupcom.EnableWindow(false);          //ʹ���ð�ť��Ч
	m_Exit.EnableWindow(false);              //ʹ�˳���ť��Ч
	m_Send1.EnableWindow(true);              //ʹ����1��ť��Ч
	m_Send2.EnableWindow(true);              //ʹ����2��ť��Ч
	m_Send3.EnableWindow(true);              //ʹ����3��ť��Ч
	m_Send4.EnableWindow(true);              //ʹ����4��ť��Ч
	m_Send5.EnableWindow(true);              //ʹ����5��ť��Ч
	m_Send6.EnableWindow(true);              //ʹ����6��ť��Ч
	m_Send7.EnableWindow(true);              //ʹ����7��ť��Ч
	AfxMessageBox("���ڴ򿪳ɹ���");
}

void CComDiagDlg::OnClosecom() 
{
	// TODO: Add your control notification handler code here
	myComm.SetPortOpen(0);
	AfxMessageBox("���ڹرճɹ���");
	m_Opencom.EnableWindow(true);             //ʹ�򿪴��ڰ�ť��Ч
	m_Closecom.EnableWindow(false);           //ʹ�رմ��ڰ�ť��Ч
	m_Setupcom.EnableWindow(true);            //ʹ���ð�ť��Ч
	m_Exit.EnableWindow(true);                //ʹ�˳���ť��Ч
	m_Send1.EnableWindow(false);              //ʹ����1��ť��Ч
	m_Send2.EnableWindow(false);              //ʹ����2��ť��Ч
	m_Send3.EnableWindow(false);              //ʹ����3��ť��Ч
	m_Send4.EnableWindow(false);              //ʹ����4��ť��Ч
	m_Send5.EnableWindow(false);              //ʹ����5��ť��Ч
	m_Send6.EnableWindow(false);              //ʹ����6��ť��Ч
	m_Send7.EnableWindow(false);              //ʹ����7��ť��Ч
}

BEGIN_EVENTSINK_MAP(CComDiagDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CComDiagDlg)
	ON_EVENT(CComDiagDlg, IDC_MSCOMM1, 1 /* OnComm */, OnOnCommMscomm1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CComDiagDlg::OnOnCommMscomm1() 
{
	// TODO: Add your control notification handler code here
	int		iLast=0;                                 //�����ַ�����
	CString strDis,strTemp;
	VARIANT input1;                                  //����VARIANT���ͱ���
	BYTE rxdata[2048];                               //�����Ŷ��������ݵ�����
	COleSafeArray safearray1;                        //����COleSafeArray���ʵ��
	long len1,k;
	UpdateData(true);
	KillTimer(1);                                    //�رճ�ʱ��ʱ��
	switch(myComm.GetCommEvent())
	{
	case 2:
		{
			m_Send1.EnableWindow(true);              //ʹ����1��ť��Ч
			m_Send2.EnableWindow(true);              //ʹ����2��ť��Ч
			m_Send3.EnableWindow(true);              //ʹ����3��ť��Ч
			m_Send4.EnableWindow(true);              //ʹ����4��ť��Ч
			m_Send5.EnableWindow(true);              //ʹ����5��ť��Ч
			m_Send6.EnableWindow(true);              //ʹ����6��ť��Ч
			m_Send7.EnableWindow(true);              //ʹ����7��ť��Ч
			while((myComm.GetInBufferCount())>iLast)
			{
				iLast=myComm.GetInBufferCount();
				Sleep(100);
			}
			//�յ�iLast���ַ�
			//��ȡ���뻺��������
			input1=myComm.GetInput();
			//��VARAIANT������ֵ��COleSafeArray���ʵ��
			safearray1=input1;     
			//ʹ��COleSafeArray��ĳ�Ա������ȡ���ݳ���
			len1=safearray1.GetOneDimSize();
			strDis="�յ�:";
			for(k=0;k<len1;k++)
			//ʹ��COleSafeArray��ĳ�Ա����������д������
			{
				safearray1.GetElement(&k,rxdata+k);
				strTemp.Format("%02X-",rxdata[k]);
				strDis+=strTemp;
			}
			strDis+="\12\15\12\15";
			m_Dis.SetSel(100000,100000);
			m_Dis.ReplaceSel(strDis);               //������ʾ
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

//���ڷ������ݺ���
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
		case 48:               //�ַ�0
		case 49:               //�ַ�1
		case 50:               //�ַ�2
		case 51:               //�ַ�3
		case 52:               //�ַ�4
		case 53:               //�ַ�5
		case 54:               //�ַ�6
		case 55:               //�ַ�7
		case 56:               //�ַ�8
		case 57:               //�ַ�9
		case 65:               //�ַ�A
		case 66:               //�ַ�B
		case 67:               //�ַ�C
		case 68:               //�ַ�D
		case 69:               //�ַ�E
		case 70:               //�ַ�F
			{
				
				strTemp+=charInput[i];
				break;
			}
		default:               //�����ַ�
			{
				if(strTemp!="")
				{
					//���ַ���ת��Ϊ��ֵ
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
		myComm.SetOutput(COleVariant(Array1));          //��������
	}

}

void CComDiagDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(nIDEvent);                     //�رճ�ʱ��ʱ��
	AfxMessageBox("��ʱ��");
	m_Send1.EnableWindow(true);              //ʹ����1��ť��Ч
	m_Send2.EnableWindow(true);              //ʹ����2��ť��Ч
	m_Send3.EnableWindow(true);              //ʹ����3��ť��Ч
	m_Send4.EnableWindow(true);              //ʹ����4��ť��Ч
	m_Send5.EnableWindow(true);              //ʹ����5��ť��Ч
	m_Send6.EnableWindow(true);              //ʹ����6��ť��Ч
	m_Send7.EnableWindow(true);              //ʹ����7��ť��Ч

	CDialog::OnTimer(nIDEvent);
}
