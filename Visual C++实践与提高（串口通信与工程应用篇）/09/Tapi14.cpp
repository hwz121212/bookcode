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
CString strStatus;                         //�����������ڴ�����ʾ��Ϣ

/////////////////////////////////////////////////////////////////////////////
// CTapi14

CTapi14::CTapi14()
{
	MyThis = this;                        //ʹMyThisָ��ǰ����ʵ��
	m_LineHandle = NULL;                  //��·�����ʼ��ΪNULL
}

void CTapi14::Create(HWND& hWnd)
{
	m_hWnd = hWnd;                //������Ĵ��ھ��
	m_hInst =(HINSTANCE)::GetWindowLong(m_hWnd, GWL_HINSTANCE);

	//��һЩ��Ҫ����������ΪNULL
	SetProp( m_hWnd, "HCALL", NULL );
	SetProp( m_hWnd, "HLINE", NULL );
	SetProp( m_hWnd, "HCOMM", NULL );
}


CTapi14::~CTapi14()
{
	//������������ֵ
	RemoveProp( m_hWnd, "HCALL" );
	RemoveProp( m_hWnd, "HLINE" );
	RemoveProp( m_hWnd, "HCOMM" );
}

//***********************************************
// ���к���
//***********************************************
LONG CTapi14::DialCall(CString  PhoneNumber )
{
	LONG	retcode =  0;			
	DWORD	i;						
	DWORD	RetApiVersion;			
	LINEEXTENSIONID	ExtensionID;	

	//���绰�����Ƿ�Ϊ��
	if( lstrlen( PhoneNumber ) < 1 )
		return( ERRORS );	

	//��ʼ����·����ע��ص�����
	if( m_LineHandle == NULL ) {
		retcode = ::lineInitialize( 
							&m_LineHandle,
							m_hInst, 
							(LINECALLBACK)lineCallbackFunc, 
							"FELIX TAPI", 
							&m_dwLines );
		if( retcode < 0 )  {
			TapiStatus("Tapi����..." );
			return (retcode);
		}
		else
			TapiStatus("Tapi��ʼ�����..." );
	}
	//
	// ����API��·
	// ��������ȷ�����ԣ�����������������ִ�� 
	//
	m_hLine = (HLINE)GetProp( m_hWnd, "HLINE" );
	if( m_hLine == NULL )
	{
		for( i=0; i < m_dwLines; i++ )
		{
			// ��ÿ����·Э��TAPI�汾
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
	// �ҵ����õ���·
	SetProp( m_hWnd, "HLINE",(HANDLE)(HLINE)m_hLine );

	//
	// ������·���ԣ��Ա㲦������
	memset( &m_LineParams, 0, sizeof( LINECALLPARAMS ) );
	m_LineParams.dwTotalSize = sizeof( LINECALLPARAMS );
	m_LineParams.dwMinRate = 9600;	
	m_LineParams.dwMaxRate = 28800;	
    m_LineParams.dwBearerMode = LINEBEARERMODE_VOICE; 
	m_LineParams.dwMediaMode  = LINEMEDIAMODE_DATAMODEM;
	//
	// ��󣬺��е绰!
	retcode = ::lineMakeCall( m_hLine, 
					&m_hCall, 
					PhoneNumber,
					0, 
					&m_LineParams );
	if( retcode < 0 ) 
			return (retcode);	
	else
		//�ȴ�5s����ʱ����Ը���ʵ����������趨
		Delay(5000);               
	return( retcode );	
}

//
//  �ص�����lineCallbackFunc(..)
//
//  �첽����TAPI���¼�
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
//���ûص���������
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
	
	//���þ��幦�ܵĻص�����
	TapiCallBack();		
}	

// *******************************************
// ����TAPI��Ϣ�Ļص�����
//
void CTapi14::TapiCallBack()
{   
	
    switch (m_dwMessage) 
        { 
        case LINE_LINEDEVSTATE:	
            switch (m_dwParam1)
            {
            	case LINEDEVSTATE_REINIT:
					TapiStatus("���³�ʼ����·..." );
            		break;
            	case LINEDEVSTATE_RINGING:
					TapiStatus("����..." );
            		break;
            } 
			break; 

        case LINE_CALLSTATE:	
            HandleCallState();
            break;
       
		case LINE_CLOSE: 
			{
			TapiStatus("��·�ѹر�..." );

			break; 
			}
		case LINE_REPLY:	
		{
			TapiStatus("��·�л�Ӧ..." );
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
//****�������״̬�ĺ���****
//********************************
void CTapi14::HandleCallState()
{
    if ((HCALL) m_dwDevice != m_hCall) {
		TapiStatus("��Ч���豸ID ...");
        return;
    }

	switch( m_dwParam1 )
	{
        case LINECALLSTATE_IDLE:
			{
			TapiStatus("��·����...");
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
			TapiStatus("��·���ṩ...");
			break;
			}
		case LINECALLSTATE_DIALTONE:
			{
			TapiStatus("������...");
            break;
			}
        case LINECALLSTATE_DIALING:		
			{
			TapiStatus("���ڲ���...");
			::SendMessage(m_hWnd, WM_TAPI_DIALING, 0, 0); 
            break;
			}
        case LINECALLSTATE_BUSY:
			{
			TapiStatus("��·æ���һ�...");
            HangupCall();
            break;
			}
        case LINECALLSTATE_SPECIALINFO:
			{
			TapiStatus("�������Ϣ,�����޷�����...");
            HangupCall();
            break;
			}
        case LINECALLSTATE_DISCONNECTED:
        {
            LPSTR pszReasonDisconnected;

            switch (m_dwParam2)
            {
                case LINEDISCONNECTMODE_NORMAL:
                    pszReasonDisconnected = "Զ�˶���";
					::SendMessage(m_hWnd, WM_TAPI_DISCONNECT, 0, 0); 
                    break;
                case LINEDISCONNECTMODE_UNKNOWN:
                    pszReasonDisconnected = "���ӽ��:δ֪ԭ��";
                    break;

                case LINEDISCONNECTMODE_REJECT:
                    pszReasonDisconnected = "Զ���˳�ͨ��";
                    break;

                case LINEDISCONNECTMODE_PICKUP:
                    pszReasonDisconnected = 
                        "���ӽ��: ���ص绰ժ��";
                    break;

                case LINEDISCONNECTMODE_FORWARDED:
                    pszReasonDisconnected = "���ӽ��: Forwarded";
                    break;

                case LINEDISCONNECTMODE_BUSY:
                    pszReasonDisconnected = "���ӽ��: ��·æ";
                    break;

                case LINEDISCONNECTMODE_NOANSWER:
                    pszReasonDisconnected = "���ӽ��:��Ӧ��";
                    break;

                case LINEDISCONNECTMODE_BADADDRESS:
                    pszReasonDisconnected = "���ӽ��: ��ַ��Ч";
                    break;

                case LINEDISCONNECTMODE_UNREACHABLE:
                    pszReasonDisconnected = "���ӽ��: ���ɵ���";
                    break;

                case LINEDISCONNECTMODE_CONGESTION:
                    pszReasonDisconnected = "���ӽ��: ����";
                    break;

                case LINEDISCONNECTMODE_INCOMPATIBLE:
                    pszReasonDisconnected = "���ӽ��: ������";
                    break;

                case LINEDISCONNECTMODE_UNAVAIL:
                    pszReasonDisconnected = "���ӽ��: ������Ч";
                    break;

                case LINEDISCONNECTMODE_NODIALTONE:
                    pszReasonDisconnected = "���ӽ��:�޲�����";
                    break;

                default:
                    pszReasonDisconnected = 
                        "���ӽ��: LINECALLSTATE; Bad Reason";
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
	// ���ر����Ĵ���
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
	// ��ȡcomm������������������
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
//  �һ�����
//
LONG CTapi14::HangupCall()
{         

	LONG retcode = 0;		

	TapiStatus("����ֹͣͨ��...");	

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
		TapiStatus("�绰�Ѿ��һ�...");
		SetProp( m_hWnd, "HCALL", NULL );
	}

	LINECALLINFO LineCallInfo;
	//
	// װ�غ�����Ϣ���ṹ��
	memset( &LineCallInfo, 0, sizeof( LINECALLINFO ) );
	LineCallInfo.dwTotalSize = sizeof( LINECALLINFO );
	lineGetCallInfo( (HCALL)m_dwDevice, &LineCallInfo );
	//
	// �ջص绰��Դ
	retcode = lineDeallocateCall( (HCALL)m_dwDevice );
	TapiStatus("�ջص绰��Դ...");
	//
	// �绰����,���
	m_hLine = (HLINE)GetProp( m_hWnd, "HLINE" ); 
	//
	// �رջ����·
	if( m_hLine != NULL )
	{
		retcode = lineClose( m_hLine );
		TapiStatus("��·�ѹر�...");
		SetProp( m_hWnd, "HLINE", (HANDLE)NULL );
	}
	TapiStatus("������ֹͣ...");
    return retcode;
}

//****************************************************
//****ͨ��LINECALLINFO�ṹ������·���****
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
//****ͨ��״̬��ʾ����***
//***************************************************

void CTapi14::TapiStatus(LPSTR lpszError, BOOL bShowMsgBox)
{
	strcpy(m_szMessage, lpszError);
	strStatus=m_szMessage;
	::SendMessage(m_hWnd, WM_TAPI_STATUS, 0, 0); 
	
	Delay(400);

	//���ԶԻ�����ʽ��ʾ. 
	if(bShowMsgBox)
		AfxMessageBox(m_szMessage);
	
	// ��������Դ���
	OutputDebugString(m_szMessage);
	OutputDebugString("\n");
}

void CTapi14::Delay(UINT lFactor)
{
	MSG msg;
	DWORD dwTimeStarted;
	dwTimeStarted = GetTickCount();

	//ȡ����Ϣѭ���Ŀ���
    while(GetTickCount() - dwTimeStarted < lFactor)
	{ 
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
	}
}
