// 9-2Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "9-2.h"
#include "9-2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TIMER_ID 1
#define TIMER_DELAY 40
#define CAMERA_WIDTH  352
#define CAMERA_HEIGHT 288

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMy92Dlg �Ի���




CMy92Dlg::CMy92Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy92Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy92Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VIDEO_WINDOW, m_videoWindow);
	DDX_Control(pDX, IDC_LISTDEVICE, m_listCtrl);
}

BEGIN_MESSAGE_MAP(CMy92Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_PREVIEW, &CMy92Dlg::OnBnClickedPreview)
	ON_BN_CLICKED(ID_CAPTURE, &CMy92Dlg::OnBnClickedCapture)
	ON_BN_CLICKED(ID_PAUSEPLAY, &CMy92Dlg::OnBnClickedPauseplay)
	ON_BN_CLICKED(ID_SAVEGRAPH, &CMy92Dlg::OnBnClickedSavegraph)
	ON_BN_CLICKED(ID_EXITAPP, &CMy92Dlg::OnBnClickedExitapp)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_STOPCAP, &CMy92Dlg::OnBnClickedStopcap)
END_MESSAGE_MAP()


// CMy92Dlg ��Ϣ�������

BOOL CMy92Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	this->m_VMRCap.EnumDevices(this->m_listCtrl);
	this->m_listCtrl.SetCurSel(0);
	m_yuvFileName = _T("");
	m_fileState = FALSE;
	m_imageWidth = CAMERA_WIDTH;
	m_imageHeight= CAMERA_HEIGHT;
	p_yuv420 = NULL;

	m_tooltip.Create(this);
	m_tooltip.Activate(TRUE);
	m_tooltip.AddTool(GetDlgItem(ID_PREVIEW), _T("Ԥ����Ƶ"));
	m_tooltip.AddTool(GetDlgItem(ID_PAUSEPLAY), _T("��ͣ/��ʼԤ��"));
	m_tooltip.AddTool(GetDlgItem(ID_CAPTURE), _T("ͼ��׽"));
	m_tooltip.AddTool(GetDlgItem(ID_STOPCAP), _T("��ֹ��׽"));
	m_tooltip.AddTool(GetDlgItem(ID_SAVEGRAPH), _T("��������"));
	m_tooltip.AddTool(GetDlgItem(ID_EXITAPP), _T("�˳�Ӧ�ó���"));
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy92Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy92Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CMy92Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CMy92Dlg::PreTranslateMessage(MSG* pMsg) 
{
	// CG: The following block was added by the ToolTips component.
	{
		// Let the ToolTip process this message.
		m_tooltip.RelayEvent(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CMy92Dlg::OnBnClickedPreview()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HWND hwnd = this->m_videoWindow.GetSafeHwnd();
	int id = this->m_listCtrl.GetCurSel();
	HRESULT hr = m_VMRCap.Init(id,hwnd,m_imageWidth,m_imageHeight);
	
	if (FAILED(hr)) 
		AfxMessageBox(_T("�޷������˲�������"));
}

void CMy92Dlg::OnBnClickedCapture()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(FALSE);

	if (dlg.DoModal()==IDOK)
	{
		m_yuvFileName = dlg.GetPathName();
		BOOL ret = m_pFile.Open(m_yuvFileName,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary);
		if (!ret)
		{
			AfxMessageBox(_T("����YUV�ļ�ʧ�ܣ�"));
			return ;
		}
		else
			m_fileState = ret;
		if (!p_yuv420)
			p_yuv420 = new BYTE [m_imageWidth*m_imageHeight*3/2];
		this->KillTimer(TIMER_ID);
		this->SetTimer(TIMER_ID,TIMER_DELAY,NULL);
	}
}

void CMy92Dlg::OnBnClickedStopcap()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer(TIMER_ID);
	if (p_yuv420)
	{
		delete [] p_yuv420;
		p_yuv420 = NULL;
	}
	if (m_fileState)
	{
		m_pFile.Close();
		m_fileState = FALSE;
	}
}

void CMy92Dlg::OnBnClickedPauseplay()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	static int c=0;
	if (!c) {
		GetDlgItem(ID_PAUSEPLAY)->SetWindowTextW(_T("��ʼԤ��"));
		c = 1;
	} else {
		GetDlgItem(ID_PAUSEPLAY)->SetWindowTextW(_T("��ͣԤ��"));
		c = 0;
	}
	m_VMRCap.Pause();
}

void CMy92Dlg::OnBnClickedSavegraph()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HRESULT hr;
	CFileDialog dlg(FALSE);
	
	if (dlg.DoModal()==IDOK)
	{
		CString inFileName = dlg.GetPathName();
		m_VMRCap.SaveGraph(inFileName);
	}
}

void CMy92Dlg::OnBnClickedExitapp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer(TIMER_ID);
	if (p_yuv420)
		delete [] p_yuv420;
	if (m_fileState)
		m_pFile.Close();
	CDialog::OnOK();
}

void CMy92Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent==TIMER_ID)
	{	//��ʱ��ȡ��ȡͼ��֡��ת����ɫ�ռ䣬д�ļ�
		if (m_fileState)
		{
			DWORD dwSize;
			dwSize = this->m_VMRCap.GrabFrame();
			if (dwSize >0 )
			{
				BYTE *pImage;
				this->m_VMRCap.GetFrame(&pImage);
				conv.RGB24_to_YV12(pImage,this->p_yuv420,m_imageWidth,m_imageHeight);
				m_pFile.Write(p_yuv420,m_imageWidth*m_imageHeight*3/2);
			}
		}
	}

	CDialog::OnTimer(nIDEvent);
}


