// capaudioDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "capaudio.h"
#include "capaudioDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static const GUID CLSID_WavDest = {0x3C78B8E2,0x6C4D,0x11D1,{0xAD,0xE2,0x0,0x0,0xF8,0x75,0x4B,0x99}};

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


// CcapaudioDlg �Ի���




CcapaudioDlg::CcapaudioDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CcapaudioDlg::IDD, pParent)
	, m_PathName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CcapaudioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PATH, m_PathName);
}

BEGIN_MESSAGE_MAP(CcapaudioDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_RECORD, &CcapaudioDlg::OnBnClickedRecord)
	
	ON_BN_CLICKED(ID_STOP, &CcapaudioDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_BUTTON_FILE_NAME, &CcapaudioDlg::OnBnClickedButtonFileName)
//	ON_WM_DESTROY()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CcapaudioDlg ��Ϣ�������

BOOL CcapaudioDlg::OnInitDialog()
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
	//GetDlgItem(ID_RECORD)->EnableWindow(FALSE);
	//GetDlgItem(ID_STOP)->EnableWindow(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CcapaudioDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CcapaudioDlg::OnPaint()
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
HCURSOR CcapaudioDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CcapaudioDlg::OnBnClickedRecord()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strName;
	GetDlgItem(IDC_EDIT_PATH)->GetWindowText(strName);
	
	if(strName.IsEmpty())
	{
		MessageBox(_T("���������ļ���!"));
		return;
	}
	GetDlgItem(ID_STOP)->EnableWindow(true);
	
	
	pGraph = NULL;
	pMC = NULL;
	pBuilder = NULL;

	CoCreateInstance(CLSID_CaptureGraphBuilder2,NULL,
							CLSCTX_INPROC_SERVER,
							IID_ICaptureGraphBuilder2,
							(void**)&pBuilder);

	CoCreateInstance(CLSID_FilterGraph, NULL, 
					CLSCTX_INPROC_SERVER, 
                    IID_IGraphBuilder, 
					(void **)&pGraph);

	pBuilder->SetFiltergraph(pGraph);

	pGraph->QueryInterface(IID_IMediaControl,(void**)&pMC);

	ICreateDevEnum *pDevEnum = NULL;
	CoCreateInstance(CLSID_SystemDeviceEnum, NULL,
					CLSCTX_INPROC, 
					IID_ICreateDevEnum,
					(void **)&pDevEnum);

	IEnumMoniker *pClassEnum = NULL;
	pDevEnum->CreateClassEnumerator(CLSID_AudioInputDeviceCategory, &pClassEnum, 0);
	ULONG cFetched;
	if (pClassEnum->Next(1, &pMoniker, &cFetched) == S_OK)     
	{
		pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)&pSrc);
		pMoniker->Release();      
	}
	pClassEnum->Release();

	CoCreateInstance(CLSID_WavDest, NULL, CLSCTX_ALL, 
                     IID_IBaseFilter, (void **)&pWaveDest);

	CoCreateInstance(CLSID_FileWriter, NULL, CLSCTX_ALL, 
                     IID_IBaseFilter, (void **)&pWriter);

	pGraph->AddFilter(pSrc,L"Wav");
	pGraph->AddFilter(pWaveDest,L"WavDest");
	pGraph->AddFilter(pWriter,L"FileWriter");

	pWriter->QueryInterface(IID_IFileSinkFilter2,(void**)&pSink);

	pSink->SetFileName(strName.AllocSysString(),NULL);

	IPin* pOutpin = FindPin(pSrc,PINDIR_OUTPUT);

	IPin* pInpin,*pOut;	
	
	pOut= FindPin(pWaveDest,PINDIR_OUTPUT);

	AM_MEDIA_TYPE type;
	type.majortype = MEDIATYPE_Stream;
	type.subtype =MEDIASUBTYPE_WAVE;
	type.formattype = FORMAT_None;
	type.bFixedSizeSamples = FALSE;
	type.bTemporalCompression = FALSE;
	type.pUnk = NULL;
	
	//�����˲�������
	pInpin = FindPin(pWaveDest,PINDIR_INPUT);
	IPin* pInpin2= FindPin(pWriter,PINDIR_INPUT);	

	//�����˲���������
	pGraph->ConnectDirect(pOutpin,pInpin,NULL);
	pGraph->ConnectDirect(pOut,pInpin2,NULL);

	pMC->Run();
	GetDlgItem(ID_RECORD)->EnableWindow(false);
	GetDlgItem(ID_STOP)->EnableWindow(true);

}

IPin* CcapaudioDlg::FindPin(IBaseFilter *pFilter, PIN_DIRECTION dir)
{
	IEnumPins* pEnumPins;
	IPin* pOutpin;
	PIN_DIRECTION pDir;
	pFilter->EnumPins(&pEnumPins);

	while (pEnumPins->Next(1,&pOutpin,NULL)==S_OK)
	{
		pOutpin->QueryDirection(&pDir);
		if (pDir==dir)
		{
			return pOutpin;
		}
	}
	return 0;
}


void CcapaudioDlg::OnBnClickedStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	pMC->Stop();
	pMC->Release();
	pGraph->Release();
	pWaveDest->Release();
	pWriter->Release();


	MessageBox(_T("¼�����"));
	GetDlgItem(IDC_EDIT_PATH)->SetWindowText(_T(""));
	GetDlgItem(ID_STOP)->EnableWindow(false);
}

void CcapaudioDlg::OnBnClickedButtonFileName()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strFilter = _T("Wav File (*.wav) | *.wav|");
	strFilter += "All File (*.*) | *.*|";
	CFileDialog dlg(FALSE, NULL, NULL, OFN_PATHMUSTEXIST|OFN_HIDEREADONLY, strFilter, this);

	if (dlg.DoModal()==IDOK)
	{
		CString strName = dlg.GetPathName();
		strName += ".wav";
		this->m_PathName = strName;
		UpdateData(FALSE);
		GetDlgItem(ID_RECORD)->EnableWindow(TRUE);
		GetDlgItem(ID_STOP)->EnableWindow(FALSE);
	}
}

//void CcapaudioDlg::OnDestroy()
//{
//	CDialog::OnDestroy();
//
//
//	// TODO: �ڴ˴������Ϣ����������
//}

void CcapaudioDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	OnBnClickedStop();
	CoUninitialize();
	CDialog::OnClose();
}
