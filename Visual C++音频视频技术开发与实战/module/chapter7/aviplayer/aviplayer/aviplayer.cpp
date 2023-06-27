// aviplayer.cpp : �������̨Ӧ�ó������ڵ㡣
//

//


#include "stdafx.h"
#include <dshow.h>

// �õ���DirectShow SDK���ӿ�
#pragma comment(lib,"strmiids.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	IGraphBuilder *pGraph = NULL;
    IMediaControl *pControl = NULL;
    IMediaEvent   *pEvent = NULL; 
    // ��ʼ��COM��.
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        printf("ERROR - Could not initialize COM library");
        return -1;
    }
// �����˲���ͼ�������
   hr=CoCreateInstance(CLSID_FilterGraph, NULL,
CLSCTX_INPROC_SERVER, 
                               IID_IGraphBuilder, (void **)&pGraph);
    if (FAILED(hr))
    {
        printf("ERROR - Could not create the Filter Graph Manager.");
        return -1;
    }
   // ��ѯý����ƺ�ý���¼��ӿ�
   hr = pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);
    hr = pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);
// ����ͼ������������Ը��Ĵ����ŵ��ļ�����
    hr = pGraph->RenderFile(L"D:\\DXSDK\\Samples\\Media\\ruby.avi", NULL);
    if (SUCCEEDED(hr))
    {
        // ����ͼ��.
        hr = pControl->Run();
        if (SUCCEEDED(hr))
        {
            //�ȴ��طŽ����¼�.
            long evCode;
            pEvent->WaitForCompletion(INFINITE, &evCode);
           // �м�: ��ʵ��Ӧ�õ���,����ʹ��INFINITE��ʶ, ��Ϊ���᲻ȷ������������
        }
    }
// �ͷ�������Դ�͹ر�COM��
    pControl->Release();
    pEvent->Release();
    pGraph->Release();
    CoUninitialize();

	printf("this is a test for vc2005!\n");
	return 0;
}

