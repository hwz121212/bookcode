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


HANDLE hCom;                                //���ڵľ��
HANDLE hThreadEvent;                      //�¼��߳̾��
DWORD ThreadProcEvent(LPVOID pParam);      //�¼���Ӧ����
bool fEventRun;                            //�¼��̺߳���ִ�б�־
HWND hWnd;                                  //���ھ��
DWORD dwThreadID;                          //�¼��߳�ID
OVERLAPPED Eol={0};                       //�¼��߳�ʹ�õ�OVERLAPPED�ṹEol
OVERLAPPED Wol={0};                       //д����ʹ�õ�OVERLAPPED�ṹWol
OVERLAPPED Rol={0};                       //������ʹ�õ�OVERLAPPED�ṹRol
DWORD	dwTimeoutValue;					//������ճ�ʱʱ�䣬msΪ��λ,���¼��߳���ʹ��


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
	myCom="COM4";            //Ĭ������
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
		m_pStatus->SetPaneText(1,strStatus);     //��ͨ�Ų�����ʾ��״̬����
		blnSeted=true;
		
	}
}

void CPC2PCView::OnSendfile() 
{
	// TODO: Add your command handler code here
	
	CFileDialog myFileDlg(true);      //���ļ��Ի���
	CEdit& myEdit=this->GetEditCtrl();
	BYTE bytFileNameLen;              //�ļ����ַ����ĳ���
	BYTE bytTemp;
	DWORD dwTemp1,dwTemp2;
	int i;
	CString myStr,myFileName,myPathName;
	CFileException e;                 //�ļ��쳣����
	bytActStatus=1;                   //��Ϊ����̬
	if(myFileDlg.DoModal()==IDOK)     //�����ļ�ѡ��Ի���ѡ���͵��ļ�
	{
		myPathName=myFileDlg.GetPathName();
		myFileName=myFileDlg.GetFileName();
		if(myFileName.GetLength()>100)
		{
			AfxMessageBox("�ļ�������ӦС��100!");	
			bytActStatus=10;          //�ָ�Ϊ����̬
			return;
		}
		else
		{
			bytFileNameLen=(BYTE)myFileName.GetLength();
		}
	}
	else
	{
		bytActStatus=10;              //�ָ�Ϊ����̬

		return;
	}
	myPathName.Replace("\\","\\\\");  //���ļ����еĵ���\���滻��˫��\\��

	//��ѡ�����ļ�
	if(!myFile.Open(myPathName,CFile::modeRead|CFile::typeBinary|CFile::shareDenyWrite,&e))
	{
		myStr.Format("%02X",e.m_cause);//�ļ��򿪴������������Ϊm_cause
		myStr+="error";
		AfxMessageBox(myStr);
		bytActStatus=10;               //�ָ�Ϊ����̬
		return;
	}
	dwFileLen=myFile.GetLength();
	if(dwFileLen>=67108864)
	{
		AfxMessageBox("�ļ�����С��64M��");//����ļ��ߴ�<64��
		bytActStatus=10;                //�ָ�Ϊ����̬
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
	
	for(i=6;i<=bytFileNameLen+5;i++)    //���ļ�����
	{
		arrSendData[i]=myFileName.GetAt(i-6);
	}
	
	bytTemp=0;

	for(i=0;i<=bytFileNameLen+5;i++)
	{
		bytTemp^=arrSendData[i];
	}
	arrSendData[bytFileNameLen+6]=bytTemp;//�����У��λ

	bytSendStatus=1;
	bytResendCount=0;

	Write(arrSendData,bytFileNameLen+7);
	myEdit.SetSel(1000000,1000000);
	myEdit.ReplaceSel("������������\15\12");

	blnNoTimeout=false;

}

void CPC2PCView::OnOpencom() 
{
	// TODO: Add your command handler code here
	//�򿪴��ڲ���
	hCom=CreateFile(myCom,              //�򿪴���COM2
		GENERIC_READ | GENERIC_WRITE, //ʹ�ö�д��ʽ
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, //ʹ���ص���ʽ
		NULL);
	if( hCom !=INVALID_HANDLE_VALUE) 
	{
		SetupComm(hCom,1500,1500);      //���÷��ͻ���512�����ջ�����1500
		DCB myDCB;
		GetCommState( hCom, &myDCB ); //��ȡ��ǰ���ڲ���
		myDCB.BaudRate=myBaudRate;
		myDCB.fBinary=TRUE;
		myDCB.fParity=myfParity;
		myDCB.ByteSize=8;
		myDCB.Parity=myParity;
		myDCB.StopBits=ONESTOPBIT;
		SetCommState(hCom,&myDCB);     //���ô���ͨѶ����
		blnOpened=true;

		//����������ִ���̺߳���
		DWORD dwParam;
		if (!SetCommMask(hCom,EV_RXCHAR))// | EV_TXEMPTY))//����������¼�����
		{
			AfxMessageBox("�����¼�����ʧ�ܣ�");
		}
		hThreadEvent=CreateThread(NULL,                 //�����¼��߳�
			0,
			(LPTHREAD_START_ROUTINE )ThreadProcEvent,   //ָ���̺߳�������
			&dwParam,
			0,                                               //�����̺߳���������ִ��
			&dwThreadID);
		if (hThreadEvent==INVALID_HANDLE_VALUE)
		{
			AfxMessageBox("�¼��̴߳���ʧ�ܣ�");
		}
		fEventRun=true;                                    //�����¼�����ִ��ѭ����
		bytActStatus=10;
		bytSendStatus=0;
		bytRcvStatus=0;
		bytResendCount=0;
		uintStxCurNo=0;
	}
	else
	{
		AfxMessageBox("��������ʧ�ܣ�");
	}
	
}

void CPC2PCView::OnClosecom() 
{
	// TODO: Add your command handler code here
	fEventRun=false;                     //ֹͣ�¼��߳�ѭ����Ĳ���
	WaitForSingleObject(hThreadEvent,    //�ȴ��¼��̺߳����˳�
		INFINITE);                        //����ʱ�صȴ���ֱ���¼��̺߳����˳�
	CloseHandle(hThreadEvent);        //�ر��¼��߳̾��
	CloseHandle(hCom);                  //�رմ��ھ��
	blnOpened=false;
}

//�¼��̺߳���
DWORD ThreadProcEvent(LPVOID pParam)
{
	DWORD dwErrors;
	COMSTAT Rcs;
	DWORD dwEvtMask,dwRes;
	Eol.hEvent=CreateEvent(NULL, //����Eol.hEvent��ԱΪ���ź�״̬
		TRUE, 
		FALSE, 
		NULL);
	while(fEventRun)
	{
		WaitCommEvent(hCom,                            //���Ӵ����¼�
			&dwEvtMask,                                 //����¼��������ֵ
			&Eol);                                       //OVERLAPPED�ṹ
		dwRes=WaitForSingleObject(Eol.hEvent,        //�ȴ����¼�������
			dwTimeoutValue);                       //��ʱʱ�䣨ms��
		
		switch (dwRes)
		{
			case  WAIT_OBJECT_0:                      //�ɹ��õ��¼����ӽ��
				{
					switch (dwEvtMask)
					{
					case EV_RXCHAR:                      //���յ�����
						{
							//�����̷߳�����Ϣ�����յ�����
							ClearCommError(hCom,                //���ھ��
								&dwErrors,                        //��ų�����Ϣ���������
								&Rcs);                             //COMSTAT���ͽṹ����
							if(Rcs.cbInQue!=0)
							{
							::PostMessage(hWnd,         //Ŀ�Ĵ��ھ��
								WM_MYMSG,              //��Ϣ����
								0,                      //���ݵĲ���1
								(LPARAM)EV_RXCHAR );    //���ݵĲ���2
							}
							break;
						}
					case EV_TXEMPTY:                    //���ͻ������ѿ�
						{
							   //����ɼ��뷢�ͻ������յĴ�����룬�������̷߳�����Ϣ
							break;
						}
					}
					break;
				}

			case WAIT_TIMEOUT:
				{
					//���ݳ�ʱ��Ϣ�����߳�
					::PostMessage(hWnd,         //Ŀ�Ĵ��ھ��
						WM_MYMSG,              //��Ϣ����
						0,                      //���ݵĲ���1
						(LPARAM)100 );         //���ݵĲ���100
					break;
				}
		}
	}
	return true;
}

//��Ϣ��Ӧ����
LONG CPC2PCView::OnReceiveEvent(WPARAM wParam,LPARAM lParam)
{
	CFileDialog myFileDlg(false);         //�����ļ��Ի���
	BYTE myByte[1100];
	BYTE bytTemp;
	CString strDis,strDis1;
	char *myChar;                       //��ȡ�ļ���ʱʹ��
	char myName[300];
	char myExt[5];
	int i;
	CEdit& myEdit=this->GetEditCtrl();
	CMainFrame* m_pGetFrame=(CMainFrame*) AfxGetApp()->m_pMainWnd ;
	CStatusBar* m_pStatus=&m_pGetFrame->m_wndStatusBar;
	CFileException e;

	switch(bytActStatus)
	{
	case 1://���Ͳ���
		{
			switch(bytSendStatus)//���͵Ĳ�ͬ״̬
			{
			case 1://���Ͳ�����1̬
				{
					switch(lParam)
					{
					case EV_RXCHAR://lParam��EV_RXCHAR��1��˵�����߳��յ�����
						{
							blnNoTimeout=true;
							bytTimeoutCounter=0;
							switch(Detect(1))
							{
							case 0://�յ�ָ���������ַ�
								{
									break;
								}
							case 4://��ʱ����
								{
									DisSend(4);
									blnNoTimeout=false;
									return -1;
									break;
								}

							case 8://��Ч�����뻺�������ַ�����Ϊ0
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
									//��������Ĳ���
									break;
								}
							case 4://��ʱ����
								{
									DisSend(4);
									return -1;
									break;
								}
							case 16://������ʧ��
								{
									DisSend(16);
									return -1;
									break;
								}
							}
							switch(myByte[0])
							{
							case 6://��Ӧ��ACK��
								{
									//���͵�ǰ��ŵ�����
									uintStxCurNo=1;

									myEdit.SetSel(1000000,1000000);
									myEdit.ReplaceSel("���ڴ�������...\15\12");

									if((uintStxCurNo*1024)<dwFileLen)
									{
										//
										arrSendData[0]=02;//STX����Ӧ02
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
										arrSendDataLast[1027]=arrSendData[1027];//���汾�η��͵����ݺ����ݸ���
										uintSendLenLast=uintSendLen;
										Write(arrSendData,1028);
										bytSendStatus=2;
										bytResendCount=0;

									}
									else
									{
										arrSendData[0]=03;//ETX����Ӧ03
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
										arrSendDataLast[uintSendLen-1]=arrSendData[uintSendLen-1];//���汾�η��͵����ݺ����ݸ���
										uintSendLenLast=uintSendLen;
										blnNoTimeout=false;
										bytSendStatus=3;
										Write(arrSendData,uintSendLen);
										bytResendCount=0;
									}
									break;
								}
							case 21://��Ӧ��NAK��
								{
									
									break;
								}
							case 24://��Ӧ��CAN��
								{
									DisSend(1);
									break;
								}
							default:
								{
									DisSend(2);//�յ���Ч�ַ�
									return -1;
									break;

								}
							}

							blnNoTimeout=false;      //����ʱ
							break;
						}
					case 100://lParam=100����ʾ�¼��̶߳���ʱ
						{
							if((!blnNoTimeout)&&(bytTimeoutCounter>20))
							{
								DisSend(4);
								bytTimeoutCounter=0;
							}
							else
							{
								if(bytTimeoutCounter<255)//���ʹ����������ʱʱ��Ӧ�ó�Щ��
									bytTimeoutCounter++;//�������ý��ն�ѡ�񱣴��ļ�λ����Ҫ��ʱ�䡣

							}
							break;
						}
					}
					break;
				}
			case 2://���Ͳ�����2̬
				{
					switch(lParam)
					{
					case EV_RXCHAR://lParam��EV_RXCHAR��1��˵�����߳��յ�����
						{
							blnNoTimeout=true;
							switch(Detect(1))
							{
							case 0://�յ�ָ���������ַ�
								{
									break;
								}
							case 4://��ʱ����
								{
									DisSend(4);
									blnNoTimeout=false;
									return -1;
									break;
								}

							case 8://��Ч�����뻺�������ַ�����Ϊ0
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
									//��������Ĳ���
									break;
								}
							case 4://��ʱ����
								{
									DisSend(4);
									blnNoTimeout=false;
									return -1;
									break;
								}
							case 16://������ʧ��
								{
									DisSend(16);
									blnNoTimeout=false;
									return -1;
									break;
								}
							}
							switch(myByte[0])
							{
							case 6://��Ӧ��ACK
								{
									//���͵�ǰ��ŵ�����

									uintStxCurNo++;//��������ż�1

									if((uintStxCurNo*1024)<dwFileLen)//�����������1024����֡,��STX��Ϊ���ݵ���ʼλ
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
										arrSendDataLast[1027]=arrSendData[1027];//���汾�η��͵����ݺ����ݸ���
										uintSendLenLast=uintSendLen;
										Write(arrSendData,uintSendLen);
										blnNoTimeout=false;
										bytSendStatus=2;
										bytResendCount=0;

										strDis.Format("�Ѵ���(%.0f%%)",(float)((uintStxCurNo+1)*1024)/dwFileLen*100);
										m_pStatus->SetPaneText(0,strDis);     //�����������ʾ��״̬����

									}
									else//�������������1024����֡����ETX��Ϊ���ݵ���ʼλ��
									{
										
										arrSendData[0]=03;//ETX����Ӧ03
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
										arrSendDataLast[uintSendLen-1]=arrSendData[uintSendLen-1];//���汾�η��͵����ݺ����ݸ���
										uintSendLenLast=uintSendLen;
										bytSendStatus=3;
										Write(arrSendData,uintSendLen);

										strDis="�Ѵ���(100%)";
										m_pStatus->SetPaneText(0,strDis);     //�����������ʾ��״̬����
										blnNoTimeout=false;
										bytResendCount=0;

									}
									break;
								}
							case 21://��Ӧ��NAK
								{
									
								
									break;
								}
							case 24://��Ӧ��CAN
								{
									
								
									break;
								}
							default:
								{
								
									break;
								}
							}

							blnNoTimeout=false;      //����ʱ
							break;
						}
					case 100://lParam=100����ʾ�¼��̶߳���ʱ
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
			case 3://���Ͳ�����3̬
				{
					
					switch(lParam)
					{
					case EV_RXCHAR://lParam��EV_RXCHAR��1��˵�����߳��յ�����
						{
							blnNoTimeout=true;
							switch(Detect(1))
							{
							case 0://�յ�ָ���������ַ�
								{
									break;
								}
							case 4://��ʱ����
								{
									DisSend(4);
									blnNoTimeout=false;
									return -1;
									break;
								}

							case 8://��Ч�����뻺�������ַ�����Ϊ0
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
									//��������Ĳ���
									break;
								}
							case 4://��ʱ����
								{
									DisSend(4);
									blnNoTimeout=false;
									return -1;
									break;
								}
							case 16://������ʧ��
								{
									DisSend(16);
									blnNoTimeout=false;
									return -1;
									break;
								}
							}
							if(myByte[0]==6)//��Ӧ��ACK��
							{

								myEdit.SetSel(1000000,1000000);
								myEdit.ReplaceSel("������ϣ�\15\12\15\12");

								strDis="�Ѵ������";
								m_pStatus->SetPaneText(0,strDis);//�����������ʾ��״̬����
								if(myFile.m_pStream!=NULL)
								{
									myFile.Close();     //�رմ򿪵��ļ�
								}
								uintStxCurNo=0;      //�����������0
								bytSendStatus=0;
								bytResendCount=0;
								bytRcvStatus=0;
								bytActStatus=10;


							}
							else//��Ӧ����ACK
							{
								if(myByte[0]==21)//��Ӧ��NAK��
								{
									bytResendCount++;
									if(bytResendCount>3)
									{
										DisSend(8);
										uintStxCurNo=0;//�����������0
										bytActStatus=10;
										bytSendStatus=0;
										bytResendCount=0;

									}
									else
									{
										Write(arrSendDataLast,uintSendLenLast);

										strDis.Format("�ط�%d�Σ�\15\12",bytResendCount);
										myEdit.SetSel(1000000,1000000);
										myEdit.ReplaceSel(strDis);
									}
								}
								else
								{
									DisSend(2);
									uintStxCurNo=0;//�����������0
									bytActStatus=10;
									bytSendStatus=0;
									bytResendCount=0;
								}

							}

							blnNoTimeout=false;      //����ʱ
							break;
						}
					case 100://lParam=100����ʾ�¼��̶߳���ʱ
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
	case 10://����״̬
		{
			switch(bytRcvStatus)
			{
			case 0:
				{
					switch(lParam)
					{
					case EV_RXCHAR://�յ�����
						{
							switch(Detect(6))
							{
							case 0://�յ�ָ���������ַ�
								{
									break;
								}
							case 4://��ʱ����
								{
									DisRcv(4);
									return -1;
									break;
								}

							case 8://��Ч�����뻺�������ַ�����Ϊ0
								{
									return 0;
									break;
								}

							}

							switch(Read(myByte,6))
							{
							case 0://�ɹ���������
								{
									//ֱ������switch�������������
									break;
								}
							case 4://��ʱ����
								{
									DisRcv(4);
									return -1;
									break;
								}
							case 16://������ʧ��
								{
									DisRcv(16);
									return -1;
									break;
								}
							}
							//�����ﴦ������ݲ��������ݴ����myByte��
							for(i=0;i<=5;i++)
							{
								arrRcvData[i]=myByte[i];
							}
							if(arrRcvData[0]==5)
							{
								//���������ܳ���
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
									//ֱ������switch�������������
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
								arrRcvData[i+6]=myByte[i];//�洢����
							}

							//У�����
							bytTemp=0;
							for(i=0;(UINT)i<=(uintRcvLen-2);i++)
							{
								bytTemp^=arrRcvData[i];
							}
							if(bytTemp!=arrRcvData[uintRcvLen-1])//��У�����
							{
								bytResendCount++;
								if (bytResendCount>3)//���Դ�������3
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
							//���ˣ�����У��������������Ѿ�����arrRcvData[]��������
							myEdit.SetSel(1000000,1000000);
							myEdit.ReplaceSel("�յ���������\15\12");
							//��ȡ�ļ�����
							if((myChar=new char[arrRcvData[5]+1])==NULL)
							{
								AfxMessageBox("������ڴ�ʱ����");
								//���ͷ���ӦCAN����ȡ�����δ���
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
							//�򿪶Ի�����ʾ�û������ļ�	
							
							myFileDlg.m_ofn.lpstrFile=myName;
							myFileDlg.m_ofn.lpstrFilter=myExt;
							if(myFileDlg.DoModal()==IDOK)
							{
								strDis=myFileDlg.GetPathName();
							}
							else
							{
								//���ͷ���ӦCAN����ȡ�����δ���
								arrSendData[0]=24;
								Write(arrSendData,1);
								DisRcv(1);
								return -1;
							}
							strDis.Replace("\\","\\\\");
							strDis+=myExt;
							if(!myFile.Open(strDis,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary,&e))
							{
								strDis.Format("�ļ���ʱ�����쳣���������Ϊ��%d��",e.m_cause);//�ļ��򿪴������������Ϊm_cause
								//strDis+="error";
								AfxMessageBox(strDis);
								bytActStatus=10;                //�ָ�Ϊ����̬
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
					case 100://��ʱ����
						{
							//����0̬ʱ���Գ�ʱ��������
							break;
						}
					
					}
					break;
				}
			case 1:
				{
					switch(lParam)
					{
					case EV_RXCHAR://�յ��ַ�
						{
							switch(Detect(1))
							{
							case 0://�յ�ָ���������ַ�
								{
									break;
								}
							case 4://��ʱ����
								{
									DisRcv(4);
									return -1;
									break;
								}

							case 8://��Ч�����뻺�������ַ�����Ϊ0
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
							switch(myByte[0])//�ж���STX����ETX
							{
							case 2://���ַ���STX
								{
									//��ȡ����
									arrRcvData[0]=myByte[0];
									uintRcvLen=1028;
									switch(Detect(1027))
									{
									case 0://�յ�ָ���������ַ�
										{
											//����switch����������Ĳ���
											break;
										}
									case 4://��ʱ����
										{
											DisRcv(4);
											return -1;
											break;
										}

									case 8://��Ч�����뻺�������ַ�����Ϊ0
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
										arrRcvData[i+1]=myByte[i];//����������arrRcvData[]������
									}
									
									uintStxCurNo=arrRcvData[1]+arrRcvData[2]*256;
									if(uintStxCurNo==1)
									{
										myEdit.SetSel(1000000,1000000);
										myEdit.ReplaceSel("���ڽ�������...\15\12");
									}
									strDis.Format("�ѽ���(%.0f%%)",(float)((uintStxCurNo+1)*1024)/dwFileLen*100);
									m_pStatus->SetPaneText(0,strDis);     //�����������ʾ��״̬����
									myFile.Seek((uintStxCurNo-1)*1024,CFile::begin);
									myFile.Write(&arrRcvData[3],1024);

									bytResendCount=0;
									arrSendData[0]=6;
									Write(arrSendData,1);
									
									break;
								}

							case 3://���ַ���ETX
								{
									//��ȡ����
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
									uintRcvLen=1+2+2+(arrRcvData[1]+arrRcvData[2]*256)+1;//�����ܳ���

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
									//���ˣ����������Ѿ�����arrRcvData[]�С�
									uintStxCurNo=arrRcvData[3]+arrRcvData[4]*256;
									if(uintStxCurNo==1)
									{
										myEdit.SetSel(1000000,1000000);
										myEdit.ReplaceSel("���ڽ�������...\15\12");
									}
									myFile.Seek((uintStxCurNo-1)*1024,CFile::begin);
									myFile.Write(&arrRcvData[5],arrRcvData[1]+arrRcvData[2]*256);

									myEdit.SetSel(1000000,1000000);
									myEdit.ReplaceSel("������ϣ�\15\12\15\12");
									strDis="�ѽ������";
									m_pStatus->SetPaneText(0,strDis);     //�����������ʾ��״̬����
									bytRcvStatus=0;
									bytActStatus=10;
									bytSendStatus=0;
									bytResendCount=0;
									arrSendData[0]=6;
									Write(arrSendData,1);
									if(myFile.m_pStream!=NULL)
									{
										myFile.Close();//�رմ򿪵��ļ�
									}
									break;
								}
							}
							break;
						}
					case 100://��ʱ����
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
	if (blnOpened)//���ݴ����Ƿ�򿪣������Ƿ����������ļ�������
	{
		if(!((bytSendStatus+bytRcvStatus)>0))//��ǰ��û��ʼ���ͣ�Ҳû��ʼ����
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
	if (!blnOpened)//���ݴ����Ƿ�򿪣������Ƿ��������á�����
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
	if (!blnOpened && blnSeted)//���ݴ����Ƿ�򿪣������Ƿ������򿪡�����
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
	if (blnOpened)//���ݴ����Ƿ�򿪣������Ƿ������رա�����
	{
		if(!((bytSendStatus+bytRcvStatus)>0))//��ǰ��û��ʼ���ͣ�Ҳû��ʼ����
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
	myEdit.SetReadOnly (true);                         //����ʾ������Ϊֻ��
	hWnd=GetSafeHwnd();                                    //��ȡ��ǰ���ڵľ��

	blnOpened=false;     //�����Ѿ��򿪱�־
	blnSeted=false;      //�Ѿ����ù�ͨ�Ų���
	bytRcvStatus=0;      //��ʼ��ʱ������״̬Ϊ�ȴ�ENQ
	dwTimeoutValue=1500; //��ʼ���¼��̳߳�ʱʱ��
	bytActStatus=10;     //��ʼ��Ϊ����̬
	blnNoTimeout=true;
	uintStxCurNo=0;
	bytTimeoutCounter=0;
	return 0;
}
bool CPC2PCView::DisSend(BYTE bytType)//����̬��ʾ��Ϣ������bytType������ʾ��Ϣ������
{
	CString strDis;
	CEdit& myEdit=this->GetEditCtrl();
	myEdit.SetReadOnly(true);
	myEdit.SetSel(1000000,1000000);
	switch(bytType)
	{
	case 1:
		{
			strDis="ȡ��������\15\12";
			break;
		}
	case 2:
		{
			strDis="�յ���Ч�����\15\12";
			break;
		}
	case 4:
		{
			strDis="�Է�����Ӧ����ʱ����\15\12";
			break;
		}
	case 8:
		{
			strDis="���Դ�������3�Σ�\15\12";
			break;
		}
	}
		
	myEdit.ReplaceSel(strDis);
	bytSendStatus=0;//�ָ�����0̬
	bytActStatus=10;//�ָ�Ϊ����̬
	bytRcvStatus=0;
	bytResendCount=0;//���Դ�����ʼ��Ϊ0
	if(myFile.m_pStream!=NULL)
	{
		myFile.Close();//�رմ򿪵��ļ�
	}
	Beep(1000,50);
	return true;

}
bool CPC2PCView::DisRcv(BYTE bytType)//����̬��ʾ��Ϣ������bytType������ʾ��Ϣ������
{
	CString strDis;
	CEdit& myEdit=this->GetEditCtrl();
	myEdit.SetReadOnly(true);
	myEdit.SetSel(1000000,1000000);
	switch(bytType)
	{
	case 1:
		{
			strDis="ȡ��������\15\12";
			break;
		}
	case 2:
		{
			strDis="�յ���Ч�����\15\12";
			break;
		}
	case 4:
		{
			strDis="�Է�����Ӧ����ʱ����\15\12";
			break;
		}
	case 8:
		{
			strDis="���Դ�������3�Σ�\15\12";
			break;
		}
	}
		
	myEdit.ReplaceSel(strDis);
	bytRcvStatus=0;           //�ָ�����0̬
	bytActStatus=10;          //�ָ�Ϊ����̬
	bytSendStatus=0;          //����̬�ָ�Ϊ0̬
	bytResendCount=0;         //���Դ�����ʼ��Ϊ0
	if(myFile.m_pStream!=NULL)
	{
		myFile.Close();       //�رմ򿪵��ļ�
	}
	return true;
}
BYTE CPC2PCView::Read(BYTE arrBin[],int count)//�����ݺ�����arrBin[]������ݣ�count�Ƕ��ĸ���
{									//�ɹ�����0����ʧ�ܷ���16����ʱ���󷵻�4
	DWORD dwRes;
	DWORD dwRead;
	Rol.hEvent=CreateEvent(NULL, //����Rol.hEventΪ���ź�״̬
		TRUE,                 
		FALSE, 
		NULL);
	if (ReadFile(hCom,
		arrBin,
		count,                     //��ȡcount���ֽ�
		NULL,
		&Rol))
	{
		 //���ڽ��յ������Ѿ��ɹ��������������arrBin[]������
		return 0;
	}
	else
	{
		dwRes = WaitForSingleObject(Rol.hEvent, 
			2000);                      //����2��Ķ���ʱ
		switch(dwRes)
		{
		case WAIT_OBJECT_0:
			{
				 if (!GetOverlappedResult(hCom, 
						&Rol, 
						&dwRead,             //ʵ�ʶ�ȡ�ֽ��������dwRead��
						TRUE))
				 {   
					 //������ʧ�ܡ�ʹ��GetLastError�����������Ի�ȡ������Ϣ
						return 16;
				 }
				 else
				 {
					   //���ڽ��յ������Ѿ��ɹ��������������arrBin[]������
					 return 0;
				 }
				 break;
			}
		case WAIT_TIMEOUT:
			{
				//���������ֳ�ʱ����
				return 4;
			}
		}
	}
	return 0;
}



//�������ݺ�����arrBin[]������ݣ�count�Ƿ��͸���
//����̬ʱ���������ݵ����������
//����̬ʱ����Ӧʱ�����������������Ӧ����ACK��NAK��CAN
bool CPC2PCView::Write(BYTE arrBin[],int count)
{
	DWORD	dwWrite;
	Wol.hEvent=CreateEvent(NULL, //����Wol.hEvent�¼������������Ϊ���ź�״̬
		TRUE, 
		FALSE, 
		NULL);
	WriteFile(hCom,                //д���ݣ�ͨ��Wol�ṹ��ȡ�������
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
//��⴮�����뻺�������Ƿ���ָ������������
//����0���У�4����ʱ����,8-��Ч
BYTE CPC2PCView::Detect(int count)
{
	DWORD dwErrors;
	COMSTAT Rcs;
	CString strDis,strDis1;
	BYTE bytTimeCount;
	ClearCommError(hCom,                  //���ھ��
		&dwErrors,                        //��ų�����Ϣ���������
		&Rcs);                             //COMSTAT���ͽṹ����
	if(Rcs.cbInQue==0)
		return 8;
	bytTimeCount=0;
	while(bytTimeCount<4)
	{
		ClearCommError(hCom,                //���ھ��
			&dwErrors,                        //��ų�����Ϣ���������
			&Rcs);                             //COMSTAT���ͽṹ����
		if(Rcs.cbInQue>=(UINT)count)
		{
			return 0;//�����뻺�������ҵ�ָ���������ַ�
		}
		Sleep(500);
		bytTimeCount++;
	}
	if((bytTimeCount>=4)&&(Rcs.cbInQue>0))//��ʱ����
	{
		return 4;//δ�ҵ�
	}
	return 8;//��Ч״̬�����뻺������Ϊ0���ַ�
}

void CPC2PCView::OnDestroy() 
{
	
	CEditView::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CPC2PCView::OnUpdateAppExit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (!blnOpened)          //���ݴ����Ƿ�򿪣������Ƿ������˳�������
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
}
