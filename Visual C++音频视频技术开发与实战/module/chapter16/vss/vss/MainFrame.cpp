// MainFrame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "vss.h"
#include "MainFrame.h"


// CMainFrame �Ի���

IMPLEMENT_DYNAMIC(CMainFrame, CBkDialogST)

CMainFrame::CMainFrame(CWnd* pParent /*=NULL*/)
	: CBkDialogST(CMainFrame::IDD, pParent)
{

}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_ONE_PIC, m_BtnOnePic);
	DDX_Control(pDX, IDC_BUTTON_FOURE_PIC, m_BtnFourePic);
	DDX_Control(pDX, IDC_BUTTON_EXIT_APP, m_BtnExitApp);
	DDX_Control(pDX, IDC_BUTTON_CHAN_L, m_BtnChan1);
	DDX_Control(pDX, IDC_BUTTON_CHAN_M, m_BtnChan2);
	DDX_Control(pDX, IDC_BUTTON_CHAN_R, m_BtnChan3);
	DDX_Control(pDX, IDC_BUTTON_MINI, m_BtnMini);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_BtnClose);
	DDX_Control(pDX, IDC_VIDEO, m_StaticVideo);
}


BEGIN_MESSAGE_MAP(CMainFrame, CBkDialogST)
	ON_BN_CLICKED(IDC_BUTTON_ONE_PIC, &CMainFrame::OnBnClickedButtonOnePic)
	ON_BN_CLICKED(IDC_BUTTON_FOURE_PIC, &CMainFrame::OnBnClickedButtonFourePic)
	ON_BN_CLICKED(IDC_BUTTON_EXIT_APP, &CMainFrame::OnBnClickedButtonExitApp)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CMainFrame::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_MINI, &CMainFrame::OnBnClickedButtonMini)
	ON_BN_CLICKED(IDC_BUTTON_CHAN_L, &CMainFrame::OnBnClickedButtonChanL)
	ON_BN_CLICKED(IDC_BUTTON_CHAN_M, &CMainFrame::OnBnClickedButtonChanM)
	ON_BN_CLICKED(IDC_BUTTON_CHAN_R, &CMainFrame::OnBnClickedButtonChanR)
	ON_WM_PAINT()
	ON_WM_TIMER()
	//ON_WM_CTLCOLOR()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMainFrame ��Ϣ�������

BOOL CMainFrame::OnInitDialog()
{
	CBkDialogST::OnInitDialog();

/////////////////////////////////////////////////////
	HWND hDesktop;
	HDC hdc; 
	DWORD w, h; 
	hDesktop = ::GetDesktopWindow ();
	hdc = ::GetDC(hDesktop); 
	ScrWidth  = w = GetDeviceCaps(hdc, HORZRES); 
	ScrHeight = h = GetDeviceCaps(hdc, VERTRES);

	bChanged = FALSE;

	if((w!=1024)&&(h!=768))
	{
		DEVMODE   lpDevMode;
		lpDevMode.dmBitsPerPel	= 32;
		lpDevMode.dmPelsWidth	= 1024;
		lpDevMode.dmPelsHeight	= 768;
		lpDevMode.dmDisplayFrequency=75;
		lpDevMode.dmSize = sizeof(lpDevMode);
		lpDevMode.dmFields = DM_PELSWIDTH|DM_PELSHEIGHT|DM_BITSPERPEL;
		LONG result = ChangeDisplaySettings(&lpDevMode,0);
		if(result == DISP_CHANGE_SUCCESSFUL)
		{
			ChangeDisplaySettings(&lpDevMode,CDS_UPDATEREGISTRY);
			bChanged = TRUE;
			//ʹ��CDS_UPDATEREGISTRY��ʾ���޸��ǳ־õ�,
			//����ע�����д������ص����� 
		}
		else
		{
			ChangeDisplaySettings(NULL,0);
		} 
	}
////////////////////////////////////////////////////////

	ModifyStyle(WS_CAPTION,0,0);
	this->ShowWindow(SW_SHOWMAXIMIZED);

	InitInterface();

	//SetBitmap(IDB_1_PIC );
	SetBitmap(IDB_4_PIC);
	
	SetTimer(0,1000,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CMainFrame::InitInterface()
{
	// ��ȡ����ָ��
	pBtnOnePic	= GetDlgItem(IDC_BUTTON_ONE_PIC);
	pBtnFourePic= GetDlgItem(IDC_BUTTON_FOURE_PIC);
	pBtnExitApp = GetDlgItem(IDC_BUTTON_EXIT_APP);
	pBtnMini	= GetDlgItem(IDC_BUTTON_MINI);
	pBtnClose	= GetDlgItem(IDC_BUTTON_CLOSE);
	pBtnChan1	= GetDlgItem(IDC_BUTTON_CHAN_L);
	pBtnChan2   = GetDlgItem(IDC_BUTTON_CHAN_M);
	pBtnChan3	= GetDlgItem(IDC_BUTTON_CHAN_R);

	pDisSysTime = GetDlgItem(IDC_STATIC_TIME);
	pDisSysTime->MoveWindow(850,54,130,80);
	
	pStaticVideo0= GetDlgItem(IDC_VIDEO0);
	pStaticVideo1= GetDlgItem(IDC_VIDEO1);
	pStaticVideo2= GetDlgItem(IDC_VIDEO2);
	pStaticVideo3= GetDlgItem(IDC_VIDEO3);

	pStaticVideo0->MoveWindow(26,53,394,311);
	pStaticVideo1->MoveWindow(26+395,53,392,311);
	pStaticVideo2->MoveWindow(26,53+311+2,394,307);
	pStaticVideo3->MoveWindow(26+395,53+311+2,392,307);

	pStaticVideo0->ShowWindow(SW_HIDE);
	pStaticVideo1->ShowWindow(SW_HIDE);
	pStaticVideo2->ShowWindow(SW_HIDE);
	pStaticVideo3->ShowWindow(SW_HIDE);

	// �ƶ���ָ��λ��
	pBtnOnePic->MoveWindow(16,702,37,37);
	pBtnFourePic->MoveWindow(16+75,702,37,37);
	pBtnMini->MoveWindow(880,2,35,35);
	pBtnClose->MoveWindow(965,3,35,35);
	pBtnChan1->MoveWindow(	876,	401,26,17);
	pBtnChan2->MoveWindow(	876+26,	402,25,16);
	pBtnChan3->MoveWindow(	876+51,	402,26,16);
	pBtnExitApp->MoveWindow(920,684,46,48);
	
	// ����λͼ
	m_BtnOnePic.SetSkin(IDB_BTN_N,IDB_BTN_D,IDB_BTN_N,IDB_BTN_N,0,0,0,0,0);
	m_BtnFourePic.SetSkin(IDB_BTN_N,IDB_BTN_D,IDB_BTN_N,IDB_BTN_N,0,0,0,0,0);
	m_BtnMini.SetSkin(IDB_MINI,IDB_MINI,IDB_MINI,IDB_MINI,0,0,0,0,0);
	m_BtnClose.SetSkin(IDB_CLOSE,IDB_CLOSE,IDB_CLOSE,IDB_CLOSE,0,0,0,0,0);
	m_BtnChan1.SetSkin(IDB_1_n,IDB_1_d,IDB_1_n,IDB_1_n,0,0,0,0,0);
	m_BtnChan2.SetSkin(IDB_2_n,IDB_2_d,IDB_2_n,IDB_2_n,0,0,0,0,0);
	m_BtnChan3.SetSkin(IDB_3_n,IDB_3_d,IDB_3_n,IDB_3_n,0,0,0,0,0);
	m_BtnExitApp.SetSkin( IDB_EXIT,IDB_EXIT, IDB_EXIT, IDB_EXIT,0,0,0,0,0);
	
	// ���������ʾ
	m_BtnOnePic.SetToolTipText(_T("��������ʾ"));
	m_BtnFourePic.SetToolTipText(_T("�Ļ�����ʾ"));
	m_BtnMini.SetToolTipText(_T("��С��"));
	m_BtnClose.SetToolTipText(_T("�ر�"));
	m_BtnChan1.SetToolTipText(_T("��1ͨ��"));
	m_BtnChan2.SetToolTipText(_T("��2ͨ��"));
	m_BtnChan3.SetToolTipText(_T("��3ͨ��"));

}
void CMainFrame::OnBnClickedButtonOnePic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetBitmap(IDB_1_PIC);
	
	//pStaticVideo0->ShowWindow(SW_SHOWNORMAL);
	//pStaticVideo1->ShowWindow(SW_HIDE);
	//pStaticVideo2->ShowWindow(SW_HIDE);
	//pStaticVideo3->ShowWindow(SW_HIDE);
	pStaticVideo0->MoveWindow(26,53,811-24,672-52);
}

void CMainFrame::OnBnClickedButtonFourePic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	SetBitmap(IDB_4_PIC);
	pStaticVideo0->MoveWindow(26,53,394,311);
	//pStaticVideo0->ShowWindow(SW_SHOWNORMAL);
	//pStaticVideo1->ShowWindow(SW_SHOWNORMAL);
	//pStaticVideo2->ShowWindow(SW_SHOWNORMAL);
	//pStaticVideo3->ShowWindow(SW_SHOWNORMAL);
}

void CMainFrame::OnBnClickedButtonExitApp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �ͷ���Դ
	if (MessageBox(_T("ȷ��Ҫ�˳����˻���"),_T("�˳�ϵͳ"),MB_OKCANCEL|MB_ICONQUESTION)==IDCANCEL)
		return ;
	else 
	{
		KillTimer(0);
		if (bChanged)
		{
			DEVMODE   lpDevMode;
			lpDevMode.dmBitsPerPel	= 32;
			lpDevMode.dmPelsWidth	= ScrWidth;
			lpDevMode.dmPelsHeight	= ScrHeight;
			lpDevMode.dmDisplayFrequency=60;
			lpDevMode.dmSize = sizeof(lpDevMode);
			lpDevMode.dmFields = DM_PELSWIDTH|DM_PELSHEIGHT|DM_BITSPERPEL;
			LONG result = ChangeDisplaySettings(&lpDevMode,0);
			if(result == DISP_CHANGE_SUCCESSFUL)
			{
				ChangeDisplaySettings(&lpDevMode,CDS_UPDATEREGISTRY);
				bChanged = TRUE;
			}
			else
			{
				ChangeDisplaySettings(NULL,0);
			} 
		}
		SendMessage(WM_SYSCOMMAND, SC_CLOSE, NULL);
	}
}

void CMainFrame::OnBnClickedButtonClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �ͷ�������Դ
	if (bChanged)
	{
		DEVMODE   lpDevMode;
		lpDevMode.dmBitsPerPel	= 32;
		lpDevMode.dmPelsWidth	= ScrWidth;
		lpDevMode.dmPelsHeight	= ScrHeight;
		lpDevMode.dmDisplayFrequency=60;
		lpDevMode.dmSize = sizeof(lpDevMode);
		lpDevMode.dmFields = DM_PELSWIDTH|DM_PELSHEIGHT|DM_BITSPERPEL;
		LONG result = ChangeDisplaySettings(&lpDevMode,0);
		if(result == DISP_CHANGE_SUCCESSFUL)
		{
			ChangeDisplaySettings(&lpDevMode,CDS_UPDATEREGISTRY);
			//bChanged = TRUE;
			//ʹ��CDS_UPDATEREGISTRY��ʾ���޸��ǳ־õ�,
			//����ע�����д������ص����� 
		}
		else
		{
			ChangeDisplaySettings(NULL,0);
		} 
	}
	SendMessage(WM_SYSCOMMAND, SC_CLOSE, NULL);
}

void CMainFrame::OnBnClickedButtonMini()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer(0);
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, NULL);
}

void CMainFrame::OnBnClickedButtonChanL()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	pStaticVideo0->ShowWindow(SW_SHOWNORMAL);
	pStaticVideo1->ShowWindow(SW_HIDE);
	pStaticVideo2->ShowWindow(SW_HIDE);
	pStaticVideo3->ShowWindow(SW_HIDE);
	HWND hVWindow = this->pStaticVideo0->GetSafeHwnd();//m_videoWindow.GetSafeHwnd();
	m_cap.PreviewImages(0 , hVWindow);
	//MessageBox(_T("��ѡ���˵�һ��ͨ��������ʾ"));
}

void CMainFrame::OnBnClickedButtonChanM()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox(_T("��ѡ���˵ڶ���ͨ��������ʾ"));
}

void CMainFrame::OnBnClickedButtonChanR()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox(_T("��ѡ���˵�����ͨ��������ʾ"));
}

void CMainFrame::OnPaint()
{
	CPaintDC pDC(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
#if 1
	CFont NewFont; 
	NewFont.CreateFont(16,      // nHeight ����߶�
					0,			// nWidth  ������
					0,			// nEscapement ������ʾ�ĽǶ�
					0,			// nOrientation  ����ĽǶ�
					FW_NORMAL,	//FW_NORMAL,//FW_BOLD,	// nWeight ����İ���
					            //FW_MEDIUM
					FALSE,		// bItalic    б������
					FALSE,		// bUnderline���»��ߵ�����
					0,			// cStrikeOut ��ɾ���ߵ�����
					GB2312_CHARSET,		//ANSI_CHARSET,	// nCharSet ������ַ���
					OUT_DEFAULT_PRECIS,	// nOutPrecision  ����ľ���
					CLIP_DEFAULT_PRECIS,	// nClipPrecision  �ü��ľ���
					DEFAULT_QUALITY,	// nQuality�߼�����������豸��ʵ��  
                                                          //����֮��ľ���  
					DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily ����������弯  
					_T("��Բ")            	    //Arial ��������
					); 
	CFont *pOldFont = pDC.SelectObject(&NewFont);
	pDC.SetBkMode(TRANSPARENT);		//ѡ���豸������
	pDC.SetTextColor(RGB(255,0,0));         //����������ɫ�������Ǻ�ɫ
	pDC.TextOut(100,10,_T("���ϿƼ���ѧ��Ƶ���ϵͳ"));
	pDC.SelectObject(&pOldFont);            // �ظ���������
	NewFont.DeleteObject();                 // ɾ���´���������
	// ��Ϊ��ͼ��Ϣ����CBkDialogST::OnPaint()
#endif

}

void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent==0)
	{
		CTime tTime = CTime::GetCurrentTime();
		CString strTime =tTime.Format("\n           %Y-%m-%d  \n\n              %H:%M:%S");
		this->pDisSysTime->SetWindowText(strTime);
	}
	CBkDialogST::OnTimer(nIDEvent);
}


