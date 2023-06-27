// TapiNewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TapiNew.h"
#include "TapiNewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CString strStatus;           //ԭ������Tapi14.CPP�У�ȫ�ֱ���������

/////////////////////////////////////////////////////////////////////////////
// CTapiNewDlg dialog

CTapiNewDlg::CTapiNewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTapiNewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTapiNewDlg)
	m_Phonenumber = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTapiNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTapiNewDlg)
	DDX_Control(pDX, IDC_DIS, m_Dis);
	DDX_Text(pDX, IDC_PNONENUMBER, m_Phonenumber);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTapiNewDlg, CDialog)
	//{{AFX_MSG_MAP(CTapiNewDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DIAL, OnDial)
	ON_BN_CLICKED(IDC_HANGUP, OnHangup)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_TAPI_DIALING,OnTapiEvent_DIALING)
	ON_MESSAGE(WM_TAPI_CONNECT,OnTapiEvent_CONNECT)
	ON_MESSAGE(WM_TAPI_DISCONNECT,OnTapiEvent_DISCONNECT)
	ON_MESSAGE(WM_TAPI_IDLE,OnTapiEvent_IDLE)
	ON_MESSAGE(WM_TAPI_STATUS,OnTapiEvent_STATUS)
	ON_MESSAGE(WM_TAPI_CALL_PROCEEDING,OnTapiEvent_CALL_PROCEEDING)
	ON_MESSAGE(WM_TAPI_CALL_ACCEPTED,OnTapiEvent_CALL_ACCEPTED)
	ON_MESSAGE(WM_TAPI_LINE_REPLY,OnTapiEvent_LINE_REPLY)
	ON_MESSAGE(WM_TAPI_VOICE_SUPPORT,OnTapiEvent_VOICE_SUPPORT)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTapiNewDlg message handlers

BOOL CTapiNewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTapiNewDlg::OnPaint() 
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
HCURSOR CTapiNewDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//*************************************
//**���ź���
//*************************************

void CTapiNewDlg::OnDial() 
{
	// TODO: Add your control notification handler code here
	myHwnd=GetSafeHwnd();
	myTapi14.Create(myHwnd);
	UpdateData(true);
	if (m_Phonenumber=="")
	{
		AfxMessageBox("������绰���룡");
		return;
	}
	myTapi14.DialCall(m_Phonenumber);
	
}
//*************************************
//**�һ�����
//*************************************

void CTapiNewDlg::OnHangup() 
{
	// TODO: Add your control notification handler code here
	myTapi14.HangupCall();

}

//*************************************
//**��ʾ��Ϣ����
//*************************************
void CTapiNewDlg::OperStatus(CString strDis)
{
	m_Dis.SetSel(1000000,1000000);
	m_Dis.ReplaceSel("\12\15");
	m_Dis.SetSel(1000000,1000000);
	m_Dis.ReplaceSel(strDis);
	m_Dis.ReplaceSel("\12\15");
	UpdateData(false);

}


//********************************************
//**********�� Ϣ �� �� �� ��**********
//********************************************
//����WM_TAPI_DIALING��Ϣ
void CTapiNewDlg::OnTapiEvent_DIALING(WPARAM wParam,LPARAM lParam)
{
	OperStatus("������");             
}

//����TAPI_LINECALLSTATE_CONNECTED��Ϣ
void CTapiNewDlg::OnTapiEvent_CONNECT(WPARAM wParam,LPARAM lParam)
{
	CString myStr;
	OperStatus("TAPI��·������");
	myStr.Format("CommHandle:%d",lParam);
	OperStatus(myStr);

}

//����WM_TAPI_DISCONNECT��Ϣ
void CTapiNewDlg::OnTapiEvent_DISCONNECT(WPARAM wParam,LPARAM lParam)
{
	OperStatus("TAPI�������");
}

//����WM_TAPI_IDLE��Ϣ
void CTapiNewDlg::OnTapiEvent_IDLE(WPARAM wParam,LPARAM lParam)
{
	OperStatus("TAPI����");
}

//����WM_TAPI_STATUS��Ϣ
void CTapiNewDlg::OnTapiEvent_STATUS(WPARAM wParam,LPARAM lParam)
{
	OperStatus(strStatus);
}

//����WM_TAPI_CALL_PROCEEDING��Ϣ
void CTapiNewDlg::OnTapiEvent_CALL_PROCEEDING(WPARAM wParam,LPARAM lParam)
{
	CString myStr;
	myStr.Format("�豸���룺%d",lParam);
	OperStatus("���н�����");
	OperStatus(myStr);
}

//����WM_TAPI_CALL_ACCEPTED��Ϣ
void CTapiNewDlg::OnTapiEvent_CALL_ACCEPTED(WPARAM wParam,LPARAM lParam)
{
	CString myStr;
	myStr.Format("�豸���룺%d",lParam);
	OperStatus("���н���");
	OperStatus(myStr);
}

//����WM_TAPI_LINE_REPLY��Ϣ
void CTapiNewDlg::OnTapiEvent_LINE_REPLY(WPARAM wParam,LPARAM lParam)
{
	CString myStr;
	myStr.Format("�豸���룺%d",lParam);
	OperStatus("��·��Ӧ");
	OperStatus(myStr);
}

//����WM_TAPI_VOICE_SUPPORT��Ϣ
void CTapiNewDlg::OnTapiEvent_VOICE_SUPPORT(WPARAM wParam,LPARAM lParam)
{
	OperStatus("����֧��");
}
