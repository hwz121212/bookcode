// Tapi14.cpp : implementation file
//

#include "stdafx.h"
#include "Tapi14.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// A pointer to my class because TAPI needs a callback
CTapi14* CTapi14::MyThis = NULL;
CString strStatus;                         //用于向主窗口传递显示信息

/////////////////////////////////////////////////////////////////////////////
// CTapi14

CTapi14::CTapi14()
{
	MyThis = this;                        //使MyThis指向当前的类实例
	m_LineHandle = NULL;                  //线路句柄初始化为NULL
}

void CTapi14::Create(HWND& hWnd)
{
	m_hWnd = hWnd;                //主程序的窗口句柄
	m_hInst =(HINSTANCE)::GetWindowLong(m_hWnd, GWL_HINSTANCE);

	//将一些必要的属性设置为NULL
	SetProp( m_hWnd, "HCALL", NULL );
	SetProp( m_hWnd, "HLINE", NULL );
	SetProp( m_hWnd, "HCOMM", NULL );
}


CTapi14::~CTapi14()
{
	//清除保存的属性值
	RemoveProp( m_hWnd, "HCALL" );
	RemoveProp( m_hWnd, "HLINE" );
	RemoveProp( m_hWnd, "HCOMM" );
}

//***********************************************
// 呼叫函数
//***********************************************
LONG CTapi14::DialCall(CString  PhoneNumber )
{
	LONG	retcode =  0;			
	DWORD	i;						
	DWORD	RetApiVersion;			
	LINEEXTENSIONID	ExtensionID;	

	//检查电话号码是否为空
	if( lstrlen( PhoneNumber ) < 1 )
		return( ERRORS );	

	//初始化线路，并注册回调函数
	if( m_LineHandle == NULL ) {
		retcode = ::lineInitialize( 
							&m_LineHandle,
							m_hInst, 
							(LINECALLBACK)lineCallbackFunc, 
							"FELIX TAPI", 
							&m_dwLines );
		if( retcode < 0 )  {
			TapiStatus("Tapi出错..." );
			return (retcode);
		}
		else
			TapiStatus("Tapi初始化完毕..." );
	}
	//
	// 遍历API线路
	// 若发现正确的属性，则跳出，继续向下执行 
	//
	m_hLine = (HLINE)GetProp( m_hWnd, "HLINE" );
	if( m_hLine == NULL )
	{
		for( i=0; i < m_dwLines; i++ )
		{
			// 对每条线路协商TAPI版本
			retcode = ::lineNegotiateAPIVersion(
							m_LineHandle,
							i, 
							EARLY_TAPI_VERSION, 
							WIN2KTAPIVERSION,
							&RetApiVersion,
							&ExtensionID );

			retcode = ::lineOpen( m_LineHandle, 
							i, 
							&m_hLine, 
							RetApiVersion,
							0,
							(DWORD)m_hWnd,
							LINECALLPRIVILEGE_MONITOR | 
							LINECALLPRIVILEGE_OWNER,
							LINEMEDIAMODE_DATAMODEM, 
							NULL );
			if( retcode == 0 )
				break;
		}
		if( retcode != 0 )
			return( ERRORS );
	}
	//
	// 找到可用的线路
	SetProp( m_hWnd, "HLINE",(HANDLE)(HLINE)m_hLine );

	//
	// 设置线路属性，以便拨打外线
	memset( &m_LineParams, 0, sizeof( LINECALLPARAMS ) );
	m_LineParams.dwTotalSize = sizeof( LINECALLPARAMS );
	m_LineParams.dwMinRate = 9600;	
	m_LineParams.dwMaxRate = 28800;	
    m_LineParams.dwBearerMode = LINEBEARERMODE_VOICE; 
	m_LineParams.dwMediaMode  = LINEMEDIAMODE_DATAMODEM;
	//
	// 最后，呼叫电话!
	retcode = ::lineMakeCall( m_hLine, 
					&m_hCall, 
					PhoneNumber,
					0, 
					&m_LineParams );
	if( retcode < 0 ) 
			return (retcode);	
	else
		//等待5s，该时间可以根据实际情况重新设定
		Delay(5000);               
	return( retcode );	
}

//
//  回调函数lineCallbackFunc(..)
//
//  异步接收TAPI的事件
//
void CALLBACK CTapi14::lineCallbackFunc(
					DWORD dwDevice,
					DWORD dwMessage,
					DWORD dwCallbackInstance, 
					DWORD dwParam1, 
					DWORD dwParam2,
					DWORD dwParam3)
{
	MyThis->SetCallbackParams(
					dwDevice, 
					dwMessage, 
					dwCallbackInstance, 
					dwParam1,
					dwParam2, 
					dwParam3);
}
//设置回调函数参数
void CTapi14::SetCallbackParams(
					DWORD dwDevice, 
					DWORD dwMessage, 
					DWORD dwCallbackInstance, 
					DWORD dwParam1,
					DWORD dwParam2, 
					DWORD dwParam3)
{
	m_dwDevice = dwDevice;
	m_dwMessage = dwMessage;
	m_dwCallbackInstance = dwCallbackInstance;
	m_dwParam1 = dwParam1;
	m_dwParam2 = dwParam2; 
	m_dwParam3 = dwParam3;
	
	//调用具体功能的回调函数
	TapiCallBack();		
}	

// *******************************************
// 处理TAPI消息的回调函数
//
void CTapi14::TapiCallBack()
{   
	
    switch (m_dwMessage) 
        { 
        case LINE_LINEDEVSTATE:	
            switch (m_dwParam1)
            {
            	case LINEDEVSTATE_REINIT:
					TapiStatus("重新初始化线路..." );
            		break;
            	case LINEDEVSTATE_RINGING:
					TapiStatus("振铃..." );
            		break;
            } 
			break; 

        case LINE_CALLSTATE:	
            HandleCallState();
            break;
       
		case LINE_CLOSE: 
			{
			TapiStatus("线路已关闭..." );

			break; 
			}
		case LINE_REPLY:	
		{
			TapiStatus("线路有回应..." );
			::PostMessage(m_hWnd, 
						WM_TAPI_LINE_REPLY, 
						m_dwParam2,  
						(LPARAM)(HCALL)m_dwDevice );
            break;
		}
        case LINE_REQUEST:
        case LINE_ADDRESSSTATE:
            break;
        case LINE_CALLINFO:
            break;
        case LINE_DEVSPECIFIC:
            break;
        case LINE_DEVSPECIFICFEATURE:
            break;
        case LINE_GATHERDIGITS:
            break;
        case LINE_GENERATE:
            break;
        case LINE_MONITORDIGITS:
            break;
        case LINE_MONITORMEDIA:
            break;
        case LINE_MONITORTONE:
            break;
        } /* switch */ 
        
} /* TapiCallBack() */

//********************************
//****处理呼叫状态的函数****
//********************************
void CTapi14::HandleCallState()
{
    if ((HCALL) m_dwDevice != m_hCall) {
		TapiStatus("无效的设备ID ...");
        return;
    }

	switch( m_dwParam1 )
	{
        case LINECALLSTATE_IDLE:
			{
			TapiStatus("线路空闲...");
			::SendMessage(m_hWnd, WM_TAPI_IDLE, 0, 0); 
			HangupCall();
			break;
			}													     
		case LINECALLSTATE_ACCEPTED:	
			{
			SetVarProps( (HWND)m_dwCallbackInstance, m_dwDevice );
			::PostMessage( m_hWnd,
						WM_TAPI_CALL_ACCEPTED, 
						0, 
						(LPARAM)(HCALL)m_dwDevice );
		 	break;
			}
		case LINECALLSTATE_PROCEEDING:	
			{
			SetVarProps( (HWND)m_dwCallbackInstance, m_dwDevice );
			::PostMessage( m_hWnd, 
						WM_TAPI_CALL_PROCEEDING, 
						0, 
						(LPARAM)(HCALL)m_dwDevice );
			break;
			}
		case LINECALLSTATE_CONNECTED:	
			{
				LineStateConnected();
				break;
			}
		case LINECALLSTATE_OFFERING:	
			{
			TapiStatus("线路已提供...");
			break;
			}
		case LINECALLSTATE_DIALTONE:
			{
			TapiStatus("拨号音...");
            break;
			}
        case LINECALLSTATE_DIALING:		
			{
			TapiStatus("正在拨号...");
			::SendMessage(m_hWnd, WM_TAPI_DIALING, 0, 0); 
            break;
			}
        case LINECALLSTATE_BUSY:
			{
			TapiStatus("线路忙，挂机...");
            HangupCall();
            break;
			}
        case LINECALLSTATE_SPECIALINFO:
			{
			TapiStatus("特殊的信息,可能无法拨号...");
            HangupCall();
            break;
			}
        case LINECALLSTATE_DISCONNECTED:
        {
            LPSTR pszReasonDisconnected;

            switch (m_dwParam2)
            {
                case LINEDISCONNECTMODE_NORMAL:
                    pszReasonDisconnected = "远端断线";
					::SendMessage(m_hWnd, WM_TAPI_DISCONNECT, 0, 0); 
                    break;
                case LINEDISCONNECTMODE_UNKNOWN:
                    pszReasonDisconnected = "连接解除:未知原因";
                    break;

                case LINEDISCONNECTMODE_REJECT:
                    pszReasonDisconnected = "远端退出通话";
                    break;

                case LINEDISCONNECTMODE_PICKUP:
                    pszReasonDisconnected = 
                        "连接解除: 本地电话摘机";
                    break;

                case LINEDISCONNECTMODE_FORWARDED:
                    pszReasonDisconnected = "连接解除: Forwarded";
                    break;

                case LINEDISCONNECTMODE_BUSY:
                    pszReasonDisconnected = "连接解除: 线路忙";
                    break;

                case LINEDISCONNECTMODE_NOANSWER:
                    pszReasonDisconnected = "连接解除:无应答";
                    break;

                case LINEDISCONNECTMODE_BADADDRESS:
                    pszReasonDisconnected = "连接解除: 地址无效";
                    break;

                case LINEDISCONNECTMODE_UNREACHABLE:
                    pszReasonDisconnected = "连接解除: 不可到达";
                    break;

                case LINEDISCONNECTMODE_CONGESTION:
                    pszReasonDisconnected = "连接解除: 堵塞";
                    break;

                case LINEDISCONNECTMODE_INCOMPATIBLE:
                    pszReasonDisconnected = "连接解除: 不兼容";
                    break;

                case LINEDISCONNECTMODE_UNAVAIL:
                    pszReasonDisconnected = "连接解除: 不再有效";
                    break;

                case LINEDISCONNECTMODE_NODIALTONE:
                    pszReasonDisconnected = "连接解除:无拨号音";
                    break;

                default:
                    pszReasonDisconnected = 
                        "连接解除: LINECALLSTATE; Bad Reason";
                    break;

            }
			TapiStatus(pszReasonDisconnected);
            HangupCall();
            break;
        }
	}	/* switch */ 
}

LONG CTapi14::LineStateConnected()
{
	TapiStatus("Hey I am connected!");
	//
	// 本地变量的处理
	LPVARSTRING lpVarStringStruct = NULL;
	size_t sizeofVarStringStruct = sizeof( VARSTRING ) + 1024;

	long lreturn;
	lpVarStringStruct = ( LPVARSTRING )LocalAlloc( 0, sizeofVarStringStruct );
	do
	{
		memset( lpVarStringStruct, 0, sizeofVarStringStruct );
		lpVarStringStruct->dwTotalSize = (DWORD)sizeofVarStringStruct;
		lreturn = lineGetID(0, 
							0, 
							(HCALL)m_dwDevice, 
							LINECALLSELECT_CALL, 
							lpVarStringStruct, 
							"comm/datamodem" );
	} while( lreturn != 0 );
	//
	// 获取comm句柄并将其存入属性区
	m_hComm = *((LPHANDLE )( ( LPBYTE )lpVarStringStruct + lpVarStringStruct->dwStringOffset ) );
	SetProp( (HWND)m_dwCallbackInstance, "HCOMM", m_hComm );
	SetVarProps( (HWND)m_dwCallbackInstance, m_dwDevice );

	::SendMessage(m_hWnd,
				WM_TAPI_CONNECT, 
				TAPI_LINECALLSTATE_CONNECTED, 
				(LPARAM)(HANDLE)m_hComm );
	LocalFree( lpVarStringStruct ); 

	return lreturn;
}

//
//  挂机函数
//
LONG CTapi14::HangupCall()
{         

	LONG retcode = 0;		

	TapiStatus("正在停止通话...");	

	m_hCall = (HCALL)GetProp( m_hWnd, "HCALL" );
	m_hComm = (HANDLE)GetProp( m_hWnd, "HCOMM" );

	if( m_hComm != NULL )
	{
		CloseHandle( m_hComm );
		SetProp( m_hWnd, "HCALL", NULL );
	}

	if( m_hCall != NULL )
	{
		retcode = lineDrop( m_hCall, 
							NULL, 
							0 );
		TapiStatus("电话已经挂机...");
		SetProp( m_hWnd, "HCALL", NULL );
	}

	LINECALLINFO LineCallInfo;
	//
	// 装载呼叫信息到结构中
	memset( &LineCallInfo, 0, sizeof( LINECALLINFO ) );
	LineCallInfo.dwTotalSize = sizeof( LINECALLINFO );
	lineGetCallInfo( (HCALL)m_dwDevice, &LineCallInfo );
	//
	// 收回电话资源
	retcode = lineDeallocateCall( (HCALL)m_dwDevice );
	TapiStatus("收回电话资源...");
	//
	// 电话空闲,清除
	m_hLine = (HLINE)GetProp( m_hWnd, "HLINE" ); 
	//
	// 关闭活动的线路
	if( m_hLine != NULL )
	{
		retcode = lineClose( m_hLine );
		TapiStatus("线路已关闭...");
		SetProp( m_hWnd, "HLINE", (HANDLE)NULL );
	}
	TapiStatus("呼叫已停止...");
    return retcode;
}

//****************************************************
//****通过LINECALLINFO结构设置线路句柄****
//***************************************************
void CTapi14::SetVarProps(HWND hWnd, DWORD hDevice )
{
	LINECALLINFO LineCallInfo;

	memset( &LineCallInfo, 0, sizeof( LINECALLINFO ) );
	SetProp( hWnd, "HCALL", (HANDLE)(HCALL)hDevice );
	LineCallInfo.dwTotalSize = sizeof( LINECALLINFO );
	lineGetCallInfo( (HCALL)hDevice, &LineCallInfo );
 	SetProp(m_hWnd, "HLINE", (HANDLE)(HLINE)LineCallInfo.hLine );
	return;
}

//****************************************************
//****通信状态显示函数***
//***************************************************

void CTapi14::TapiStatus(LPSTR lpszError, BOOL bShowMsgBox)
{
	strcpy(m_szMessage, lpszError);
	strStatus=m_szMessage;
	::SendMessage(m_hWnd, WM_TAPI_STATUS, 0, 0); 
	
	Delay(400);

	//想以对话框形式显示. 
	if(bShowMsgBox)
		AfxMessageBox(m_szMessage);
	
	// 输出到调试窗口
	OutputDebugString(m_szMessage);
	OutputDebugString("\n");
}

void CTapi14::Delay(UINT lFactor)
{
	MSG msg;
	DWORD dwTimeStarted;
	dwTimeStarted = GetTickCount();

	//取得消息循环的控制
    while(GetTickCount() - dwTimeStarted < lFactor)
	{ 
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
	}
}
