//////////////////////////////////////////////////////////////////////
//
//  This class is designed to provide simple interface for 
//  simultaneous Video Capture & Preview using DirectShow
//
//////////////////////////////////////////////////////////////////////
// VMR_Capture.h: interface for the CVMR_Capture class.
//////////////////////////////////////////////////////////////////////


#pragma once

#include <dshow.h>
#include <d3d9.h>
#include <vmr9.h>
//#include "Convert.h"

//#define WM_GRAPHNOTIFY  WM_USER+13
enum PLAYER_STATE {INIT,RUNNING,PAUSED,STOPPED};

class CVMR_Capture  
{
public:
	//constructor/deconstructor
	CVMR_Capture();
	virtual ~CVMR_Capture();
	
	int EnumDevices(HWND hList);        //ö���豸
	HRESULT Init(int iDeviceID,HWND hWnd,int iWidth,int iHeight);
	DWORD GetFrame(BYTE ** pFrame);		//��ȡ�����ͼ��֡
	BOOL Pause();						//��ͣԤ��������
	DWORD GrabFrame();					//�ػ�ͼ��

	void CloseInterfaces(void);			//�رսӿڣ��ͷ���Դ
	void SaveGraph(CString wFileName);	//�����˲�������
	//ColorSpaceConversions conv;			//��ɫ�ռ�ת��

protected:
	
	IGraphBuilder			*m_pGB;			//�˲������������
	IMediaControl			*m_pMC;			//ý����ƽӿ�
	IMediaEventEx			*m_pME;			//ý���¼��ӿ�
	IVMRWindowlessControl9	*m_pWC;			//VMR-9�ӿ�
	IPin					*m_pCamOutPin;	//��Ƶ�ɼ��˲�������
	IBaseFilter				*m_pDF;			//��Ƶ�ɼ��˲���

	PLAYER_STATE			m_psCurrent;

	int		m_nWidth;						//ͼ��֡���
	int		m_nHeight;						//ͼ��֡�߶�
	BYTE	*m_pFrame;						//�����ͼ��֡����ָ��
	long	m_nFramelen;					//�����ͼ��֡���ݴ�С
	
	bool BindFilter(int deviceId, IBaseFilter **pFilter);
	HRESULT InitializeWindowlessVMR(HWND hWnd);
	HRESULT InitVideoWindow(HWND hWnd,int width, int height);
	void StopCapture();
	
	void DeleteMediaType(AM_MEDIA_TYPE *pmt);
	bool Convert24Image(BYTE *p32Img,BYTE *p24Img,DWORD dwSize32);
	
private:
	
};

