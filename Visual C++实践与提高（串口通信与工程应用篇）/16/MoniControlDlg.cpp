// MoniControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MoniControl.h"
#include "MoniControlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMoniControlDlg dialog

CMoniControlDlg::CMoniControlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMoniControlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMoniControlDlg)
	m_Address = 0;
	m_BaudRate = 0;
	m_Com = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMoniControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMoniControlDlg)
	DDX_Control(pDX, IDC_UPMICRO, m_UpMicro);
	DDX_Control(pDX, IDC_UP, m_Up);
	DDX_Control(pDX, IDC_SMALLMICRO, m_SmallMicro);
	DDX_Control(pDX, IDC_SMALL, m_Small);
	DDX_Control(pDX, IDC_SHORTMICRO, m_ShortMicro);
	DDX_Control(pDX, IDC_SHORT, m_Short);
	DDX_Control(pDX, IDC_RIGHTUP, m_RightUp);
	DDX_Control(pDX, IDC_RIGHTMICRO, m_RightMicro);
	DDX_Control(pDX, IDC_RIGHTDOWN, m_RightDown);
	DDX_Control(pDX, IDC_RIGHT, m_Right);
	DDX_Control(pDX, IDC_OPENLIGHT, m_OpenLight);
	DDX_Control(pDX, IDC_OPENCOM, m_OpenCom);
	DDX_Control(pDX, IDC_OPENBRUSH, m_OpenBrush);
	DDX_Control(pDX, IDC_NEARMICRO, m_NearMicro);
	DDX_Control(pDX, IDC_NEAR, m_Near);
	DDX_Control(pDX, IDC_LONGMICRO, m_LongMicro);
	DDX_Control(pDX, IDC_LONG, m_Long);
	DDX_Control(pDX, IDC_LEFTUP, m_LeftUp);
	DDX_Control(pDX, IDC_LEFTMICRO, m_LeftMicro);
	DDX_Control(pDX, IDC_LEFTDOWN, m_LeftDown);
	DDX_Control(pDX, IDC_LEFT, m_Left);
	DDX_Control(pDX, IDC_FARMICRO, m_FarMicro);
	DDX_Control(pDX, IDC_FAR, m_Far);
	DDX_Control(pDX, IDC_DOWNMICRO, m_DownMicro);
	DDX_Control(pDX, IDC_DOWN, m_Down);
	DDX_Control(pDX, IDC_CLOSELIGHT, m_CloseLight);
	DDX_Control(pDX, IDC_CLOSECOM, m_CloseCom);
	DDX_Control(pDX, IDC_CLOSEBRUSH, m_CloseBrush);
	DDX_Control(pDX, IDC_BIGMICRO, m_BigMicro);
	DDX_Control(pDX, IDC_BIG, m_Big);
	DDX_Control(pDX, IDC_ACTSTATUS, m_ActStatus);
	DDX_CBIndex(pDX, IDC_COMBO_ADDRESS, m_Address);
	DDX_CBIndex(pDX, IDC_COMBO_BAUDRATE, m_BaudRate);
	DDX_CBIndex(pDX, IDC_COMBO_COM, m_Com);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMoniControlDlg, CDialog)
	//{{AFX_MSG_MAP(CMoniControlDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_OPENCOM, OnOpencom)
	ON_BN_CLICKED(IDC_CLOSECOM, OnClosecom)
	ON_CBN_CLOSEUP(IDC_COMBO_ADDRESS, OnCloseupComboAddress)
	ON_WM_MOVE()
	ON_WM_MOUSEMOVE()
	ON_WM_CLOSE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMoniControlDlg message handlers

BOOL CMoniControlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	int	i=0;
	//���ظ�����ť��ͼ��
	hIconU_N=AfxGetApp()->LoadIcon(IDI_ICON_UP_N);
	hIconU_O=AfxGetApp()->LoadIcon(IDI_ICON_UP_O);
	hIconU_P=AfxGetApp()->LoadIcon(IDI_ICON_UP_P);

	hIconD_N=AfxGetApp()->LoadIcon(IDI_ICON_DOWN_N);
	hIconD_O=AfxGetApp()->LoadIcon(IDI_ICON_DOWN_O);
	hIconD_P=AfxGetApp()->LoadIcon(IDI_ICON_DOWN_P);

	hIconL_N=AfxGetApp()->LoadIcon(IDI_ICON_LEFT_N);
	hIconL_O=AfxGetApp()->LoadIcon(IDI_ICON_LEFT_O);
	hIconL_P=AfxGetApp()->LoadIcon(IDI_ICON_LEFT_P);

	hIconR_N=AfxGetApp()->LoadIcon(IDI_ICON_RIGHT_N);
	hIconR_O=AfxGetApp()->LoadIcon(IDI_ICON_RIGHT_O);
	hIconR_P=AfxGetApp()->LoadIcon(IDI_ICON_RIGHT_P);

	hIconLU_N=AfxGetApp()->LoadIcon(IDI_ICON_LEFTUP_N);
	hIconLU_O=AfxGetApp()->LoadIcon(IDI_ICON_LEFTUP_O);
	hIconLU_P=AfxGetApp()->LoadIcon(IDI_ICON_LEFTUP_P);

	hIconLD_N=AfxGetApp()->LoadIcon(IDI_ICON_LEFTDOWN_N);
	hIconLD_O=AfxGetApp()->LoadIcon(IDI_ICON_LEFTDOWN_O);
	hIconLD_P=AfxGetApp()->LoadIcon(IDI_ICON_LEFTDOWN_P);

	hIconRU_N=AfxGetApp()->LoadIcon(IDI_ICON_RIGHTUP_N);
	hIconRU_O=AfxGetApp()->LoadIcon(IDI_ICON_RIGHTUP_O);
	hIconRU_P=AfxGetApp()->LoadIcon(IDI_ICON_RIGHTUP_P);

	hIconRD_N=AfxGetApp()->LoadIcon(IDI_ICON_RIGHTDOWN_N);
	hIconRD_O=AfxGetApp()->LoadIcon(IDI_ICON_RIGHTDOWN_O);
	hIconRD_P=AfxGetApp()->LoadIcon(IDI_ICON_RIGHTDOWN_P);

	hIconB_N=AfxGetApp()->LoadIcon(IDI_ICON_BIG_N);
	hIconB_O=AfxGetApp()->LoadIcon(IDI_ICON_BIG_O);
	hIconB_P=AfxGetApp()->LoadIcon(IDI_ICON_BIG_P);

	hIconS_N=AfxGetApp()->LoadIcon(IDI_ICON_SMALL_N);
	hIconS_O=AfxGetApp()->LoadIcon(IDI_ICON_SMALL_O);
	hIconS_P=AfxGetApp()->LoadIcon(IDI_ICON_SMALL_P);

	hIconF_N=AfxGetApp()->LoadIcon(IDI_ICON_FAR_N);
	hIconF_O=AfxGetApp()->LoadIcon(IDI_ICON_FAR_O);
	hIconF_P=AfxGetApp()->LoadIcon(IDI_ICON_FAR_P);

	hIconN_N=AfxGetApp()->LoadIcon(IDI_ICON_NEAR_N);
	hIconN_O=AfxGetApp()->LoadIcon(IDI_ICON_NEAR_O);
	hIconN_P=AfxGetApp()->LoadIcon(IDI_ICON_NEAR_P);

	hIconLG_N=AfxGetApp()->LoadIcon(IDI_ICON_LONG_N);
	hIconLG_O=AfxGetApp()->LoadIcon(IDI_ICON_LONG_O);
	hIconLG_P=AfxGetApp()->LoadIcon(IDI_ICON_LONG_P);

	hIconSH_N=AfxGetApp()->LoadIcon(IDI_ICON_SHORT_N);
	hIconSH_O=AfxGetApp()->LoadIcon(IDI_ICON_SHORT_O);
	hIconSH_P=AfxGetApp()->LoadIcon(IDI_ICON_SHORT_P);

	hIconO_N=AfxGetApp()->LoadIcon(IDI_ICON_OPEN_N);
	hIconO_O=AfxGetApp()->LoadIcon(IDI_ICON_OPEN_O);
	hIconO_P=AfxGetApp()->LoadIcon(IDI_ICON_OPEN_P);

	hIconC_N=AfxGetApp()->LoadIcon(IDI_ICON_CLOSE_N);
	hIconC_O=AfxGetApp()->LoadIcon(IDI_ICON_CLOSE_O);
	hIconC_P=AfxGetApp()->LoadIcon(IDI_ICON_CLOSE_P);

	//��ʼ��������������sendArray
	sendArray.RemoveAll();
	sendArray.SetSize(16);
	for(i=0;i<=3;i++)
	{
		sendArray.SetAt(i,0xFF);
	}
	for(i=4;i<=10;i++)
	{
		sendArray.SetAt(i,0);
	}
	sendArray.SetAt(13,0xFF);
	sendArray.SetAt(14,0xEE);
	sendArray.SetAt(15,0xEE);

	m_CloseCom.EnableWindow(false);       //ʹ�رմ��ڰ�ť��Ч
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMoniControlDlg::OnPaint() 
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
HCURSOR CMoniControlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}




void CMoniControlDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	POINT	myPoint;
	myPoint.x=point.x;
	myPoint.y=point.y;
	ClientToScreen(&myPoint);
	//���¡��ϡ���ť
	if(m_CRect_U.PtInRect(myPoint))
	{
		m_Up.SetIcon(hIconU_P);         //����ͼ��Ϊ����ʱ��ʽ��
		SendCommand(10100);             //�����ϲ�������
		MSG	myMsg;
		this->SetCapture();             //���������Ϣ���մ���
		while(1)
		{
			//�����Ƿ���WM_LBUTTONUP��Ϣ
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);             //�����ļ��ʱ��
				m_Up.SetIcon(hIconU_O);//����ͼ��Ϊ����ʱ��ʽ��
				SendCommand(10101);    //����ֹͣ�ϲ�������
				Sleep(20);             //�����ļ��ʱ��
				::ReleaseCapture();    //ȡ���������Ϣ������
				break;
			}
		}
	}
	//���¡��¡���ť
	if(m_CRect_D.PtInRect(myPoint))
	{
		m_Down.SetIcon(hIconD_P);
		SendCommand(10200);
		MSG	myMsg;
		this->SetCapture();
		while(1)
		{
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);
				m_Down.SetIcon(hIconD_O);
				SendCommand(10201);
				Sleep(20);
				::ReleaseCapture();
				break;
			}
		}
	}

	//���¡��󡿰�ť
	if(m_CRect_L.PtInRect(myPoint))
	{
		m_Left.SetIcon(hIconL_P);
		SendCommand(10300);
		MSG	myMsg;
		this->SetCapture();
		while(1)
		{
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);
				m_Left.SetIcon(hIconL_O);
				SendCommand(10301);
				Sleep(20);
				::ReleaseCapture();
				break;
			}
		}
	}
	//���¡��ҡ���ť
	if(m_CRect_R.PtInRect(myPoint))
	{
		m_Right.SetIcon(hIconR_P);
		SendCommand(10400);
		MSG	myMsg;
		this->SetCapture();
		while(1)
		{
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);
				m_Right.SetIcon(hIconR_O);
				SendCommand(10401);
				Sleep(20);
				::ReleaseCapture();
				break;
			}
		}
	}
	//���¡����ϡ���ť
	if(m_CRect_LU.PtInRect(myPoint))
	{
		m_LeftUp.SetIcon(hIconLU_P);
		SendCommand(13100);
		MSG	myMsg;
		this->SetCapture();
		while(1)
		{
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);
				m_LeftUp.SetIcon(hIconLU_O);
				SendCommand(13101);
				Sleep(20);
				::ReleaseCapture();
				break;
			}
		}
	}
	//���¡����¡���ť
	if(m_CRect_LD.PtInRect(myPoint))
	{
		m_LeftDown.SetIcon(hIconLD_P);
		SendCommand(13200);
		MSG	myMsg;
		this->SetCapture();
		while(1)
		{
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);
				m_LeftDown.SetIcon(hIconLD_O);
				SendCommand(13201);
				Sleep(20);
				::ReleaseCapture();
				break;
			}
		}
	}
	//���¡����ϡ���ť
	if(m_CRect_RU.PtInRect(myPoint))
	{
		m_RightUp.SetIcon(hIconRU_P);
		SendCommand(14100);
		MSG	myMsg;
		this->SetCapture();
		while(1)
		{
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);
				m_RightUp.SetIcon(hIconRU_O);
				SendCommand(14101);
				Sleep(20);
				::ReleaseCapture();
				break;
			}
		}
	}
	//���¡����¡���ť
	if(m_CRect_RD.PtInRect(myPoint))
	{
		m_RightDown.SetIcon(hIconRD_P);
		SendCommand(14200);
		MSG	myMsg;
		this->SetCapture();
		while(1)
		{
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);
				m_RightDown.SetIcon(hIconRD_O);
				SendCommand(14201);
				Sleep(20);
				::ReleaseCapture();
				break;
			}
		}
	}
	//���¡��ϡ�΢����ť
	if(m_CRect_UM.PtInRect(myPoint))
	{
		m_UpMicro.SetIcon(hIconU_P);
		SendCommand(10110);
		MSG	myMsg;
		this->SetCapture();
		while(1)
		{
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);
				m_UpMicro.SetIcon(hIconU_O);
				m_ActStatus.SetWindowText("�޲���!");
				//SendCommand('U');
				//Sleep(20);
				::ReleaseCapture();
				break;
			}
		}
	}
	//���¡��¡�΢����ť
	if(m_CRect_DM.PtInRect(myPoint))
	{
		m_DownMicro.SetIcon(hIconD_P);
		SendCommand(10210);
		MSG	myMsg;
		this->SetCapture();
		while(1)
		{
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);
				m_DownMicro.SetIcon(hIconD_O);
				m_ActStatus.SetWindowText("�޲���!");
				//SendCommand('D');
				//Sleep(20);
				::ReleaseCapture();
				break;
			}
		}
	}
	//���¡���΢����ť
	if(m_CRect_LM.PtInRect(myPoint))
	{
		m_LeftMicro.SetIcon(hIconL_P);
		SendCommand(10310);
		MSG	myMsg;
		this->SetCapture();
		while(1)
		{
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);
				m_LeftMicro.SetIcon(hIconL_O);
				m_ActStatus.SetWindowText("�޲���!");
				//SendCommand('L');
				//Sleep(20);
				::ReleaseCapture();
				break;
			}
		}
	}
	//���¡��ҡ�΢����ť
	if(m_CRect_RM.PtInRect(myPoint))
	{
		m_RightMicro.SetIcon(hIconR_P);
		SendCommand(10410);
		MSG	myMsg;
		this->SetCapture();
		while(1)
		{
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);
				m_RightMicro.SetIcon(hIconR_O);
				m_ActStatus.SetWindowText("�޲���!");
				//SendCommand('R');
				//Sleep(20);
				::ReleaseCapture();
				break;
			}
		}
	}
	//���¡��󡿰�ť
	if(m_CRect_B.PtInRect(myPoint))
	{
		m_Big.SetIcon(hIconB_P);
		SendCommand(20100);
		MSG	myMsg;
		this->SetCapture();
		while(1)
		{
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);
				m_Big.SetIcon(hIconB_O);
				SendCommand(20101);
				Sleep(20);
				::ReleaseCapture();
				break;
			}
		}
	}
	//���¡�С����ť
	if(m_CRect_S.PtInRect(myPoint))
	{
		m_Small.SetIcon(hIconS_P);
		SendCommand(20200);
		MSG	myMsg;
		this->SetCapture();
		while(1)
		{
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);
				m_Small.SetIcon(hIconS_O);
				SendCommand(20201);
				Sleep(20);
				::ReleaseCapture();
				break;
			}
		}
	}
	//���¡�Զ����ť
	if(m_CRect_F.PtInRect(myPoint))
	{
		m_Far.SetIcon(hIconF_P);
		SendCommand(20300);
		MSG	myMsg;
		this->SetCapture();
		while(1)
		{
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);
				m_Far.SetIcon(hIconF_O);
				SendCommand(20301);
				Sleep(20);
				::ReleaseCapture();
				break;
			}
		}
	}
	//���¡�������ť
	if(m_CRect_N.PtInRect(myPoint))
	{
		m_Near.SetIcon(hIconN_P);
		SendCommand(20400);
		MSG	myMsg;
		this->SetCapture();
		while(1)
		{
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);
				m_Near.SetIcon(hIconN_O);
				SendCommand(20401);
				Sleep(20);
				::ReleaseCapture();
				break;
			}
		}
	}
	//���¡�������ť
	if(m_CRect_LG.PtInRect(myPoint))
	{
		m_Long.SetIcon(hIconLG_P);
		SendCommand(20500);
		MSG	myMsg;
		this->SetCapture();
		while(1)
		{
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);
				m_Long.SetIcon(hIconLG_O);
				SendCommand(20501);
				Sleep(20);
				::ReleaseCapture();
				break;
			}
		}
	}
	//���¡��̡���ť
	if(m_CRect_SH.PtInRect(myPoint))
	{
		m_Short.SetIcon(hIconSH_P);
		SendCommand(20600);
		MSG	myMsg;
		this->SetCapture();
		while(1)
		{
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);
				m_Short.SetIcon(hIconSH_O);
				SendCommand(20601);
				Sleep(20);
				::ReleaseCapture();
				break;
			}
		}
	}
	//���¡���΢����ť
	if(m_CRect_BM.PtInRect(myPoint))
	{
		m_BigMicro.SetIcon(hIconB_P);
		SendCommand(20110);
		MSG	myMsg;
		this->SetCapture();
		while(1)
		{
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);
				m_BigMicro.SetIcon(hIconB_O);
				m_ActStatus.SetWindowText("�޲���!");
				//SendCommand(20111);
				//Sleep(20);
				::ReleaseCapture();
				break;
			}
		}
	}
	//���¡�С��΢����ť
	if(m_CRect_SM.PtInRect(myPoint))
	{
		m_SmallMicro.SetIcon(hIconS_P);
		SendCommand(20210);
		MSG	myMsg;
		this->SetCapture();
		while(1)
		{
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);
				m_SmallMicro.SetIcon(hIconS_O);
				m_ActStatus.SetWindowText("�޲���!");
				//SendCommand(20211);
				//Sleep(20);
				::ReleaseCapture();
				break;
			}
		}
	}
	//���¡�Զ��΢����ť
	if(m_CRect_FM.PtInRect(myPoint))
	{
		m_FarMicro.SetIcon(hIconF_P);
		SendCommand(20310);
		MSG	myMsg;
		this->SetCapture();
		while(1)
		{
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);
				m_FarMicro.SetIcon(hIconF_O);
				m_ActStatus.SetWindowText("�޲���!");
				//SendCommand(20311);
				//Sleep(20);
				::ReleaseCapture();
				break;
			}
		}
	}
	//���¡�����΢����ť
	if(m_CRect_NM.PtInRect(myPoint))
	{
		m_NearMicro.SetIcon(hIconN_P);
		SendCommand(20410);
		MSG	myMsg;
		this->SetCapture();
		while(1)
		{
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);
				m_NearMicro.SetIcon(hIconN_O);
				m_ActStatus.SetWindowText("�޲���!");
				//SendCommand(20411);
				//Sleep(20);
				::ReleaseCapture();
				break;
			}
		}
	}
	//���¡�����΢����ť
	if(m_CRect_LGM.PtInRect(myPoint))
	{
		m_LongMicro.SetIcon(hIconLG_P);
		SendCommand(20510);
		MSG	myMsg;
		this->SetCapture();
		while(1)
		{
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);
				m_LongMicro.SetIcon(hIconLG_O);
				m_ActStatus.SetWindowText("�޲���!");
				//SendCommand(20511);
				//Sleep(20);
				::ReleaseCapture();
				break;
			}
		}
	}
	//���¡��̡�΢����ť
	if(m_CRect_SHM.PtInRect(myPoint))
	{
		m_ShortMicro.SetIcon(hIconSH_P);
		SendCommand(20610);
		MSG	myMsg;
		this->SetCapture();
		while(1)
		{
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);
				m_ShortMicro.SetIcon(hIconSH_O);
				m_ActStatus.SetWindowText("�޲���!");
				//SendCommand(20611);
				//Sleep(20);
				::ReleaseCapture();
				break;
			}
		}
	}
	//���¡�������ˢ��ť
	if(m_CRect_OB.PtInRect(myPoint))
	{
		m_OpenBrush.SetIcon(hIconO_P);
		SendCommand(30100);
		MSG	myMsg;
		this->SetCapture();
		while(1)
		{
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);
				m_OpenBrush.SetIcon(hIconO_O);
				m_ActStatus.SetWindowText("�޲���!");
				//SendCommand(30101);
				//Sleep(20);
				::ReleaseCapture();
				break;
			}
		}
	}
	//���¡��ء���ˢ��ť
	if(m_CRect_CB.PtInRect(myPoint))
	{
		m_CloseBrush.SetIcon(hIconC_P);
		SendCommand(30200);
		MSG	myMsg;
		this->SetCapture();
		while(1)
		{
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);
				m_CloseBrush.SetIcon(hIconC_O);
				m_ActStatus.SetWindowText("�޲���!");
				//SendCommand(30201);
				//Sleep(20);
				::ReleaseCapture();
				break;
			}
		}
	}
	//���¡�������ư�ť
	if(m_CRect_OL.PtInRect(myPoint))
	{
		m_OpenLight.SetIcon(hIconO_P);
		SendCommand(30300);
		MSG	myMsg;
		this->SetCapture();
		while(1)
		{
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);
				m_OpenLight.SetIcon(hIconO_O);
				m_ActStatus.SetWindowText("�޲���!");
				//SendCommand(30301);
				//Sleep(20);
				::ReleaseCapture();
				break;
			}
		}
	}
	//���¡��ء���ư�ť
	if(m_CRect_CL.PtInRect(myPoint))
	{
		m_CloseLight.SetIcon(hIconC_P);
		SendCommand(30400);
		MSG	myMsg;
		this->SetCapture();
		while(1)
		{
			if(GetMessage(&myMsg,NULL,WM_LBUTTONUP,WM_LBUTTONUP))
			{
				Sleep(20);
				m_CloseLight.SetIcon(hIconC_O);
				m_ActStatus.SetWindowText("�޲���!");
				//SendCommand(30401);
				//Sleep(20);
				::ReleaseCapture();
				break;
			}
		}
	}

	CDialog::OnLButtonDown(nFlags, point);
}


void CMoniControlDlg::OnOpencom() 
{
	// TODO: Add your control notification handler code here
	CComboBox	*m_ComboCom=NULL;
	CComboBox	*m_ComboBaudRate=NULL;
	UpdateData(true);                           //���¿ؼ�������
	//���㴮��ͨ�Ų���
	CString strPara;                            //���ڲ����ַ���
	myComm.SetCommPort(m_Com+1);                //ָ�����ں�
	switch(m_BaudRate)
	{
	case 0:
		{
			strPara="9600";
			break;
		}
	case 1:
		{
			strPara="4800";
			break;
		}
	case 2:
		{
			strPara="2400";
			break;
		}
	case 3:
		{
			strPara="1200";
			break;
		}
	}
	strPara+=",N,8,1";

	myComm.SetSettings(strPara);             //ͨ�Ų�������
	myComm.SetInBufferSize(1024);            //ָ�����ջ�������С
	myComm.SetInBufferCount(0);              //��ս��ջ�����
	myComm.SetInputMode(1);                  //�������ݻ�ȡ��ʽ
	myComm.SetInputLen(0);                   //����ÿ�ζ�ȡ����
	myComm.SetRThreshold(1);                 //���ý���OnComm�¼�����ֵ
	myComm.SetPortOpen(1);                   //�򿪴���
	m_OpenCom.EnableWindow(false);           //ʹ�򿪴��ڰ�ť��Ч
	m_CloseCom.EnableWindow(true);           //ʹ�رմ��ڰ�ť��Ч
	AfxMessageBox("���ڴ򿪳ɹ���");	
	m_ComboCom=(CComboBox*)GetDlgItem(IDC_COMBO_COM);
	m_ComboCom->EnableWindow(false);        //ʹ�˿�ѡ�����Ч
	m_ComboBaudRate=(CComboBox*)GetDlgItem(IDC_COMBO_BAUDRATE);
	m_ComboBaudRate->EnableWindow(false);   //ʹ������ѡ�����Ч
}

void CMoniControlDlg::OnClosecom() 
{
	// TODO: Add your control notification handler code here
	CComboBox	*m_ComboCom=NULL;
	CComboBox	*m_ComboBaudRate=NULL;
	m_OpenCom.EnableWindow(true);           //ʹ�򿪴��ڰ�ť��Ч
	m_CloseCom.EnableWindow(false);         //ʹ�رմ��ڰ�ť��Ч
	myComm.SetPortOpen(0);
	AfxMessageBox("���ڹرճɹ���");
	m_ComboCom=(CComboBox*)GetDlgItem(IDC_COMBO_COM);
	m_ComboCom->EnableWindow(true);        //ʹ�˿�ѡ�����Ч
	m_ComboBaudRate=(CComboBox*)GetDlgItem(IDC_COMBO_BAUDRATE);
	m_ComboBaudRate->EnableWindow(true);   //ʹ������ѡ�����Ч
}

void CMoniControlDlg::OnCloseupComboAddress() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	SendCommand(40100);            //�����л��豸��ַ����
	Sleep(20);
	
}

//************************************
//*******��ȡ��̬��ť��λ������*******
//************************************
CRect	CMoniControlDlg::GetRect(CStatic *pStatic)
{
	RECT myRect;
	CRect myCRect;
	pStatic->GetWindowRect(&myRect);
	myCRect.top=myRect.top;
	myCRect.left=myRect.left;
	myCRect.right=myRect.right;
	myCRect.bottom=myRect.bottom;
	return myCRect;
}

void CMoniControlDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	
	// TODO: Add your message handler code here
	bMoved=true;                //��λ�������ƶ�����־
}

void CMoniControlDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	POINT	myPoint;
	myPoint.x=point.x;
	myPoint.y=point.y;
	//ת���ͻ�������ֵ����Ļ��
	ClientToScreen(&myPoint);
	//�����Ի����ƶ��������¼������ť��λ��
	if(bMoved)
	{
		bMoved=false;                        //��λ�ƶ���־
		m_CRect_U=GetRect(&m_Up);            //��ȡ�ϰ�ťλ��
		m_CRect_D=GetRect(&m_Down);
		m_CRect_L=GetRect(&m_Left);
		m_CRect_R=GetRect(&m_Right);
		m_CRect_UM=GetRect(&m_UpMicro);
		m_CRect_DM=GetRect(&m_DownMicro);
		m_CRect_LM=GetRect(&m_LeftMicro);
		m_CRect_RM=GetRect(&m_RightMicro);
		m_CRect_LU=GetRect(&m_LeftUp);
		m_CRect_LD=GetRect(&m_LeftDown);
		m_CRect_RU=GetRect(&m_RightUp);
		m_CRect_RD=GetRect(&m_RightDown);

		m_CRect_B=GetRect(&m_Big);
		m_CRect_BM=GetRect(&m_BigMicro);
		m_CRect_S=GetRect(&m_Small);
		m_CRect_SM=GetRect(&m_SmallMicro);
		m_CRect_F=GetRect(&m_Far);
		m_CRect_FM=GetRect(&m_FarMicro);
		m_CRect_N=GetRect(&m_Near);
		m_CRect_NM=GetRect(&m_NearMicro);
		m_CRect_LG=GetRect(&m_Long);
		m_CRect_LGM=GetRect(&m_LongMicro);
		m_CRect_SH=GetRect(&m_Short);
		m_CRect_SHM=GetRect(&m_ShortMicro);

		m_CRect_OB=GetRect(&m_OpenBrush);
		m_CRect_CB=GetRect(&m_CloseBrush);
		m_CRect_OL=GetRect(&m_OpenLight);
		m_CRect_CL=GetRect(&m_CloseLight);	
	}
	//�����롾�ϡ���ť���뿪���ϡ���ť
	if(m_CRect_U.PtInRect(myPoint))
	{
		m_Up.SetIcon(hIconU_O);
	}
	else
	{
		m_Up.SetIcon(hIconU_N);
	}
	//���¡�
	if(m_CRect_D.PtInRect(myPoint))
	{
		m_Down.SetIcon(hIconD_O);
	}
	else
	{
		m_Down.SetIcon(hIconD_N);
	}
	//����
	if(m_CRect_L.PtInRect(myPoint))
	{
		m_Left.SetIcon(hIconL_O);
	}
	else
	{
		m_Left.SetIcon(hIconL_N);
	}
	//���ҡ�
	if(m_CRect_R.PtInRect(myPoint))
	{
		m_Right.SetIcon(hIconR_O);
	}
	else
	{
		m_Right.SetIcon(hIconR_N);
	}
	//�����ϡ�
	if(m_CRect_LU.PtInRect(myPoint))
	{
		m_LeftUp.SetIcon(hIconLU_O);
	}
	else
	{
		m_LeftUp.SetIcon(hIconLU_N);
	}
	//�����¡�
	if(m_CRect_LD.PtInRect(myPoint))
	{
		m_LeftDown.SetIcon(hIconLD_O);
	}
	else
	{
		m_LeftDown.SetIcon(hIconLD_N);
	}
	//�����ϡ�
	if(m_CRect_RU.PtInRect(myPoint))
	{
		m_RightUp.SetIcon(hIconRU_O);
	}
	else
	{
		m_RightUp.SetIcon(hIconRU_N);
	}
	//�����¡�
	if(m_CRect_RD.PtInRect(myPoint))
	{
		m_RightDown.SetIcon(hIconRD_O);
	}
	else
	{
		m_RightDown.SetIcon(hIconRD_N);
	}
	//���ϡ���΢��
	if(m_CRect_UM.PtInRect(myPoint))
	{
		m_UpMicro.SetIcon(hIconU_O);
	}
	else
	{
		m_UpMicro.SetIcon(hIconU_N);
	}
	//���¡���΢��
	if(m_CRect_DM.PtInRect(myPoint))
	{
		m_DownMicro.SetIcon(hIconD_O);
	}
	else
	{
		m_DownMicro.SetIcon(hIconD_N);
	}
	//���󡿣�΢��
	if(m_CRect_LM.PtInRect(myPoint))
	{
		m_LeftMicro.SetIcon(hIconL_O);
	}
	else
	{
		m_LeftMicro.SetIcon(hIconL_N);
	}
	//���ҡ���΢��
	if(m_CRect_RM.PtInRect(myPoint))
	{
		m_RightMicro.SetIcon(hIconR_O);
	}
	else
	{
		m_RightMicro.SetIcon(hIconR_N);
	}
	//���󡿹�Ȧ
	if(m_CRect_B.PtInRect(myPoint))
	{
		m_Big.SetIcon(hIconB_O);
	}
	else
	{
		m_Big.SetIcon(hIconB_N);
	}
	//��С����Ȧ
	if(m_CRect_S.PtInRect(myPoint))
	{
		m_Small.SetIcon(hIconS_O);
	}
	else
	{
		m_Small.SetIcon(hIconS_N);
	}
	//���󡿹�Ȧ��΢��
	if(m_CRect_BM.PtInRect(myPoint))
	{
		m_BigMicro.SetIcon(hIconB_O);
	}
	else
	{
		m_BigMicro.SetIcon(hIconB_N);
	}
	//��С����Ȧ��΢��
	if(m_CRect_SM.PtInRect(myPoint))
	{
		m_SmallMicro.SetIcon(hIconS_O);
	}
	else
	{
		m_SmallMicro.SetIcon(hIconS_N);
	}
	//��Զ������
	if(m_CRect_F.PtInRect(myPoint))
	{
		m_Far.SetIcon(hIconF_O);
	}
	else
	{
		m_Far.SetIcon(hIconF_N);
	}
	//��Զ�����΢��
	if(m_CRect_FM.PtInRect(myPoint))
	{
		m_FarMicro.SetIcon(hIconF_O);
	}
	else
	{
		m_FarMicro.SetIcon(hIconF_N);
	}
	//����������
	if(m_CRect_N.PtInRect(myPoint))
	{
		m_Near.SetIcon(hIconN_O);
	}
	else
	{
		m_Near.SetIcon(hIconN_N);
	}
	//���������΢��
	if(m_CRect_NM.PtInRect(myPoint))
	{
		m_NearMicro.SetIcon(hIconN_O);
	}
	else
	{
		m_NearMicro.SetIcon(hIconN_N);
	}
	//����������
	if(m_CRect_LG.PtInRect(myPoint))
	{
		m_Long.SetIcon(hIconLG_O);
	}
	else
	{
		m_Long.SetIcon(hIconLG_N);
	}
	//���������࣬΢��
	if(m_CRect_LGM.PtInRect(myPoint))
	{
		m_LongMicro.SetIcon(hIconLG_O);
	}
	else
	{
		m_LongMicro.SetIcon(hIconLG_N);
	}
	//���̡�����
	if(m_CRect_SH.PtInRect(myPoint))
	{
		m_Short.SetIcon(hIconSH_O);
	}
	else
	{
		m_Short.SetIcon(hIconSH_N);
	}
	//���̡����࣬΢��
	if(m_CRect_SHM.PtInRect(myPoint))
	{
		m_ShortMicro.SetIcon(hIconSH_O);
	}
	else
	{
		m_ShortMicro.SetIcon(hIconSH_N);
	}
	//��������ˢ
	if(m_CRect_OB.PtInRect(myPoint))
	{
		m_OpenBrush.SetIcon(hIconO_O);
	}
	else
	{
		m_OpenBrush.SetIcon(hIconO_N);
	}
	//���ء���ˢ
	if(m_CRect_CB.PtInRect(myPoint))
	{
		m_CloseBrush.SetIcon(hIconC_O);
	}
	else
	{
		m_CloseBrush.SetIcon(hIconC_N);
	}
	//���������
	if(m_CRect_OL.PtInRect(myPoint))
	{
		m_OpenLight.SetIcon(hIconO_O);
	}
	else
	{
		m_OpenLight.SetIcon(hIconO_N);
	}
	//���ء����
	if(m_CRect_CL.PtInRect(myPoint))
	{
		m_CloseLight.SetIcon(hIconC_O);
	}
	else
	{
		m_CloseLight.SetIcon(hIconC_N);
	}

	CDialog::OnMouseMove(nFlags, point);
}
void CMoniControlDlg::SendCommand(int iType)
{
	int		i=0;
	BYTE	bytXor=0;    //���У���ֽ�����
	BYTE	bytCommand;  //��������ֽ�����

	//����iType����������ֵbytCommand
	switch(iType)
	{
	case 10100:
		{
			//���²�����ʾ��Ϣ�ı�
			m_ActStatus.SetWindowText("���ϵ�����̨!");
			UpdateData(false);
			bytCommand=0x92;                     //���������ֽ�����
			break;
		}
	case 10101:
		{
			m_ActStatus.SetWindowText("�޲���!");//ֹͣ���ϵ�����̨!
			UpdateData(false);
			bytCommand=0x93;
			break;
		}
	case 10200:
		{
			m_ActStatus.SetWindowText("���µ�����̨!");
			UpdateData(false);
			bytCommand=0x94;
			break;
		}
	case 10201:
		{
			m_ActStatus.SetWindowText("�޲���!");//ֹͣ���µ�����̨!
			UpdateData(false);
			bytCommand=0x93;
			break;
		}
	case 10300:
		{
			m_ActStatus.SetWindowText("���������̨!");
			UpdateData(false);
			bytCommand=0x96;
			break;
		}
	case 10301:
		{
			m_ActStatus.SetWindowText("�޲���!");//ֹͣ���������̨!
			UpdateData(false);
			bytCommand=0x97;
			break;
		}
	case 10400:
		{
			m_ActStatus.SetWindowText("���ҵ�����̨!");
			UpdateData(false);
			bytCommand=0x98;
			break;
		}
	case 10401:
		{
			m_ActStatus.SetWindowText("�޲���!");//ֹͣ���ҵ�����̨!
			UpdateData(false);
			bytCommand=0x97;
			break;
		}

	case 10110:
		{
			m_ActStatus.SetWindowText("���ϵ�����̨��΢��!");
			UpdateData(false);
			bytCommand=0xB8;
			break;
		}
	case 10210:
		{
			m_ActStatus.SetWindowText("���µ�����̨��΢��!");
			UpdateData(false);
			bytCommand=0xB9;
			break;
		}
	case 10310:
		{
			m_ActStatus.SetWindowText("���������̨��΢��!");
			UpdateData(false);
			bytCommand=0xB6;
			break;
		}
	case 10410:
		{
			m_ActStatus.SetWindowText("���ҵ�����̨��΢��!");
			UpdateData(false);
			bytCommand=0xB7;
			break;
		}

	case 13100:
		{
			m_ActStatus.SetWindowText("�����ϵ�����̨!");
			UpdateData(false);
			bytCommand=0xA4;
			break;
		}
	case 13101:
		{
			m_ActStatus.SetWindowText("�޲���!");//ֹͣ�����ϵ�����̨!
			UpdateData(false);
			bytCommand=0xA8;
			break;
		}
	case 13200:
		{
			m_ActStatus.SetWindowText("�����µ�����̨!");
			UpdateData(false);
			bytCommand=0xA5;
			break;
		}
	case 13201:
		{
			m_ActStatus.SetWindowText("�޲���!");//ֹͣ�����µ�����̨!
			UpdateData(false);
			bytCommand=0xA8;
			break;
		}
	case 14100:
		{
			m_ActStatus.SetWindowText("�����ϵ�����̨!");
			UpdateData(false);
			bytCommand=0xA6;
			break;
		}
	case 14101:
		{
			m_ActStatus.SetWindowText("�޲���!");//ֹͣ�����ϵ�����̨!
			UpdateData(false);
			bytCommand=0xA8;
			break;
		}
	case 14200:
		{
			m_ActStatus.SetWindowText("�����µ�����̨!");
			UpdateData(false);
			bytCommand=0xA7;
			break;
		}
	case 14201:
		{
			m_ActStatus.SetWindowText("�޲���!");//ֹͣ�����µ�����̨!
			UpdateData(false);
			bytCommand=0xA8;
			break;
		}
	case 20100:
		{
			m_ActStatus.SetWindowText("�����Ȧ!");
			UpdateData(false);
			bytCommand=0x86;
			break;
		}
	case 20101:
		{
			m_ActStatus.SetWindowText("�޲���!");//ֹͣ�����Ȧ!
			UpdateData(false);
			bytCommand=0x87;
			break;
		}
	case 20200:
		{
			m_ActStatus.SetWindowText("��С��Ȧ!");
			UpdateData(false);
			bytCommand=0x88;
			break;
		}
	case 20201:
		{
			m_ActStatus.SetWindowText("�޲���!");//ֹͣ��С��Ȧ!
			UpdateData(false);
			bytCommand=0x87;
			break;
		}
	case 20300:
		{
			m_ActStatus.SetWindowText("������!");
			UpdateData(false);
			bytCommand=0x8A;
			break;
		}
	case 20301:
		{
			m_ActStatus.SetWindowText("�޲���!");//ֹͣ������!
			UpdateData(false);
			bytCommand=0x8B;
			break;
		}
	case 20400:
		{
			m_ActStatus.SetWindowText("��С����!");
			UpdateData(false);
			bytCommand=0x8C;
			break;
		}
	case 20401:
		{
			m_ActStatus.SetWindowText("�޲���!");//ֹͣ��С����!
			UpdateData(false);
			bytCommand=0x8B;
			break;
		}
	case 20500:
		{
			m_ActStatus.SetWindowText("����ӳ�!");
			UpdateData(false);
			bytCommand=0x8E;
			break;
		}
	case 20501:
		{
			m_ActStatus.SetWindowText("�޲���!");//ֹͣ����ӳ�!
			UpdateData(false);
			bytCommand=0x8F;
			break;
		}
	case 20600:
		{
			m_ActStatus.SetWindowText("��������!");
			UpdateData(false);
			bytCommand=0x90;
			break;
		}
	case 20601:
		{
			m_ActStatus.SetWindowText("�޲���!");//ֹͣ��������!
			UpdateData(false);
			bytCommand=0x8F;
			break;
		}
	case 20110:
		{
			m_ActStatus.SetWindowText("�����Ȧ,΢��!");
			UpdateData(false);
			bytCommand=0xB0;
			break;
		}
	case 20210:
		{
			m_ActStatus.SetWindowText("��С��Ȧ,΢��!");
			UpdateData(false);
			bytCommand=0xB1;
			break;
		}
	case 20310:
		{
			m_ActStatus.SetWindowText("������,΢��!");
			UpdateData(false);
			bytCommand=0xB2;
			break;
		}
	case 20410:
		{
			m_ActStatus.SetWindowText("��С����,΢��!");
			UpdateData(false);
			bytCommand=0xB3;
			break;
		}
	case 20510:
		{
			m_ActStatus.SetWindowText("����ӳ�,΢��!");
			UpdateData(false);
			bytCommand=0xB4;
			break;
		}
	case 20610:
		{
			m_ActStatus.SetWindowText("��������,΢��!");
			UpdateData(false);
			bytCommand=0xB5;
			break;
		}
	case 30100:
		{
			m_ActStatus.SetWindowText("����ˢ!");
			UpdateData(false);
			bytCommand=0xA0;
			break;
		}
	case 30200:
		{
			m_ActStatus.SetWindowText("�ر���ˢ!");
			UpdateData(false);
			bytCommand=0xA1;
			break;
		}
	case 30300:
		{
			m_ActStatus.SetWindowText("�����!");
			UpdateData(false);
			bytCommand=0xA2;
			break;
		}
	case 30400:
		{
			m_ActStatus.SetWindowText("�ر����!");
			UpdateData(false);
			bytCommand=0xA3;
			break;
		}
	}

	//����iType���;��������
	if(iType==40100)
	{
		m_ActStatus.SetWindowText("ѡ���豸��ַ!");
		UpdateData(false);
		if(m_Address!=0)
		{
			//�����л��豸��ַ������
			sendArray.SetAt(6,0);
			sendArray.SetAt(10,m_Address);
			sendArray.SetAt(11,0x80);
			bytXor=0;
			for(i=4;i<=11;i++)
			{
				bytXor^=sendArray.GetAt(i);
			}
			sendArray.SetAt(12,bytXor);
			if(myComm.GetPortOpen())
			{
				myComm.SetOutput(COleVariant(sendArray));
			}
			else
			{
				m_ActStatus.SetWindowText("���ȴ򿪴���!");
				UpdateData(false);
			}

		}
	}
	else
	{
		//�����豸��������
		if(m_Address==0 && iType<30000)
		{
			m_ActStatus.SetWindowText("��̨����ͷ���ܹ㲥����!");
			UpdateData(false);
			return;
		}
		sendArray.SetAt(6,1);
		sendArray.SetAt(10,m_Address);
		sendArray.SetAt(11,bytCommand);
		bytXor=0;
		for(i=4;i<=11;i++)
		{
			bytXor^=sendArray.GetAt(i);
		}
		sendArray.SetAt(12,bytXor);
		if(myComm.GetPortOpen())
		{
			myComm.SetOutput(COleVariant(sendArray));
		}
		else
		{
			m_ActStatus.SetWindowText("���ȴ򿪴���!");
			UpdateData(false);
		}

	}

}


void CMoniControlDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	//�������Ǵ򿪵ģ���ر�����
	if(myComm.GetPortOpen())
	{
		myComm.SetPortOpen(0);
	}
	CDialog::OnClose();
}

int CMoniControlDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	//�����ؼ���ʵ��
	DWORD style=WS_VISIBLE|WS_CHILD;
	if (!myComm.Create(NULL,style,CRect(0,0,0,0),this,IDC_MSCOMM1))
	{
		AfxMessageBox("����MSComm�ؼ�ʧ�ܣ�");
		m_OpenCom.EnableWindow(false);        //ʹ�򿪴��ڰ�ť��Ч
		m_CloseCom.EnableWindow(false);       //ʹ�رմ��ڰ�ť��Ч
		return -1;
	}	
	return 0;
}
