//-------------------------------------------------------------------
// CCaptureClass��Ƶ��׽��ʵ���ļ�CaptureVideo.cpp
//-------------------------------------------------------------------
// CaptureVideo.cpp: implementation of the CCaptureClass class.
//
/////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CaptureClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCaptureClass::CCaptureClass()
{
	// COM ���ʼ��
	CoInitialize(NULL);
	m_hWnd = NULL;
	m_pVW = NULL;
	m_pMC = NULL;
	m_pGB = NULL;
	m_pBF = NULL;
	m_pCapture = NULL; 
}
CCaptureClass::~CCaptureClass()
{
	//
	if(m_pMC)
		m_pMC->Stop();
	if(m_pVW)
	{
		m_pVW->put_Visible(OAFALSE);
		m_pVW->put_Owner(NULL);
	}
	srelease(m_pCapture);
	srelease(m_pMC);
	srelease(m_pGB);
	srelease(m_pBF);
	CoUninitialize();
}

/*
ϵͳ�豸ö����Ϊ���ǰ�����ö����ע����ϵͳ�е�Fitler�ṩ��ͳһ�ķ������������ܹ����ֲ�ͬ��Ӳ���豸��������ͬһ��Filter֧�����ǡ������Щʹ��Windows����ģ�ͺ�KSProxy Filter���豸��˵�Ƿǳ����õġ�ϵͳ�豸ö���������ǰ���ͬ���豸ʵ�����жԴ�����ע����Ȼ����֧����ͬFilter����
��������������ϵͳ�豸ö������ѯ�豸��ʱ��ϵͳ�豸ö����Ϊ�ض����͵��豸���磬��Ƶ�������Ƶѹ����������һ��ö�ٱ�Enumerator��������ö������Category enumerator��Ϊÿ���������͵��豸����һ��Moniker������ö�����Զ���ÿһ�ּ��弴�õ��豸�������ڡ�
���������µĲ���ʹ��ϵͳ�豸ö������
����1�� ���÷���CoCreateInstance����ϵͳ�豸ö���������ʶ��CLSID��ΪCLSID_SystemDeviceEnum��
����2�� ����ICreateDevEnum::CreateClassEnumerator������������ö����������Ϊ����Ҫ�õ������͵�CLSID���÷�������һ��IEnumMoniker�ӿ�ָ�룬���ָ�������ͣ��ǿյģ��򲻴��ڣ�����ICreateDevEnum::CreateClassEnumerator������S_FALSE�����Ǵ�����룬ͬʱIEnumMonikerָ�루��ע��ͨ���������أ�Ҳ�ǿյģ����Ҫ�������ڵ���CreateClassEnumerator��ʱ����ȷ��S_OK���бȽ϶�����ʹ�ú�SUCCEEDED��
����3�� ʹ��IEnumMoniker::Next�������εõ�IEnumMonikerָ���е�ÿ��moniker���÷�������һ��IMoniker�ӿ�ָ�롣��Next����ö�ٵĵײ������ķ���ֵ��Ȼ��S_FALSE��������������Ҫ��S_OK�����м��顣
����4�� ��Ҫ�õ����豸��Ϊ�Ѻõ����ƣ�������Ҫ���û������н�����ʾ��������IMoniker::BindToStorage������
����5�� �����Ҫ���ɲ���ʼ��������豸��Filter����3����ָ���IMonitor::BindToObject����������������IFilterGraph::AddFilter�Ѹ�Filter��ӵ���ͼ�С�
*/

int CCaptureClass::EnumDevices(HWND hList)
{
	if (!hList)	return -1;
	int id = 0;

	//ö�ٲ����豸
	ICreateDevEnum *pCreateDevEnum;
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, 
						CLSCTX_INPROC_SERVER,
						IID_ICreateDevEnum,
						(void**)&pCreateDevEnum);

	if (hr != NOERROR) 	return -1;
	
	IEnumMoniker *pEm;
	//������Ƶ����ö����
	hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,&pEm, 0);
	//������Ƶ������
	//hr = pCreateDevEnum->CreateClassEnumerator(CLSID_AudioInputDeviceCategory,&pEm, 0);

	if (hr != NOERROR) return -1;
	//����ö������λ
	pEm->Reset();
	ULONG cFetched;
	IMoniker *pM;
	while(hr = pEm->Next(1, &pM, &cFetched), hr==S_OK)
	{
		IPropertyBag *pBag;
		//�豸����ҳ
		hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
		if(SUCCEEDED(hr)) 
		{
			VARIANT var;
			var.vt = VT_BSTR;
			hr = pBag->Read(L"FriendlyName", &var, NULL);
			if (hr == NOERROR) 
			{
				id++;
				::SendMessage(hList, CB_ADDSTRING, 0,(LPARAM)var.bstrVal);
				SysFreeString(var.bstrVal);
			}
			pBag->Release();
		}
		pM->Release();
	}
	return id;
}


/*��ʼԤ����Ƶ����*/
HRESULT CCaptureClass::PreviewImages(int iDeviceID, HWND hWnd)
{
	HRESULT hr;
	
	// ��ʼ����Ƶ�����˲������������
	hr = InitCaptureGraphBuilder();
	if (FAILED(hr))
	{
		AfxMessageBox(_T("Failed to get video interfaces!"));
		return hr;
	}

	// ��ָ���ɼ��豸���˲�������
	if(!BindFilter(iDeviceID, &m_pBF))
		return S_FALSE;
	// ���˲�����ӵ��˲���������
	hr = m_pGB->AddFilter(m_pBF, L"Capture Filter");
	
	// ��Ⱦý�壬���������˲�����������
    hr = m_pCapture->RenderStream( &PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video, m_pBF, NULL, NULL );

	if( FAILED( hr ) )
	{
		AfxMessageBox(_T("Can��t build the graph"));
		return hr;
	}

	//������Ƶ��ʾ����
	m_hWnd = hWnd; 
	SetupVideoWindow();
	//test for config
	hr = m_pMC->Run();
	if(FAILED(hr))
	{
		AfxMessageBox(_T("Couldn��t run the graph!"));
		return hr;
	}
	return S_OK;
}

/*���ò�����Ƶ���ļ�����ʼ��׽��Ƶ����д�ļ�*/
HRESULT CCaptureClass::CaptureImages(CString inFileName)
{
	HRESULT hr=0;
	
	// ��ֹͣ��Ƶ
	m_pMC->Stop();
	// �����ļ�����ע��ú����ĵڶ�������������
	hr = m_pCapture->SetOutputFileName(&MEDIASUBTYPE_Avi, inFileName.AllocSysString(), &pMux, NULL );
    // ��Ⱦý�壬���������˲���
	hr = m_pCapture->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video, m_pBF, NULL, pMux );
	pMux->Release();
	// �ظ���Ƶ
	m_pMC->Run();
	return hr;
}

// ��ָ���ɼ��豸���˲�������
bool CCaptureClass::BindFilter(int deviceId, IBaseFilter **pFilter)
{
	if (deviceId < 0) return false;

	// enumerate all video capture devices
	
	ICreateDevEnum *pCreateDevEnum;

	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, 
					CLSCTX_INPROC_SERVER,
					IID_ICreateDevEnum,
					(void**)&pCreateDevEnum);
	if (hr != NOERROR) return false;
	
	IEnumMoniker *pEm;

	hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,&pEm, 0);
	if (hr != NOERROR) return false;
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

/* �����˲����������������ѯ����ֿ��ƽӿ� */
HRESULT CCaptureClass::InitCaptureGraphBuilder()
{
	HRESULT hr;

	// ����IGraphBuilder�ӿ�
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, 
						CLSCTX_INPROC_SERVER,
						IID_IGraphBuilder, (void **)&m_pGB);
	if (FAILED(hr)) return hr;
	
	// ����ICaptureGraphBuilder2�ӿ�
	hr = CoCreateInstance(CLSID_CaptureGraphBuilder2 , NULL,
						CLSCTX_INPROC,
						IID_ICaptureGraphBuilder2, (void **)&m_pCapture);
	if (FAILED(hr)) return hr;

	// ��ʼ���˲������������IGraphBuilder
	m_pCapture->SetFiltergraph(m_pGB);
	
	// ��ѯý����ƽӿ�
	hr = m_pGB->QueryInterface(IID_IMediaControl, (void **)&m_pMC);
	if (FAILED(hr)) return hr;
	// ��ѯ��Ƶ���ڽӿ�
	hr = m_pGB->QueryInterface(IID_IVideoWindow, (LPVOID *) &m_pVW);
	if (FAILED(hr)) return hr;

	return hr;

}

/* ������Ƶ��ʾ���ڵ����� */ 
HRESULT CCaptureClass::SetupVideoWindow()
{
	HRESULT hr;
	hr = m_pVW->put_Owner((OAHWND)m_hWnd);
	if (FAILED(hr)) return hr;

	hr = m_pVW->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN);
	if (FAILED(hr)) return hr;

	ResizeVideoWindow();
	hr = m_pVW->put_Visible(OATRUE);
	return hr;
}

/* ������Ƶ���ڴ�С */
void CCaptureClass::ResizeVideoWindow()
{
	if (m_pVW)
	{
		//��ͼ�������������
		CRect rc;
		::GetClientRect(m_hWnd,&rc);
		m_pVW->SetWindowPosition(0, 0, rc.right, rc.bottom);
	} 
}

/* ���������˲��������ļ����Ա���ʹ��GraphEdit����鿴*/
void CCaptureClass::SaveGraph(TCHAR *wFileName)
{
	HRESULT hr;
	//CFileDialog dlg(TRUE);
	
	//if (dlg.DoModal()==IDOK)
	{
		//WCHAR wFileName[MAX_PATH];
		//MultiByteToWideChar(CP_ACP, 0, dlg.GetPathName(), -1, wFileName, MAX_PATH);
			
		IStorage* pStorage=NULL;
		
		// First, create a document file that will hold the GRF file
		hr = ::StgCreateDocfile(wFileName, STGM_CREATE|STGM_TRANSACTED|STGM_READWRITE|STGM_SHARE_EXCLUSIVE,	0, &pStorage);
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

/*��������ͷ����Դ��ʽ���ֱ��ʡ�RGB/I420��*/
void CCaptureClass::ConfigCameraPin(HWND hwndParent)
{
    HRESULT hr;
	IAMStreamConfig *pSC;
    ISpecifyPropertyPages *pSpec;

	//ֻ��ֹͣ�󣬲��ܽ���pin���Ե�����
	m_pMC->Stop();

	hr = m_pCapture->FindInterface(&PIN_CATEGORY_CAPTURE,
                        &MEDIATYPE_Video, m_pBF,
                        IID_IAMStreamConfig, (void **)&pSC);

    CAUUID cauuid;

	hr = pSC->QueryInterface(IID_ISpecifyPropertyPages, (void **)&pSpec);
	if(hr == S_OK)
	{
		hr = pSpec->GetPages(&cauuid);
		//��ʾ����ҳ
		hr = OleCreatePropertyFrame(hwndParent,	30, 30, NULL, 1, 
						(IUnknown **)&pSC, cauuid.cElems,
						(GUID *)cauuid.pElems, 0, 0, NULL);
		
		//�ͷ��ڴ桢��Դ
  		CoTaskMemFree(cauuid.pElems);
		pSpec->Release();
		pSC->Release();
	}
	//�ظ�����
	m_pMC->Run();

}

/*����ͼ����������ȡ�ɫ�ȡ����Ͷȵ�*/
void CCaptureClass::ConfigCameraFilter(HWND hwndParent)
{
	HRESULT hr=0;

	ISpecifyPropertyPages *pProp;

	hr = m_pBF->QueryInterface(IID_ISpecifyPropertyPages, (void **)&pProp);

	if (SUCCEEDED(hr)) 
	{
		// ��ȡ�˲������ƺ�IUnknown�ӿ�ָ��
		FILTER_INFO FilterInfo;
		hr = m_pBF->QueryFilterInfo(&FilterInfo); 
		IUnknown *pFilterUnk;
		m_pBF->QueryInterface(IID_IUnknown, (void **)&pFilterUnk);

		// ��ʾ��ҳ
		CAUUID caGUID;
		pProp->GetPages(&caGUID);

		OleCreatePropertyFrame(
			hwndParent,				// ������
			0, 0,                   // Reserved
			FilterInfo.achName,     // �Ի������
			1,                      // ���˲�����Ŀ����Ŀ
			&pFilterUnk,            // Ŀ��ָ������ 
			caGUID.cElems,          // ����ҳ��Ŀ
			caGUID.pElems,          // ����ҳ��CLSID����
			0,                      // ���ر�ʶ
			0, NULL                 // Reserved
		);

		// �ͷ��ڴ桢��Դ
		CoTaskMemFree(caGUID.pElems);
		pFilterUnk->Release();
		FilterInfo.pGraph->Release(); 
		pProp->Release();
	}
	//m_pMC->Run();
}

