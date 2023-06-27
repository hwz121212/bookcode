// Tapi14.h

#ifndef __MSM_Tapi14__
#define __MSM_Tapi14__

#define TAPI_CURRENT_VERSION 0x00010004

#include <tapi.h>

//
// �Զ�����Ϣ�������������򴫵�ͨ�Ž���
//

#define TAPI_LINECALLSTATE_CONNECTED WM_USER+5

#define WM_TAPI_DIALING			WM_USER+10
#define WM_TAPI_CONNECT			WM_TAPI_DIALING+1
#define WM_TAPI_DISCONNECT		WM_TAPI_DIALING+2
#define WM_TAPI_IDLE			WM_TAPI_DIALING+3	
#define WM_TAPI_STATUS			WM_TAPI_DIALING+4
#define WM_TAPI_CALL_PROCEEDING	WM_TAPI_DIALING+6
#define WM_TAPI_CALL_ACCEPTED	WM_TAPI_DIALING+7
#define WM_TAPI_LINE_REPLY		WM_TAPI_DIALING+8
#define WM_TAPI_VOICE_SUPPORT	WM_TAPI_DIALING+9

//�������سɹ��������
#define SUCCESS 0
#define ERRORS	-1


//TAPI�汾�ų���
#define TAPI_VERSION_1_0 0x00010003
#define TAPI_VERSION_1_4 0x00010004
#define TAPI_VERSION_2_0 0x00020000

//������ʹ�õ�TAPI�汾�ų���
#define WIN2KTAPIVERSION		TAPI_VERSION_1_4
#define EARLY_TAPI_VERSION		TAPI_VERSION_1_0


/////////////////////////////////////////////////////////////////////////////
// CTapi14 window

class CTapi14
{
protected:
	static CTapi14* MyThis;         //���ڱ��浱ǰ��ʵ��
	HWND  m_hWnd;					//�����򴰿ھ��
	HINSTANCE m_hInst;				//������ʵ�����


	//�ص�����ʹ����Щ���������ڱ�����ǰͨ��״̬
	DWORD m_dwDevice, m_dwMessage,m_dwCallbackInstance;

    DWORD m_dwParam1, m_dwParam2, m_dwParam3;

    HLINEAPP m_LineHandle;	        //TAPI��·���
    HCALL m_hCall;		          	//���о��
    HLINE m_hLine;		          	//��·��� 
	HANDLE m_hComm;					//comm���
	DWORD m_dwLines;				//��Ч����·/�豸����
	LINECALLPARAMS m_LineParams;	//ͨ�Ų����ṹ����
	
	int  m_nDevice;
	long m_nPrivilege;
	long m_nMediaMode;

    DWORD m_dwAPIVersion;			//API�汾��
    char m_szPhoneNumber[64];		//���е绰����
    char m_szMessage[128];			//TAPI��Ϣ�ַ���

// Construction
public:
	CTapi14();

// Attributes
public:
// Operations
protected:
// Overrides
	// protected virtual functions
    virtual void TapiCallBack();                 //�ص�������
    virtual void HandleCallState();              //�������״̬�ĺ���

protected:
	void SetCallbackParams(                      //���ûص���������
				DWORD dwDevice, DWORD dwMsg, 
				DWORD dwCallbackInstance, 
				DWORD dwParam1, DWORD dwParam2, 
				DWORD dwParam3);
	void Delay(UINT lFactor);                    //��ʱ����
	void SetVarProps(HWND hWnd, DWORD hDevice ); //���ñ������Ժ���
	LONG LineStateConnected();                   //������·�����ӵĺ���

public:
// Overrides
	//
	// public virtual functions
	//
	virtual void Create(HWND& hWnd);             //��������
	virtual LONG DialCall( CString PhoneNumber );//���ź���
    virtual LONG HangupCall();                   //�һ�����
	
// Implementation
public:
	virtual ~CTapi14();
	void TapiStatus(LPSTR lpszError,            //����TAPI״̬�ĺ���
				BOOL bShowMsgBox=FALSE);
	LPSTR GetTapiStatus() const                 //��ȡTAPI״̬�ĺ���
	{
		return (LPSTR)m_szMessage;
	}
	// static functions
    static void CALLBACK lineCallbackFunc(      //�ص���������TAPI�Զ�����
								DWORD dwDevice,
								DWORD dwMessage,
								DWORD dwCallbackInstance, 
								DWORD dwParam1,
								DWORD dwParam2, 
								DWORD dwParam3);
};

#endif // __MSM_Tapi14__

/////////////////////////////////////////////////////////////////////////////
