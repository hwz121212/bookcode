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
	//�����ؼ���ʵ��
	DWORD style=WS_VISIBLE|WS_CHILD;
	if (!myComm.Create(NULL,style,CRect(0,0,0,0),this,IDC_MSCOMM1))
	{
		AfxMessageBox("����MSComm�ؼ�ʧ�ܣ�");
		m_Opencom.EnableWindow(false);        //ʹ���򿪴��ڡ���ť��Ч
		m_Closecom.EnableWindow(false);       //ʹ���رմ��ڡ���ť��Ч
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
	dblBaud=pow(2,(double)m_BaudRate);          //��ȡ������
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
	myComm.SetCommPort(m_Com+1);             //ָ�����ں�myCom
	myComm.SetSettings(strPara);             //ͨ�Ų�������
	myComm.SetInBufferSize(1024);            //ָ�����ջ�������С
	myComm.SetInBufferCount(0);              //��ս��ջ�����
	myComm.SetInputMode(1);                  //�������ݻ�ȡ��ʽ
	myComm.SetInputLen(0);                   //����ÿ�ζ�ȡ����
	myComm.SetRThreshold(1);                 //���ý���OnComm�¼�����ֵ
	myComm.SetPortOpen(1);                   //�򿪴���
	m_Opencom.EnableWindow(false);           //ʹ�򿪴��ڰ�ť��Ч
	m_Closecom.EnableWindow(true);           //ʹ�رմ��ڰ�ť��Ч
	m_Exit.EnableWindow(false);              //ʹ�˳���ť��Ч
	GetDlgItem(IDC_COMBO_COM)->EnableWindow(false);
	GetDlgItem(IDC_COMBO_B)->EnableWindow(false);
	GetDlgItem(IDC_COMBO_P)->EnableWindow(false);
	m_Dis.SetSel(100000,100000);
	m_Dis.ReplaceSel("���ڴ򿪳ɹ���\12\15");
	m_Dis.SetSel(100000,100000);
	m_Dis.ReplaceSel("\12\15");
	UpdateData(false);
}

void CPSTN_FileTransDlg::OnClosecom() 
{
	// TODO: Add your control notification handler code here
	myComm.SetPortOpen(0);
	m_Dis.SetSel(100000,100000);
	m_Dis.ReplaceSel("���ڹرճɹ���\12\15");
	m_Dis.SetSel(100000,100000);
	m_Dis.ReplaceSel("\12\15");
	UpdateData(false);
	m_Opencom.EnableWindow(true);           //ʹ�򿪴��ڰ�ť��Ч
	m_Closecom.EnableWindow(false);         //ʹ�رմ��ڰ�ť��Ч
	m_Exit.EnableWindow(true);              //ʹ�˳���ť��Ч
	GetDlgItem(IDC_COMBO_COM)->EnableWindow(true);
	GetDlgItem(IDC_COMBO_B)->EnableWindow(true);
	GetDlgItem(IDC_COMBO_P)->EnableWindow(true);

}

void CPSTN_FileTransDlg::OnSendfile() 
{
	// TODO: Add your control notification handler code here
	CFileDialog myFileDlg(true);          //���ļ��Ի���
	CFile myFile;
	CString myStr,myFileName,myPathName;
	CFileException e;                     //�ļ��쳣����
	myFileDlg.m_ofn.lpstrFilter="*.TXT";
	myFileDlg.m_ofn.lpstrTitle="���ı��ļ�";
	if(myFileDlg.DoModal()==IDOK)         //�����ļ�ѡ��Ի���ѡ���͵��ļ�
	{
		myPathName=myFileDlg.GetPathName();
		myFileName=myFileDlg.GetFileName();
	}
	else
	{
		return;
	}
	myPathName.Replace("\\","\\\\");    //���ļ����еĵ���\���滻��˫��\\��

	//��ѡ�����ļ�
	if(!myFile.Open(myPathName,CFile::modeRead,&e))
	{
		myStr.Format("%02X",e.m_cause); //�ļ��򿪴������������Ϊm_cause
		myStr+="error";
		AfxMessageBox(myStr);
		return;
	}
	lFileLen=myFile.GetLength();
	if(lFileLen>=10240)                //����ļ��ߴ�<10K
	{
		m_Dis.SetSel(100000,100000);
		m_Dis.ReplaceSel("�ļ�����С��10K��\12\15");
		m_Dis.SetSel(100000,100000);
		m_Dis.ReplaceSel("\12\15");
		UpdateData(false);
		return;
	}
	myFile.Read(charSendData,lFileLen);
	myFile.Close();

	//����ʹ��ʱ��Ӧ���öγ���ȡ��ע�ͣ���8�д��롣
	/*myStr="ATDT";
	UpdateData(true);
	myStr+=m_Phone;
	myStr+="\12\15";
	myComm.SetOutput(COleVariant(myStr));//��������
	iActStatus=1;                        //���뷢��̬
	iSendStatus=101;                     //�л�����״̬
	SetTimer(1,2000,NULL);               //������ʱ��ʱ��
	*/ //�������������

	//����Modem���Գ���ʱ��ʹ�øöδ��룬��4�С�
	iActStatus=1;
	iSendStatus=102;
	iRcvStatus=200;
	SetTimer(1,2000,NULL);
	//��Modem���Դ��������

	this->SetWindowText("�����ļ�");
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
	VARIANT input1;                          //����һ��VARIANT�ṹ�ı���
	BYTE rxdata[2048];                       //�����Ŷ��������ݵ�����
	long len1,k;
	COleSafeArray safearray1;                //����COleSafeArray���ʵ��
	int counts,i;
	CString input2;
	int	iParityTemp;
	CFileDialog myFileDlg(false);            //�����ļ��Ի���
	CFile myFile;
	CString myStr,myFileName,myPathName;
	CFileException e;                        //�ļ��쳣����

	KillTimer(1);                            //�رճ�ʱ��ʱ��

	switch(myComm.GetCommEvent())
	{
	case 2://�յ��ַ�
		{
			switch(iActStatus)
			{
			case 1:                                           //���Ͳ���״̬
				{
					for(i=0;i<10;i++)                         //�����ʱ2����
					{
						Sleep(200);                           //��ʱ200ms
						counts=myComm.GetInBufferCount();     //��ȡ���ջ������е��ַ���
						if(iSendStatus==101)     //iSendStatusΪ101̬ʱ����Ҫ����2���ַ�
						{
							if (counts>=2)
								break;
						}
						else//iSendStatusΪ102��105̬ʱֻ��Ҫ����1���ַ�
						{
							if (counts>=1)
								break;

						}
						
					}
					if(i==10)
					{
						m_Dis.SetSel(100000,100000);
						m_Dis.ReplaceSel("��ʱ����\12\15");
						m_Dis.SetSel(100000,100000);
						m_Dis.ReplaceSel("\12\15");
						UpdateData(false);
						return;
					}
					input1=myComm.GetInput();
					//��VARAIANT������ֵ��COleSafeArray���ʵ��
					safearray1=input1;            
					len1=safearray1.GetOneDimSize();//ʹ��COleSafeArray��ĳ�Ա������ȡ���ݳ���
					for(k=0;k<len1;k++)
					//ʹ��COleSafeArray��ĳ�Ա����������д������
						safearray1.GetElement(&k,rxdata+k);
					//AfxMessageBox(input2);
					switch(iSendStatus)
					{
					case 101:                                 //�ȴ�CONNECT ...
						{

							rxdata[len1]='\0';
							input2=rxdata;                    //�õ����յ��ַ���
							input2.MakeUpper();               //�����ַ�����Ϊ��д
							m_Dis.SetSel(100000,100000);      //������ʾ����
							m_Dis.ReplaceSel(input2);
							UpdateData(false);				
							if(input2.Find("CO")>=0)          //�յ�CONNECT 
							{
								iSendStatus=102;              //����״̬
							}
							break;
						}
					case 102:                                 //�ȴ�NAK ,Ȼ�󷢵�1֡����
						{
							
							if(rxdata[0]==21)                 //�յ�NAK 
							{
								m_Dis.SetSel(100000,100000);
								m_Dis.ReplaceSel("��ʼ�����ļ���\12\15");
								m_Dis.SetSel(100000,100000);
								m_Dis.ReplaceSel("\12\15");
								UpdateData(false);
								iSendCur=1;
								bytSendNow=1;
								charSendNow[0]=01;
								charSendNow[1]=01;
								charSendNow[2]=(char)0xFE;
								if(lFileLen<128)               //�ļ�����С��128�ֽڣ��貹�ո�
								{
									for(i=0;i<lFileLen;i++)
									{
										charSendNow[i+3]=charSendData[i];
									}
									for(i=lFileLen;i<128;i++)
									{
										charSendNow[i+3]=32;   //����ո�

									}
									iParityTemp=0;
									for(i=3;i<131;i++)
									{
										iParityTemp+=charSendNow[i];
									}
									iParityTemp=iParityTemp%256;
									charSendNow[131]=(char)iParityTemp;//���У��λCheckSum
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
									for(i=0;i<128;i++)              //ֱ�ӻ�ȡ������128�ֽ�����
									{
										charSendNow[i+3]=charSendData[i];
									}
									iParityTemp=0;
									for(i=3;i<131;i++)
									{
										iParityTemp+=charSendNow[i];
									}
									iParityTemp=iParityTemp%256;
									charSendNow[131]=(char)iParityTemp;//���У��λCheckSum
									ArraySend.RemoveAll();
									ArraySend.SetSize(132);
									for(i=0;i<132;i++)
									{
										ArraySend.SetAt(i,charSendNow[i]);
									}
									myComm.SetOutput(COleVariant(ArraySend)); //��������֡
									iSendStatus=103;                      //����״̬

								}

							} 
							SetTimer(1,2000,NULL);                //������ʱ��ʱ��
							break;
						}

					case 103:                                     //�ȴ�ACK��
						{

							switch(rxdata[0])
							{
							case 6:                               //��Ӧ��ACK
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

									if((iSendCur*128)>lFileLen)          //ʣ�����ݲ���128
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
											charSendNow[i+3]=32;         //����ո�

										}
										iParityTemp=0;
										for(i=3;i<131;i++)
										{
											iParityTemp+=charSendNow[i];
										}
										iParityTemp=iParityTemp%256;
										charSendNow[131]=(char)iParityTemp;//���У��λCheckSum
										ArraySend.RemoveAll();
										ArraySend.SetSize(132);
										for(i=0;i<132;i++)
										{
											ArraySend.SetAt(i,charSendNow[i]);
										}
										myComm.SetOutput(COleVariant(ArraySend)); 
										iSendStatus=104;
									}
									else//ʣ�����ݲ�С��128
									{
										charSendNow[0]=1;
										charSendNow[1]=bytSendNow;
										charSendNow[2]=255-charSendNow[1];
										for(i=0;i<128;i++)              //ֱ�ӻ�ȡ������128�ֽ�����
										{
											charSendNow[i+3]=charSendData[i+(iSendCur-1)*128];
										}
										iParityTemp=0;
										for(i=3;i<131;i++)
										{
											iParityTemp+=charSendNow[i];
										}
										iParityTemp=iParityTemp%256;
										charSendNow[131]=(char)iParityTemp;//���У��λCheckSum
										ArraySend.RemoveAll();
										ArraySend.SetSize(132);
										for(i=0;i<132;i++)
										{
											ArraySend.SetAt(i,charSendNow[i]);
										}
										myComm.SetOutput(COleVariant(ArraySend)); //��������֡

									}
									break;
								}
							case 21://��Ӧ��NAK
								{
									//�ط��ϴε�����֡
									myComm.SetOutput(COleVariant(ArraySend)); 
									break;

								}
							default:
								{
									m_Dis.SetSel(100000,100000);
									m_Dis.ReplaceSel("���յ���Ч���ַ�");
									UpdateData(false);
									iSendStatus=100;              //�ָ���ʼ״̬
									iRcvStatus=200;
									iActStatus=0;
									return;                       //ֱ���˳����մ������
									break;
								}
							}
							SetTimer(1,2000,NULL);                //������ʱ��ʱ��
							break;
						}
					case 104:                                    //�ȴ�ACK����EOT
						{

							switch(rxdata[0])
							{
							case 6:                              //��Ӧ��ACK
								{

									ArraySend.RemoveAll();
									ArraySend.SetSize(1);
									ArraySend.SetAt(0,4);
									myComm.SetOutput(COleVariant(ArraySend)); 
									iSendStatus=105;

									break;
								}
							case 21:                             //��Ӧ��NAK
								{
									//�ط��ϴε�����֡
									myComm.SetOutput(COleVariant(ArraySend)); 
									break;

								}
							default:
								{
									m_Dis.SetSel(100000,100000);
									m_Dis.ReplaceSel("���յ���Ч���ַ���\12\15");
									m_Dis.SetSel(100000,100000);
									m_Dis.ReplaceSel("\12\15");
									UpdateData(false);
									iSendStatus=100;              //�ָ���ʼ״̬
									iRcvStatus=200;
									iActStatus=0;
									return;                       //ֱ���˳����մ������
									break;
								}
							}
							SetTimer(1,2000,NULL);                //������ʱ��ʱ��

							break;
						}
					case 105:                                     //�ȴ�ACK,����ͨ��
						{

							switch(rxdata[0])
							{
							case 6:                               //��Ӧ��ACK
								{

									m_Dis.SetSel(100000,100000);
									m_Dis.ReplaceSel("������ϣ�\12\15");
									m_Dis.SetSel(100000,100000);
									m_Dis.ReplaceSel("\12\15");
									UpdateData(false);

									//��Modem����ʱ��ʹ����γ��򣬹�5�С�
									iSendStatus=100;
									iSendCur=1;
									iActStatus=0;
									bytSendNow=1;
									Beep(400,30);
									//��Modem���Գ���ν���

									//��������Modemʱ��ʹ����γ��򣬹�9�С�
									/*Sleep(1000);
									ArraySend.RemoveAll();
									ArraySend.SetSize(3);
									ArraySend.SetAt(0,43);                //��+++
									ArraySend.SetAt(1,43);                
									ArraySend.SetAt(2,43);                
									myComm.SetOutput(COleVariant(ArraySend)); 
									iSendStatus=106;                //�л�״̬��106
									SetTimer(1,2000,NULL);          //������ʱ��ʱ��
									*/
									//��Modem���Գ���ν���

									break;
								}
							case 21:   //��Ӧ��NAK
								{
									//�ط��ϴε�����֡
									myComm.SetOutput(COleVariant(ArraySend)); 
									SetTimer(1,2000,NULL);                //������ʱ��ʱ��							
									break;

								}
							default:
								{
									m_Dis.SetSel(100000,100000);
									m_Dis.ReplaceSel("���յ���Ч���ַ���\12\15");
									m_Dis.SetSel(100000,100000);
									m_Dis.ReplaceSel("\12\15");
									UpdateData(false);
									iSendStatus=100;                     //�ָ���ʼ״̬
									iRcvStatus=200;
									iActStatus=0;
									return;                              //ֱ���˳����մ������
									break;
								}
							}
							break;
						}
					case 106:                                           //�ȴ�Modem��Ӧ�����һ�����
						{
							//ֻҪ�յ�Modem����Ӧ��ִ�йһ�����
							ArraySend.RemoveAll();
							ArraySend.SetSize(5);
							ArraySend.SetAt(0,65);                //��"ATH\12\15"
							ArraySend.SetAt(1,84);                //
							ArraySend.SetAt(2,72);                //
							ArraySend.SetAt(3,10);                //
							ArraySend.SetAt(4,13);                //
							myComm.SetOutput(COleVariant(ArraySend)); 

							iSendStatus=100;                      //�ָ�Ϊ��ʼ״̬
							iSendCur=1;
							iActStatus=0;
							bytSendNow=1;
							Beep(400,30);
							break;
						}
					}

					break;
				}
			case 2:                                               //���ղ���״̬
				{
					switch(iRcvStatus)
					{
					case 201:                                     //�ȴ�CONNECT...
						{

							for(i=0;i<10;i++)                     //�����ʱ2����
							{
								Sleep(200);                       //��ʱ200ms
								counts=myComm.GetInBufferCount(); //��ȡ���ջ������е��ַ���
								if (counts>=2)
								{
									break;
								}
							}
							if(i==10)
							{
								m_Dis.SetSel(100000,100000);
								m_Dis.ReplaceSel("��ʱ����\12\15");
								m_Dis.SetSel(100000,100000);
								m_Dis.ReplaceSel("\12\15");
								UpdateData(false);
								iActStatus=0;
								iSendStatus=100;                   //�ָ���ʼ״̬
								iRcvStatus=200;
								return;
							}
							input1=myComm.GetInput();
							//��VARAIANT������ֵ��COleSafeArray���ʵ��
							safearray1=input1;            
							len1=safearray1.GetOneDimSize();      //ʹ��COleSafeArray��ĳ�Ա������ȡ���ݳ���
							for(k=0;k<len1;k++)
							//ʹ��COleSafeArray��ĳ�Ա����������д������
								safearray1.GetElement(&k,rxdata+k);

							rxdata[len1]='\0';
							input2=rxdata;                           //�õ����յ��ַ���
							input2.MakeUpper();                      //�����ַ�����Ϊ��д
							m_Dis.SetSel(100000,100000);             //������ʾ����
							m_Dis.ReplaceSel(input2);
							UpdateData(false);				
							if(input2.Find("CO")>=0)                 //���յ�CONNECT 
							{
								iRcvStatus=202;                      //����״̬
								ArraySend.RemoveAll();
								ArraySend.SetSize(1);
								ArraySend.SetAt(0,21);                //��NAK
								myComm.SetOutput(COleVariant(ArraySend)); 
							}

							SetTimer(1,2000,NULL);
							break;
						}
					case 202:                                         //�ȴ���һ֡����
						{

							for(i=0;i<10;i++)                         //�����ʱ2����
							{
								Sleep(200);                           //��ʱ200ms
								counts=myComm.GetInBufferCount();     //��ȡ���ջ������е��ַ���
								if (counts>=132)
								{
									break;
								}
							}
							if(i==10)
							{
								m_Dis.SetSel(100000,100000);
								m_Dis.ReplaceSel("��ʱ����\12\15");
								m_Dis.SetSel(100000,100000);
								m_Dis.ReplaceSel("\12\15");
								UpdateData(false);
								iActStatus=0;
								iSendStatus=100;               //�ָ���ʼ״̬
								iRcvStatus=200;
								return;
							}
							input1=myComm.GetInput();
							//��VARAIANT������ֵ��COleSafeArray���ʵ��
							safearray1=input1;            
							len1=safearray1.GetOneDimSize();//ʹ��COleSafeArray��ĳ�Ա������ȡ���ݳ���
							for(k=0;k<len1;k++)
							{
							//ʹ��COleSafeArray��ĳ�Ա����������д������
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
									m_Dis.ReplaceSel("���Դ������ޣ�\12\15");
									m_Dis.SetSel(100000,100000);
									m_Dis.ReplaceSel("\12\15");
									UpdateData(false);
									iRcvStatus=200;                       //�ָ���ʼ״̬
									iAgain=0;
									iActStatus=0;
									bytRcvNow=1;
									return;
								}
								else
								{
									ArraySend.RemoveAll();
									ArraySend.SetSize(1);
									ArraySend.SetAt(0,21);                //��NAK
									myComm.SetOutput(COleVariant(ArraySend)); 
								}

							}
							iParityTemp=0;
							for(i=3;i<131;i++)
							{
								iParityTemp+=rxdata[i];
							}
							iParityTemp=iParityTemp%256;
							if(rxdata[131]!=(BYTE)iParityTemp)            //��У��δͨ��
							{
								iAgain++;
								myStr.Format("%d",iAgain);
								m_Again=myStr;
								UpdateData(false);
								if (iAgain>10)
								{
									m_Dis.SetSel(100000,100000);
									m_Dis.ReplaceSel("���Դ������ޣ�\12\15");
									m_Dis.SetSel(100000,100000);
									m_Dis.ReplaceSel("\12\15");
									UpdateData(false);
									iActStatus=0;
									iRcvStatus=200;                      //�ָ���ʼ״̬
									iAgain=0;
									return;
								}
								else
								{
									ArraySend.RemoveAll();
									ArraySend.SetSize(1);
									ArraySend.SetAt(0,21);               //��NAK
									myComm.SetOutput(COleVariant(ArraySend)); 
								}

							}
							m_Dis.SetSel(100000,100000);
							m_Dis.ReplaceSel("��ʼ�����ļ���\12\15");
							m_Dis.SetSel(100000,100000);
							m_Dis.ReplaceSel("\12\15");
							UpdateData(false);
							iRcvCur=1;                                   //���մ���Ϊ1
							bytRcvNow=1;                                 //֡���Ϊ1
							for(i=0;i<128;i++)
							{
								charRcvData[i]=rxdata[i+3];
							}
							iRcvStatus=203;
							ArraySend.RemoveAll();
							ArraySend.SetSize(1); 
							ArraySend.SetAt(0,6);                       //��ACK
							myComm.SetOutput(COleVariant(ArraySend)); 

							SetTimer(1,2000,NULL);
							break;
						}

					case 203:                                          //�ȴ����ݣ���������֡��EOT֡
						{

							myComm.SetInputLen(1);                     //����ֻ��һ���ַ�
							input1=myComm.GetInput();
							myComm.SetInputLen(0);                     //���ö�ȫ��������
							//��VARAIANT������ֵ��COleSafeArray���ʵ��
							safearray1=input1;    
							k=0;
							safearray1.GetElement(&k,rxdata);
							switch(rxdata[0])
							{
							case 4:                                    //�յ�EOT
								{

									//myStr="txt";
									myFileDlg.m_ofn.lpstrFilter="*.TXT";
									myFileDlg.m_ofn.lpstrDefExt="txt";
									myFileDlg.m_ofn.lpstrTitle="�����ı��ļ�";
									//�����ļ�ѡ��Ի���ѡ�񱣴��ļ�
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
										m_Dis.ReplaceSel("ȡ�������ļ���\12\15");
										m_Dis.SetSel(100000,100000);
										m_Dis.ReplaceSel("\12\15");
										UpdateData(false);
										return;
									}
									myPathName.Replace("\\","\\\\");  //���ļ����еĵ���\���滻��˫��\\��

									//��ѡ�����ļ�
									if(!myFile.Open(myPathName,CFile::modeWrite|CFile::modeCreate,&e))//
									{
										myStr.Format("%02X",e.m_cause);//�ļ��򿪴������������Ϊm_cause
										myStr+="error";
										AfxMessageBox(myStr);
										return;
									}
									myFile.SetLength(0);//iRcvCur*128);
									myFile.Write(charRcvData,iRcvCur*128);
									myFile.Close();	
									m_Dis.SetSel(100000,100000);
									m_Dis.ReplaceSel("�ļ��ѱ��棡\12\15");
									m_Dis.SetSel(100000,100000);
									m_Dis.ReplaceSel("\12\15");
									UpdateData(false);

									ArraySend.RemoveAll();
									ArraySend.SetSize(1);
									ArraySend.SetAt(0,6);                //��ACK
									myComm.SetOutput(COleVariant(ArraySend)); 

									//��Modem����ʱ��ʹ����δ��룬��6�С�
									iRcvStatus=200;                     //�ָ�Ϊ��ʼ״̬
									iRcvCur=1;
									iActStatus=0;
									iAgain=0;
									bytRcvNow=1;
									Beep(400,30);
									//��Modem���Դ��������

									//����ʹ��ʱ��ʹ����δ��룬��9�С�
									/*Sleep(1000);
									ArraySend.RemoveAll();
									ArraySend.SetSize(3);
									ArraySend.SetAt(0,43);                //��+++
									ArraySend.SetAt(1,43);                //
									ArraySend.SetAt(2,43);                //
									myComm.SetOutput(COleVariant(ArraySend)); 
									iRcvStatus=204;                       //�л�״̬��204
									SetTimer(1,2000,NULL);                //������ʱ��ʱ��*/
									//����ʹ�ô��������
									
									break;
								}
							case 1://�յ�SOH
								{
									
									for(i=0;i<10;i++)                         //�����ʱ2����
									{
										Sleep(200);                           //��ʱ200ms
										counts=myComm.GetInBufferCount();     //��ȡ���ջ������е��ַ���
										if (counts>=131)
										{
											break;
										}
									}
									if(i==10)
									{
										m_Dis.SetSel(100000,100000);
										m_Dis.ReplaceSel("��ʱ����\12\15");
										m_Dis.SetSel(100000,100000);
										m_Dis.ReplaceSel("\12\15");
										UpdateData(false);
										iActStatus=0;
										iSendStatus=100;               //�ָ���ʼ״̬
										iRcvStatus=200;
										return;
									}
									input1=myComm.GetInput();
									//��VARAIANT������ֵ��COleSafeArray���ʵ��
									safearray1=input1;            
									len1=safearray1.GetOneDimSize();//ʹ��COleSafeArray��ĳ�Ա������ȡ���ݳ���
									for(k=0;k<len1;k++)
									{
									//ʹ��COleSafeArray��ĳ�Ա����������д������
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
											m_Dis.ReplaceSel("���Դ������ޣ�\12\15");
											m_Dis.SetSel(100000,100000);
											m_Dis.ReplaceSel("\12\15");
											UpdateData(false);
											iRcvStatus=200;                 //�ָ���ʼ״̬
											iAgain=0;
											iRcvCur=1;
											iActStatus=0;
											iSendStatus=100;               //�ָ���ʼ״̬
											bytRcvNow=1;
											return;
										}
										else
										{
											ArraySend.RemoveAll();
											ArraySend.SetSize(1);
											ArraySend.SetAt(0,21);                //��NAK
											myComm.SetOutput(COleVariant(ArraySend)); 
										}

									}
									iParityTemp=0;
									for(i=3;i<131;i++)
									{
										iParityTemp+=rxdata[i];
									}
									iParityTemp=iParityTemp%256;
									if(rxdata[131]!=(BYTE)iParityTemp)  //��У��δͨ��
									{
										iAgain++;
										myStr.Format("%d",iAgain);
										m_Again=myStr;
										UpdateData(false);
										if (iAgain>10)
										{
											m_Dis.SetSel(100000,100000);
											m_Dis.ReplaceSel("���Դ������ޣ�\12\15");
											m_Dis.SetSel(100000,100000);
											m_Dis.ReplaceSel("\12\15");
											UpdateData(false);
											iRcvStatus=200;                 //�ָ���ʼ״̬
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
											ArraySend.SetAt(0,21);                //��NAK
											myComm.SetOutput(COleVariant(ArraySend)); 
										}

									}

									if(rxdata[1]==bytRcvNow+1 ||(rxdata[1]==0 && bytRcvNow==255))
									{
										iRcvCur++;               //���մ�����1
										myStr.Format("%d",iRcvCur);
										m_Number=myStr;
										UpdateData(false);
										if(bytRcvNow<255)//֡��ż�1
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
										ArraySend.SetAt(0,6);                //��ACK
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
											ArraySend.SetAt(0,6);                //��ACK
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
							//ֻҪ�յ�Modem����Ӧ��ִ�йһ�����
							ArraySend.RemoveAll();
							ArraySend.SetSize(5);
							ArraySend.SetAt(0,65);                //��"ATH\12\15"
							ArraySend.SetAt(1,84);                //
							ArraySend.SetAt(2,72);                //
							ArraySend.SetAt(3,10);                //
							ArraySend.SetAt(4,13);                //
							myComm.SetOutput(COleVariant(ArraySend)); 

							iRcvStatus=200;                        //�ָ�Ϊ��ʼ״̬
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
	//����ʹ�õĴ��룬��9�С�
	/*
	CString	myStr;
	myStr="ats0=1\12\15";              //�Զ�Ӧ��
	myComm.SetOutput(COleVariant(myStr));
	m_Dis.SetSel(100000,100000);
	m_Dis.ReplaceSel("�ȴ���Է�����...");
	UpdateData(false);
	iActStatus=2;
	iRcvStatus=201;                   //�л�״̬Ϊ201
	SetTimer(1,2000,NULL);            //������ʱ��ʱ��
	*/
	//����ʹ�ô��������

	//��Modem����ʹ�õĴ���Σ���8�С�
	iActStatus=2;
	iRcvStatus=202;
	iSendStatus=100;
	ArraySend.RemoveAll();
	ArraySend.SetSize(1);
	ArraySend.SetAt(0,21);            //��NAK
	myComm.SetOutput(COleVariant(ArraySend)); 
	SetTimer(1,2000,NULL);
	//��Modem���Դ��������-

	this->SetWindowText("�����ļ�");
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
							m_Dis.ReplaceSel("���ͳ���\12\15");
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
							m_Dis.ReplaceSel("���ճ���\12\15");
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
							m_Dis.ReplaceSel("���ճ���\12\15");
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
