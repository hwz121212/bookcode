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


extern CString strStatus;           //原声明在Tapi14.CPP中，全局变量声明区

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
//**拨号函数
//*************************************

void CTapiNewDlg::OnDial() 
{
	// TODO: Add your control notification handler code here
	myHwnd=GetSafeHwnd();
	myTapi14.Create(myHwnd);
	UpdateData(true);
	if (m_Phonenumber=="")
	{
		AfxMessageBox("请输入电话号码！");
		return;
	}
	myTapi14.DialCall(m_Phonenumber);
	
}
//*************************************
//**挂机函数
//*************************************

void CTapiNewDlg::OnHangup() 
{
	// TODO: Add your control notification handler code here
	myTapi14.HangupCall();

}

//*************************************
//**显示信息函数
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
//**********消 息 处 理 函 数**********
//********************************************
//处理WM_TAPI_DIALING消息
void CTapiNewDlg::OnTapiEvent_DIALING(WPARAM wParam,LPARAM lParam)
{
	OperStatus("拨号中");             
}

//处理TAPI_LINECALLSTATE_CONNECTED消息
void CTapiNewDlg::OnTapiEvent_CONNECT(WPARAM wParam,LPARAM lParam)
{
	CString myStr;
	OperStatus("TAPI线路已连接");
	myStr.Format("CommHandle:%d",lParam);
	OperStatus(myStr);

}

//处理WM_TAPI_DISCONNECT消息
void CTapiNewDlg::OnTapiEvent_DISCONNECT(WPARAM wParam,LPARAM lParam)
{
	OperStatus("TAPI解除连接");
}

//处理WM_TAPI_IDLE消息
void CTapiNewDlg::OnTapiEvent_IDLE(WPARAM wParam,LPARAM lParam)
{
	OperStatus("TAPI空闲");
}

//处理WM_TAPI_STATUS消息
void CTapiNewDlg::OnTapiEvent_STATUS(WPARAM wParam,LPARAM lParam)
{
	OperStatus(strStatus);
}

//处理WM_TAPI_CALL_PROCEEDING消息
void CTapiNewDlg::OnTapiEvent_CALL_PROCEEDING(WPARAM wParam,LPARAM lParam)
{
	CString myStr;
	myStr.Format("设备号码：%d",lParam);
	OperStatus("呼叫进行中");
	OperStatus(myStr);
}

//处理WM_TAPI_CALL_ACCEPTED消息
void CTapiNewDlg::OnTapiEvent_CALL_ACCEPTED(WPARAM wParam,LPARAM lParam)
{
	CString myStr;
	myStr.Format("设备号码：%d",lParam);
	OperStatus("呼叫接受");
	OperStatus(myStr);
}

//处理WM_TAPI_LINE_REPLY消息
void CTapiNewDlg::OnTapiEvent_LINE_REPLY(WPARAM wParam,LPARAM lParam)
{
	CString myStr;
	myStr.Format("设备号码：%d",lParam);
	OperStatus("线路回应");
	OperStatus(myStr);
}

//处理WM_TAPI_VOICE_SUPPORT消息
void CTapiNewDlg::OnTapiEvent_VOICE_SUPPORT(WPARAM wParam,LPARAM lParam)
{
	OperStatus("语音支持");
}
