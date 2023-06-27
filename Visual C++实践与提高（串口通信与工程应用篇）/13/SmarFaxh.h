#ifndef __SMARTFAX_H_
#define __SMARTFAX_H_
#include <tapi.h>
#include <windows.h>

typedef  HANDLE SmartFaxObj;
enum EResolution
{        
    RE_FINE,    
    RE_STANDARD
};

enum EClass
{ 
	CLASS_1,
	CLASS_2
};

enum EErrorCorrect
{	
	ECM_DISABLE,
	ECM_ENABLE 
};

enum EBinaryFile
{
	BFT_DISABLE,
	BFT_ENABLE 
};

enum ECreateHead
{ 
	CH_DISABLE,
	CH_ENABLE	
};

enum EUsed2D
{ 
	U2D_DISABLE,
	U2D_ENABLE
};


enum EFaxSpeed
{ 
	FS_2400,
	FS_4800,
	FS_7200,
	FS_9600,
	FS_1200,
	FS_1440,
};



enum EVolume
{ 
	VO_OFF,
	VO_LOW,
	VO_MIDDLE,
	VO_HIGH		
};



typedef struct tag_SFaxParam
{
	HCALL			hCall;
	HLINE			hLine;
	EResolution		Resolution;				// ��������(RE_FINE | RE_STARDARD)

	unsigned char	nComPort ;				// �˿ں�(1 - 256 )

	EFaxSpeed		Speed;					//�����ٶ� ( 24 | 48 | 72 | 96 | 120 |144)

	EUsed2D			Is2D;					//ѹ����ʽ(U2D_ENABLE | U2D_DISABLE)

	EClass			Class;					//��������(CLASS_1 | CLASS_2 | CLASS_1.0 | CLASS_2.0)

	EVolume			Volume;				//ModemӦ������( 0 | 1 | 2 | 3 )

	char			FileName[MAX_PATH];		//�����ļ���

	char			Identifi[56];			//����ʶ���(һ�������Լ��Ĵ������)

	EErrorCorrect	Ecm;					//����ʽ(ECM_ENABLE | ECM_DISABLE )

	HWND			Hwnd;					// ��Ϣ���ھ��

	UINT			Msg;					//��ϢID (WM_SMARTFAX)

	SmartFaxObj		*hFax;					//���������

	// send extrac parameter
	char			FaxNumber[21];			//�������
	
	char			From[128];				//��������Ϣ

	char			To[128];				//��������Ϣ
				
	ECreateHead		CreateHead;				//��������ҳü��Ϣ( CH_DISABLE | CH_ENABLE)

	EBinaryFile		BinaryFile;				//�������ļ�����(BFT_DISABLE | BFT_ENABLE )

	int				nStartPage;				//��ʼҳ
		
	#if defined(__cplusplus) && !defined(__BORLANDC__)
    //EXPDEF SFaxParam();
	#endif

}SFaxParam;







				  
const unsigned short D1DMR	= 0;		// 1-D Modified Huffman
const unsigned short D2DMR	= 1;		// 2-D Modified Huffman
const unsigned short D2DMMR	= 3;		// 2-D Modified Modified Read





typedef void (CALLBACK * MODEMLISLITNECALLBACK)(DWORD dwDeviceId, const char *sLineName, const char *ComPort,unsigned long lParam);

static void CALLBACK ModemListCallbackFunc(
						DWORD dwDeviceId, 
						const char *sLineName, 
						const char *ComPort,
						unsigned long lParam);


static void CALLBACK ModemListCallbackFunc(DWORD dwDevice, 
										   const char *sLineName, 
										   const char *ComPort,unsigned long lParam)
{
	fprintf(stderr,"DeviceID: %d \nLineName: %s\nCommPort: %s \n",dwDevice,sLineName,ComPort);	
}


/**********************************************************************************
������:<GetModemDeviceList>
----------------------------
����:		������п���Modem�б���Ϣ
----------------------------
����:
	1: lParam		
	2: lpfnCallback  �ص�����

************************************************************************************/
bool GetModemDeviceList(
			unsigned long lParam, 
			MODEMLISLITNECALLBACK lpfnCallback = ModemListCallbackFunc );





/**********************************************************************************
������:<ErrorCorrectFaxPage>
----------------------------
����:		��������ҳ
----------------------------
����:
	1: Input			�����ļ���		
	2: Output			����ļ���
	3: CompressionDF	ѹ����ʽ

************************************************************************************/


int ErrorCorrectFaxPage(const char *Input,
						const char*Output,
						unsigned short CompressionDF = D2DMMR);





long InitFaxTapiCall(HLINE &hLine,HCALL &hCall);
int ModemGetComPort( const char* strName );





/**********************************************************************************
������:<AbortPort>
----------------------------
����:			�жϴ������!
----------------------------
����:
	1: hFax		���������	

************************************************************************************/

int AbortPort(SmartFaxObj *hFax);




/**********************************************************************************
������:<SmartFaxMonitorPort>
----------------------------
����:			���Ӷ˿���Ϣ!
----------------------------
����:
	1: hFax		���������	
	2: nPort	�˿ں�
	3: hWnd		��Ϣ���ھ��
	4: Msg		��ϢID (WM_SMARTFAX)

************************************************************************************/

int SmartFaxMonitorPort(
			SmartFaxObj *hFax ,
			unsigned char nPort,
			HWND hWnd,
			UINT Msg);






/**********************************************************************************
������:<TapiSmartReceiveFax>
----------------------------
����:			ͨ��TAPI�ӿڽ��մ���!
----------------------------
����:
	1: FaxParam		������� (��SFaxParam����)	
	
************************************************************************************/

int TapiSmartReceiveFax(SFaxParam *FaxParam);








/**********************************************************************************
������:<_TapiSmartReceiveFax>
----------------------------
����:			ͨ��TAPI�ӿڽ��մ���!
----------------------------
����:
	1:	hFax			���������	
	2:	hCall			�������
	3:	hline			�������
	4:	FileName		�����ļ���
	5:	Identifi		����ʶ���(һ�������Լ��Ĵ������)
	6:	Volume			ModemӦ������( 0 | 1 | 2 | 3 )
	7:	Speed			������Ҫ���ٶ�( 24 | 48 | 72 | 96 | 120 |144) 
	8:	Class			��������(CLASS_1 | CLASS_2 | CLASS_1.0 | CLASS_2.0)
	9:	Is2d			ѹ����ʽ(U2D_ENABLE | U2D_DISABLE) 
	10: ECM				����ʽ(ECM_ENABLE | ECM_DISABLE )
	11: hWnd			��Ϣ���ھ��
	1:  Msg				��ϢID (WM_SMARTFAX)
	

	

����ֵ:
  
	0:	    End if function completes successfully
	-1:     Exception error	
	101:    Failed to Open FAX file ~
	102:    Couldn't conneced  within 35 secs of ATA command
	103:	Resevr
	104:    Failed to send CSI frames 
	105:    Failed to send DIS frames 
	106:    Failed to send NFS frames 
	107:    Failed to send other negotiating frames
	108:    Failed to send CFR frames
	109:    Failed to training
	110:    Failed to send FTT frames
	111:    Failed to set training speed  3 times
	112:    Failed to send CRP frames
	113:    Failed to dropped carrier within 5 s 
	114:    Failed to respond to +FRM properly
	115:    Failed to get modem data
	116:    Failed to accept page data
  	201:	Couldn't be found transmit file 
	202:	Transmit file isn't TIFF CLASS
	203:	Call isn't answered within 30 s
	204:	Machine can't receive fax data
	205:	Couldn't set +FTM
	206:	Couldn't set +FTM
	210:	NO DIALTONE
	211:	BUSY
	212:	NO ANSWER
	213:	NO CARRIER

************************************************************************************/

int _TapiSmartReceiveFax(
			SmartFaxObj *hFax ,
			HCALL &hCall,
			HLINE &hline,
			const char *FileName,
			const char *Identifi,
			EVolume Volume ,
			EFaxSpeed Speed,
			EClass Class,
			EUsed2D Is2d,
			EErrorCorrect ECM,
			HWND hWnd,
			UINT Msg);








/**********************************************************************************
������:<TapiSmartSendFax>
----------------------------
����:			ͨ��TAPI�ӿڷ��ʹ���!
----------------------------
����:
	1: FaxParam		������� (��SFaxParam����)		
	
************************************************************************************/

int TapiSmartSendFax(SFaxParam *FaxParam);











/**********************************************************************************
������:<_TapiSmartSendFax>
----------------------------
����:			ͨ��TAPI�ӿڷ��ʹ���!
----------------------------
����:
	1:	hFax			���������	
	2:	hCall			�������
	3:	hline			�������
	4:	FileName		�����ļ���
	5:	Identifi		����ʶ���(һ�������Լ��Ĵ������)
	6:	Volume			ModemӦ������( 0 | 1 | 2 | 3 )
	7:	Speed			������Ҫ���ٶ�( 24 | 48 | 72 | 96 | 120 |144) 
	8:	Class			��������(CLASS_1 | CLASS_2 | CLASS_1.0 | CLASS_2.0)
	9:	Is2d			ѹ����ʽ(U2D_ENABLE | U2D_DISABLE) 
	10: ECM				����ʽ(ECM_ENABLE | ECM_DISABLE )
	11: CreateHead		��������ҳü��Ϣ
	12: Resolution		��������
	13: From			������
	14: To				������
	15: hWnd			��Ϣ���ھ��
	16: Msg				��ϢID (WM_SMARTFAX)

����ֵ:
  
	0:	    End if function completes successfully
	-1:     Exception error	
	101:    Failed to Open FAX file ~
	102:    Couldn't conneced  within 35 secs of ATA command
	103:	Resevr
	104:    Failed to send CSI frames 
	105:    Failed to send DIS frames 
	106:    Failed to send NFS frames 
	107:    Failed to send other negotiating frames
	108:    Failed to send CFR frames
	109:    Failed to training
	110:    Failed to send FTT frames
	111:    Failed to set training speed  3 times
	112:    Failed to send CRP frames
	113:    Failed to dropped carrier within 5 s 
	114:    Failed to respond to +FRM properly
	115:    Failed to get modem data
	116:    Failed to accept page data
  	201:	Couldn't be found transmit file 
	202:	Transmit file isn't TIFF CLASS
	203:	Call isn't answered within 30 s
	204:	Machine can't receive fax data
	205:	Couldn't set +FTM
	206:	Couldn't set +FTM
	210:	NO DIALTONE
	211:	BUSY
	212:	NO ANSWER
	213:	NO CARRIER

	
************************************************************************************/

int _TapiSmartSendFax(SmartFaxObj *hFax ,
					  HCALL &hCall,
					  HLINE &hline,
					  const char *Tel,
					  const char *FileName,
					  const char *Identifi,
					  EVolume Volume ,
					  EFaxSpeed Speed,
					  EClass Class,
					  EUsed2D Is2d,
					  EErrorCorrect ECM,
					  ECreateHead CreateHead,
					  EResolution Resolution,
					  const char * From ,
					  const char * Receiver,
					  HWND hWnd,
					  UINT Msg,
					  int nStartPage);




/**********************************************************************************
������:	<SmartReceiveFax>
----------------------------
����:	ֱ��ͨ���˿ڽ��մ���
----------------------------
����:
	1: FaxParam		������� (��SFaxParam����)		
	
************************************************************************************/

int SmartReceiveFax(SFaxParam *FaxParam);




/**********************************************************************************
������:<_SmartReceiveFax>
----------------------------
����:	ֱ��ͨ���˿ڽ��մ���
----------------------------
����:
	1:	hFax			���������	
	2:	nPort			�˿ں�	
	3:	FileName		�����ļ���
	4:	Identifi		����ʶ���(һ�������Լ��Ĵ������)
	5:	Volume			ModemӦ������( 0 | 1 | 2 | 3 )
	6:	Speed			������Ҫ���ٶ�( 24 | 48 | 72 | 96 | 120 |144) 
	7:	Class			��������(CLASS_1 | CLASS_2 | CLASS_1.0 | CLASS_2.0)
	8:	Is2d			ѹ����ʽ(U2D_ENABLE | U2D_DISABLE) 
	9:  ECM				����ʽ(ECM_ENABLE | ECM_DISABLE )	
	10: hWnd			��Ϣ���ھ��
	11: Msg				��ϢID (WM_SMARTFAX)
	
************************************************************************************/

int _SmartReceiveFax(
			 SmartFaxObj *hFax,
			 unsigned char nPort,
			 const char *FaxFileName, 
			 const char *Identifi,
			 EVolume Volume = VO_LOW,  
			 EFaxSpeed Speed =FS_1440,					 
			 EClass Class = CLASS_1,
			 EUsed2D Is2d = U2D_ENABLE,
			 EErrorCorrect ECM = ECM_ENABLE,
			 HWND hWnd = NULL,
			 UINT Msg = NULL);



/**********************************************************************************
������:_SmartReceiveFax
����:���մ����ļ�
����:
	1: nPort		�˿ں�	
	2: FaxFileName	�����ļ���
	3: Identifi     ����ʶ���(һ�������Լ��Ĵ������)
	4: Speed		������Ҫ���ٶ�(default 96) 
	5: Fclass		CLASS TYPE (defualt Class 1)
	6: Twodee		ѹ����ʽ(0 - 1D,1 - 2D defaul 1 ) 
	7: ECM			����ʽ(defaul 1)
	8: hWnd			���ܴ�����Ϣ�Ĵ��ھ��
	9: Msg			������Ϣ

����ֵ:

    0:	    End if function completes successfully
	-1:     Exception error	
	101:    Failed to Open FAX file ~
	102:    Couldn't conneced  within 35 secs of ATA command
	103:	Resevr
	104:    Failed to send CSI frames 
	105:    Failed to send DIS frames 
	106:    Failed to send NFS frames 
	107:    Failed to send other negotiating frames
	108:    Failed to send CFR frames
	109:    Failed to training
	110:    Failed to send FTT frames
	111:    Failed to set training speed  3 times
	112:    Failed to send CRP frames
	113:    Failed to dropped carrier within 5 s 
	114:    Failed to respond to +FRM properly
	115:    Failed to get modem data
	116:    Failed to accept page data
  	201:	Couldn't be found transmit file 
	202:	Transmit file isn't TIFF CLASS
	203:	Call isn't answered within 30 s
	204:	Machine can't receive fax data
	205:	Couldn't set +FTM
	206:	Couldn't set +FTM
	210:	NO DIALTONE
	211:	BUSY
	212:	NO ANSWER
	213:	NO CARRIER


*******************************************************************************/






/**********************************************************************************
������:	<SmartSendFax>
----------------------------
����:	ֱ��ͨ���˿ڽ��մ���
----------------------------
����:
	1: FaxParam		������� (��SFaxParam����)		
	
************************************************************************************/
int SmartSendFax(SFaxParam *FaxParam);



/**********************************************************************************
������:<_SmartSendFax>
----------------------------
����:	ֱ��ͨ���˿ڷ��ʹ���
----------------------------
����:
	1:	hFax			���������	
	2:	nPort			�˿ں�		
	3:	FileName		�����ļ���
	4:	Identifi		����ʶ���(һ�������Լ��Ĵ������)
	5:	Volume			ModemӦ������( 0 | 1 | 2 | 3 )
	6:	Speed			������Ҫ���ٶ�( 24 | 48 | 72 | 96 | 120 |144) 
	7:	Class			��������(CLASS_1 | CLASS_2 | CLASS_1.0 | CLASS_2.0)
	8:	Is2d			ѹ����ʽ(U2D_ENABLE | U2D_DISABLE) 
	9:  ECM				����ʽ(ECM_ENABLE | ECM_DISABLE )
	10: CreateHead		��������ҳü��Ϣ
	11: Resolution		��������
	12: From			������
	13: To				������
	14: hWnd			��Ϣ���ھ��
	15: Msg				��ϢID (WM_SMARTFAX)

	
************************************************************************************/

int _SmartSendFax(SmartFaxObj *hFax ,
		  unsigned char nPort,
		  const char *Tel,
		  const char *FaxFileName, 
		  const char *Identifi,
		  EVolume Volume ,
		  EFaxSpeed Speed,
		  EUsed2D Is2d,
		  EErrorCorrect ECM,
		  ECreateHead CreateHead,
		  EResolution Resolution,
		  const char * From ,
		  const char * Receiver,
		  HWND hWnd,
		  UINT Msg,
		  int nStartPage);

/**********************************************************************************
������:SmartSendFax
����:���ʹ����ļ�
����:
	1: nPort		�˿ں�
	2: Tel			���ܶ˺���
	3: FaxFileName	�����ļ���
	4: Identifi     ����ʶ���(һ�������Լ��Ĵ������)
	5: Speed		������Ҫ���ٶ�(default 96) 
	6: Fclass		CLASS TYPE (defualt Class 1)
	7: Twodee		ѹ����ʽ(0 - 1D,1 - 2D defaul 1 ) 
	8: ECM			����ʽ(defaul 1)
	9: hWnd			���ܴ�����Ϣ�Ĵ��ھ��
	9: Msg			������Ϣ

����ֵ:

    0:	    End if function completes successfully
	-1:     Exception error	
	101:    Failed to Open FAX file ~
	102:    Couldn't conneced  within 35 secs of ATA command
	103:	Resevr
	104:    Failed to send CSI frames 
	105:    Failed to send DIS frames 
	106:    Failed to send NFS frames 
	107:    Failed to send other negotiating frames
	108:    Failed to send CFR frames
	109:    Failed to training
	110:    Failed to send FTT frames
	111:    Failed to set training speed  3 times
	112:    Failed to send CRP frames
	113:    Failed to dropped carrier within 5 s 
	114:    Failed to respond to +FRM properly
	115:    Failed to get modem data
	116:    Failed to accept page data
  	201:	Couldn't be found transmit file 
	202:	Transmit file isn't TIFF CLASS
	203:	Call isn't answered within 30 s
	204:	Machine can't receive fax data
	205:	Couldn't set +FTM
	206:	Couldn't set +FTM
	210:	NO DIALTONE
	211:	BUSY
	212:	NO ANSWER
	213:	NO CARRIER

*******************************************************************************/




	
// fax message for windows 

#define WM_SMARTFAX				WM_USER+101


#define WM_FAXMISSIONINOVER		0x101
#define WM_FAXCHANGESTATE		0x102
#define WM_FAXSETCIS			0x103
#define WM_FAXSETSPEED			0x104
#define WM_FAXMISSIONOUTOVER	0x105
#define WM_FAXRECVPAGEDATA		0x106
#define WM_FAXSENDPAGEDATA		0x107
#define WM_ACCEPTPAGE			0x108
#define WM_REJECTPAGE			0x109
#define WM_FAXSPEED				0x110
#define WM_FAXPROCESSPAGEDATA	0x111
#define WM_FAXUSERCANCE			0x112
#define WM_FAXECM				0x113
#define WM_FAXPAGE				0x114

#define WM_FAXRING				0x115

#define WM_FAXMONITORCLOSE		0x116
#define WM_FAXMONITORSTART		0x117
#define WM_FAXMONITORFAIL		0x118

#define WM_FAXANI				0x119


#define FAXINIT					0
#define DIALFAX					1
#define ANSWER					2
#define NEGOTIATION				3
#define TRAINING				4



#endif //__SMARTFAX_H_

