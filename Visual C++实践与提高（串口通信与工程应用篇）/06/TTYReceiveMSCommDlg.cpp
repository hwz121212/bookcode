// TTYReceiveMSCommDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TTYReceiveMSComm.h"
#include "TTYReceiveMSCommDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTTYReceiveMSCommDlg dialog

CTTYReceiveMSCommDlg::CTTYReceiveMSCommDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTTYReceiveMSCommDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTTYReceiveMSCommDlg)
	m_Para = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTTYReceiveMSCommDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTTYReceiveMSCommDlg)
	DDX_Control(pDX, IDC_CLOSECOM, m_Closecom);
	DDX_Control(pDX, IDC_SETUPCOM, m_Setupcom);
	DDX_Control(pDX, IDC_OPENCOM, m_Opencom);
	DDX_Control(pDX, IDC_EXIT, m_Exit);
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	DDX_Text(pDX, IDC_PARA, m_Para);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTTYReceiveMSCommDlg, CDialog)
	//{{AFX_MSG_MAP(CTTYReceiveMSCommDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SETUPCOM, OnSetupcom)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDC_OPENCOM, OnOpencom)
	ON_BN_CLICKED(IDC_CLOSECOM, OnClosecom)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTTYReceiveMSCommDlg message handlers

BOOL CTTYReceiveMSCommDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//blnOpened=false;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTTYReceiveMSCommDlg::OnPaint() 
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
HCURSOR CTTYReceiveMSCommDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTTYReceiveMSCommDlg::OnSetupcom() 
{
	// TODO: Add your control notification handler code here
	CString strStatus,strTemp;
	double dblBaud;
	if(mySetupDlg.DoModal()==IDOK)
	{
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
	m_Para=strStatus;
	UpdateData(false);
	}

}

void CTTYReceiveMSCommDlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	this->EndDialog(IDOK);                     //�رճ���
	
}

void CTTYReceiveMSCommDlg::OnOpencom() 
{
	// TODO: Add your control notification handler code here
	//���µĳ�ʼ��ֻ��һ�����ӣ�����ʵ�ʳ���Ҫ��Ĳ�ͬ��
	//��ʼ�������������в��б���ִ����Ǳ���ġ�
	CString strPara;                          //���ڲ���
	myComm.SetCommPort(myCom);                //ָ�����ں�myCom
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
	m_Opencom.EnableWindow(false);           //ʹ���򿪴��ڡ���ť��Ч
	m_Closecom.EnableWindow(true);           //ʹ���رմ��ڡ���ť��Ч
	m_Setupcom.EnableWindow(false);          //ʹ�����á���ť��Ч
	m_Exit.EnableWindow(false);              //ʹ���˳�����ť��Ч
	AfxMessageBox("���ڴ򿪳ɹ���");
}

void CTTYReceiveMSCommDlg::OnClosecom() 
{
	// TODO: Add your control notification handler code here
	myComm.SetPortOpen(0);
	AfxMessageBox("���ڹرճɹ���");
	m_Opencom.EnableWindow(true);           //ʹ�򿪴��ڰ�ť��Ч
	m_Closecom.EnableWindow(false);         //ʹ�رմ��ڰ�ť��Ч
	m_Setupcom.EnableWindow(true);          //ʹ���ð�ť��Ч
	m_Exit.EnableWindow(true);              //ʹ�˳���ť��Ч
}

int CTTYReceiveMSCommDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
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
	m_Para="COM1,9600,N,8,1";
	return 0;
}

BEGIN_EVENTSINK_MAP(CTTYReceiveMSCommDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CTTYReceiveMSCommDlg)
	ON_EVENT(CTTYReceiveMSCommDlg, IDC_MSCOMM1, 1 /* OnComm */, OnOnCommMscomm1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CTTYReceiveMSCommDlg::OnOnCommMscomm1() 
{
	// TODO: Add your control notification handler code here
	VARIANT input1;                     //����VARIANT���ͱ���
	BYTE rxdata[2048];                  //�����Ŷ��������ݵ�����
	long len1,k;
	COleSafeArray safearray1;           //����COleSafeArray���ʵ��
	CString strDis;
	switch(myComm.GetCommEvent())
	{
	case 2:
		//�յ� RThreshold ���ַ�
		//��ӽ��մ������
		input1=myComm.GetInput();
		//��VARAIANT������ֵ��COleSafeArray���ʵ��
		safearray1=input1;     
		//ʹ��COleSafeArray��ĳ�Ա������ȡ���ݳ���
		len1=safearray1.GetOneDimSize();
		for(k=0;k<len1;k++)
		//ʹ��COleSafeArray��ĳ�Ա����������д������
			safearray1.GetElement(&k,rxdata+k);

		for(k=0;k<1;k++)
		{
			if(rxdata[k]==13)
			{
				m_Edit1.SetSel(1000000,1000000);
				m_Edit1.ReplaceSel("\15\12");
				UpdateData(false);
			}
			else
			{
				if(rxdata[k]<=126 && rxdata[k]>=32)
				{
					strDis+=rxdata[k];
					m_Edit1.SetSel(1000000,1000000);
					m_Edit1.ReplaceSel(strDis);
					strDis="";
					UpdateData(false);
				}
			}
		}
	}
}
