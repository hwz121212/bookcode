// Tapi14.h

#ifndef __MSM_Tapi14__
#define __MSM_Tapi14__

#define TAPI_CURRENT_VERSION 0x00010004

#include <tapi.h>

//
// 自定义消息，用于向主程序传递通信进度
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

//函数返回成功与错误常数
#define SUCCESS 0
#define ERRORS	-1


//TAPI版本号常数
#define TAPI_VERSION_1_0 0x00010003
#define TAPI_VERSION_1_4 0x00010004
#define TAPI_VERSION_2_0 0x00020000

//程序中使用的TAPI版本号常数
#define WIN2KTAPIVERSION		TAPI_VERSION_1_4
#define EARLY_TAPI_VERSION		TAPI_VERSION_1_0


/////////////////////////////////////////////////////////////////////////////
// CTapi14 window

class CTapi14
{
protected:
	static CTapi14* MyThis;         //用于保存当前类实例
	HWND  m_hWnd;					//主程序窗口句柄
	HINSTANCE m_hInst;				//主程序实例句柄


	//回调函数使用这些参数，用于表征当前通信状态
	DWORD m_dwDevice, m_dwMessage,m_dwCallbackInstance;

    DWORD m_dwParam1, m_dwParam2, m_dwParam3;

    HLINEAPP m_LineHandle;	        //TAPI线路句柄
    HCALL m_hCall;		          	//呼叫句柄
    HLINE m_hLine;		          	//线路句柄 
	HANDLE m_hComm;					//comm句柄
	DWORD m_dwLines;				//有效的线路/设备个数
	LINECALLPARAMS m_LineParams;	//通信参数结构变量
	
	int  m_nDevice;
	long m_nPrivilege;
	long m_nMediaMode;

    DWORD m_dwAPIVersion;			//API版本号
    char m_szPhoneNumber[64];		//呼叫电话号码
    char m_szMessage[128];			//TAPI信息字符串

// Construction
public:
	CTapi14();

// Attributes
public:
// Operations
protected:
// Overrides
	// protected virtual functions
    virtual void TapiCallBack();                 //回调函数体
    virtual void HandleCallState();              //处理呼叫状态的函数

protected:
	void SetCallbackParams(                      //设置回调参数函数
				DWORD dwDevice, DWORD dwMsg, 
				DWORD dwCallbackInstance, 
				DWORD dwParam1, DWORD dwParam2, 
				DWORD dwParam3);
	void Delay(UINT lFactor);                    //延时函数
	void SetVarProps(HWND hWnd, DWORD hDevice ); //设置变量属性函数
	LONG LineStateConnected();                   //处理线路已连接的函数

public:
// Overrides
	//
	// public virtual functions
	//
	virtual void Create(HWND& hWnd);             //创建函数
	virtual LONG DialCall( CString PhoneNumber );//拨号函数
    virtual LONG HangupCall();                   //挂机函数
	
// Implementation
public:
	virtual ~CTapi14();
	void TapiStatus(LPSTR lpszError,            //发布TAPI状态的函数
				BOOL bShowMsgBox=FALSE);
	LPSTR GetTapiStatus() const                 //获取TAPI状态的函数
	{
		return (LPSTR)m_szMessage;
	}
	// static functions
    static void CALLBACK lineCallbackFunc(      //回调函数，由TAPI自动调用
								DWORD dwDevice,
								DWORD dwMessage,
								DWORD dwCallbackInstance, 
								DWORD dwParam1,
								DWORD dwParam2, 
								DWORD dwParam3);
};

#endif // __MSM_Tapi14__

/////////////////////////////////////////////////////////////////////////////
