//////////////////////////////////////////////////////////////////////
//
//  This class is designed to provide simple interface for 
//  simultaneous Video Capture & Preview using DirectShow
//
//////////////////////////////////////////////////////////////////////
//
//	References: MS DirectShow Samples
//
//		
// VMR_Capture.cpp: implementation of the CVMR_Capture class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VMR_Capture.h"

#define RELEASE_POINTER(x) { if (x) x->Release(); x = NULL; }

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CVMR_Capture::CVMR_Capture()
{
	CoInitialize(NULL);
	m_pGB = NULL;
	m_pMC = NULL;
	m_pME = NULL;			
	m_pWC = NULL;		
	m_pDF =NULL;
	m_pCamOutPin =NULL;
	m_pFrame=NULL;
	m_nFramelen=0;

	m_psCurrent=STOPPED;
}

CVMR_Capture::~CVMR_Capture()
{
	CloseInterfaces();
	CoUninitialize( );
}

/* �����˲���������Ӹ����˲��������Ӳ���������*/
HRESULT CVMR_Capture::Init(int iDeviceID,HWND hWnd, int iWidth, int iHeight)
{
	HRESULT hr;
	
	//�ٴε��ú������ͷ��Ѿ�����������
	CloseInterfaces();

	// ����IGraphBuilder
    hr = CoCreateInstance(CLSID_FilterGraph, NULL, 
					CLSCTX_INPROC_SERVER, 
					IID_IGraphBuilder, (void **)&m_pGB);

    if (SUCCEEDED(hr))
    {
        // ����VMR����ӵ�Graph��
        InitializeWindowlessVMR(hWnd);        
		
		// ��ָ�����豸����һ���˲���
		if(!BindFilter(iDeviceID, &m_pDF))
			return S_FALSE;
		// ��Ӳɼ��豸�˲�����Graph��
		hr = m_pGB->AddFilter(m_pDF, L"Video Capture");
		if (FAILED(hr)) return hr;
		
		// ��ȡ�����˲���������
		IEnumPins  *pEnum;
		m_pDF->EnumPins(&pEnum);
		hr |= pEnum->Reset();
		hr |= pEnum->Next(1, &m_pCamOutPin, NULL); 
			
        // ��ȡý����ƺ��¼��ӿ�
        hr |= m_pGB->QueryInterface(IID_IMediaControl, (void **)&m_pMC);
        hr |= m_pGB->QueryInterface(IID_IMediaEventEx, (void **)&m_pME);     

		// ���ô���֪ͨ��Ϣ����
        //hr = pME->SetNotifyWindow((OAHWND)hWnd, WM_GRAPHNOTIFY, 0);
		
		// ƥ����Ƶ�ֱ��ʣ�����Ƶ��ʾ��������
		hr |= InitVideoWindow(hWnd,iWidth, iHeight);

		// Ϊ����ͼ��֡�����ڴ�
		m_nFramelen=iWidth*iHeight*3;
		m_pFrame=(BYTE*) new BYTE[m_nFramelen];		

		// ����Graph,������Ƶ
		m_psCurrent = STOPPED;
		hr |= m_pGB->Render(m_pCamOutPin);
		hr |= m_pMC->Run();

		if (FAILED(hr)) return hr;

		m_psCurrent = RUNNING;
	}

	return hr;
}

/* ����VMR����ӡ�����VMR */
HRESULT CVMR_Capture::InitializeWindowlessVMR(HWND hWnd)
{
    IBaseFilter* pVmr = NULL;

    // ����VMR
    HRESULT hr = CoCreateInstance(CLSID_VideoMixingRenderer, NULL,
                                  CLSCTX_INPROC, IID_IBaseFilter, (void**)&pVmr);
    if (SUCCEEDED(hr)) 
    {	
		//���VMR���˲���������
        hr = m_pGB->AddFilter(pVmr, L"Video Mixing Renderer");
        if (SUCCEEDED(hr)) 
        {
            // �����޴�����Ⱦģʽ
            IVMRFilterConfig* pConfig;
            hr = pVmr->QueryInterface(IID_IVMRFilterConfig, (void**)&pConfig);
            if( SUCCEEDED(hr)) 
            {
                pConfig->SetRenderingMode(VMRMode_Windowless);
                pConfig->Release();
            }

			// ���ô���Ĵ���Ϊ��ʾ����
            hr = pVmr->QueryInterface(IID_IVMRWindowlessControl, (void**)&m_pWC);
            if( SUCCEEDED(hr)) 
            {
                m_pWC->SetVideoClippingWindow(hWnd);
            }
        }
        pVmr->Release();
    }

    return hr;
}

/* ��ָ���Ĳɼ��豸��Filter���� */
bool CVMR_Capture::BindFilter(int deviceId, IBaseFilter **pFilter)
{
	HRESULT hr;
	if (deviceId < 0)  return false;
	
    // enumerate all video capture devices
	ICreateDevEnum  *pCreateDevEnum;
    hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
						IID_ICreateDevEnum, (void**)&pCreateDevEnum);
    if (hr != NOERROR)	return false;

    IEnumMoniker *pEm;
    hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEm, 0);
    if (hr != NOERROR)	return false;

    pEm->Reset();
    ULONG cFetched;
    IMoniker *pM;
	int index = 0;
    while(hr = pEm->Next(1, &pM, &cFetched), hr==S_OK, index <= deviceId)
    {
		IPropertyBag *pBag;
		hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
		if(SUCCEEDED(hr)) 
		{
			VARIANT var;
			var.vt = VT_BSTR;
			hr = pBag->Read(L"FriendlyName", &var, NULL);
			if (hr == NOERROR) 
			{
				if (index == deviceId)
				{
					pM->BindToObject(0, 0, IID_IBaseFilter, (void**)pFilter);
				}
				SysFreeString(var.bstrVal);
			}
			pBag->Release();
		}
		pM->Release();
		index++;
    }
	return true;
}

/* ���ò���ͼ��֡�ĸ�ʽ���������и�ʽ�Ƿ���Ԥ����ʽ����û������Ĭ�ϸ�ʽ���� */
HRESULT CVMR_Capture::InitVideoWindow(HWND hWnd,int width, int height)
{
	HRESULT hr;
	RECT rcDest;
	
    IAMStreamConfig *pConfig;
    IEnumMediaTypes *pMedia;
    AM_MEDIA_TYPE *pmt = NULL, *pfnt = NULL;

    hr = m_pCamOutPin->EnumMediaTypes( &pMedia );
    if(SUCCEEDED(hr))
    {
		//��������Ƶ�����и�ʽ����һ�飬���Ƿ���Ԥ���ĸ�ʽ
        while(pMedia->Next(1, &pmt, 0) == S_OK)
        {
            if( pmt->formattype == FORMAT_VideoInfo )
            {
                VIDEOINFOHEADER *vih = (VIDEOINFOHEADER *)pmt->pbFormat;
				// ��ǰ�ĸ�ʽ�Ƿ���Ԥ����ʽ��ͬ������͸���ͬ
                if( vih->bmiHeader.biWidth == width && vih->bmiHeader.biHeight == height )
                {
                    pfnt = pmt;
				    break;
                }
                DeleteMediaType( pmt );
            }  
        }
        pMedia->Release();
    }
	
    hr = m_pCamOutPin->QueryInterface( IID_IAMStreamConfig, (void **) &pConfig );
    if(SUCCEEDED(hr))
    {
		// ��Ԥ���ĸ�ʽ
        if( pfnt != NULL )
        {
            hr=pConfig->SetFormat( pfnt );
            DeleteMediaType( pfnt );
        }
		// û��Ԥ���ĸ�ʽ����ȡȱʡý���ʽ
        hr = pConfig->GetFormat( &pfnt );
        if(SUCCEEDED(hr))
        {
            m_nWidth = ((VIDEOINFOHEADER *)pfnt->pbFormat)->bmiHeader.biWidth;   //��ȡ��
            m_nHeight = ((VIDEOINFOHEADER *)pfnt->pbFormat)->bmiHeader.biHeight; //��ȡ��
            DeleteMediaType( pfnt );
        }

    }
	// ��ȡ���봰�ڵ�������������ʾ����
	::GetClientRect (hWnd,&rcDest);
    hr = m_pWC->SetVideoPosition(NULL, &rcDest);
    return hr;
}

/* �ͷ�������Դ���Ͽ����� */
void CVMR_Capture::CloseInterfaces(void)
{
    HRESULT hr;
   	// ֹͣý��ط�
    if(m_pMC) hr = m_pMC->Stop();	    
    m_psCurrent = STOPPED;

    // �ͷŲ�����ӿ�ָ��
	if(m_pCamOutPin)
		m_pCamOutPin->Disconnect();

	RELEASE_POINTER(m_pCamOutPin);        
    RELEASE_POINTER(m_pMC);    
    RELEASE_POINTER(m_pGB);    
    RELEASE_POINTER(m_pWC);	
	RELEASE_POINTER(m_pDF);

	// �ͷŷ�����ڴ�
	if(m_pFrame!=NULL)
		delete []m_pFrame;
}

/* ɾ��ý������ */
void CVMR_Capture::DeleteMediaType(AM_MEDIA_TYPE *pmt)
{
    // allow NULL pointers for coding simplicity
    if (pmt == NULL) {
        return;
    }

    if (pmt->cbFormat != 0) {
        CoTaskMemFree((PVOID)pmt->pbFormat);

        pmt->cbFormat = 0;
        pmt->pbFormat = NULL;
    }
    if (pmt->pUnk != NULL) {
        pmt->pUnk->Release();
        pmt->pUnk = NULL;
    }

    CoTaskMemFree((PVOID)pmt);
}

/* �Ѳ����ͼ��֡�ռ䴫�� */
DWORD CVMR_Capture::GetFrame(BYTE **pFrame)
{
	if(m_pFrame && m_nFramelen)
	{
		*pFrame = m_pFrame;
	}
	
	return m_nFramelen;
}

/* ��VMR�л�ȡһ֡ͼ���ʽ��RGB24/I420 */
DWORD CVMR_Capture::GrabFrame()
{
	if(m_pWC ) 
    {
		BYTE* lpCurrImage = NULL;

        if(m_pWC->GetCurrentImage(&lpCurrImage) == S_OK)
        {
			// ��ȡͼ��֡����lpCurrImage
			LPBITMAPINFOHEADER  pdib = (LPBITMAPINFOHEADER) lpCurrImage;
			if(m_pFrame==NULL || (pdib->biHeight * pdib->biWidth * 3) !=m_nFramelen )
			{
				if(m_pFrame!=NULL)
				delete []m_pFrame;

				m_nFramelen = pdib->biHeight * pdib->biWidth * 3;
				m_pFrame = new BYTE [pdib->biHeight * pdib->biWidth * 3] ;
			}			
			if(pdib->biBitCount == 32) 
			{
				DWORD  dwSize=0, dwWritten=0;			

				BYTE *pTemp32;
				pTemp32=lpCurrImage + sizeof(BITMAPINFOHEADER);
				//change from 32 to 24 bit /pixel
				this->Convert24Image(pTemp32, m_pFrame, pdib->biSizeImage);
			}
			// �ͷŸ�ͼ��lpCurrImage
			CoTaskMemFree(lpCurrImage);
		}
		else {
			return -1;
		}
	}else{
		return -1;
	}

    return m_nFramelen;
}

/* ARGB32 to RGB24 */
bool CVMR_Capture::Convert24Image(BYTE *p32Img, BYTE *p24Img,DWORD dwSize32)
{
	if(p32Img != NULL && p24Img != NULL && dwSize32>0)
	{
		DWORD dwSize24;
		dwSize24=(dwSize32 * 3)/4;
		BYTE *pTemp=p32Img,*ptr=p24Img;
		
		for (DWORD index = 0; index < dwSize32/4 ; index++)
		{									
			unsigned char r = *(pTemp++);  	unsigned char g = *(pTemp++);
			unsigned char b = *(pTemp++); 	(pTemp++);//skip alpha

			*(ptr++) = b; 		*(ptr++) = g; 	*(ptr++) = r;
		}
	} else {
		return false;
	}
	
	return true;
}


/* ֹͣ���� */
void CVMR_Capture::StopCapture()
{
    HRESULT hr;

	if((m_psCurrent == PAUSED) || (m_psCurrent == RUNNING))
    {
        LONGLONG pos = 0;
        hr = m_pMC->Stop();
        m_psCurrent = STOPPED;		
        // Display the first frame to indicate the reset condition
        hr = m_pMC->Pause();
    }
}

/* ��ͣ */
BOOL CVMR_Capture::Pause()
{	
    if (!m_pMC) return FALSE;
  
    if(((m_psCurrent == PAUSED) || (m_psCurrent == STOPPED)) )
    {
		this->StopCapture();
        if (SUCCEEDED(m_pMC->Run()))
            m_psCurrent = RUNNING;
    }
    else
    {
        if (SUCCEEDED(m_pMC->Pause()))
            m_psCurrent = PAUSED;
    }

	return TRUE;
}

/* ö�ٱ���ϵͳ�Ĳɼ��豸 */
int  CVMR_Capture::EnumDevices(HWND hList)
{
	if (!hList) return  -1;
	int id = 0;
    
	// enumerate all video capture devices
    ICreateDevEnum *pCreateDevEnum;
    HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, 
						CLSCTX_INPROC_SERVER,
						IID_ICreateDevEnum, (void**)&pCreateDevEnum);
    if (hr != NOERROR) return -1;
	
	IEnumMoniker *pEm;
    hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEm, 0);
    if (hr != NOERROR) return -1;

    pEm->Reset();
    ULONG cFetched;
    IMoniker *pM;
    while(hr = pEm->Next(1, &pM, &cFetched), hr==S_OK)
    {
		IPropertyBag *pBag;
		hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
		if(SUCCEEDED(hr)) 
		{
			VARIANT var;
			var.vt = VT_BSTR;
			hr = pBag->Read(L"FriendlyName", &var, NULL);
			if (hr == NOERROR) 
			{
				id++;
				(long)SendMessage(hList, CB_ADDSTRING, 0,(LPARAM)var.bstrVal);
				SysFreeString(var.bstrVal);
			}
			pBag->Release();
		}
		pM->Release();
    }
	return id;
}

/* �ѵ�ǰ�������˲��������浽*.grf */
void CVMR_Capture::SaveGraph(CString wFileName)
{
	HRESULT hr;

	{
		IStorage* pStorage=NULL;
		
		// First, create a document file that will hold the GRF file
		hr = ::StgCreateDocfile(wFileName.AllocSysString(), STGM_CREATE|STGM_TRANSACTED|STGM_READWRITE|STGM_SHARE_EXCLUSIVE,	0, &pStorage);
		if (FAILED(hr))
		{
			AfxMessageBox(TEXT("Can not create a document"));
			return;
		}

		// Next, create a stream to store.
		WCHAR wszStreamName[] = L"ActiveMovieGraph"; 
		IStream *pStream;

		hr = pStorage->CreateStream(wszStreamName,STGM_WRITE|STGM_CREATE|STGM_SHARE_EXCLUSIVE, 0, 0, &pStream);

		if(FAILED(hr))
		{
			AfxMessageBox(TEXT("Can not create a stream"));
			pStorage->Release();
			return;
		}

		// The IpersistStream::Save method converts a stream
		// into a persistent object.
		IPersistStream *pPersist = NULL;

		m_pGB->QueryInterface(IID_IPersistStream,  reinterpret_cast<void**>(&pPersist));
		hr = pPersist->Save(pStream, TRUE);
		pStream->Release();
		pPersist->Release();

		if(SUCCEEDED(hr))
		{
			hr = pStorage->Commit(STGC_DEFAULT);
			if (FAILED(hr))
			{
			AfxMessageBox(TEXT("can not store it"));
			}
		}
		pStorage->Release();
	}

}