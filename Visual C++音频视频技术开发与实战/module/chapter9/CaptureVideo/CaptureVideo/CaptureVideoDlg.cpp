// CaptureVideoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CaptureVideo.h"
#include "CaptureVideoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CCaptureVideoDlg �Ի���




CCaptureVideoDlg::CCaptureVideoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCaptureVideoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCaptureVideoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VIDEO_WINDOW, m_videoWindow);
	DDX_Control(pDX, IDC_COMBO1, m_listCtrl);
}

BEGIN_MESSAGE_MAP(CCaptureVideoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_PREVIEW, &CCaptureVideoDlg::OnBnClickedPreview)
	ON_BN_CLICKED(ID_CAPTURE, &CCaptureVideoDlg::OnBnClickedCapture)
	ON_BN_CLICKED(ID_VIDEO_FORMAT, &CCaptureVideoDlg::OnBnClickedVideoFormat)
	ON_BN_CLICKED(ID_IMAGE_PARAMETER, &CCaptureVideoDlg::OnBnClickedImageParameter)
	ON_BN_CLICKED(ID_SAVEGRAPH, &CCaptureVideoDlg::OnBnClickedSavegraph)
	ON_BN_CLICKED(ID_EXIT, &CCaptureVideoDlg::OnBnClickedExit)
END_MESSAGE_MAP()


// CCaptureVideoDlg ��Ϣ�������

BOOL CCaptureVideoDlg::OnInitDialog()
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

	//ShowWindow(SW_MINIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_cap.EnumDevices(m_listCtrl.GetSafeHwnd());
	m_listCtrl.SetCurSel (0); 
	
	m_tooltip.Create(this);
	m_tooltip.Activate(TRUE);
	m_tooltip.AddTool(GetDlgItem(ID_PREVIEW), _T("��ʼԤ����Ƶ"));
	m_tooltip.AddTool(GetDlgItem(ID_CAPTURE), _T("��ʼ���񡢱�����Ƶ"));
	m_tooltip.AddTool(GetDlgItem(ID_VIDEO_FORMAT), _T("��Ƶ��ʽ"));
	m_tooltip.AddTool(GetDlgItem(ID_IMAGE_PARAMETER), _T("ͼ�����"));
	m_tooltip.AddTool(GetDlgItem(ID_SAVEGRAPH), _T("��������"));
	m_tooltip.AddTool(GetDlgItem(ID_EXIT), _T("�˳�Ӧ�ó���"));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCaptureVideoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCaptureVideoDlg::OnPaint()
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
HCURSOR CCaptureVideoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CCaptureVideoDlg::PreTranslateMessage(MSG* pMsg) 
{
	// CG: The following block was added by the ToolTips component.
	{
		// Let the ToolTip process this message.
		m_tooltip.RelayEvent(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CCaptureVideoDlg::OnBnClickedPreview()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HWND hVWindow = m_videoWindow.GetSafeHwnd();
	int id = m_listCtrl.GetCurSel();

	m_cap.PreviewImages(id , hVWindow);
}

void CCaptureVideoDlg::OnBnClickedCapture()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strFilter = _T("AVI File (*.avi) | *.avi|");
	strFilter += "All File (*.*) | *.*|";

	CFileDialog dlg(TRUE, NULL, NULL, OFN_PATHMUSTEXIST|OFN_HIDEREADONLY, strFilter, this);
	if (dlg.DoModal() == IDOK)
	{
		CString m_sourceFile = dlg.GetPathName();	
		m_cap.CaptureImages(m_sourceFile);
	}
}

void CCaptureVideoDlg::OnBnClickedVideoFormat()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_cap.ConfigCameraPin(this->m_hWnd);
}

void CCaptureVideoDlg::OnBnClickedImageParameter()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_cap.ConfigCameraFilter(this->m_hWnd);	
}

void CCaptureVideoDlg::OnBnClickedSavegraph()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE);
	if (dlg.DoModal()==IDOK)
	{
		CString str=dlg.GetPathName();
		TCHAR *inFileName = str.GetBuffer(str.GetLength());
		str.ReleaseBuffer();
		m_cap.SaveGraph(inFileName);
	}
}

void CCaptureVideoDlg::OnBnClickedExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}
