// SoundDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Sound.h"
#include "SoundDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSoundDlg dialog

CSoundDlg::CSoundDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSoundDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSoundDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	 m_bPlay=FALSE;
	 m_bPause=FALSE;
	 Iscda=0;
	 m_MCIDeviceID=0;

}

void CSoundDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSoundDlg)
	DDX_Control(pDX, IDC_STOP, m_stop);
	DDX_Control(pDX, IDC_PLAY, m_play);
	DDX_Control(pDX, IDC_PAUSE, m_pause);
	DDX_Control(pDX, IDC_OPEN, m_open);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSoundDlg, CDialog)
	//{{AFX_MSG_MAP(CSoundDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_PAUSE, OnPause)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CLOSE, OnClose)
	//}}AFX_MSG_MAP
	ON_MESSAGE(MM_MCINOTIFY,OnMciNotify)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSoundDlg message handlers

BOOL CSoundDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_play.EnableWindow(FALSE); //�����Ű�ť����
	m_stop.EnableWindow(FALSE); //��ֹͣ��ť����
	m_pause.EnableWindow(FALSE); //����ͣ��ť����
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSoundDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSoundDlg::OnPaint() 
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
HCURSOR CSoundDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSoundDlg::OnPlay() 
{
	MCI_PLAY_PARMS mciPlay;
	DWORD dwError;
    if(!m_bPlay)
	{
	  mciPlay.dwCallback=(long)GetSafeHwnd();
	  if(Iscda==1) mciPlay.dwFrom=1;
	  else  mciPlay.dwFrom=0;
	  dwError=mciSendCommand(m_MCIDeviceID,MCI_PLAY,MCI_FROM|MCI_NOTIFY,
		              (DWORD)(LPVOID)&mciPlay);
       }
    if(m_bPlay)
	{
	  if(m_bPause){
		  dwError=mciSendCommand(m_MCIDeviceID,MCI_RESUME,0,NULL);
	  }
	  m_bPause=!m_bPause;
	    }
	if(dwError)
		{
			ShowError(dwError);
		}
      m_play.EnableWindow(FALSE);
	  m_stop.EnableWindow(TRUE);
	  m_pause.EnableWindow(TRUE);
	  m_open.EnableWindow(FALSE);
	  m_bPlay=TRUE;
	
}

void CSoundDlg::OnOpen() 
{
	CString filename;
	CString str;
	MCI_OPEN_PARMS mciOpen;
	DWORD dwError;
    //��ѡ���ļ��Ի���
	static char szFilter[]
	="������Ƶ�ļ�(*.wav)|*.wav|MIDI Audio File(*.mid)|*.mid|CD Audio(*.cda)|*.cda|�����ļ�(*.*)|*.*||";
	CFileDialog dlg(TRUE,"wav",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	if(dlg.DoModal()==IDOK)
	{
		filename=dlg.GetPathName();//�õ��ļ���
		str=filename.Right(3);//�õ��ļ�����չ��
        if(!strcmp(str,"wav")) //�ж��Ƿ���wav�ļ�
		{
			mciOpen.lpstrDeviceType="waveaudio";
		}
		if(!strcmp(str,"mid"))//�ж��Ƿ���mid�ļ�
		{
			mciOpen.lpstrDeviceType="sequencer";
		}
		if(!strcmp(str,"cda"))//�ж��Ƿ���cda�ļ�
		{
			mciOpen.lpstrDeviceType="cdaudio";
			Iscda=1;
		}
		
		mciOpen.lpstrElementName=filename;//���ô��ļ�
		dwError=mciSendCommand(0,MCI_OPEN,MCI_OPEN_TYPE|MCI_OPEN_ELEMENT,
			             (DWORD)(LPVOID)&mciOpen);//��MCI�豸
		if(dwError)
		{
			ShowError(dwError);
		}
		m_MCIDeviceID=mciOpen.wDeviceID;//��ô򿪵�MCI�豸��ID
		m_play.EnableWindow(TRUE);
		m_stop.EnableWindow(TRUE);
		m_pause.EnableWindow(TRUE);
		m_open.EnableWindow(FALSE);
		m_bPlay=FALSE;
		m_bPause=FALSE;
	}
 	
}

void CSoundDlg::OnPause() 
{
	DWORD dwError;
 if(!m_bPause)
	{
		dwError=mciSendCommand(m_MCIDeviceID,MCI_PAUSE,0,NULL);
		if(dwError)
		{
			ShowError(dwError);
		}
		m_play.EnableWindow(TRUE);
	    m_stop.EnableWindow(TRUE);
		m_pause.EnableWindow(FALSE);
	    m_open.EnableWindow(FALSE);
		m_bPause=!m_bPause;
	}	
}

void CSoundDlg::OnStop() 
{
	mciSendCommand(m_MCIDeviceID,MCI_STOP,MCI_WAIT,NULL);
	mciSendCommand(m_MCIDeviceID,MCI_CLOSE,MCI_WAIT,NULL);
    m_bPlay=FALSE;
    m_bPause=FALSE;
	Iscda=0;
    m_play.EnableWindow(FALSE);
    m_stop.EnableWindow(FALSE);
	m_pause.EnableWindow(FALSE);
    m_open.EnableWindow(TRUE);
	
}

void CSoundDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	mciSendCommand(m_MCIDeviceID,MCI_STOP,MCI_WAIT,NULL);//ֹͣ����
	mciSendCommand(m_MCIDeviceID,MCI_CLOSE,MCI_WAIT,NULL);//�ر�MCI�豸
}
LRESULT CSoundDlg::OnMciNotify(WPARAM wParam,LPARAM lParam)
{
	if(wParam==MCI_NOTIFY_SUCCESSFUL)
	{
		m_bPlay=FALSE;
		m_bPause=FALSE;
		Iscda=0;
		return 0;
	}
	return -1;
}
void CSoundDlg::ShowError(DWORD dwError)
{
	char szBuf[1000];
    MessageBeep(MB_ICONEXCLAMATION);
	if(mciGetErrorString(dwError,(LPSTR)szBuf,MAXERRORLENGTH))
		MessageBox(szBuf,"MCI����",MB_ICONEXCLAMATION);
	else 
        MessageBox("δ֪����","MCI����",MB_ICONEXCLAMATION);
}
void CSoundDlg::OnClose() 
{
	CSoundDlg::OnDestroy();
	CSoundDlg::OnOK();	
}
