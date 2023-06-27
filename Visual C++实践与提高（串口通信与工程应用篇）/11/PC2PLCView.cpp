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

//����ȫ�ֱ���
HANDLE hCom;                               //���ھ��
DWORD ThreadProcWrite(LPVOID pParam);      //д�̺߳���
DWORD ThreadProcRead(LPVOID pParam);       //���̺߳���
OVERLAPPED Wol={0};                        //д����OVERLAPPED�ṹ����
OVERLAPPED Rol={0};                        //������OVERLAPPED�ṹ����
HANDLE hThreadWrite;                       //д�߳̾��
HANDLE hThreadRead;                        //���߳̾��
HWND hWnd;                                 //���ھ��

BYTE myRByte[300];                         //����Ѷ�����
BYTE myWByte[300];                         //�����д����
 
long dataRLen;                             //�������ݵĳ���
long dataWLen;                             //�������ݵĳ���

bool blnError;                             //�����־���ڽ������������ʹ��
int	intWrite=0;                            //��ӳд������״̬��0�������壬1��д����2��д��ȷ
int intRead=0;                             //��ӳ��������״̬��0�������壬1��������2������ȷ


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
	myCom="COM4";                      //Ĭ������
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
		m_pStatus->SetPaneText(1,strStatus);            //��ͨ�Ų�����ʾ��״̬����
		
	}
}
//*******************************************
//***���ղ�������*************************
//********************************************
void CPC2PLCView::OnReceive() 
{
	// TODO: Add your command handler code here
	int i,j;
	CString strDis,strTemp;
	char myChar[20];
	BYTE xorByte;                                     //�����żУ���
	PurgeComm(hCom,PURGE_RXCLEAR);                    //��ս��պͷ��ͻ�����
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
	if (!myfuncWrite())                              //����ENQ����������
	{
		myEdit.SetSel(1000000,1000000);
		strDis="";
		strDis+="   ͨ�Ŵ���\15\12\15\12";
		myEdit.ReplaceSel(strDis);
		Beep(1000,50);
		return;
	}

	dataRLen=3;
	intRead=0;
	if(myfuncRead(5))                                //�����ݣ�Ӧ��Ϊ��ACK�����ȣ�����ȡ��ֵ��
	{
		strDis="--> ";
		for(i=0;i<=2;i++)
		{
			strTemp.Format("%02X",myRByte[i]);      //��16��������ʽ��Ϊ2λ��ʽ
			strDis+=strTemp;
			strDis+="|";
		}
		myEdit.SetSel(1000000,1000000);
		strDis+="\15\12";
		strDis.MakeUpper();
		myEdit.ReplaceSel(strDis);                 //��ʾ���յ�������

	}
	else//������˵��ͨ�Ź��ϣ��˳��˴ζ����ݲ���
	{
		blnError=true;
		myEdit.SetSel(1000000,1000000);
		strDis="";
		strDis+="   ͨ�Ŵ���\15\12\15\12";
		myEdit.ReplaceSel(strDis);
		Beep(1000,50);
		return;
	}
	for(i=0;i<3;i++)                               //�����ݽ���3��У��
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
		if(!myfuncWrite())                        //��У��δͨ�������ӦNAK��Ҫ���ط�
		{
			blnError=true;
			break;
		}
		dataRLen=3;
		intRead=0;
		if(myfuncRead(21))//�ٴζ�ȡ���ݣ�Ӧ��Ϊ��ACK�����ȣ�����ȡ��ֵ��
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
			strDis+="   ͨ�Ŵ���\15\12\15\12";
			strDis.MakeUpper();
			myEdit.ReplaceSel(strDis);
			Beep(1000,50);
			return;
		}

	}


	if (blnError)//������˵��ͨ�Ŵ��ڹ��ϣ����˳����β���
	{
		myEdit.SetSel(1000000,1000000);
		strDis="";
		strDis+="   ͨ�Ŵ���\15\12\15\12";
		strDis.MakeUpper();
		myEdit.ReplaceSel(strDis);
		Beep(1000,50);
		blnError=false;
		return;
	}
	//����ͨ�ţ���������
	myWByte[0]=6;                                 //�յ����ȼ���ȡ��ֵ����У����ȷ����ӦACK
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
		strDis+="   ͨ�Ŵ���\15\12\15\12";
		strDis.MakeUpper();
		myEdit.ReplaceSel(strDis);
		Beep(1000,50);
		return;
	}

	//��ӦACK�ɹ����ȴ���������
	dataRLen=myRByte[1]+1;
	for(i=0;i<3;i++)                            //��1��δ������ȷ���ݣ������²�������ѭ��3��
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
			myEdit.ReplaceSel(strDis);         //��ʾ���յ�������

			if(myRByte[dataRLen-1]==xorByte)   //У������
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
		if(!myfuncWrite())                    //����У�������ӦNAK��Ҫ���ط�
		{
			blnError=true;
			break;
		}

	}
	if (blnError)//��blnError����1��˵��ͨ�Ŵ��ڹ��ϣ����˳����β���
	{
		myEdit.SetSel(1000000,1000000);
		strDis="";
		strDis+="   ͨ�Ŵ���\15\12\15\12";
		strDis.MakeUpper();
		myEdit.ReplaceSel(strDis);
		Beep(1000,50);
		blnError=false;
		return;
	}
	//�����Ѿ����أ������Ѿ�У����ȷ
	myWByte[0]=6;                          //��ӦACK
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
		strDis+="   ͨ�Ŵ���\15\12\15\12";
		myEdit.ReplaceSel(strDis);
		Beep(1000,50);
		return;
	}
	myEdit.SetSel(1000000,1000000);
	strDis="";
	strDis+="   ������ϣ�\15\12\15\12";
	myEdit.ReplaceSel(strDis);           //��ʾ�ɹ���Ϣ
	Beep(1000,50);
	
}

int CPC2PLCView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CEdit& myEdit=this->GetEditCtrl( );
	myEdit.SetReadOnly (true);          //����ʾ������Ϊֻ��
	hWnd=GetSafeHwnd();                 //��ȡ��ǰ���ڵľ��
	blnOpened=false;
	return 0;
}

//*****************************
//****���̺߳���****************
//*****************************
DWORD  ThreadProcRead(LPVOID pParam)
{
	
	CString myStr;
	DWORD dwRes;
	DWORD dwRead;                      //ʵ�ʶ������ֽ���
	intRead=0;
	Rol.hEvent=CreateEvent(NULL,       //����Rol��hEvent��ԱΪ���ź�״̬
			TRUE, 
			FALSE, 
			NULL);
	if (Rol.hEvent == NULL)
	{
		AfxMessageBox("hEvent��");
		intRead=1;
         return -1;
	}
	if (ReadFile(hCom,               //���ھ��
			&myRByte,                //��Ŷ�ȡ����
			dataRLen,                //����ȡ���ֽ���
			NULL,
			&Rol))                   //ָ�򴴽�hComʱ��Rol��ָ��
	{
		intRead=2;

         //��������봦���Ѷ�ȡ���ݵĴ��룬�Ѷ�ȡ���ݴ����myRByte�����С�
	}
	else
	{
		dwRes = WaitForSingleObject(Rol.hEvent, 
				2000);              //����2��ĳ�ʱ
		switch(dwRes)
		{
		case WAIT_OBJECT_0:
			 if (!GetOverlappedResult(hCom, 
					&Rol, 
					&dwRead,        //ʵ�ʶ������ֽ���
					TRUE))          //TRUE��ʾֱ��������ɸú����ŷ���
			 {   
				 //����ʧ�ܣ�����ʹ��GetLastError����������ȡ������Ϣ��
				intRead=1;

			}
			else
			{
			    //�����ɹ���ɣ����ݶ���������ŵ�myRByte�����С�
                //��������봦�����ݵĴ���
				intRead=2;
			 }
			 break;
		case WAIT_TIMEOUT:
			//������ʧ�ܣ�ԭ���Ƕ���ʱ��
			intRead=1;
			break;
		default:
			 //������Լ���Ĭ������µĴ�����롣
			 intRead=1;
			 break;
		}
	}
	CloseHandle(Rol.hEvent);
	return 0;
}

//*****************************
//****д�̺߳���****************
//*****************************
DWORD  ThreadProcWrite(LPVOID pParam)
{
	CString myStr;
	DWORD dwRes;
	DWORD dwWrite;
	intWrite=0;
	Wol.Internal=0;                //����OVERLAPPED�ṹWol
	Wol.InternalHigh=0;
	Wol.Offset=0;
	Wol.OffsetHigh=0;
	Wol.hEvent=CreateEvent(NULL,   //����Wol��hEvent��ԱΪ���ź�״̬
         TRUE,
         FALSE,
         NULL);
	if (Wol.hEvent == NULL)
	{
		AfxMessageBox("hEvent��");
		intWrite=1;
         return -1;
	}
	if (WriteFile(hCom,           //���ھ��
			&myWByte,             //��Ŵ���������
			dataWLen,             //�����͵��ֽ���
			NULL,
			&Wol))                //ָ�򴴽�hComʱ��Wol��ָ��
	{
         //���������ɹ����͵Ĵ�����롣
		intWrite=2;

	}
	else
	{
		dwRes = WaitForSingleObject(Wol.hEvent,
				 500);           //����д��ʱ500ms
		switch(dwRes)
		{
		case WAIT_OBJECT_0:
			 if (!GetOverlappedResult(hCom, 
					&Wol, 
					&dwWrite, 
					TRUE))
			 {   
				intWrite=1;
				//����ʧ�ܣ�����ʹ��GetLastError����������ȡ������Ϣ��
			 }
			 else
			 {
				//�������ݳɹ�
				intWrite=2;
				//��������뷢�ͳɹ��Ĵ������
			 }
			 break;
		case WAIT_TIMEOUT:
			//����ʧ�ܣ�ԭ���Ƿ��ͳ�ʱ
			intWrite=1;
			break;
		default:
			//������Լ���Ĭ������µĴ�����롣
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
		CloseHandle(hCom);           //�رմ��ھ��
	}
	// TODO: Add your message handler code here
	
}

bool  CPC2PLCView::myfuncWrite()
{
	//д���ڲ���
	DWORD dwThreadID;//
	DWORD dwParam;
	int	 i;
	for(i=0;i<3;i++)
	{
		hThreadWrite=CreateThread(NULL,
			0,
			(LPTHREAD_START_ROUTINE )ThreadProcWrite, //д�̺߳�������
			&dwParam,
			0,                                        //�����̺߳�����ִ�и��߳�
			&dwThreadID);
		if (hThreadWrite==NULL)
		{
			AfxMessageBox("д�̴߳���ʧ�ܣ�");
			intWrite=1;
			return false;
		}
		while (intWrite==0)
		{
			Sleep(100);                              //�ȴ�д�������
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
	//�����ڲ�������
	DWORD dwThreadID;
	DWORD dwParam;
	CString strDis;
	int i;
	for(i=0;i<3;i++)
	{
		hThreadRead=CreateThread(NULL,
				0,
				(LPTHREAD_START_ROUTINE )ThreadProcRead,//���̺߳�������
				&dwParam,
				0,                                      //�����̺߳�����ִ�и��߳�
				&dwThreadID);
		if (hThreadRead==NULL)
		{
			AfxMessageBox("���̴߳���ʧ�ܣ�");
			intRead=1;
			return false;
		}
		while (intRead==0)
		{
			Sleep(100);                                //�ȴ����������
		}
		if (intRead==2)
		{
			return true;
		}
		else
		{
			myWByte[0]=ackChar;                       //����ENQ��NAK��ascii��Ϊ5��21��
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
	//���ݴ����Ƿ�򿪣������Ƿ��������ա�����
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
	hCom=CreateFile(myCom,                            //��������COM2
		GENERIC_READ | GENERIC_WRITE, 
		0,
		NULL,
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL| FILE_FLAG_OVERLAPPED, //ʹ���ص���ʽ
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

		//��ʾ���ڳɹ���
		myEdit.SetReadOnly (true);
		myEdit.SetSel(1000000,1000000);
		strDis=myCom;
		strDis+="�򿪳ɹ���\15\12\15\12";
		myEdit.ReplaceSel(strDis);
		blnOpened=true;
	}
	else
	{
		//��ʾ���ڴ�ʧ��
		myEdit.SetReadOnly (true);
		myEdit.SetSel(1000000,1000000);
		strDis=myCom;
		strDis+="��ʧ�ܣ�\15\12\15\12";
		myEdit.ReplaceSel(strDis);
		blnOpened=false;
	}
}

void CPC2PLCView::OnUpdateSetup(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//���ݴ����Ƿ�򿪣������Ƿ��������á�����
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
	//���ݴ����Ƿ�򿪣������Ƿ������򿪡�����
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
	//���ݴ����Ƿ�򿪣������Ƿ������رա�����
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

		CString strDis;                         //��ʾ���ڳɹ��ر�
		CEdit& myEdit=this->GetEditCtrl( );
		myEdit.SetReadOnly (true);
		myEdit.SetSel(1000000,1000000);
		strDis=myCom;
		strDis+="  �ѹرգ�\15\12\15\12";
		myEdit.ReplaceSel(strDis);
		blnOpened=false;
	}
	
}

void CPC2PLCView::OnUpdateAppExit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//���ݴ����Ƿ�򿪣������Ƿ������˳�������
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
