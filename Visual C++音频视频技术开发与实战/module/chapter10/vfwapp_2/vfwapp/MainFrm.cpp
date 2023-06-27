// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "vfwapp.h"

#include "MainFrm.h"
#include "xvid_codec.h"
//#include "convert.h"

//#pragma comment(lib,"cscc.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
#define XDIM 704				//ͼ���ȣ�Ԥ����㹻��
#define YDIM 576				//ͼ��߶ȣ�Ԥ����㹻��

unsigned char bufo[XDIM*YDIM*3+40];//Ԥ��ʾ��ͼ��RGB��ʽ

//the parameters used by VCM
HIC             hic1;			//���������
HIC             hic2;			//���������
LPBITMAPINFO    lpbiIn;			//�����ʽ
LPBITMAPINFO	lpbiTmp;		//the output format of compressor
LPBITMAPINFO    lpbiOut;		//�����ʽ
COMPVARS        pc;				//�������ýṹ��
BOOL            IsKeyFrame;		//
BOOL			bSaveAVI=FALSE;	//
long            FrameSize;		//
int				CurrentID;		//
//UINT			uiVideoX=0;		//��ʾͼ��Ŀ��
//UINT			uiVideoY=0;		//��ʾͼ��ĸ߶�
BOOL			bPreview=FALSE;	//
int				nStreamLength;	//
int				nOstreamSize;	//

CFrameWnd	m_wndSource;		//�������´���
HWND		m_hWndCap;			//VFW�豸����
CRect		disRect;			//��ʾ���ڵĿͻ�����
CMainFrame *pMainFrame=NULL;	//MainFrame ָ��
enum		VFW_STATE{PREVIEW,ENCDEC};
VFW_STATE	m_vfwState = PREVIEW;

///////////////////////////////////////////////////////////////////////////////////////////////////


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_VFW_INITVFW, &CMainFrame::OnVfwInitvfw)
	ON_COMMAND(ID_VFW_VIDEOFORMAT, &CMainFrame::OnVfwVideoformat)
	ON_WM_CLOSE()
	ON_COMMAND(ID_VFW_PREVIEWVIDEO, &CMainFrame::OnVfwPreviewvideo)
	ON_COMMAND(ID_VFW_CODEC, &CMainFrame::OnVfwCodec)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//����Ҫ״̬���͹�����
#if 0
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}

	// TODO: �������Ҫ��������ͣ������ɾ��������
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
#endif
	
	lpbiIn  = new BITMAPINFO;  
	lpbiTmp = new BITMAPINFO;
	lpbiOut = new BITMAPINFO; 
	pMainFrame=this;
	::GetClientRect(m_wndSource.m_hWnd,&disRect);
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{

	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.cx = 352+8;
	cs.cy = 288+54;
	cs.lpszName=_T("VFW�ɼ�");
	cs.style&=~FWS_ADDTOTITLE;

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


/****************************************************************************
 *	VFW callback routines
 ***************************************************************************/

// Function name	: EXPORT ErrorCallbackProc
// Description	    : 
// Return type		: LRESULT CALLBACK 
// Argument         : HWND hWnd
// Argument         : int nErrID
// Argument         : LPSTR lpErrorText
LRESULT CALLBACK EXPORT ErrorCallbackProc(HWND hWnd, int nErrID, LPSTR lpErrorText)
{
	if(nErrID==0)
		return TRUE;
	MessageBox(NULL,(LPCWSTR)lpErrorText,_T(""),MB_OK);
	return TRUE;
}


// Function name	: PASCAL StatusCallbackProc
// Description	    : 
// Return type		: LRESULT FAR 
// Argument         : HWND hWnd
// Argument         : int nID
// Argument         : LPSTR lpStatusText
LRESULT FAR PASCAL StatusCallbackProc(HWND hWnd, int nID, LPSTR lpStatusText)
{
	if(nID==IDS_CAP_END){
		if((CurrentID==IDS_CAP_STAT_VIDEOAUDIO)||(CurrentID==IDS_CAP_STAT_VIDEOONLY))
			return TRUE;
	}
	CurrentID = nID;
	return (LRESULT) TRUE;
}


// Function name	: PASCAL VideoCallbackProc
// Description	    : Encode the captured frame
// Return type		: LRESULT FAR 
// Argument         : HWND hWnd
// Argument         : LPVIDEOHDR lpVHdr
LRESULT FAR PASCAL VideoCallbackProc(HWND hWnd, LPVIDEOHDR lpVHdr)
{
	unsigned char *bufi, *buf;
	int type=0;
	int quant=0;
	int declen=0;
	int enclen=0;
	bufi = new unsigned char[lpVHdr->dwBytesUsed+40];	//original image
	buf = new unsigned char[lpVHdr->dwBytesUsed];		//coded stream

	memcpy((void *)(bufi), lpVHdr->lpData, lpVHdr->dwBytesUsed);
	
	unsigned char *buf1;
	buf1 = buf;
	

	if (m_vfwState==ENCDEC) {
   //Encode
		buf1 = (unsigned char*)ICSeqCompressFrame(&pc,0,bufi, &IsKeyFrame,&FrameSize);
		//enc_main(bufi, buf, (int *)&FrameSize, &IsKeyFrame, -1);
		////////////////////////////////
		if (bSaveAVI){
			AVIStreamSetFormat(pMainFrame->ps,pMainFrame->m_Frame++,lpbiTmp,sizeof(BITMAPINFO));
			AVIStreamWrite(pMainFrame->ps,pMainFrame->m_Frame, 1, (LPBYTE)buf1,
						 lpbiTmp->bmiHeader.biSizeImage,AVIIF_KEYFRAME,NULL,NULL);
		}
		////////////////////////////////
   //Decode
		ICDecompress(hic2,0,&lpbiTmp->bmiHeader,buf1,&lpbiOut->bmiHeader,&bufo[40]);
	} else {
		enc_main(bufi,buf, &IsKeyFrame,&type,&quant,&enclen);
		declen = dec_main(buf, bufi, enclen,lpbiIn->bmiHeader.biWidth);
		pMainFrame->conv.YV12_to_RGB24(bufi,
									   bufi+(lpbiIn->bmiHeader.biWidth*lpbiIn->bmiHeader.biHeight),
									   bufi+(lpbiIn->bmiHeader.biWidth*lpbiIn->bmiHeader.biHeight*5/4),
									   &bufo[40],
									   lpbiIn->bmiHeader.biWidth,
									   lpbiIn->bmiHeader.biHeight);
	}

	pMainFrame->GetActiveView()->InvalidateRect(NULL,FALSE);											

	delete bufi;
	delete buf;

	return (LRESULT) TRUE;
}


// CMainFrame ��Ϣ�������

/*��ʼ��VFW�豸*/ 
void CMainFrame::OnVfwInitvfw()
{
	// TODO: �ڴ���������������
	DWORD fsize;

	// ������Ƶ����
	if(!m_wndSource.CreateEx(WS_EX_TOPMOST,NULL,
							_T("Source"),WS_OVERLAPPED|WS_CAPTION,
							CRect(0,0,352,288),NULL,0))
		return;
	
	m_hWndCap = capCreateCaptureWindow(_T("Capture Window"),WS_CHILD|WS_VISIBLE,
									  0,0,352,288,
									  m_wndSource.m_hWnd,0);

	//m_wndSource.ShowWindow(SW_SHOW);
	// ע��ص�����
	capSetCallbackOnError(m_hWndCap,(FARPROC)ErrorCallbackProc);
	capSetCallbackOnStatus(m_hWndCap,(FARPROC)StatusCallbackProc);
	capSetCallbackOnVideoStream(m_hWndCap,(FARPROC)VideoCallbackProc);

	// ������Ƶ�豸
	capDriverConnect(m_hWndCap,0);	//(HWND m_hWndCap, int index);//index : 0--9
	// ��ȡ�����������ܲ���
	capDriverGetCaps(m_hWndCap,&m_caps,sizeof(CAPDRIVERCAPS));
	if (m_caps.fHasOverlay)
		capOverlay(m_hWndCap,TRUE);
	// ����Ԥ�����ʿ�ʼԤ��
	capPreviewRate(m_hWndCap,1000/25);
	capPreview(m_hWndCap,bPreview);


	fsize = capGetVideoFormatSize(m_hWndCap);
	capGetVideoFormat(m_hWndCap, lpbiIn, fsize);
	
	AfxMessageBox(_T("��ʼ���ɹ���"));
}

/*����XVID CODEC��Ƶ������㷨*/
void CMainFrame::Config_XVIECODEC()
{
	////////////////////////////////////////////////////////////////
	ENC_PARAM m_Param;
	m_Param.width = lpbiIn->bmiHeader.biWidth;	//��Ƶͼ����
	m_Param.height= lpbiIn->bmiHeader.biHeight;	//��Ƶͼ��߶�
	m_Param.bitrate = 800000;					//������С��ʹ����������
	m_Param.max_key_interval = 100;				//�ؼ�֡���
	m_Param.framerate = 25;						//֡��
	m_Param.quant = 0;							//����������0��ʾʹ����������

	enc_init(&m_Param);							//����xvid codec������
	dec_init(m_Param.width,m_Param.height);		//����xvid codec������
	////////////////////////////////////////////////////////////////
}

/* ������Ƶ��ʽ���ֱ��ʺ���Ƶ��ʽ��RGB/I420 */
void CMainFrame::OnVfwVideoformat()
{
	// TODO: �ڴ���������������
	DWORD fsize;
	if(m_caps.fHasDlgVideoFormat){
		capDlgVideoFormat(m_hWndCap);
		fsize = capGetVideoFormatSize(m_hWndCap);
		capGetVideoFormat(m_hWndCap, lpbiIn, fsize);
		Config_XVIECODEC();
	}
}

void CMainFrame::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	capCaptureAbort(m_hWndCap);
	capDriverDisconnect(m_hWndCap);
	Sleep(100);
	capSetCallbackOnError(m_hWndCap,NULL);
	capSetCallbackOnStatus(m_hWndCap,NULL);
	capSetCallbackOnVideoStream(m_hWndCap,NULL);
	delete lpbiIn;
	delete lpbiTmp;
	delete lpbiOut;
	if (m_vfwState==ENCDEC){
		ICDecompressEnd(hic2);
		ICClose(hic2);
		ICSeqCompressFrameEnd(&pc);
		ICCompressEnd(hic1);
		ICClose(hic1);
		AVIStreamClose(ps);
		if(m_pFile != NULL)
			AVIFileRelease(m_pFile);
	}

	enc_stop();
	dec_stop();

	Sleep(100);
	CFrameWnd::OnClose();
}

/* ��ʼ����Ԥ����Ƶ */
void CMainFrame::OnVfwPreviewvideo()
{
	// TODO: �ڴ���������������
	CAPTUREPARMS CapParms;

	bPreview =! bPreview;
	if(bPreview){
		capCaptureGetSetup(m_hWndCap,&CapParms,sizeof(CAPTUREPARMS));
		CapParms.dwIndexSize=324000;
		CapParms.fMakeUserHitOKToCapture=!CapParms.fMCIControl;
		CapParms.wPercentDropForError=100;
		CapParms.wNumVideoRequested=5;
		CapParms.wChunkGranularity=0;
		CapParms.fYield=TRUE;
		CapParms.fCaptureAudio=FALSE;
		CapParms.vKeyAbort=0;
		CapParms.fAbortLeftMouse=CapParms.fAbortRightMouse=FALSE;
		CapParms.dwRequestMicroSecPerFrame=1000000/25;
		capSetCallbackOnYield(m_hWndCap,NULL);
		capCaptureSetSetup(m_hWndCap,&CapParms,sizeof(CAPTUREPARMS));

		capCaptureSequenceNoFile(m_hWndCap);
		m_vfwState  = PREVIEW;
	}else{
		capCaptureAbort(m_hWndCap);
	}
}

/* �Բ������Ƶ�����롢���봦�� */
void CMainFrame::OnVfwCodec()
{
	// TODO: �ڴ���������������
	DWORD fsize;
	/* VCM initialization */
	hic1 = ICOpen(mmioFOURCC('v','i','d','c'),  mmioFOURCC('X','V','I','D'),  ICMODE_COMPRESS);
	if (hic1 == 0) 
		AfxMessageBox(_T("�򿪱�����ʧ��!"));

	hic2 = ICOpen(mmioFOURCC('v','i','d','c'),  mmioFOURCC('X','V','I','D'),  ICMODE_DECOMPRESS);
	if (hic2 == 0) 
		AfxMessageBox(_T("�򿪽�����ʧ��!"));

	fsize = capGetVideoFormatSize(m_hWndCap);
	capGetVideoFormat(m_hWndCap, lpbiIn, fsize);
	
	InitAVIWriteOpt();

	lpbiOut->bmiHeader.biSize          = sizeof(BITMAPINFOHEADER);
	lpbiOut->bmiHeader.biWidth         = lpbiIn->bmiHeader.biWidth;
	lpbiOut->bmiHeader.biHeight        = lpbiIn->bmiHeader.biHeight;
	lpbiOut->bmiHeader.biPlanes        = 1;
	lpbiOut->bmiHeader.biBitCount      = 24;
	lpbiOut->bmiHeader.biCompression   = BI_RGB;
	lpbiOut->bmiHeader.biSizeImage     = lpbiIn->bmiHeader.biWidth*lpbiIn->bmiHeader.biHeight*3;
	lpbiOut->bmiHeader.biXPelsPerMeter = 0;
	lpbiOut->bmiHeader.biYPelsPerMeter = 0;
	lpbiOut->bmiHeader.biClrUsed       = 0;
	lpbiOut->bmiHeader.biClrImportant  = 0;

//	get the format of the input video
	if (ICCompressGetFormat(hic1,lpbiIn,lpbiTmp)!=ICERR_OK) 
		AfxMessageBox(_T("���������ܶ�ȡ�����ʽ��"));
	if (ICCompressQuery(hic1,lpbiIn,lpbiTmp) != ICERR_OK)   
		AfxMessageBox(_T("���ܴ�����������������ʽ��"));

//	set the parameters of the CODEC
	pc.cbSize         = sizeof(COMPVARS);			//�ṹ���С
	pc.dwFlags        = ICMF_COMPVARS_VALID;
	pc.hic            = hic1;						//���������
	pc.fccType        = mmioFOURCC('v','i','d','c');
	pc.fccHandler     = mmioFOURCC('X','V','I','D');
	pc.lpbiOut        = lpbiTmp;					//�����ʽ
	pc.lKey           = 100;						//key֡Ƶ��
	pc.lQ             = 10000;						//ͼ������

	if(!ICSeqCompressFrameStart(&pc, lpbiIn))
		return;
	ICDecompressBegin(hic2,lpbiTmp,lpbiOut);
	m_vfwState  = ENCDEC;
}

void CMainFrame::InitAVIWriteOpt()
{
	CString filename;
	CFileDialog FileDlg(FALSE,_T("avi"));
	if (FileDlg.DoModal()==IDOK)
	{
		filename = FileDlg.GetPathName();
		//capGetVideoFormat(m_hWndCap,&m_InInfo,sizeof(m_InInfo));
		m_Frame = 0 ;
		//AVI�ļ���ʼ��
		AVIFileInit() ;
		bSaveAVI = TRUE;
		
		//���ļ�
		AVIFileOpen(&m_pFile,filename,OF_WRITE | OF_CREATE,NULL);
		memset(&strhdr, 0, sizeof(strhdr)) ;
		strhdr.fccType    = streamtypeVIDEO; 
		strhdr.fccHandler = 0  ;
		strhdr.dwScale    = 1  ;
		strhdr.dwRate     = 25 ; 
		strhdr.dwSuggestedBufferSize = lpbiIn->bmiHeader.biSizeImage;
		SetRect(&strhdr.rcFrame, 0, 0, lpbiIn->bmiHeader.biWidth, lpbiIn->bmiHeader.biHeight);
		ps = NULL;
		//�ļ��ļ���
		AVIFileCreateStream(m_pFile,&ps,&strhdr); 
		
		//��ʼ��׽
		capCaptureSequenceNoFile(m_hWndCap);
	}
}