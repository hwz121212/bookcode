// FaxMachineDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FaxMachine.h"
#include "FaxMachineDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define		TAPI_MAX_VERSION 0x0FFF0FFF
#define		MAX_ENUM_COUNT		6
#define		SRL_KEY       1
#define		DM3_IPT_KEY   2
#define		END_KEY       3
#define		USEREVT_KEY   4
#define		SUCCESS		  0

bool		bSendNotRcv=true;
time_t		g_tInitTime;
DWORD		g_dwNumDevs;
DWORD		g_dwTAPIVer= 0x00020000;
LINEINITIALIZEEXPARAMS lineInitializeExParams;
//HANDLE		hIOCP;            
HLINEAPP	g_hLineApp = NULL;
BOOL		g_bShuttingDown = FALSE;
BOOL		g_bStoppingCall = FALSE;
BOOL		g_bInitializing = FALSE;
BOOL		g_bTapiInUse = FALSE;
HCALL		g_hCall = NULL;
HLINE		g_hLine = NULL;
BOOL		g_bConnected = FALSE;
DWORD		dwAPIVersion;

BOOL		InitializeTAPI(DWORD dwDeviceID);
BOOL		ShutdownTAPI();
//LPTSTR		FormatTapiError (long lError);
VOID FAR PASCAL  lineCallbackFuncSend(DWORD dwDevice,
									  DWORD dwMsg,
									  DWORD dwCallbackInstance, 
									  DWORD dwParam1,
									  DWORD dwParam2, 
									  DWORD dwParam3);
VOID FAR PASCAL  lineCallbackFuncRcv(DWORD dwDevice, 
									 DWORD dwMsg, 
									 DWORD dwCallbackInstance, 
									 DWORD dwParam1, 
									 DWORD dwParam2, 
									 DWORD dwParam3);
EFaxSpeed	GetSelSpeed(int Index);
EVolume		GetFaxVolume(int Index);

CFaxMachineDlg *g_FaxDialog = NULL;
/////////////////////////////////////////////////////////////////////////////
// CFaxMachineDlg dialog

CFaxMachineDlg::CFaxMachineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFaxMachineDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFaxMachineDlg)
	m_Phone = _T("01012345678");
	m_Volume = 0;
	m_To = _T("B");
	m_Identity = _T("1234567890");
	m_Time = _T("");
	m_From = _T("A");
	m_Page = _T("0");
	m_Status = _T("");
	m_File = _T("c:\\file.tif");
	m_Ecm = TRUE;
	m_Compress = TRUE;
	m_CallerNo = _T("");
	m_AutoReply = FALSE;
	m_ActualSpeed = _T("");
	m_PortType = 0;
	m_FaxSpeed = 0;
	m_FaxProtocol = 0;
	m_FaxHead = TRUE;
	m_HighResolution = 0;
	m_RadioSend = 0;
	m_Remote = _T("");
	m_Data = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFaxMachineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFaxMachineDlg)
	DDX_Control(pDX, IDC_SENDFAX, m_SendFax);
	DDX_Control(pDX, IDC_RECEIVEFAX, m_ReceiveFax);
	DDX_Control(pDX, IDC_EXIT, m_Exit);
	DDX_Control(pDX, IDC_ABORT, m_Abort);
	DDX_Control(pDX, IDC_COMBO_MODEMLIST, m_ModemList);
	DDX_Text(pDX, IDC_PHONE, m_Phone);
	DDX_Slider(pDX, IDC_VOLUME, m_Volume);
	DDX_Text(pDX, IDC_TO, m_To);
	DDX_Text(pDX, IDC_IDENTITY, m_Identity);
	DDX_Text(pDX, IDC_TIME, m_Time);
	DDX_Text(pDX, IDC_FROM, m_From);
	DDX_Text(pDX, IDC_PAGE, m_Page);
	DDX_Text(pDX, IDC_STATUS, m_Status);
	DDX_Text(pDX, IDC_FILE, m_File);
	DDX_Check(pDX, IDC_ECM, m_Ecm);
	DDX_Check(pDX, IDC_COMPRESS, m_Compress);
	DDX_Text(pDX, IDC_CALLERNO, m_CallerNo);
	DDX_Check(pDX, IDC_AUTOREPLY, m_AutoReply);
	DDX_Text(pDX, IDC_ACTUALSPEED, m_ActualSpeed);
	DDX_CBIndex(pDX, IDC_PORTTYPE, m_PortType);
	DDX_CBIndex(pDX, IDC_FAXSPEED, m_FaxSpeed);
	DDX_CBIndex(pDX, IDC_FAXPROTOCOL, m_FaxProtocol);
	DDX_Check(pDX, IDC_FAXHEAD, m_FaxHead);
	DDX_Radio(pDX, IDC_HIGH, m_HighResolution);
	DDX_Radio(pDX, IDC_RADIO_SEND, m_RadioSend);
	DDX_Text(pDX, IDC_REMOTE, m_Remote);
	DDX_Text(pDX, IDC_DATA, m_Data);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFaxMachineDlg, CDialog)
	//{{AFX_MSG_MAP(CFaxMachineDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SENDFAX, OnSendfax)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDC_RADIO_SEND, OnRadioSend)
	ON_BN_CLICKED(IDC_RADIO_RCV, OnRadioRcv)
	ON_BN_CLICKED(IDC_ABORT, OnAbort)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_FAXHEAD, OnFaxhead)
	ON_BN_CLICKED(IDC_RECEIVEFAX, OnReceivefax)
	ON_BN_CLICKED(IDC_AUTOREPLY, OnAutoreply)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_SMARTFAX, OnSmartFax)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFaxMachineDlg message handlers

BOOL CFaxMachineDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CWnd* myWnd;
	CSliderCtrl	*slider  = (CSliderCtrl	*)GetDlgItem(IDC_VOLUME);
	slider->SetRange(0,3);

	m_Volume = 1;
	this->UpdateData(false);
	GetModemDeviceList((unsigned long )&m_ModemList,FillComboBox);


	m_ModemList.SetCurSel(0);		
	bSendNotRcv=true;
	g_FaxDialog = this;
	m_HighResolution=0;
	m_RadioSend=0;
	m_bEcmFlag=false;
	UpdateData(false);
	m_ReceiveFax.EnableWindow(false);
	myWnd=this->GetDlgItem(IDC_STATIC_CALLERNO);
	myWnd->EnableWindow(false);
	myWnd=this->GetDlgItem(IDC_AUTOREPLY);
	myWnd->EnableWindow(false);
	g_hCall = 0;
	g_hLine = 0 ;

	m_bFaxing = false ;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFaxMachineDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFaxMachineDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFaxMachineDlg::FillComboBox(DWORD dwDevice, const char *sLineName, const char *ComPort, unsigned long lParam)
{

	CComboBox *ModemList = (CComboBox *)lParam;
	int index = ModemList->AddString(sLineName);
	ModemList->SetItemData(index,dwDevice);	

}

int CFaxMachineDlg::TapiSendFax()
{

 
	this->UpdateData();

	//DWORD CurrentProcess = GetPriorityClass(GetCurrentProcess());


	SFaxParam *Sender =(SFaxParam *) new SFaxParam; 
	Sender->hFax = &g_hFax;

	Sender->hCall = g_hCall;
	Sender->hLine = g_hLine;


	
	strcpy(Sender->FileName,GetFullPath(m_File));
	strcpy(Sender->FaxNumber,m_Phone) ;

	Sender->Hwnd = this->GetSafeHwnd();
	Sender->Msg = WM_SMARTFAX;
	Sender->nComPort = m_PortType;
	
	Sender->Speed = GetSelSpeed(m_FaxSpeed);
	Sender->Is2D = m_Compress == TRUE ? U2D_ENABLE : U2D_DISABLE ;
	Sender->CreateHead = m_FaxHead == TRUE ? CH_ENABLE : CH_DISABLE;
	Sender->Class = m_FaxProtocol == 0 ? CLASS_1 : CLASS_2  ;
	strcpy(Sender->Identifi,m_Identity);
	Sender->Ecm = m_Ecm == TRUE ? ECM_ENABLE : ECM_DISABLE ;
	Sender->Volume =GetFaxVolume(m_Volume) ;

	strcpy(Sender->From,m_From);
	strcpy(Sender->To,m_To);

	Sender->Resolution = m_HighResolution == 0 ?  RE_FINE : RE_STANDARD ;
	Sender->nStartPage = 1 ;

	TapiSmartSendFax(Sender);
	delete Sender;
	
	return 0;
}
CString CFaxMachineDlg::GetFullPath(CString FileName)
{	
	int nPos = FileName.Find(':');
	if(nPos ==-1)
	{
		return GetWorkPath()+FileName;
	}
	return FileName;
}
CString CFaxMachineDlg::GetWorkPath()
{
	char szPath[512];
	CString strTemp;
	int nPos;
	CString strWorkPath = _T( "" );
	
	GetModuleFileName( NULL , szPath , 512 );
	strTemp = szPath;
	nPos = strTemp.Find( '\\' );
	while( nPos != -1 )
	{
		strWorkPath += strTemp.Left( nPos + 1 );
		strTemp = strTemp.Right( strlen( strTemp ) - nPos -1 );
		nPos = strTemp.Find( '\\' );
	}
	return strWorkPath;

}




EFaxSpeed GetSelSpeed(int Index)
{
	switch(Index)
	{
	case 0:
		return FS_1440;
	case 1:
		return FS_1200;
	case 2:
		return FS_9600;
	case 3:
		return FS_7200;
	case 4:
		return FS_4800;
	default:
		return FS_2400;
	}
}





EVolume GetFaxVolume(int Index)
{
	switch(Index)
	{
	case 0:
		return VO_OFF;
	case 1:
		return VO_LOW;
	case 2:
		return VO_MIDDLE;
	default :
		return VO_HIGH;	
	}
}


#define CHAN_DEBUG_PRINT TRACE
VOID FAR PASCAL  lineCallbackFuncSend(DWORD dwDevice, DWORD dwMsg, DWORD dwCallbackInstance, DWORD dwParam1, DWORD dwParam2, DWORD dwParam3)
{
	static int n_RingTimes = 0 ;
	if(g_tInitTime !=(time_t)dwCallbackInstance)
		return ;
	
	 switch(dwMsg)
    {
       
        case LINE_CALLSTATE:
        {
		
            switch(dwParam1)
            {
              
				case LINECALLSTATE_CONNECTED:
				{
    				
					if(g_FaxDialog&&IsWindow(g_FaxDialog->GetSafeHwnd()))
					{
						g_FaxDialog->TapiSendFax();
					}												
					break;
				}


                case LINECALLSTATE_DISCONNECTED:
                {
					lineDrop((HCALL) dwDevice, NULL, 0);				
					n_RingTimes = 0;
                    
 					break;
               }

            
            }

        }
           
    } 

}

VOID FAR PASCAL  lineCallbackFuncRcv(DWORD dwDevice, DWORD dwMsg, DWORD dwCallbackInstance, DWORD dwParam1, DWORD dwParam2, DWORD dwParam3)
{
	//TRACE(" get the dwDevice %d \n",dwDevice);	
	//TRACE(" get the dwMessageID %d \n",dwMsg);
	//TRACE(" get the dwCallbackInstance %d \n",dwCallbackInstance);
	//TRACE(" get the dwParam1 %d \n",dwParam1);
	//TRACE(" get the dwParam2 %d \n",dwParam2);
	//TRACE(" get the dwParam3 %d \n",dwParam3);
	//TRACE("----------------------------------------------\n");
	static int n_RingTimes = 0 ;
	if(g_tInitTime !=(time_t)dwCallbackInstance)
	{
		return ;
	}
	switch(dwMsg)
    {
        

    case LINE_CALLSTATE:
    {
        switch(dwParam1)
        {
           
			case LINECALLSTATE_IDLE:
			{

				CHAN_DEBUG_PRINT("get Tapi msg LINECALLSTATE_IDLE\n");				
				lineDeallocateCall((HCALL) dwDevice);
				n_RingTimes = 0;					

				if(g_FaxDialog && IsWindow(g_FaxDialog->GetSafeHwnd()))
				{
					g_FaxDialog->PostMessage(WM_SMARTFAX,WM_FAXMONITORSTART,0);
				}
					                 
				break;
			}


			case LINECALLSTATE_CONNECTED:
			{

				CHAN_DEBUG_PRINT("get Tapi msg LINECALLSTATE_CONNECTED\n");
				
				if(g_FaxDialog&&IsWindow(g_FaxDialog->GetSafeHwnd()))
				{
					g_FaxDialog->RecvFaxInTapi();							
				}												
				break;
			}


            case LINECALLSTATE_DISCONNECTED:
            {
				CHAN_DEBUG_PRINT("get Tapi msg LINECALLSTATE_DISCONNECTED\n");
				lineDrop((HCALL) dwDevice, NULL, 0);				
				n_RingTimes = 0;
                
				break;
            }

            case LINECALLSTATE_CONFERENCED:
            {

				CHAN_DEBUG_PRINT("get Tapi msg LINECALLSTATE_CONFERENCED\n");	
				n_RingTimes = 0;
                
				break;						 
            }
			case LINECALLSTATE_OFFERING:			
			{										
				g_hCall  =  (HCALL) dwDevice;						
				CHAN_DEBUG_PRINT("get Tapi msg LINECALLSTATE_OFFERING -------------------\n");
				n_RingTimes = 0;
				
				break;
			}

			case LINECALLSTATE_ACCEPTED:
			{
					CHAN_DEBUG_PRINT("get Tapi msg LINECALLSTATE_ACCEPTED\n");
					g_hCall  =  (HCALL) dwDevice;					
				
				break;
			}

        }

        break;
    }

    case LINE_CLOSE:
		{
			CHAN_DEBUG_PRINT("get Tapi msg LINE_CLOSE\n");
			n_RingTimes = 0;
			break;
		}

    case LINE_LINEDEVSTATE:
		{
        
			switch(dwParam1)
			{

			case LINECALLSTATE_IDLE:
				{
					CHAN_DEBUG_PRINT("get Tapi msg LINECALLSTATE_IDLE ..........\n ");				
					n_RingTimes = 0;
					break;
				}
			

			case LINEDEVSTATE_RINGING:
				{
					CHAN_DEBUG_PRINT("get Tapi msg LINEDEVSTATE_RINGING\n");				
			
					if(g_FaxDialog&&IsWindow(g_FaxDialog->GetSafeHwnd()))
					{
						g_FaxDialog->PostMessage(WM_SMARTFAX,WM_FAXRING,n_RingTimes++);
					}
					break;                
			
				}
			}

        break;
		}      

    } // End switch(dwMsg)
	
}

BOOL InitializeTAPI(DWORD dwDeviceID)
{


	long lReturn;
    BOOL bTryReInit = TRUE;
	HINSTANCE hInstance;
    //若初始化成功
    if (g_hLineApp)
	{
        return TRUE;
	}


	if(g_bTapiInUse)
	{
		return TRUE;
	}

    //若正在初始化，则失败返回
    if (g_bInitializing)
	{
        return FALSE;
	}

    g_bInitializing = TRUE;

	hInstance = GetModuleHandle(NULL);
	LPLINEDEVCAPS lpDevCaps = NULL;


	 //初始化TAPI
    do
    {
			

#if		TAPI_CURRENT_VERSION >= 0x00020000
		
		memset(&lineInitializeExParams, 0, sizeof(LINEINITIALIZEEXPARAMS));
		lineInitializeExParams.dwTotalSize = sizeof(LINEINITIALIZEEXPARAMS);
		lineInitializeExParams.dwOptions = LINEINITIALIZEEXOPTION_USEHIDDENWINDOW;
				
		dwAPIVersion = TAPI_CURRENT_VERSION;
		if(bSendNotRcv)
		{
			lReturn = lineInitializeEx(&g_hLineApp, 
								hInstance, 
								lineCallbackFuncSend, 
								"SmartFaxSample",
								&g_dwNumDevs, 
								&dwAPIVersion, 
								&lineInitializeExParams);

		}
		else
		{
			lReturn = lineInitializeEx(&g_hLineApp, 
								hInstance, 
								lineCallbackFuncRcv, 
								"SmartFaxSample", 
								&g_dwNumDevs, 
								&dwAPIVersion, 
								&lineInitializeExParams);

		}
#else
		//不支持UNICODE
		if(bSendNotRcv)
		{
			 lReturn = lineInitialize(&g_hLineApp, 
								 hInstance, 
								 lineCallbackFuncSend, 
								 "SmartFaxSample", 
								 &g_dwNumDevs);

		}
		else
		{
			 lReturn = lineInitialize(&g_hLineApp,
								 hInstance, 
								 lineCallbackFuncRcv, 
								 "SmartFaxSample", 
								 &g_dwNumDevs);

		}
#endif
		
		
				

        //其它程序已经响应了REINIT消息，等5s后重试。
        //若仍旧，则提示使用者。
        if (lReturn == LINEERR_REINIT)
        {
            if (bTryReInit)
            {
                MSG msg; 
                DWORD dwTimeStarted;

                dwTimeStarted = GetTickCount();

                while(GetTickCount() - dwTimeStarted < 5000)
                {
                    if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
                    {
                        TranslateMessage(&msg);
                        DispatchMessage(&msg);
                    }
                }
            
                bTryReInit = FALSE;
                continue;
            }
            else
            {
                AfxMessageBox("初始化失败！");

                g_bInitializing = FALSE;
                return FALSE;
            }
        }

        if (lReturn == LINEERR_NODEVICE)
        {
          
			AfxMessageBox("没有找到设备！\n");
            g_bInitializing = FALSE;
            return FALSE;            
        }
        else if(lReturn != SUCCESS)
        {
            AfxMessageBox("线路初始化错误: ");
            g_bInitializing = FALSE;
            return FALSE;
        }

    } while(lReturn != SUCCESS);


	LINEEXTENSIONID LineExtensionID;

   if (lReturn = lineNegotiateAPIVersion(g_hLineApp, 
						  dwDeviceID, 
						  0x00010004, 
						  TAPI_MAX_VERSION, 
						  &dwAPIVersion, 
						  &LineExtensionID))
   {
	  g_bInitializing = FALSE;
      return FALSE;
   }



   lpDevCaps = (LINEDEVCAPS *)malloc(sizeof(LINEDEVCAPS)+1000);
   if(!lpDevCaps)
   {
		TRACE("Out of memory \n");
		g_bInitializing = FALSE;
		return FALSE;
   }

   memset(lpDevCaps, 0, sizeof(LINEDEVCAPS)+1000);
   lpDevCaps->dwTotalSize = sizeof(LINEDEVCAPS)+1000;

   
   if( (lReturn = lineGetDevCaps(g_hLineApp, 
					   dwDeviceID, 
					   dwAPIVersion,
					   0,
					   lpDevCaps))  != SUCCESS)
   {
		free(lpDevCaps);
		g_bInitializing = FALSE;
    	return FALSE;   
   }
   
   
   if (!(lpDevCaps->dwMediaModes & LINEMEDIAMODE_DATAMODEM))
   {
	   free(lpDevCaps);
	   g_bInitializing = FALSE;
	   return FALSE;   
   }
   
    free(lpDevCaps);
  
   
	g_tInitTime = time(NULL);
	if (lReturn = lineOpen(g_hLineApp, 
							dwDeviceID, 
							&g_hLine, 
							dwAPIVersion, 
							0, 
							g_tInitTime,
							LINECALLPRIVILEGE_OWNER,
							LINEMEDIAMODE_DATAMODEM, 
							NULL))
	{
		if(0x80000048)
		{
			AfxMessageBox("TAPI Modem无法使用！");
		}
		
		g_bInitializing = FALSE;
		return FALSE;
	}


   if( (lReturn = lineSetStatusMessages(g_hLine, 
									   0x1ffffff, 
									   0) ) )
   {
	   g_bInitializing = FALSE;
	   return FALSE;
   }

    g_bInitializing = FALSE;
	g_bTapiInUse = TRUE;
	return TRUE;
}



//
//  FUNCTION: BOOL ShutdownTAPI()
//
//  PURPOSE: Shuts down all use of TAPI
//
//  PARAMETERS:
//    None
//
//  RETURN VALUE:
//    True if TAPI successfully shut down.
//
//  COMMENTS:
//
//    If ShutdownTAPI fails, then its likely either a problem
//    with the service provider (and might require a system
//    reboot to correct) or the application ran out of memory.
//
//

BOOL ShutdownTAPI()
{
    long lReturn;

    if (g_hLineApp == NULL)
        return TRUE;

    if (g_bShuttingDown)
        return TRUE;

    g_bShuttingDown = TRUE;

	lineDrop(g_hCall, NULL, 0);
	lineDeallocateCall(g_hCall);
	lineClose(g_hLine);

    
    do
    {
        lReturn = lineShutdown(g_hLineApp);
      
    } while(lReturn != SUCCESS);

    g_bTapiInUse = FALSE;
    g_bConnected = FALSE;
    g_hLineApp = NULL;
    g_hCall = NULL;
    g_hLine = NULL;
    g_bShuttingDown = FALSE;
    return TRUE;
}





//将TAPI线路错误信息转换为字符串
/*LPTSTR FormatTapiError (long lError)
{
   static LPTSTR pszLineError[] = 
   {
     TEXT("LINEERR No Error"),
     TEXT("LINEERR_ALLOCATED"),
     TEXT("LINEERR_BADDEVICEID"),
     TEXT("LINEERR_BEARERMODEUNAVAIL"),
     TEXT("LINEERR Unused constant, ERROR!!"),
     TEXT("LINEERR_CALLUNAVAIL"),
     TEXT("LINEERR_COMPLETIONOVERRUN"),
     TEXT("LINEERR_CONFERENCEFULL"),
     TEXT("LINEERR_DIALBILLING"),
     TEXT("LINEERR_DIALDIALTONE"),
     TEXT("LINEERR_DIALPROMPT"),
     TEXT("LINEERR_DIALQUIET"),
     TEXT("LINEERR_INCOMPATIBLEAPIVERSION"),
     TEXT("LINEERR_INCOMPATIBLEEXTVERSION"),
     TEXT("LINEERR_INIFILECORRUPT"),
     TEXT("LINEERR_INUSE"),
     TEXT("LINEERR_INVALADDRESS"),
     TEXT("LINEERR_INVALADDRESSID"),
     TEXT("LINEERR_INVALADDRESSMODE"),
     TEXT("LINEERR_INVALADDRESSSTATE"),
     TEXT("LINEERR_INVALAPPHANDLE"),
     TEXT("LINEERR_INVALAPPNAME"),
     TEXT("LINEERR_INVALBEARERMODE"),
     TEXT("LINEERR_INVALCALLCOMPLMODE"),
     TEXT("LINEERR_INVALCALLHANDLE"),
     TEXT("LINEERR_INVALCALLPARAMS"),
     TEXT("LINEERR_INVALCALLPRIVILEGE"),
     TEXT("LINEERR_INVALCALLSELECT"),
     TEXT("LINEERR_INVALCALLSTATE"),
     TEXT("LINEERR_INVALCALLSTATELIST"),
     TEXT("LINEERR_INVALCARD"),
     TEXT("LINEERR_INVALCOMPLETIONID"),
     TEXT("LINEERR_INVALCONFCALLHANDLE"),
     TEXT("LINEERR_INVALCONSULTCALLHANDLE"),
     TEXT("LINEERR_INVALCOUNTRYCODE"),
     TEXT("LINEERR_INVALDEVICECLASS"),
     TEXT("LINEERR_INVALDEVICEHANDLE"),
     TEXT("LINEERR_INVALDIALPARAMS"),
     TEXT("LINEERR_INVALDIGITLIST"),
     TEXT("LINEERR_INVALDIGITMODE"),
     TEXT("LINEERR_INVALDIGITS"),
     TEXT("LINEERR_INVALEXTVERSION"),
     TEXT("LINEERR_INVALGROUPID"),
     TEXT("LINEERR_INVALLINEHANDLE"),
     TEXT("LINEERR_INVALLINESTATE"),
     TEXT("LINEERR_INVALLOCATION"),
     TEXT("LINEERR_INVALMEDIALIST"),
     TEXT("LINEERR_INVALMEDIAMODE"),
     TEXT("LINEERR_INVALMESSAGEID"),
     TEXT("LINEERR Unused constant, ERROR!!"),
     TEXT("LINEERR_INVALPARAM"),
     TEXT("LINEERR_INVALPARKID"),
     TEXT("LINEERR_INVALPARKMODE"),
     TEXT("LINEERR_INVALPOINTER"),
     TEXT("LINEERR_INVALPRIVSELECT"),
     TEXT("LINEERR_INVALRATE"),
     TEXT("LINEERR_INVALREQUESTMODE"),
     TEXT("LINEERR_INVALTERMINALID"),
     TEXT("LINEERR_INVALTERMINALMODE"),
     TEXT("LINEERR_INVALTIMEOUT"),
     TEXT("LINEERR_INVALTONE"),
     TEXT("LINEERR_INVALTONELIST"),
     TEXT("LINEERR_INVALTONEMODE"),
     TEXT("LINEERR_INVALTRANSFERMODE"),
     TEXT("LINEERR_LINEMAPPERFAILED"),
     TEXT("LINEERR_NOCONFERENCE"),
     TEXT("LINEERR_NODEVICE"),
     TEXT("LINEERR_NODRIVER"),
     TEXT("LINEERR_NOMEM"),
     TEXT("LINEERR_NOREQUEST"),
     TEXT("LINEERR_NOTOWNER"),
     TEXT("LINEERR_NOTREGISTERED"),
     TEXT("LINEERR_OPERATIONFAILED"),
     TEXT("LINEERR_OPERATIONUNAVAIL"),
     TEXT("LINEERR_RATEUNAVAIL"),
     TEXT("LINEERR_RESOURCEUNAVAIL"),
     TEXT("LINEERR_REQUESTOVERRUN"),
     TEXT("LINEERR_STRUCTURETOOSMALL"),
     TEXT("LINEERR_TARGETNOTFOUND"),
     TEXT("LINEERR_TARGETSELF"),
     TEXT("LINEERR_UNINITIALIZED"),
     TEXT("LINEERR_USERUSERINFOTOOBIG"),
     TEXT("LINEERR_REINIT"),
     TEXT("LINEERR_ADDRESSBLOCKED"),
     TEXT("LINEERR_BILLINGREJECTED"),
     TEXT("LINEERR_INVALFEATURE"),
     TEXT("LINEERR_NOMULTIPLEINSTANCE")
   };

   _declspec(thread) static TCHAR szError[512];
   DWORD dwError;
   HMODULE hTapiUIMod = GetModuleHandle(TEXT("TAPIUI.DLL"));

   if (hTapiUIMod)
   {
      dwError = FormatMessage(FORMAT_MESSAGE_FROM_HMODULE,
							(LPCVOID)hTapiUIMod, 
							TAPIERROR_FORMATMESSAGE(lError),
							0, 
							szError,
							sizeof(szError)/sizeof(TCHAR), 
							NULL);
      if (dwError)
         return szError;
   }

   //与调高位，使dwError是正值
   dwError = (DWORD)lError & 0x7FFFFFFF;

   if ((lError > 0) || (dwError > sizeof(pszLineError)/sizeof(pszLineError[0])))
   {
      wsprintf(szError, TEXT("Unknown TAPI error code: 0x%lx"), lError);
      return szError;
   }

   return pszLineError[dwError];
}*/

void CFaxMachineDlg::OnSendfax() 
{
	// TODO: Add your control notification handler code here
	m_Time="";
	m_ActualSpeed="";
	m_Page="0";
	this->UpdateData(false);

	if(m_PortType==0)                         //通过Tapi发送 
	{
		int nSel =  m_ModemList.GetCurSel();
		DWORD dwDevice = m_ModemList.GetItemData(nSel);
		
		if(dwDevice >=0 )
		{
			InitializeTAPI(dwDevice);
			InitFaxTapiCall(g_hLine,g_hCall);
		}
		
		
	}else                                    //通过Com端口发送
	{				
		ComPortSendFax();		
	}
	
}

int CFaxMachineDlg::ComPortSendFax()
{

	this->GetDlgItem(IDC_SENDFAX)->EnableWindow(false);
	this->GetDlgItem(IDC_EXIT)->EnableWindow(false);
	this->UpdateData();
	
	//声明SFaxParam型对象Sender
	SFaxParam *Sender =(SFaxParam *) new SFaxParam; 
	//初始化Sender
	Sender->hFax = &g_hFax;
	strcpy(Sender->FileName,m_File);
	strcpy(Sender->FaxNumber,m_Phone) ;
	Sender->Hwnd = this->GetSafeHwnd();
	Sender->Msg = WM_SMARTFAX;
	Sender->nComPort = m_PortType;
	Sender->Speed = GetSelSpeed(m_FaxSpeed);
	Sender->Is2D = m_Compress == TRUE ? U2D_ENABLE : U2D_DISABLE ;
	Sender->CreateHead = m_Ecm == TRUE ? CH_ENABLE : CH_DISABLE;
	Sender->Class = m_FaxProtocol == 0  ? CLASS_1 : CLASS_2  ;
	strcpy(Sender->Identifi,m_Identity);
	Sender->Ecm = m_Ecm == TRUE ? ECM_ENABLE : ECM_DISABLE ;
	Sender->Volume = GetFaxVolume(m_Volume) ;
	strcpy(Sender->From,m_From);
	strcpy(Sender->To,m_To);
	Sender->nStartPage = 1 ;
	Sender->Resolution = m_HighResolution == 0 ?  RE_FINE : RE_STANDARD ;

	//调用端口发送传真函数SmartSendFax
	int rc = SmartSendFax(Sender);
	//释放对象
	delete Sender;	

	return rc;
}

//*********************************************
//********** WM_SMARTFAX消息处理函数 *********
//*********************************************
void CFaxMachineDlg::OnSmartFax(WPARAM wParam, LPARAM lParam)
{

	if(bSendNotRcv)
	{
		//当前是发送传真操作
		static unsigned long faxdata = 0 ;
		
		this->UpdateData();

		switch(wParam)
		{

		case WM_FAXUSERCANCE:
			{
				m_Status =  "用户取消发送传真...";
				ShutdownTAPI();		
				break;
			}

		case WM_FAXMISSIONOUTOVER:
			{
				ShutdownTAPI();
			
				GetDlgItem(IDC_SENDFAX)->EnableWindow(true);
				GetDlgItem(IDC_EXIT)->EnableWindow(true);
				GetDlgItem(IDC_ABORT)->EnableWindow(false);

				switch (lParam)
				{
				case 0:
					{
						m_Status =  "成功发送传真。";
						break;
					}
				case 888:
					{
						m_Status =  "发送传真失败(用户取消)。";
						break;
					}
				default:
					{
						m_Status =  "传真发送失败！";
						break;
					}
				}
				KillTimer(100);   
			}
			break;		
			
		case WM_FAXCHANGESTATE:					
			{

				switch(lParam)
				{

				case FAXINIT:
					{

						m_bEcmFlag = false ;
						m_nTimes = 0 ;
						SetTimer(100,1000, 0); 
						m_Remote="";
						faxdata = 0;
						m_Data.Format("%dK",0);	

						GetDlgItem(IDC_SENDFAX)->EnableWindow(false);
						GetDlgItem(IDC_EXIT)->EnableWindow(false);
						GetDlgItem(IDC_ABORT)->EnableWindow(true);


						m_Status =  "初始化设备。";
						this->UpdateData(false);
						break;
					}
				case DIALFAX:
					{
						m_Status =  "拨号...";
						break;
					}
				case ANSWER:
					{
						m_Status =  "应答...";
						break; 
					}
				case NEGOTIATION:
					{
						m_Status =  "协商版本...";
						break; 
					}
				case TRAINING:
					{
						m_Status =  "训练....";
						break; 
					}
			
				}
			}

			break; 
		case WM_FAXSETCIS:
			{

				m_Remote.Format("%s",(char*)lParam );	
				m_Remote.TrimLeft(" ");
				m_Remote.TrimRight(" ");

				break; 
			}

		case WM_FAXSENDPAGEDATA:
			{
				faxdata+=(long)lParam;
				m_Data.Format("%dK",faxdata/1024);							
				break;
			}

		case WM_ACCEPTPAGE:
			{
				m_Status =  "接受页 ...";
				
				break;
			}
		case WM_REJECTPAGE:
			{
				m_Status =  "弹出页 ...";
				
				break;
			}

		case WM_FAXSPEED:
			{
				m_ActualSpeed.Format("%d%s",lParam,"00 bps");
				break;
			}

		case WM_FAXPAGE:
			{
				m_nPage = (int)lParam;
				m_Page.Format("Page %d",m_nPage);
				break;
			}

		case WM_FAXECM:
			{
				m_bEcmFlag  =  lParam == 0 ? false : true ;
				break;
			}

		case WM_FAXPROCESSPAGEDATA:	
			{
		
    			m_Status =  "正发送传真页...";
				
				switch(lParam)
				{
				case D1DMR:
					{

						if(m_bEcmFlag)
							m_Status +=  "(ECM MH)...";
						else
							m_Status += "(1DMH)...";
					
						break;
					}
				case D2DMR:
					{
								
						if(m_bEcmFlag)
							m_Status +=  "(ECM 2DMR)...";
						else
							m_Status += "(2DMR)...";			

						break;	
					}
				case D2DMMR:
					{

						if(m_bEcmFlag)
							m_Status +=  "(ECM MMR)...";
						else
							m_Status += "(2DMMR)...";
						break;
					}
				}
			}
			break;



		default:
			;
		}
		this->UpdateData(false);
	}
	else
	{
		//当前是接收传真操作
		this->UpdateData(FALSE);
		this->UpdateData(TRUE);

		static unsigned long faxdata = 0 ;
		
		switch(wParam)
		{
		case WM_FAXANI:
			{
				m_CallerNo = (char*)lParam ;
				m_Status =  "呼叫来自" + m_CallerNo ;
				this->UpdateData(FALSE);
				break;
			}
		case WM_FAXMONITORCLOSE:
			{
				m_Status =  "停止监听...";
				break;
			}

		case WM_FAXMONITORSTART:
			{
				m_Status =  "等待呼叫...";
				m_CallerNo="";
				break;
			}

		case WM_FAXUSERCANCE:
			{
				m_Status =  "用户取消接收传真...";
				break;
			}

		case WM_FAXMISSIONINOVER:
			{

				m_bFaxing = false ;			

				if(!m_AutoReply)
				{
					ShutdownTAPI();
				}
				else
				{
					lineDrop(g_hCall , NULL, 0);		
				}

				KillTimer(100);  
				
				this->GetDlgItem(IDC_RECEIVEFAX)->EnableWindow(true);			
				this->GetDlgItem(IDC_ABORT)->EnableWindow(false);
				this->GetDlgItem(IDC_EXIT)->EnableWindow(true);
							
				if (lParam==0)
					m_Status =  "接收传真成功！";
				else if(lParam==888)
					m_Status =  "传真接收失败(因用户取消)。";
				else 
					m_Status =  "传真接收失败！";
				
				if(m_AutoReply && m_PortType!=0)
				{
					SmartFaxMonitorPort(&g_hFax,m_PortType,GetSafeHwnd(),WM_SMARTFAX);
				}
				break;
			}
			
		case WM_FAXCHANGESTATE:					
			{
					
				switch(lParam)
				{

				case FAXINIT:
					{
					
						m_nTimes = 0 ;
						SetTimer(100,1000, 0); 
						faxdata = 0;
						m_Status =  "初始化设备。";
						m_Remote="";
						m_CallerNo="";
						m_ActualSpeed=("00 bps");
						m_Data="0 K";
						this->GetDlgItem(IDC_RECEIVEFAX)->EnableWindow(false);
						this->GetDlgItem(IDC_ABORT)->EnableWindow(true);
						this->GetDlgItem(IDC_EXIT)->EnableWindow(false);
						break;
					}

				case DIALFAX:
					{
						m_Status =  "拨号...";
						break;
					}
				case ANSWER:
					{
						m_Status =  "应答...";
						break; 
					}
				case NEGOTIATION:
					{
						m_Status =  "协商版本号...";
						break; 
					}
				case TRAINING:
					{
						m_Status =  "训练....";
						break; 	
					}
				}
				break; 
			}

		case WM_FAXSETCIS:
			{

				m_Remote.Format("%s",(char*)lParam );	
				m_Remote.TrimLeft(" ");
				m_Remote.TrimRight(" ");

				break; 
			}

		case WM_FAXRECVPAGEDATA:
			{
				faxdata+=(unsigned long)lParam;
				m_Data.Format("%dK",faxdata/1024);							
				break;
			}

		case WM_ACCEPTPAGE:
			{
				m_Status =  "接受页...";
			
				break;
			}
		case WM_REJECTPAGE:
			{
				m_Status =  "弹出页...";
			
				break;
			}
		case WM_FAXSPEED:
			{
				m_ActualSpeed.Format("%d%s",lParam,"00 bps");
				break;
			}
		case WM_FAXPAGE:
			{
				m_nPage = (int)lParam;
				m_Page.Format("%d",m_nPage);
				break;
			}
		case WM_FAXECM:
			{

				m_bEcmFlag  =  lParam == 0 ? false : true ;
				break;
			}

		case WM_FAXRING:
			{
				int nRingTimes = (int)lParam ;
				if(m_CallerNo.GetLength())
				{
					m_Status =  "呼叫来自" + m_CallerNo ;
				}
				else 
				{
					m_Status =  "无名呼叫...";
				}

				TRACE(m_Status);
				this->UpdateData(false);
				
				if(nRingTimes >= 2  )
				{
					if(m_PortType==0 )
						RecvFaxInTapi();
					else 
						OnReceivefax();

					TRACE("应答呼叫...\n");
				}
				break;
			}

		case WM_FAXPROCESSPAGEDATA:	
			{

    			m_Status =  "正在接收传真页。";
				
						
				switch(lParam)
				{
					case D1DMR:
						{
							m_Status +=  "(1DMH)...";
							break;
						}
					case D2DMR:
						{
							m_Status +=  "(2DMR)...";
							break;	
						}
					case D2DMMR:
						{
							if(m_bEcmFlag)
							{
								m_Status +=  "(ECM MMR)...";
							}
							else 
							{
								m_Status += "(2DMMR)...";
							}
							break;
						}
				}
				break;
			}

		}
		this->UpdateData(false);
	}
}

void CFaxMachineDlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	this->EndDialog(0);
}

void CFaxMachineDlg::OnRadioSend() 
{
	// TODO: Add your control notification handler code here
	CWnd *myWnd;
	myWnd=this->GetDlgItem(IDC_HIGH);
	myWnd->EnableWindow(true);
	myWnd=this->GetDlgItem(IDC_NORMAL);
	myWnd->EnableWindow(true);
	myWnd=this->GetDlgItem(IDC_STATIC_RESOLUTION);
	myWnd->EnableWindow(true);
	myWnd=this->GetDlgItem(IDC_AUTOREPLY);
	myWnd->EnableWindow(false);
	myWnd=this->GetDlgItem(IDC_STATIC_PHONE);
	myWnd->EnableWindow(true);
	myWnd=this->GetDlgItem(IDC_PHONE);
	myWnd->EnableWindow(true);
	myWnd=this->GetDlgItem(IDC_STATIC_FROM);
	myWnd->EnableWindow(true);
	myWnd=this->GetDlgItem(IDC_STATIC_TO);
	myWnd->EnableWindow(true);
	myWnd=this->GetDlgItem(IDC_FROM);
	myWnd->EnableWindow(true);
	myWnd=this->GetDlgItem(IDC_TO);
	myWnd->EnableWindow(true);
	myWnd=this->GetDlgItem(IDC_FAXHEAD);
	myWnd->EnableWindow(true);

	myWnd=this->GetDlgItem(IDC_STATIC_DATA);
	myWnd->SetWindowText("发送数据:");
	myWnd=this->GetDlgItem(IDC_FAXHEAD);
	myWnd->EnableWindow(true);
	myWnd=this->GetDlgItem(IDC_STATIC_CALLERNO);
	myWnd->EnableWindow(false);
	m_ReceiveFax.EnableWindow(false);
	m_SendFax.EnableWindow(true);
	bSendNotRcv=true;

	UpdateData(true);
	ShutdownTAPI();	
}

void CFaxMachineDlg::OnRadioRcv() 
{
	// TODO: Add your control notification handler code here
	CWnd *myWnd;
	myWnd=this->GetDlgItem(IDC_HIGH);
	myWnd->EnableWindow(false);
	myWnd=this->GetDlgItem(IDC_NORMAL);
	myWnd->EnableWindow(false);
	myWnd=this->GetDlgItem(IDC_STATIC_RESOLUTION);
	myWnd->EnableWindow(false);
	myWnd=this->GetDlgItem(IDC_AUTOREPLY);
	myWnd->EnableWindow(true);
	myWnd=this->GetDlgItem(IDC_STATIC_PHONE);
	myWnd->EnableWindow(false);
	myWnd=this->GetDlgItem(IDC_PHONE);
	myWnd->EnableWindow(false);
	myWnd=this->GetDlgItem(IDC_STATIC_FROM);
	myWnd->EnableWindow(false);
	myWnd=this->GetDlgItem(IDC_STATIC_TO);
	myWnd->EnableWindow(false);
	myWnd=this->GetDlgItem(IDC_FROM);
	myWnd->EnableWindow(false);
	myWnd=this->GetDlgItem(IDC_TO);
	myWnd->EnableWindow(false);
	myWnd=this->GetDlgItem(IDC_FAXHEAD);
	myWnd->EnableWindow(false);
	myWnd=this->GetDlgItem(IDC_STATIC_DATA);
	myWnd->SetWindowText("接收数据:");
	myWnd=this->GetDlgItem(IDC_STATIC_CALLERNO);
	myWnd->EnableWindow(true);
	m_SendFax.EnableWindow(false);
	m_ReceiveFax.EnableWindow(true);
	bSendNotRcv=false;
	UpdateData(true);

	ShutdownTAPI();
	OnAutoreply();	
	/*if(m_AutoReply)
	{
		if(!InitializeTAPI(0))
		{
			if(g_bInitializing)
			{
				ShutdownTAPI();
			}
			AfxMessageBox("InitializeTAPI fail ... \n");
		}
	}*/

}

void CFaxMachineDlg::OnAbort() 
{
	// TODO: Add your control notification handler code here
	AbortPort(&g_hFax);
	
}

void CFaxMachineDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == 100 )
	{
		CTimeSpan ts(0,0,0,m_nTimes++);		
		m_Time.Format("%01d:%01d:%02d",ts.GetHours(),ts.GetMinutes(),ts.GetSeconds());
		this->UpdateData(false);
	}
	CDialog::OnTimer(nIDEvent);
}

void CFaxMachineDlg::OnFaxhead() 
{
	// TODO: Add your control notification handler code here
	BOOL fEnable ;
	this->UpdateData();
	fEnable = m_FaxHead ;
	GetDlgItem(IDC_FROM)->EnableWindow(fEnable);
	GetDlgItem(IDC_TO)->EnableWindow(fEnable);
	GetDlgItem(IDC_STATIC_FROM)->EnableWindow(fEnable);
	GetDlgItem(IDC_STATIC_TO)->EnableWindow(fEnable);
}

void CFaxMachineDlg::OnReceivefax() 
{
	// TODO: Add your control notification handler code here
	m_Time="";
	this->UpdateData(TRUE);
	
	if(m_PortType==0)                        //通过Tapi接收
	{
		if(m_AutoReply)
		{
			InitFaxTapiCall(g_hLine,g_hCall);
		}
		else
		{

			int nSel =  m_ModemList.GetCurSel();
			DWORD dwDevice = m_ModemList.GetItemData(nSel);

			if(dwDevice >=0 )
			{
				InitializeTAPI(dwDevice);
				InitFaxTapiCall(g_hLine,g_hCall);
			}
		}

		return ;
	}
	else                                  //通过Com端口接收
	{

		RecvFaxInComPort();

	}
}

bool CFaxMachineDlg::RecvFaxInComPort()
{

	SFaxParam *FaxParam =(SFaxParam *) new SFaxParam; 	

	FaxParam->hFax = &g_hFax;
	FaxParam->Hwnd = this->GetSafeHwnd();
	FaxParam->Msg = WM_SMARTFAX ;
	FaxParam->nComPort = m_PortType;
	FaxParam->Speed = GetSelSpeed(m_FaxSpeed);
	FaxParam->Is2D = m_Compress == TRUE ? U2D_ENABLE : U2D_DISABLE ;
	FaxParam->Volume = GetFaxVolume(m_Volume);
	FaxParam->Class = m_FaxProtocol == 0 ? CLASS_1 : CLASS_2  ;
	FaxParam->Ecm =  m_Ecm == TRUE ? ECM_ENABLE : ECM_DISABLE ;	
	strcpy(FaxParam->FileName,m_File);	
	strcpy(FaxParam->Identifi,m_Identity);	
	
	SmartReceiveFax(FaxParam);
	
	delete FaxParam;

	return true;
}
bool CFaxMachineDlg::RecvFaxInTapi()
{

	if(m_bFaxing)
	{
		return false;
	}

	m_bFaxing = true;
		
	this->UpdateData();
	SFaxParam *FaxParam =(SFaxParam *) new SFaxParam; 	

	FaxParam->hFax = &g_hFax;
	FaxParam->hCall = g_hCall;
	FaxParam->hLine = g_hLine;
	FaxParam->Hwnd = this->GetSafeHwnd();
	FaxParam->Msg = WM_SMARTFAX;
	FaxParam->Speed = GetSelSpeed(m_FaxSpeed);
	FaxParam->Is2D = m_Compress == TRUE ? U2D_ENABLE : U2D_DISABLE ;
	FaxParam->Volume = GetFaxVolume(m_Volume);
	FaxParam->Class = m_FaxProtocol == 0 ? CLASS_1 : CLASS_2  ;
	FaxParam->Ecm =  m_Ecm == TRUE ? ECM_ENABLE : ECM_DISABLE ;	
	strcpy(FaxParam->FileName,m_File);	
	strcpy(FaxParam->Identifi,m_Identity);	

	TapiSmartReceiveFax(FaxParam);
	delete FaxParam;


	return true;

}

void CFaxMachineDlg::OnAutoreply() 
{
	// TODO: Add your control notification handler code here
	this->UpdateData(TRUE);
		
	
	if(m_PortType==0)                       //通过Tapi接收 
	{
		int nSel =  m_ModemList.GetCurSel();
		DWORD dwDevice = m_ModemList.GetItemData(nSel);
		
		if(dwDevice >=0)
		{
			
			if(m_AutoReply)
			{
				
				if(!InitializeTAPI(dwDevice))
				{
					if(g_hLineApp||g_bTapiInUse)
					{
						ShutdownTAPI();
					}
					
					m_AutoReply = FALSE ;
					UpdateData(FALSE);
					
					AfxMessageBox("InitializeTAPI fail ... \n");
				}
				else
				{
					PostMessage(WM_SMARTFAX,WM_FAXMONITORSTART,0);
				}
				
			}
			else
			{
				ShutdownTAPI();
				PostMessage(WM_SMARTFAX,WM_FAXMONITORCLOSE,0);
			}
			
		}
		
		
	}else                                  //通过Com端口接收
	{

		if(m_AutoReply)
		{
			if(SmartFaxMonitorPort(&g_hFax,m_PortType,GetSafeHwnd(),WM_SMARTFAX) == 0 )
			{
				m_Status =  "Waiting for call ...";	
					
			}
			else
			{
				m_Status =  "Monitor device failed ...";	
				m_AutoReply = FALSE;
				g_hFax = NULL;
			}

			UpdateData(FALSE);
		}
		else
		{
			AbortPort(&g_hFax);
		}
	}	
}
