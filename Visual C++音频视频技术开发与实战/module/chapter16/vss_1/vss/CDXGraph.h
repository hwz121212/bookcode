//
// CDXGraph.h
//

#ifndef __H_CDXGraph__
#define __H_CDXGraph__

#include <streams.h>

// �˲�������֪ͨ���ض�����
#define WM_GRAPHNOTIFY  (WM_USER+20)

class CDXGraph
{
//private:
public:
	IGraphBuilder	*pGraph;		//�˲������������
	IMediaControl	*pMediaControl;	//ý����ƽӿڣ���run��stop��pause
	IMediaEventEx	*pMediaEvent;	//ý���¼��ӿ�
	IBasicVideo		*pBasicVideo;	//��Ƶ�����ӿ�
	IBasicAudio		*pBasicAudio;	//��Ƶ�����ӿ�
	IVideoWindow	*pVideoWindow;	//��Ƶ���ڽӿ�
	IMediaSeeking	*pMediaSeeking;	//ý�嶨λ�ӿ�

	DWORD				mObjectTableEntry; 

public:
	CDXGraph();
	virtual ~CDXGraph();

public:
	virtual bool Create(void);		//�����˲������������
	virtual void Release(void);		//�ͷ����нӿ�
	virtual bool Attach(IGraphBuilder * inGraphBuilder);

	//IGraphBuilder * GetGraph(void);		//Not outstanding reference count
	IMediaEventEx * GetEventHandle(void);	//����IMediaEventExָ��
	
	//�������ŷ��������˲���
	bool ConnectFilters(IPin * inOutputPin, IPin * inInputPin, const AM_MEDIA_TYPE * inMediaType = 0);
	//�Ͽ������˲���
	void DisconnectFilters(IPin * inOutputPin);
	//������ʾ����
	bool SetDisplayWindow(HWND inWindow);
	//���ô���֪ͨ��Ϣ
	bool SetNotifyWindow(HWND inWindow);
	//���ڴ�С�ı䴦����
	bool ResizeVideoWindow(long inLeft, long inTop, long inWidth, long inHeight);
	//�����¼�
	void HandleEvent(WPARAM inWParam, LPARAM inLParam);
	
	//ý������״̬
	bool Run(void);        // Control filter graph
	bool Stop(void);
	bool Pause(void);
	bool IsRunning(void);  // Filter graph status
	bool IsStopped(void);
	bool IsPaused(void);
	
	//������ʾ����ȫ����ʾ
	bool SetFullScreen(BOOL inEnabled);
	bool GetFullScreen(void);

	// ý�嶨λ
	bool GetCurrentPosition(double * outPosition);
	bool GetStopPosition(double * outPosition);
	bool SetCurrentPosition(double inPosition);
	bool SetStartStopPosition(double inStart, double inStop);
	bool GetDuration(double * outDuration);
	bool SetPlaybackRate(double inRate);

	//����ý������: range from -10000 to 0, and 0 is FULL_VOLUME.
	bool SetAudioVolume(long inVolume);
	long GetAudioVolume(void);

	//������Ƶƽ��: range from -10000(left) to 10000(right), and 0 is both.
	bool SetAudioBalance(long inBalance);
	long GetAudioBalance(void);
	
	//����ý���ļ�
	//bool RenderFile(char * inFile);
	bool RenderFile(TCHAR * inFile);
	
	//ץͼ
	bool SnapshotBitmap(TCHAR *outFile);//const char * outFile);
	
	int m_nVolume;
	void ChangeAudioVolume(int nVolume);
	
	//��������
	void Mute();
	void UnMute();

private:
	//��GraphEdit����ʱʹ��
	void AddToObjectTable(void) ;
	void RemoveFromObjectTable(void);
	//��ѯ�йؽӿ�
	bool QueryInterfaces(void);
};

#endif // __H_CDXGraph__