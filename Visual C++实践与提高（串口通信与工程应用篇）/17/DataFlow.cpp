// DataFlow.cpp : implementation file
//

#include "stdafx.h"
#include "DataFlow.h"
#include "GPSPublic.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataFlow

CDataFlow::CDataFlow()
{
	InitVariable();
}

CDataFlow::CDataFlow(CString com, DWORD dwMessage)
{
	InitVariable();
	m_Com = com;
}


CDataFlow::~CDataFlow()
{
	DestroyWindow();
}


BEGIN_MESSAGE_MAP(CDataFlow, CWnd)
	//{{AFX_MSG_MAP(CDataFlow)
	ON_MESSAGE(WM_COM_TO_DATA_FLOW,OnComMsg)
	ON_MESSAGE(WM_INITCENTER,OnInitCenter)
	ON_MESSAGE(WM_DECODE_MSG,OnDecodeMsg)
	ON_MESSAGE(WM_RESPONSE_MSG,OnResponseMsg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDataFlow message handlers

DWORD CDataFlow::GetMeMsg()
{
	return this->m_dwToMeMsg;
}

HWND CDataFlow::Create()
{
	CRect ct(0,0,0,0);
	CreateEx(0,NULL,NULL,WS_CHILD|WS_POPUP,ct,NULL,0,NULL);
	if(!m_hWnd)
		AfxMessageBox("Create Window Fail!");
	return m_hWnd;
}

///////////////////////////////////////////////////////////////////
// 函数名：	DealFlow
// 功  能：	将记录下来的数据头和数据尾之间的数据提取出来，发送解码消息，由解码程序解码，并将其从数据缓冲区中删除
// 参  数：	
// 返回值：	
// 备  注：	
///////////////////////////////////////////////////////////////////
void CDataFlow::DealFlow()
{		
	if ((m_dwDataGramLen < 0) 
		|| (m_dwDataGramLen > MAX_NEMA_SENTENCE_MAX_LENGTH))
	{
		return;
	}

	BYTE gramBytes[MAX_NEMA_SENTENCE_MAX_LENGTH+1];
	memset(gramBytes, 0x00, sizeof(gramBytes));

	for (int i = 0;i < m_dwDataGramLen;i++)
	{
		gramBytes[i] = m_Data[m_dwDataGramHead+i];
	}

	m_Data.RemoveAt(0, m_dwDataGramTail);
	
	
	this->PostMessage(WM_DECODE_MSG,(DWORD)(BYTE*)gramBytes,(DWORD)(m_dwDataGramLen));
	
	m_dwDataGramHead=0;
	m_dwDataGramTail=0;
	m_dwDataGramLen=0;		
		
	return;
}

///////////////////////////////////////////////////////////////////
// 函数名：	SearchFlow
// 功  能：	处理串口接收到的数据
// 参  数：	
// 返回值：	BOOL--查找数据缓冲区中是否有符合标准的协议数据包
// 备  注：	
///////////////////////////////////////////////////////////////////
BOOL CDataFlow::SearchFlow()
{
	for (int i = 0;i < m_Data.GetUpperBound(); i++)
	{
		// 检测到数据头后，将其位置记录下来
		if ((m_Data[i] == NEMA_HEAD_STANDAD) 
			|| (m_Data[i] == NEMA_HEAD_TEXT))
		{
			m_dwDataGramHead = i;
		}

		// 检测到数据尾后，将其位置记录下来
		if ((m_Data[i] == NEMA_TAIL_STANDAD_1) 
			&& (m_Data[i+1] == NEMA_TAIL_STANDAD_2) )
		{
			m_dwDataGramTail = i + 1;
			m_dwDataGramLen = m_dwDataGramTail-m_dwDataGramHead+1;
			return TRUE;
		}
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////
// 函数名：	OnComMsg
// 功  能：	处理串口接收到的数据
// 参  数：	DWORD dwEvent--接收到的数据存储区指针
//			DWORD dwLen--接收到的数据的长度
// 返回值：	
// 备  注：	
//////////////////////////////////////////////////////////////////
void CDataFlow::OnComMsg(DWORD dwEvent, DWORD dwLen)
{
	if(!dwLen)
	{
		m_dwComEvent=dwEvent;
		return;
	}
	
	while(dwLen > 0)
	{
		// 将数据拷贝到本地数组中
		BYTE s[MAX_COM_IN_LENGTH+1];
		int len = min(MAX_COM_IN_LENGTH, dwLen);
		memset(s, 0, sizeof(s));
		memcpy(s,(BYTE * )dwEvent, len);
		s[len]='\0';
		dwLen -= len;

		CString content = s;					
		
		// 发送给主窗体，有数据到达，并显示
		::SendMessage(AfxGetApp()->GetMainWnd()->m_hWnd, WM_RECEIVE_COM_DATA, (WPARAM)&m_Com, (LPARAM)&content);
				
		for(DWORD i=0; i<len; i++)
		{
			m_Data.Add(s[i]);
		}	
	}

	while(SearchFlow())	DealFlow();
	return;
}

void CDataFlow::OnInitCenter(WPARAM wp,LPARAM lp)
{	
	return;
}

void CDataFlow::SetEditCtrl(CEdit *pReceEdit, CEdit *pSendEdit)
{
	m_pReceEdit=pReceEdit;
	m_pSendEdit=pSendEdit;
}


GPSPack* CDataFlow::DecodeNEMA_Text(CString source)
{
	if (source.GetLength() != NEMA_TEXT_LENGTH) return NULL;

	GPSPack* pack = new GPSPack();
	memset(pack, 0x00, sizeof(GPSPack));

	pack->GPS_NEMA_TEXT.bodyType = NEMATYPE_TEXT_POS;
	int iLen = 0;		//协议解析的当前字符位置
	int itemLen = 0;	//协议解析的当前项的长度

	
	//----------------------------------------------------------------
	// 句头起始符			   1       始终为 '@'
	itemLen = 1;
	CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_TEXT.head, source.Mid(iLen, itemLen), itemLen);
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	// 日期部分
	// 年                      2       UTC年的最后两位数字
	iLen += itemLen;
	itemLen = 2;
	CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_TEXT.body.date.year, source.Mid(iLen, itemLen));
	pack->GPS_NEMA_TEXT.body.date.year += 2000;
	
	// 月                      2       UTC月, "01".."12"
	iLen += itemLen;
	itemLen = 2;
	CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_TEXT.body.date.month, source.Mid(iLen, itemLen));
		
	// 日                      2       UTC日, "01".."31"
	iLen += itemLen;
	itemLen = 2;
	CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_TEXT.body.date.day, source.Mid(iLen, itemLen));	
	//----------------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------------------
	// 时间部分
	// 时                      2       UTC时, "00".."23"
	iLen += itemLen;
	itemLen = 2;
	CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_TEXT.body.time.hour, source.Mid(iLen, itemLen));	
		
	// 分                      2       UTC分, "00".."59"
	iLen += itemLen;
	itemLen = 2;
	CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_TEXT.body.time.minute, source.Mid(iLen, itemLen));	

	// 秒                      2       UTC秒, "00".."59"
	iLen += itemLen;
	itemLen = 2;
	CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_TEXT.body.time.second, source.Mid(iLen, itemLen));	
	//------------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------------
	// 位置部分

	// 纬度半球                1       'N' 或 'S'
	iLen += itemLen;
	itemLen = 1;
	CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_TEXT.body.latitudeType, source.Mid(iLen, itemLen), itemLen);	
		
	// 纬度坐标                7       WGS84坐标系统，坐标格式ddmmmmm,在第4位数字后省略了一个小数点。
	iLen += itemLen;
	itemLen = 7;
	CGPSPublic::ConvertToLatitude((double&)pack->GPS_NEMA_TEXT.body.latitude.latitude, source.Mid(iLen, itemLen));
	
	// 经度半球                1       'E' 或 'W'
	iLen += itemLen;
	itemLen = 1;
	CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_TEXT.body.longitudeType, source.Mid(iLen, itemLen), itemLen);	
		
	// 经度坐标                8       WGS84坐标系统，坐标格式dddmmmmm,在第5位数字后省略了一个小数点。
	iLen += itemLen;
	itemLen = 8;
	CGPSPublic::ConvertToLongitude(pack->GPS_NEMA_TEXT.body.longitude.longitude, source.Mid(iLen, itemLen));

	// 定位状态                1       'd'--2维差分定位;'D'--3维差分定位;'g'--2维定位;'G'--3维定位;'S'--模拟状态;'_'--无效
	iLen += itemLen;
	itemLen = 1;
	CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_TEXT.body.gpsStatus, source.Mid(iLen, itemLen), itemLen);	

	// 水平定位误差            3       单位为“米”
	iLen += itemLen;
	itemLen = 3;
	CGPSPublic::ConvertToDouble(pack->GPS_NEMA_TEXT.body.hdop, source.Mid(iLen, itemLen));

	// 高度符号                1       '+' 或 '-'
	iLen += itemLen;
	itemLen = 1;
	CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_TEXT.body.altitudeSymbol, source.Mid(iLen, itemLen), itemLen);	

	// 高度                    5       海拔高，单位为“米”
	iLen += itemLen;
	itemLen = 5;
	CGPSPublic::ConvertToDouble(pack->GPS_NEMA_TEXT.body.altitude.altitude, source.Mid(iLen, itemLen));
	//----------------------------------------------------------------------------------------


	//------------------------------------------------------------------------------------
	//方向和速度部分

	// 东/西 速度方向          1       'E' 或 'W'
	iLen += itemLen;
	itemLen = 1;
	CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_TEXT.body.xDirect, source.Mid(iLen, itemLen), itemLen);	

	// 东/西速度               4       单位是“米/秒”，在第三位后省略了一个小数点，("1234" = 123.4 m/s)
	iLen += itemLen;
	itemLen = 4;
	CGPSPublic::ConvertToDoubleAddPoint(pack->GPS_NEMA_TEXT.body.xVolity, source.Mid(iLen, itemLen), 3);


	// 南/北 速度方向          1       'S' 或 'N'
	iLen += itemLen;
	itemLen = 1;
	CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_TEXT.body.yDirect, source.Mid(iLen, itemLen), itemLen);	

	// 南/北 速度              4       单位是“米/秒”，在第三位后省略了一个小数点, ("1234" = 123.4 m/s)
	iLen += itemLen;
	itemLen = 4;
	CGPSPublic::ConvertToDoubleAddPoint(pack->GPS_NEMA_TEXT.body.yVolity, source.Mid(iLen, itemLen), 3);


	// 垂直速度方向            1       'U' (上) 或 'D' (下)
	iLen += itemLen;
	itemLen = 1;
	CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_TEXT.body.zDirect, source.Mid(iLen, itemLen), itemLen);

	// 垂直速度                4       单位是“米/秒”，在第二位后省略了一个小数点,("1234" = 12.34 m/s)
	iLen += itemLen;
	itemLen = 4;
	CGPSPublic::ConvertToDoubleAddPoint(pack->GPS_NEMA_TEXT.body.zVolity, source.Mid(iLen, itemLen), 3);

	// 句尾结束符              2        回车, '0x0D', 和换行'0x0A'
	iLen += itemLen;
	itemLen = 2;
	CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_TEXT.tail, source.Mid(iLen, itemLen), itemLen);
	
	return pack;
}

///////////////////////////////////////////////////////////////////
// 函数名：	DecodeNEMA_GPGGA
// 功  能：	解码NEMA的GPGGA协议数据
// 参  数：	
// 返回值：	GPSPack*--解析后的协议数据包
// 备  注：	GPS定位信息
//////////////////////////////////////////////////////////////////
GPSPack* CDataFlow::DecodeNEMA_GPGGA()
{
	int total=16;

	// 判断当数据包中的数据项少于协议规定的15项时,返回
	if (m_dataArray.GetSize() < total) return NULL;

	// 定义数据变量
	GPSPack* pack = new GPSPack();
	memset(pack, 0x00, sizeof(GPSPack));

	// 为数据包的包头和包类型赋值
	pack->GPS_NEMA_GPGGA.head = NEMA_HEAD_STANDAD;
	pack->GPS_NEMA_GPGGA.bodyType = NEMATYPE_STANDARD_GPGGA;

	// 定义解析数据时用到的变量	
	int itemCount;		// 当前解析的是第几项
	int itemLen;		// 当前解析项的长度
	int iLen = 0;		// 当前解析项从第几个字符开始读取
	
	//----------------------------------------------------------------------------
	// GPS定位信息
	// $GPGGA,<1>,<2>,<3>,<4>,<5>,<6>,<7>,<8>,<9>,M,<10>,M,<11>,<12>*hh<CR><LF>
	// 从第一项依次解析每个数据项
	//----------------------------------------------------------------------------
	for (itemCount = 1; itemCount <total; itemCount++)
	{
		// 设置每项从数据的第一个字符开始处理
		iLen = 0;
		// 并从数组中取出要解析的数据项
		CString* item = m_dataArray.GetAt(itemCount);

		// 开始逐项解析数据项
		switch (itemCount)
		{
		case 1:
			//----------------------------------------------------------------------------------------------
			// 时间部分		<1> UTC时间，hhmmss（时分秒）格式
			// 时                      2       UTC时, "00".."23"			
			itemLen = 2;
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_GPGGA.body.time.hour, 
				item->Mid(iLen, itemLen));	
				
			// 分                      2       UTC分, "00".."59"
			iLen += itemLen;
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_GPGGA.body.time.minute, 
				item->Mid(iLen, itemLen));

			// 秒                      2       UTC秒, "00".."59"
			iLen += itemLen;
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_GPGGA.body.time.second, 
				item->Mid(iLen, itemLen));
			//------------------------------------------------------------------------------------------------
			break;

		case 2:
			//------------------------------------------------------------------------------------------------
			// 纬度坐标		<2> 纬度ddmm.mmmm（度分）格式（前面的0也将被传输）			
			CGPSPublic::ConvertToLatitudeHavePoint(
				(double&)pack->GPS_NEMA_GPGGA.body.latitude.latitude, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 3:
			//------------------------------------------------------------------------------------------------
			// 纬度半球		<3> 纬度半球N（北半球）或S（南半球）			
			itemLen = 1;
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_GPGGA.body.latitudeType, 
				*item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 4:
			//------------------------------------------------------------------------------------------------
			// 经度坐标		<4> 经度dddmm.mmmm（度分）格式（前面的0也将被传输）			
			CGPSPublic::ConvertToLongitudeHavePoint(
				(double&)pack->GPS_NEMA_GPGGA.body.longitude.longitude, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 5:
			//------------------------------------------------------------------------------------------------
			// 经度半球		<5> 经度半球E（东经）或W（西经）			
			itemLen = 1;
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_GPGGA.body.longitudeType, 
				*item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 6:
			//------------------------------------------------------------------------------------------------
			// 定位状态		<6> GPS状态：0=未定位，1=非差分定位，2=差分定位，6=正在估算			
			itemLen = 1;
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_GPGGA.body.gpsStatus, 
				*item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 7:
			//------------------------------------------------------------------------------------------------
			// 卫星数量		<7> 正在使用解算位置的卫星数量（00~12）（前面的0也将被传输）
			CGPSPublic::ConvertToInt(pack->GPS_NEMA_GPGGA.body.sateCount, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 8:
			//------------------------------------------------------------------------------------------------
			// 水平定位误差	<8> HDOP水平精度因子（0.5~99.9）			
			CGPSPublic::ConvertToDouble(pack->GPS_NEMA_GPGGA.body.hdop, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 9:
			//------------------------------------------------------------------------------------------------
			// 海拔			<9> 海拔高度（-9999.9~99999.9）			
			CGPSPublic::ConvertToDouble(pack->GPS_NEMA_GPGGA.body.altitude.altitude, *item);
			//------------------------------------------------------------------------------------------------
			break;		

		case 11:
			//------------------------------------------------------------------------------------------------
			// 高度			<10> 地球椭球面相对大地水准面的高度
			CGPSPublic::ConvertToDouble(pack->GPS_NEMA_GPGGA.body.height, *item);
			//------------------------------------------------------------------------------------------------
			break;	
			
		case 13:
			//------------------------------------------------------------------------------------------------
			// 差分时间		<11> 差分时间（从最近一次接收到差分信号开始的秒数，如果不是差分定位将为空）			
			CGPSPublic::ConvertToInt(pack->GPS_NEMA_GPGGA.body.diffSecond, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 14:
			//------------------------------------------------------------------------------------------------
			// 差分站编号	<12> 差分站ID号0000~1023（前面的0也将被传输，如果不是差分定位将为空）
			if (item->GetLength() > 0)
			{
				itemLen = 4;			
				CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_GPGGA.body.diffStationID, 
					*item->Mid(iLen, itemLen), itemLen);
			}
			break;
			//------------------------------------------------------------------------------------------------

		case 15:
			//------------------------------------------------------------------------------------------------
			//hh校验码
			itemLen = 2;			
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_GPGGA.check, 
				item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;
		}		
	}

	// 设置数据包的数据尾和协议校验码开始符
	pack->GPS_NEMA_GPGGA.checkBegin = NEMA_CHECK_STANDAD;
	pack->GPS_NEMA_GPGGA.tail[0] = NEMA_TAIL_STANDAD_1;
	pack->GPS_NEMA_GPGGA.tail[1] = NEMA_TAIL_STANDAD_2;

	return pack;
}

///////////////////////////////////////////////////////////////////
// 函数名：	DecodeNEMA_GPGSA
// 功  能：	解码NEMA的GPGSA协议数据
// 参  数：	
// 返回值：	GPSPack*--解析后的协议数据包
// 备  注：	当前卫星信息
///////////////////////////////////////////////////////////////////
GPSPack* CDataFlow::DecodeNEMA_GPGSA()
{
	int total=19;

	// 判断当数据包中的数据项少于协议规定的15项时,返回
	if (m_dataArray.GetSize() < total) return NULL;

	// 定义数据变量
	GPSPack* pack = new GPSPack();
	memset(pack, 0x00, sizeof(GPSPack));

	// 为数据包的包头和包类型赋值
	pack->GPS_NEMA_GPGSA.head = NEMA_HEAD_STANDAD;
	pack->GPS_NEMA_GPGSA.bodyType = NEMATYPE_STANDARD_GPGSA;

	// 定义解析数据时用到的变量	
	int itemCount;		// 当前解析的是第几项
	int itemLen;		// 当前解析项的长度
	int iLen = 0;		// 当前解析项从第几个字符开始读取
	
	//----------------------------------------------------------------------------
	// 当前卫星信息
	// $GPGSA,<1>,<2>,<3>,<3>,<3>,<3>,<3>,<3>,<3>,<3>,<3>,<3>,<3>,<3>,<4>,<5>,<6>*hh<CR><LF>
	// 从第一项依次解析每个数据项
	//----------------------------------------------------------------------------
	for (itemCount = 1; itemCount <total; itemCount++)
	{
		// 设置每项从数据的第一个字符开始处理
		iLen = 0;
		// 并从数组中取出要解析的数据项
		CString* item = m_dataArray.GetAt(itemCount);

		// 开始逐项解析数据项
		switch (itemCount)
		{
		case 1:
			//------------------------------------------------------------------------------------------------
			// 定位状态		<1> 模式，M=手动，A=自动			
			itemLen = 1;
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_GPGSA.body.gpsmode, 
				*item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 2:
			//------------------------------------------------------------------------------------------------
			// 定位类型		<2> 定位类型，1=没有定位，2=2D定位，3=3D定位		
			itemLen = 1;
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_GPGSA.body.postype, 
				*item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
			//----------------------------------------------------------------------------------------------
			// 时间部分		<3> PRN码（伪随机噪声码），正在用于解算位置的卫星号（01~32，前面的0也将被传输）。		
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_GPGSA.body.prn[itemCount-3], *item);			
			//------------------------------------------------------------------------------------------------
			break;

		case 15:
			//------------------------------------------------------------------------------------------------
			// pdop			<4> PDOP位置精度因子（0.5~99.9）			
			CGPSPublic::ConvertToDouble(pack->GPS_NEMA_GPGSA.body.pdop, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 16:
			//------------------------------------------------------------------------------------------------
			// hdop			<5> HDOP水平精度因子（0.5~99.9）		
			CGPSPublic::ConvertToDouble(pack->GPS_NEMA_GPGSA.body.hdop, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 17:
			//------------------------------------------------------------------------------------------------
			// vdop			<6> VDOP垂直精度因子（0.5~99.9）			
			CGPSPublic::ConvertToDouble(pack->GPS_NEMA_GPGSA.body.vdop, *item);
			//------------------------------------------------------------------------------------------------
			break;
		}		
	}

	// 设置数据包的数据尾和协议校验码开始符
	pack->GPS_NEMA_GPGSA.checkBegin = NEMA_CHECK_STANDAD;
	pack->GPS_NEMA_GPGSA.tail[0] = NEMA_TAIL_STANDAD_1;
	pack->GPS_NEMA_GPGSA.tail[1] = NEMA_TAIL_STANDAD_2;

	return pack;
}

///////////////////////////////////////////////////////////////////
// 函数名：	DecodeNEMA_GPGSV
// 功  能：	解码NEMA的GPGSV协议数据
// 参  数：	
// 返回值：	GPSPack*--解析后的协议数据包
// 备  注：	可见卫星信息,<4>,<5>,<6>,<7>信息将按照每颗卫星进行循环显示，
//			每条GSV语句最多可以显示4颗卫星的信息。
//			其他卫星信息将在下一序列的NMEA0183语句中输出。
///////////////////////////////////////////////////////////////////
GPSPack* CDataFlow::DecodeNEMA_GPGSV()
{
	int total = 5;

	// 判断当数据包中的数据项少于协议规定的15项时,返回
	if (m_dataArray.GetSize() < total) return NULL;

	total = m_dataArray.GetSize();

	// 定义数据变量
	GPSPack* pack = new GPSPack();
	memset(pack, 0x00, sizeof(GPSPack));

	// 为数据包的包头和包类型赋值
	pack->GPS_NEMA_GPGSV.head = NEMA_HEAD_STANDAD;
	pack->GPS_NEMA_GPGSV.bodyType = NEMATYPE_STANDARD_GPGSV;

	// 定义解析数据时用到的变量	
	int itemCount;		// 当前解析的是第几项
	int itemLen;		// 当前解析项的长度
	int iLen = 0;		// 当前解析项从第几个字符开始读取
	
	//----------------------------------------------------------------------------
	// 可见卫星信息
	// $GPGSV,<1>,<2>,<3>,<4>,<5>,<6>,<7>,…<4>,<5>,<6>,<7>*hh<CR><LF>
	// 从第一项依次解析每个数据项
	//----------------------------------------------------------------------------
	for (itemCount = 1; itemCount <total; itemCount++)
	{
		// 设置每项从数据的第一个字符开始处理
		iLen = 0;
		// 并从数组中取出要解析的数据项
		CString* item = m_dataArray.GetAt(itemCount);

		// 开始逐项解析数据项
		switch (itemCount)
		{
		case 1:
			//------------------------------------------------------------------------------------------------
			//		<1> GSV语句的总数		
			CGPSPublic::ConvertToInt(pack->GPS_NEMA_GPGSV.body.total, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 2:
			//------------------------------------------------------------------------------------------------
			//		<2> 本句GSV的编号		
			CGPSPublic::ConvertToInt(pack->GPS_NEMA_GPGSV.body.no, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 3:
			//------------------------------------------------------------------------------------------------
			//		<3> 可见卫星的总数（00~12，前面的0也将被传输）
			itemLen = 2;
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_GPGSV.body.validsate, 
				item->Mid(iLen, itemLen));
			//------------------------------------------------------------------------------------------------
			break;	

		case 4:
		case 8:
		case 12:
		case 16:
			//------------------------------------------------------------------------------------------------
			//		<4> PRN码（伪随机噪声码）（01~32，前面的0也将被传输）			
			CGPSPublic::ConvertToInt(pack->GPS_NEMA_GPGSV.body.prn[(itemCount)/4-1], *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 5:
		case 9:
		case 13:
		case 17:
			//------------------------------------------------------------------------------------------------
			//		<5> 卫星仰角（00~90度，前面的0也将被传输）			
			CGPSPublic::ConvertToInt(pack->GPS_NEMA_GPGSV.body.yj[(itemCount-1)/4-1], *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 6:
		case 10:
		case 14:
		case 18:
			//------------------------------------------------------------------------------------------------
			//		<6> 卫星方位角（000~359度，前面的0也将被传输）
			CGPSPublic::ConvertToInt(pack->GPS_NEMA_GPGSV.body.fwj[(itemCount-2)/4-1], *item);
			//------------------------------------------------------------------------------------------------
			break;


		case 7:
		case 11:
		case 15:
		case 19:
			//------------------------------------------------------------------------------------------------
			//		<7> 信噪比（00~99dB，没有跟踪到卫星时为空，前面的0也将被传输）
			CGPSPublic::ConvertToInt(pack->GPS_NEMA_GPGSV.body.xzb[(itemCount-3)/4-1], *item);
			//------------------------------------------------------------------------------------------------
			break;		
		}		
	}

	// 设置数据包的数据尾和协议校验码开始符
	pack->GPS_NEMA_GPGSV.checkBegin = NEMA_CHECK_STANDAD;
	pack->GPS_NEMA_GPGSV.tail[0] = NEMA_TAIL_STANDAD_1;
	pack->GPS_NEMA_GPGSV.tail[1] = NEMA_TAIL_STANDAD_2;

	return pack;
}

///////////////////////////////////////////////////////////////////
// 函数名：	DecodeNEMA_GPRMC
// 功  能：	解码NEMA的GPGGA协议数据
// 参  数：	
// 返回值：	GPSPack*--解析后的协议数据包
// 备  注：	推荐定位信息
//////////////////////////////////////////////////////////////////
GPSPack* CDataFlow::DecodeNEMA_GPRMC()
{
	int total=14;

	// 判断当数据包中的数据项少于协议规定的15项时,返回
	if (m_dataArray.GetSize() < total) return NULL;

	// 定义数据变量
	GPSPack* pack = new GPSPack();
	memset(pack, 0x00, sizeof(GPSPack));

	// 为数据包的包头和包类型赋值
	pack->GPS_NEMA_GPRMC.head = NEMA_HEAD_STANDAD;
	pack->GPS_NEMA_GPRMC.bodyType = NEMATYPE_STANDARD_GPRMC;

	// 定义解析数据时用到的变量	
	int itemCount;		// 当前解析的是第几项
	int itemLen;		// 当前解析项的长度
	int iLen = 0;		// 当前解析项从第几个字符开始读取
	

	//----------------------------------------------------------------------------
	// 推荐定位信息
	// $GPRMC,<1>,<2>,<3>,<4>,<5>,<6>,<7>,<8>,<9>,<10>,<11>,<12>*hh<CR><LF>
	// 从第一项依次解析每个数据项
	//----------------------------------------------------------------------------
	for (itemCount = 1; itemCount <total; itemCount++)
	{
		// 设置每项从数据的第一个字符开始处理
		iLen = 0;
		// 并从数组中取出要解析的数据项
		CString* item = m_dataArray.GetAt(itemCount);

		// 开始逐项解析数据项
		switch (itemCount)
		{
		case 1:
			//----------------------------------------------------------------------------------------------
			// 时间部分		<1> UTC时间，hhmmss（时分秒）格式
			// 时                      2       UTC时, "00".."23"			
			itemLen = 2;
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_GPRMC.body.time.hour, 
				item->Mid(iLen, itemLen));	
				
			// 分                      2       UTC分, "00".."59"
			iLen += itemLen;
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_GPRMC.body.time.minute, 
				item->Mid(iLen, itemLen));

			// 秒                      2       UTC秒, "00".."59"
			iLen += itemLen;
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_GPRMC.body.time.second, 
				item->Mid(iLen, itemLen));
			//------------------------------------------------------------------------------------------------
			break;

		case 2:
			//------------------------------------------------------------------------------------------------
			// 定位状态		<2> 定位状态，A=有效定位，V=无效定位			
			itemLen = 1;
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_GPRMC.body.posvalid, 
				*item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 3:
			//------------------------------------------------------------------------------------------------
			// 纬度坐标		<3> 纬度ddmm.mmmm（度分）格式（前面的0也将被传输）			
			CGPSPublic::ConvertToLatitudeHavePoint(
				(double&)pack->GPS_NEMA_GPRMC.body.latitude.latitude, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 4:
			//------------------------------------------------------------------------------------------------
			// 纬度半球		<4> 纬度半球N（北半球）或S（南半球）			
			itemLen = 1;
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_GPRMC.body.latitudeType, 
				*item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 5:
			//------------------------------------------------------------------------------------------------
			// 经度坐标		<5> 经度dddmm.mmmm（度分）格式（前面的0也将被传输）			
			CGPSPublic::ConvertToLongitudeHavePoint(
				(double&)pack->GPS_NEMA_GPRMC.body.longitude.longitude, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 6:
			//------------------------------------------------------------------------------------------------
			// 经度半球		<6> 经度半球E（东经）或W（西经）			
			itemLen = 1;
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_GPRMC.body.longitudeType, 
				*item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 7:
			//------------------------------------------------------------------------------------------------
			// 速度			<7> 地面速率（000.0~999.9节，前面的0也将被传输）
			CGPSPublic::ConvertToDouble(pack->GPS_NEMA_GPRMC.body.volity, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 8:
			//------------------------------------------------------------------------------------------------
			// 方向			<8> 地面航向（000.0~359.9度，以真北为参考基准，前面的0也将被传输）		
			CGPSPublic::ConvertToDouble(pack->GPS_NEMA_GPRMC.body.direct, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 9:
			//----------------------------------------------------------------------------------------------
			// 日期部分		<9> UTC日期，ddmmyy（日月年）格式
			// 日                      2       UTC日, "01".."31"		
			itemLen = 2;
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_GPRMC.body.date.day, 
				item->Mid(iLen, itemLen));			
				
			// 月                      2       UTC月, "01".."12"
			iLen += itemLen;
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_GPRMC.body.date.month, 
				item->Mid(iLen, itemLen));

			// 年                      2       UTC年的最后两位数字
			iLen += itemLen;
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_GPRMC.body.date.year, 
				item->Mid(iLen, itemLen));
			pack->GPS_NEMA_GPRMC.body.date.year += 2000;
			//------------------------------------------------------------------------------------------------
			break;

		case 10:
			//------------------------------------------------------------------------------------------------
			// 磁偏角		<10> 磁偏角（000.0~180.0度，前面的0也将被传输）		
			CGPSPublic::ConvertToDouble(pack->GPS_NEMA_GPRMC.body.cpj, *item);
			//------------------------------------------------------------------------------------------------
			break;			


		case 11:
			//------------------------------------------------------------------------------------------------
			// 磁偏角方向	<11> 磁偏角方向，E（东）或W（西）
			itemLen = 1;
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_GPRMC.body.cpjdirect, 
				*item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 12:
			//------------------------------------------------------------------------------------------------
			// 模式			<12> 模式指示（仅NMEA0183 3.00版本输出，A=自主定位，D=差分，E=估算，N=数据无效）
			itemLen = 1;
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_GPRMC.body.mode, 
				*item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;
			
		case 13:
			//------------------------------------------------------------------------------------------------
			//hh校验码
			itemLen = 2;			
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_GPRMC.check, 
				item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;
		}		
	}

	// 设置数据包的数据尾和协议校验码开始符
	pack->GPS_NEMA_GPRMC.checkBegin = NEMA_CHECK_STANDAD;
	pack->GPS_NEMA_GPRMC.tail[0] = NEMA_TAIL_STANDAD_1;
	pack->GPS_NEMA_GPRMC.tail[1] = NEMA_TAIL_STANDAD_2;

	return pack;
}


///////////////////////////////////////////////////////////////////
// 函数名：	DecodeNEMA_GPVTG
// 功  能：	解码NEMA的GPGGA协议数据
// 参  数：	
// 返回值：	GPSPack*--解析后的协议数据包
// 备  注：	地面速度信息
//////////////////////////////////////////////////////////////////
GPSPack* CDataFlow::DecodeNEMA_GPVTG()
{
	int total=11;

	// 判断当数据包中的数据项少于协议规定的15项时,返回
	if (m_dataArray.GetSize() < total) return NULL;

	// 定义数据变量
	GPSPack* pack = new GPSPack();
	memset(pack, 0x00, sizeof(GPSPack));

	// 为数据包的包头和包类型赋值
	pack->GPS_NEMA_GPVTG.head = NEMA_HEAD_STANDAD;
	pack->GPS_NEMA_GPVTG.bodyType = NEMATYPE_STANDARD_GPVTG;

	// 定义解析数据时用到的变量	
	int itemCount;		// 当前解析的是第几项
	int itemLen;		// 当前解析项的长度
	int iLen = 0;		// 当前解析项从第几个字符开始读取
	

	//----------------------------------------------------------------------------
	// 地面速度信息
	// $GPVTG,<1>,T,<2>,M,<3>,N,<4>,K,<5>*hh<CR><LF>
	// 从第一项依次解析每个数据项
	//----------------------------------------------------------------------------
	for (itemCount = 1; itemCount <total; itemCount++)
	{
		// 设置每项从数据的第一个字符开始处理
		iLen = 0;
		// 并从数组中取出要解析的数据项
		CString* item = m_dataArray.GetAt(itemCount);


		// 开始逐项解析数据项
		switch (itemCount)
		{
		
		case 1:
			//------------------------------------------------------------------------------------------------
			// 方向			<1> 以真北为参考基准的地面航向（000~359度，前面的0也将被传输）		
			CGPSPublic::ConvertToInt(pack->GPS_NEMA_GPVTG.body.directtn, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 3:
			//------------------------------------------------------------------------------------------------
			// 方向			<2> 以磁北为参考基准的地面航向（000~359度，前面的0也将被传输）	
			CGPSPublic::ConvertToInt(pack->GPS_NEMA_GPVTG.body.directcn, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 5:
			//------------------------------------------------------------------------------------------------
			// 速度			<3> 地面速率（000.0~999.9节，前面的0也将被传输）	
			CGPSPublic::ConvertToDouble(pack->GPS_NEMA_GPVTG.body.volityj, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 7:
			//------------------------------------------------------------------------------------------------
			// 方向			<4> 地面速率（0000.0~1851.8公里/小时，前面的0也将被传输）
			CGPSPublic::ConvertToDouble(pack->GPS_NEMA_GPVTG.body.volitykm, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 9:
			//------------------------------------------------------------------------------------------------
			// 模式			<5> 模式指示（仅NMEA0183 3.00版本输出，A=自主定位，D=差分，E=估算，N=数据无效）
			itemLen = 1;
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_GPVTG.body.mode, 
				*item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 10:
			//------------------------------------------------------------------------------------------------
			//hh校验码
			itemLen = 2;			
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_GPVTG.check, 
				item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;
		}			
	}

	// 设置数据包的数据尾和协议校验码开始符
	pack->GPS_NEMA_GPVTG.checkBegin = NEMA_CHECK_STANDAD;
	pack->GPS_NEMA_GPVTG.tail[0] = NEMA_TAIL_STANDAD_1;
	pack->GPS_NEMA_GPVTG.tail[1] = NEMA_TAIL_STANDAD_2;

	return pack;
}


///////////////////////////////////////////////////////////////////
// 函数名：	DecodeNEMA_GPGLL
// 功  能：	解码NEMA的GPGGA协议数据
// 参  数：	
// 返回值：	GPSPack*--解析后的协议数据包
// 备  注：	定位地理信息
///////////////////////////////////////////////////////////////////
GPSPack* CDataFlow::DecodeNEMA_GPGLL()
{
	int total=9;

	// 判断当数据包中的数据项少于协议规定的15项时,返回
	if (m_dataArray.GetSize() < total) return NULL;

	// 定义数据变量
	GPSPack* pack = new GPSPack();
	memset(pack, 0x00, sizeof(GPSPack));

	// 为数据包的包头和包类型赋值
	pack->GPS_NEMA_GPGLL.head = NEMA_HEAD_STANDAD;
	pack->GPS_NEMA_GPGLL.bodyType = NEMATYPE_STANDARD_GPGLL;

	// 定义解析数据时用到的变量	
	int itemCount;		// 当前解析的是第几项
	int itemLen;		// 当前解析项的长度
	int iLen = 0;		// 当前解析项从第几个字符开始读取
	

	//----------------------------------------------------------------------------
	// 定位地理信息
	// $GPGLL,<1>,<2>,<3>,<4>,<5>,<6>,<7>*hh<CR><LF>
	// 从第一项依次解析每个数据项
	//----------------------------------------------------------------------------
	for (itemCount = 1; itemCount <total; itemCount++)
	{
		// 设置每项从数据的第一个字符开始处理
		iLen = 0;
		// 并从数组中取出要解析的数据项
		CString* item = m_dataArray.GetAt(itemCount);

		// 开始逐项解析数据项
		switch (itemCount)
		{
		case 1:
			//------------------------------------------------------------------------------------------------
			// 纬度坐标		<1> 纬度ddmm.mmmm（度分）格式（前面的0也将被传输）		
			CGPSPublic::ConvertToLatitudeHavePoint(
				(double&)pack->GPS_NEMA_GPGLL.body.latitude.latitude, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 2:
			//------------------------------------------------------------------------------------------------
			// 纬度半球		<2> 纬度半球N（北半球）或S（南半球）		
			itemLen = 1;
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_GPGLL.body.latitudeType, 
				*item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 3:
			//------------------------------------------------------------------------------------------------
			// 经度坐标		<3> 经度dddmm.mmmm（度分）格式（前面的0也将被传输）		
			CGPSPublic::ConvertToLongitudeHavePoint(
				(double&)pack->GPS_NEMA_GPGLL.body.longitude.longitude, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 4:
			//------------------------------------------------------------------------------------------------
			// 经度半球		<4> 经度半球E（东经）或W（西经）			
			itemLen = 1;
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_GPGLL.body.longitudeType, 
				*item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 5:
			//----------------------------------------------------------------------------------------------
			// 时间部分		<5> UTC时间，hhmmss（时分秒）格式
			// 时                      2       UTC时, "00".."23"			
			itemLen = 2;
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_GPGLL.body.time.hour, 
				item->Mid(iLen, itemLen));	
				
			// 分                      2       UTC分, "00".."59"
			iLen += itemLen;
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_GPGLL.body.time.minute, 
				item->Mid(iLen, itemLen));

			// 秒                      2       UTC秒, "00".."59"
			iLen += itemLen;
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_GPGLL.body.time.second, 
				item->Mid(iLen, itemLen));
			//------------------------------------------------------------------------------------------------
			break;

		case 6:
			//------------------------------------------------------------------------------------------------
			// 定位状态		<6> 定位状态，A=有效定位，V=无效定位			
			itemLen = 1;
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_GPGLL.body.posvalid, 
				*item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;
		
		case 7:
			//------------------------------------------------------------------------------------------------
			// 模式			<7> 模式指示（仅NMEA0183 3.00版本输出，A=自主定位，D=差分，E=估算，N=数据无效
			itemLen = 1;
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_GPGLL.body.mode, 
				*item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;
			
		case 8:
			//------------------------------------------------------------------------------------------------
			//hh校验码
			itemLen = 2;			
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_GPGLL.check, 
				item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;
		}		
	}

	// 设置数据包的数据尾和协议校验码开始符
	pack->GPS_NEMA_GPGLL.checkBegin = NEMA_CHECK_STANDAD;
	pack->GPS_NEMA_GPGLL.tail[0] = NEMA_TAIL_STANDAD_1;
	pack->GPS_NEMA_GPGLL.tail[1] = NEMA_TAIL_STANDAD_2;

	return pack;

}


///////////////////////////////////////////////////////////////////
// 函数名：	DecodeNEMA_GPZDA
// 功  能：	解码NEMA的GPZDA协议数据
// 参  数：	
// 返回值：	GPSPack*--解析后的协议数据包
// 备  注：	时间和日期信息
///////////////////////////////////////////////////////////////////
GPSPack* CDataFlow::DecodeNEMA_GPZDA()
{
	int total=6;

	// 判断当数据包中的数据项少于协议规定的15项时,返回
	if (m_dataArray.GetSize() < total) return NULL;

	// 定义数据变量
	GPSPack* pack = new GPSPack();
	memset(pack, 0x00, sizeof(GPSPack));

	// 为数据包的包头和包类型赋值
	pack->GPS_NEMA_GPZDA.head = NEMA_HEAD_STANDAD;
	pack->GPS_NEMA_GPZDA.bodyType = NEMATYPE_STANDARD_GPZDA;

	// 定义解析数据时用到的变量	
	int itemCount;		// 当前解析的是第几项
	int itemLen;		// 当前解析项的长度
	int iLen = 0;		// 当前解析项从第几个字符开始读取
	

	//----------------------------------------------------------------------------
	// 时间和日期信息
	// $GPZDA,<1>,<2>,<3>,<4>*hh<CR><LF>
	// 从第一项依次解析每个数据项
	//----------------------------------------------------------------------------
	for (itemCount = 1; itemCount <total; itemCount++)
	{
		// 设置每项从数据的第一个字符开始处理
		iLen = 0;
		// 并从数组中取出要解析的数据项
		CString* item = m_dataArray.GetAt(itemCount);

		// 开始逐项解析数据项
		switch (itemCount)
		{
		case 1:
			//----------------------------------------------------------------------------------------------
			// 时间部分		<1> UTC时间，hhmmss（时分秒）格式
			// 时                      2       UTC时, "00".."23"			
			itemLen = 2;
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_GPZDA.body.time.hour, 
				item->Mid(iLen, itemLen));	
				
			// 分                      2       UTC分, "00".."59"
			iLen += itemLen;
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_GPZDA.body.time.minute, 
				item->Mid(iLen, itemLen));

			// 秒                      2       UTC秒, "00".."59"
			iLen += itemLen;
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_GPZDA.body.time.second, 
				item->Mid(iLen, itemLen));
			//------------------------------------------------------------------------------------------------
			break;

		case 2:
			//----------------------------------------------------------------------------------------------
			// 日			<2> UTC日期，日			
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_GPZDA.body.date.day, *item);	
			//------------------------------------------------------------------------------------------------
			break;

		case 3:
			//----------------------------------------------------------------------------------------------
			// 月			<3> UTC日期，月		
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_GPZDA.body.date.month, *item);	
			//------------------------------------------------------------------------------------------------
			break;

		case 4:
			//----------------------------------------------------------------------------------------------
			// 年			<4> UTC日期，年	
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_GPZDA.body.date.year, *item);	
			//------------------------------------------------------------------------------------------------
			break;
		
		case 5:
			//------------------------------------------------------------------------------------------------
			//hh校验码
			itemLen = 2;			
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_GPZDA.check, 
				item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;
		}		
	}

	// 设置数据包的数据尾和协议校验码开始符
	pack->GPS_NEMA_GPZDA.checkBegin = NEMA_CHECK_STANDAD;
	pack->GPS_NEMA_GPZDA.tail[0] = NEMA_TAIL_STANDAD_1;
	pack->GPS_NEMA_GPZDA.tail[1] = NEMA_TAIL_STANDAD_2;

	return pack;
}

///////////////////////////////////////////////////////////////////
// 函数名：	DecodeNEMA_GPDTM
// 功  能：	解码NEMA的GPDTM协议数据
// 参  数：	
// 返回值：	GPSPack*--解析后的协议数据包
// 备  注：	大地坐标系信息
///////////////////////////////////////////////////////////////////
GPSPack* CDataFlow::DecodeNEMA_GPDTM()
{
	int total=10;

	// 判断当数据包中的数据项少于协议规定的15项时,返回
	if (m_dataArray.GetSize() < total) return NULL;

	// 定义数据变量
	GPSPack* pack = new GPSPack();
	memset(pack, 0x00, sizeof(GPSPack));

	// 为数据包的包头和包类型赋值
	pack->GPS_NEMA_GPDTM.head = NEMA_HEAD_STANDAD;
	pack->GPS_NEMA_GPDTM.bodyType = NEMATYPE_STANDARD_GPDTM;

	// 定义解析数据时用到的变量	
	int itemCount;		// 当前解析的是第几项
	int itemLen;		// 当前解析项的长度
	int iLen = 0;		// 当前解析项从第几个字符开始读取
	

	//----------------------------------------------------------------------------
	// 大地坐标系信息
	// $GPDTM,<1>,<2>,<3>,<4>,<5>,<6>,<7>,<8>*hh<CR><LF>
	// 从第一项依次解析每个数据项
	//----------------------------------------------------------------------------
	for (itemCount = 1; itemCount <total; itemCount++)
	{
		// 设置每项从数据的第一个字符开始处理
		iLen = 0;
		// 并从数组中取出要解析的数据项
		CString* item = m_dataArray.GetAt(itemCount);

		// 开始逐项解析数据项
		switch (itemCount)
		{
		case 1:
			//------------------------------------------------------------------------------------------------
			// 坐标系		<1>本地坐标系代码 W84	
			itemLen = item->GetLength();
			pack->GPS_NEMA_GPDTM.body.localdatum = new char[itemLen+1];
			memset(pack->GPS_NEMA_GPDTM.body.localdatum, 0x00, itemLen+1);
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_GPDTM.body.localdatum[0], 
				item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 2:
			//------------------------------------------------------------------------------------------------
			// 子代码		<2>坐标系子代码 空		
			itemLen = item->GetLength();
			pack->GPS_NEMA_GPDTM.body.subdatum = new char[itemLen+1];
			memset(pack->GPS_NEMA_GPDTM.body.subdatum, 0x00, itemLen+1);
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_GPDTM.body.subdatum[0], 
				item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 3:
			//------------------------------------------------------------------------------------------------
			// 纬度偏移量	<3>纬度偏移量	
			CGPSPublic::ConvertToDouble(
				(double&)pack->GPS_NEMA_GPDTM.body.latitudeoffset, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 4:
			//------------------------------------------------------------------------------------------------
			// 纬度半球		<4>纬度半球N（北半球）或S（南半球）	
			itemLen = 1;
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_GPDTM.body.latitudetype, 
				*item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 5:
			//------------------------------------------------------------------------------------------------
			// 经度偏移量	<5>经度偏移量	
			CGPSPublic::ConvertToDouble(
				(double&)pack->GPS_NEMA_GPDTM.body.longitudeoffset, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 6:
			//------------------------------------------------------------------------------------------------
			// 经度半球		<6>经度半球E（东经）或W（西经）		
			itemLen = 1;
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_GPDTM.body.longitudetype, 
				*item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 7:
			//------------------------------------------------------------------------------------------------
			// 高度偏移量	<7>高度偏移量	
			CGPSPublic::ConvertToDouble(
				(double&)pack->GPS_NEMA_GPDTM.body.alitudeoffset, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 8:
			//------------------------------------------------------------------------------------------------
			// 坐标系		<8>坐标系代码 W84	
			itemLen = item->GetLength();
			pack->GPS_NEMA_GPDTM.body.datum = new char[itemLen+1];
			memset(pack->GPS_NEMA_GPDTM.body.datum, 0x00, itemLen+1);
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_GPDTM.body.datum[0], 
				item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;		
			
		case 9:
			//------------------------------------------------------------------------------------------------
			//hh校验码
			itemLen = 2;			
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_GPDTM.check, 
				item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;
		}		
	}

	// 设置数据包的数据尾和协议校验码开始符
	pack->GPS_NEMA_GPDTM.checkBegin = NEMA_CHECK_STANDAD;
	pack->GPS_NEMA_GPDTM.tail[0] = NEMA_TAIL_STANDAD_1;
	pack->GPS_NEMA_GPDTM.tail[1] = NEMA_TAIL_STANDAD_2;

	return pack;
}

//高明公司扩展协议


///////////////////////////////////////////////////////////////////
// 函数名：	DecodeNEMA_PGRME
// 功  能：	解码NEMA的PGRME协议数据
// 参  数：	
// 返回值：	GPSPack*--解析后的协议数据包
// 备  注：	估计误差信息
///////////////////////////////////////////////////////////////////
GPSPack* CDataFlow::DecodeNEMA_PGRME()
{
	int total=8;

	// 判断当数据包中的数据项少于协议规定的15项时,返回
	if (m_dataArray.GetSize() < total) return NULL;

	// 定义数据变量
	GPSPack* pack = new GPSPack();
	memset(pack, 0x00, sizeof(GPSPack));

	// 为数据包的包头和包类型赋值
	pack->GPS_NEMA_PGRME.head = NEMA_HEAD_STANDAD;
	pack->GPS_NEMA_PGRME.bodyType = NEMATYPE_GARMIN_PGRME;

	// 定义解析数据时用到的变量	
	int itemCount;		// 当前解析的是第几项
	int itemLen;		// 当前解析项的长度
	int iLen = 0;		// 当前解析项从第几个字符开始读取
	

	//----------------------------------------------------------------------------
	// 估计误差信息
	// $PGRME,<1>,M,<2>,M,<3>,M*hh<CR><LF>
	// 从第一项依次解析每个数据项
	//----------------------------------------------------------------------------
	for (itemCount = 1; itemCount <total; itemCount++)
	{
		// 设置每项从数据的第一个字符开始处理
		iLen = 0;
		// 并从数组中取出要解析的数据项
		CString* item = m_dataArray.GetAt(itemCount);

		// 开始逐项解析数据项
		switch (itemCount)
		{	
		case 1:
			//------------------------------------------------------------------------------------------------
			// 误差			<1> HPE（水平估计误差），0.0~999.9米
			CGPSPublic::ConvertToDouble(pack->GPS_NEMA_PGRME.body.hpe, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 3:
			//------------------------------------------------------------------------------------------------
			// 误差			<2> VPE（垂直估计误差），0.0~999.9米
			CGPSPublic::ConvertToDouble(pack->GPS_NEMA_PGRME.body.vpe, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 5:
			//------------------------------------------------------------------------------------------------
			// 误差			<3> EPE（位置估计误差），0.0~999.9米
			CGPSPublic::ConvertToDouble(pack->GPS_NEMA_PGRME.body.epe, *item);
			//------------------------------------------------------------------------------------------------
			break;			
			
		case 7:
			//------------------------------------------------------------------------------------------------
			//hh校验码
			itemLen = 2;			
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_PGRME.check, 
				item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;
		}		
	}

	// 设置数据包的数据尾和协议校验码开始符
	pack->GPS_NEMA_PGRME.checkBegin = NEMA_CHECK_STANDAD;
	pack->GPS_NEMA_PGRME.tail[0] = NEMA_TAIL_STANDAD_1;
	pack->GPS_NEMA_PGRME.tail[1] = NEMA_TAIL_STANDAD_2;

	return pack;
}


///////////////////////////////////////////////////////////////////
// 函数名：	DecodeNEMA_PGRMF
// 功  能：	解码NEMA的PGRMF协议数据
// 参  数：	
// 返回值：	GPSPack*--解析后的协议数据包
// 备  注：	高明公司GPS定位信息
//////////////////////////////////////////////////////////////////
GPSPack* CDataFlow::DecodeNEMA_PGRMF()
{
	int total=17;

	// 判断当数据包中的数据项少于协议规定的15项时,返回
	if (m_dataArray.GetSize() < total) return NULL;

	// 定义数据变量
	GPSPack* pack = new GPSPack();
	memset(pack, 0x00, sizeof(GPSPack));

	// 为数据包的包头和包类型赋值
	pack->GPS_NEMA_PGRMF.head = NEMA_HEAD_STANDAD;
	pack->GPS_NEMA_PGRMF.bodyType = NEMATYPE_GARMIN_PGRMF;

	// 定义解析数据时用到的变量	
	int itemCount;		// 当前解析的是第几项
	int itemLen;		// 当前解析项的长度
	int iLen = 0;		// 当前解析项从第几个字符开始读取
	

	//----------------------------------------------------------------------------
	// GPS定位信息
	// $PGRMF,<1>,<2>,<3>,<4>,<5>,<6>,<7>,<8>,<9>,<10>,<11>,<12>,<13>,<14>,<15>*hh<CR><LF>
	// 从第一项依次解析每个数据项
	//----------------------------------------------------------------------------
	for (itemCount = 1; itemCount <total; itemCount++)
	{
		// 设置每项从数据的第一个字符开始处理
		iLen = 0;
		// 并从数组中取出要解析的数据项
		CString* item = m_dataArray.GetAt(itemCount);

		// 开始逐项解析数据项
		switch (itemCount)
		{
		case 1:
			//----------------------------------------------------------------------------------------------
			// GPS周数		<1> GPS周数（0~1023）	
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_PGRMF.body.gpscircle, *item);	
			//------------------------------------------------------------------------------------------------
			break;

		case 2:
			//----------------------------------------------------------------------------------------------
			// GPS秒数		<2> GPS秒数（0~604799）	
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_PGRMF.body.gpssecond, *item);	
			//------------------------------------------------------------------------------------------------
			break;

		case 3:
			//----------------------------------------------------------------------------------------------
			// 日期部分		<3> UTC日期，ddmmyy（日月年）格式
			// 日                      2       UTC日, "01".."31"				
			itemLen = 2;
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_PGRMF.body.date.day, 
				item->Mid(iLen, itemLen));	
				
			// 月                      2       UTC月, "01".."12"
			iLen += itemLen;
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_PGRMF.body.date.month, 
				item->Mid(iLen, itemLen));

			// 年                      2       UTC年的最后两位数字
			iLen += itemLen;
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_PGRMF.body.date.year, 
				item->Mid(iLen, itemLen));
			pack->GPS_NEMA_PGRMF.body.date.year += 2000;
			//------------------------------------------------------------------------------------------------
			break;

		case 4:
			//----------------------------------------------------------------------------------------------
			// 时间部分		<4> UTC时间，hhmmss（时分秒）格式
			// 时                      2       UTC时, "00".."23"
			itemLen = 2;
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_PGRMF.body.time.hour, 
				item->Mid(iLen, itemLen));	
				
			// 分                      2       UTC分, "00".."59"
			iLen += itemLen;
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_PGRMF.body.time.minute, 
				item->Mid(iLen, itemLen));

			// 秒                      2       UTC秒, "00".."59"
			iLen += itemLen;
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_PGRMF.body.time.second, 
				item->Mid(iLen, itemLen));
			//------------------------------------------------------------------------------------------------
			break;

		case 5:
			//----------------------------------------------------------------------------------------------
			// GPS跳秒数	<5> GPS跳秒数
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_PGRMF.body.gpsjump, *item);	
			//------------------------------------------------------------------------------------------------
			break;

		case 6:
			//------------------------------------------------------------------------------------------------
			// 纬度坐标		<6> 纬度ddmm.mmmm（度分）格式（前面的0也将被传输）		
			CGPSPublic::ConvertToLatitudeHavePoint(
				(double&)pack->GPS_NEMA_PGRMF.body.latitude.latitude, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 7:
			//------------------------------------------------------------------------------------------------
			// 纬度半球		<7> 纬度半球N（北半球）或S（南半球）			
			itemLen = 1;
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_PGRMF.body.latitudeType, 
				*item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 8:
			//------------------------------------------------------------------------------------------------
			// 经度坐标		<8> 经度dddmm.mmmm（度分）格式（前面的0也将被传输）			
			CGPSPublic::ConvertToLongitudeHavePoint(
				(double&)pack->GPS_NEMA_PGRMF.body.longitude.longitude, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 9:
			//------------------------------------------------------------------------------------------------
			// 经度半球		<9> 经度半球E（东经）或W（西经）			
			itemLen = 1;
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_PGRMF.body.longitudeType, 
				*item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;


		case 10:
			//------------------------------------------------------------------------------------------------
			// 定位状态		<10> 模式，M=手动，A=自动			
			itemLen = 1;
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_PGRMF.body.gpsmode, 
				*item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 11:
			//------------------------------------------------------------------------------------------------
			// 定位类型		<11> 定位类型，0=没有定位，1=2D定位，2=3D定位		
			itemLen = 1;
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_PGRMF.body.postype, 
				*item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 12:
			//------------------------------------------------------------------------------------------------
			// 速度			<12> 地面速率（0~1851公里/小时）
			CGPSPublic::ConvertToInt(pack->GPS_NEMA_PGRMF.body.volity, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 13:
			//------------------------------------------------------------------------------------------------
			// 方向			<13> 地面航向（000~359度，以真北为参考基准）		
			CGPSPublic::ConvertToInt(pack->GPS_NEMA_PGRMF.body.direct, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 14:
			//------------------------------------------------------------------------------------------------
			// PDOP			<14> PDOP位置精度因子（0~9，四舍五入取整）	
			CGPSPublic::ConvertToInt(pack->GPS_NEMA_PGRMF.body.pdop, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 15:
			//------------------------------------------------------------------------------------------------
			// TDOP			<15> TDOP时间精度因子（0~9，四舍五入取整）	
			CGPSPublic::ConvertToInt(pack->GPS_NEMA_PGRMF.body.tdop, *item);
			//------------------------------------------------------------------------------------------------
			break;		
			
		case 16:
			//------------------------------------------------------------------------------------------------
			//hh校验码
			itemLen = 2;			
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_PGRMF.check, 
				item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;
		}		
	}

	// 设置数据包的数据尾和协议校验码开始符
	pack->GPS_NEMA_PGRMF.checkBegin = NEMA_CHECK_STANDAD;
	pack->GPS_NEMA_PGRMF.tail[0] = NEMA_TAIL_STANDAD_1;
	pack->GPS_NEMA_PGRMF.tail[1] = NEMA_TAIL_STANDAD_2;

	return pack;
}

///////////////////////////////////////////////////////////////////
// 函数名：	DecodeNEMA_PGRMM
// 功  能：	解码NEMA的PGRMM协议数据
// 参  数：	
// 返回值：	GPSPack*--解析后的协议数据包
// 备  注：	高明公司坐标系统信息
///////////////////////////////////////////////////////////////////
GPSPack* CDataFlow::DecodeNEMA_PGRMM()
{
	int total=3;

	// 判断当数据包中的数据项少于协议规定的15项时,返回
	if (m_dataArray.GetSize() < total) return NULL;

	// 定义数据变量
	GPSPack* pack = new GPSPack();
	memset(pack, 0x00, sizeof(GPSPack));

	// 为数据包的包头和包类型赋值
	pack->GPS_NEMA_PGRMM.head = NEMA_HEAD_STANDAD;
	pack->GPS_NEMA_PGRMM.bodyType = NEMATYPE_GARMIN_PGRMM;

	// 定义解析数据时用到的变量	
	int itemCount;		// 当前解析的是第几项
	int itemLen;		// 当前解析项的长度
	int iLen = 0;		// 当前解析项从第几个字符开始读取
	

	//----------------------------------------------------------------------------
	// 坐标系统信息
	// $PGRMM,<1>*hh<CR><LF>
	// 从第一项依次解析每个数据项
	//----------------------------------------------------------------------------
	for (itemCount = 1; itemCount <total; itemCount++)
	{
		// 设置每项从数据的第一个字符开始处理
		iLen = 0;
		// 并从数组中取出要解析的数据项
		CString* item = m_dataArray.GetAt(itemCount);

		// 开始逐项解析数据项
		switch (itemCount)
		{	
		case 1:
			//------------------------------------------------------------------------------------------------
			//坐标系名称	<1> 当前使用的坐标系名称（数据长度可变，如“WGS 84”在与MapSource进行实时连接的时候使用。）
			itemLen = item->GetLength();	
			pack->GPS_NEMA_PGRMM.body.dwLen = itemLen;
			pack->GPS_NEMA_PGRMM.body.datum = new char[itemLen+1];
			memset(pack->GPS_NEMA_PGRMM.body.datum, 0x00, itemLen+1);
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_PGRMM.body.datum[0], 
				item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;
		
		case 2:
			//------------------------------------------------------------------------------------------------
			//hh校验码
			itemLen = 2;			
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_PGRMM.check, 
				item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;
		}		
	}

	// 设置数据包的数据尾和协议校验码开始符
	pack->GPS_NEMA_PGRMM.checkBegin = NEMA_CHECK_STANDAD;
	pack->GPS_NEMA_PGRMM.tail[0] = NEMA_TAIL_STANDAD_1;
	pack->GPS_NEMA_PGRMM.tail[1] = NEMA_TAIL_STANDAD_2;

	return pack;
}


///////////////////////////////////////////////////////////////////
// 函数名：	DecodeNEMA_PGRMT
// 功  能：	解码NEMA的PGRMT协议数据
// 参  数：	
// 返回值：	GPSPack*--解析后的协议数据包
// 备  注：	高明公司工作状态信息
///////////////////////////////////////////////////////////////////
GPSPack* CDataFlow::DecodeNEMA_PGRMT()
{
	int total=11;

	// 判断当数据包中的数据项少于协议规定的15项时,返回
	if (m_dataArray.GetSize() < total) return NULL;

	// 定义数据变量
	GPSPack* pack = new GPSPack();
	memset(pack, 0x00, sizeof(GPSPack));

	// 为数据包的包头和包类型赋值
	pack->GPS_NEMA_PGRMT.head = NEMA_HEAD_STANDAD;
	pack->GPS_NEMA_PGRMT.bodyType = NEMATYPE_GARMIN_PGRMT;

	// 定义解析数据时用到的变量	
	int itemCount;		// 当前解析的是第几项
	int itemLen;		// 当前解析项的长度
	int iLen = 0;		// 当前解析项从第几个字符开始读取
	

	//----------------------------------------------------------------------------
	// 工作状态信息
	// $PGRMT,<1>,<2>,<3>,<4>,<5>,<6>,<7>,<8>,<9>*hh<CR><LF>
	// 从第一项依次解析每个数据项
	//----------------------------------------------------------------------------
	for (itemCount = 1; itemCount <total; itemCount++)
	{
		// 设置每项从数据的第一个字符开始处理
		iLen = 0;
		// 并从数组中取出要解析的数据项
		CString* item = m_dataArray.GetAt(itemCount);

		// 开始逐项解析数据项
		switch (itemCount)
		{	
		case 1:
			//------------------------------------------------------------------------------------------------
			//	<1> 产品型号和软件版本（数据长度可变，如“GPS 15L/15H VER 2.05”）
			itemLen = item->GetLength();
			pack->GPS_NEMA_PGRMT.body.dwLen = itemLen;
			pack->GPS_NEMA_PGRMT.body.version = new char[itemLen+1];
			memset(pack->GPS_NEMA_PGRMT.body.version, 0x00, itemLen+1);
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_PGRMT.body.version[0], 
				item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 2:
			//------------------------------------------------------------------------------------------------
			//	<2> ROM校验测试，P=通过，F=失败
			itemLen = 1;			
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_PGRMT.body.romcheck, 
				item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 3:
			//------------------------------------------------------------------------------------------------
			//	<3> 接收机不连续故障，P=通过，F=失败
			itemLen = 1;			
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_PGRMT.body.fault, 
				item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 4:
			//------------------------------------------------------------------------------------------------
			//	<4> 存储的数据，R=保持，L=丢失
			itemLen = 1;			
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_PGRMT.body.storedata, 
				item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 5:
			//------------------------------------------------------------------------------------------------
			//	<5> 时钟的信息，R=保持，L=丢失
			itemLen = 1;			
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_PGRMT.body.clock, 
				item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 6:
			//------------------------------------------------------------------------------------------------
			//	<6> 振荡器不连续漂移，P=通过，F=检测到过度漂移
			itemLen = 1;			
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_PGRMT.body.piaoyi, 
				item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 7:
			//------------------------------------------------------------------------------------------------
			//	<7> 数据不连续采集，C=正在采集，如果没有采集则为空
			itemLen = 1;			
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_PGRMT.body.datacollect, 
				item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 8:
			//------------------------------------------------------------------------------------------------
			//	<8> GPS接收机温度，单位为摄氏度
			CGPSPublic::ConvertToDouble(pack->GPS_NEMA_PGRMT.body.temperature, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 9:
			//------------------------------------------------------------------------------------------------
			//	<9> GPS接收机配置数据，R=保持，L=丢失
			itemLen = 1;			
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_PGRMT.body.configdata, 
				item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;
		
		case 10:
			//------------------------------------------------------------------------------------------------
			//hh校验码
			itemLen = 2;			
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_PGRMT.check, 
				item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;
		}		
	}

	// 设置数据包的数据尾和协议校验码开始符
	pack->GPS_NEMA_PGRMT.checkBegin = NEMA_CHECK_STANDAD;
	pack->GPS_NEMA_PGRMT.tail[0] = NEMA_TAIL_STANDAD_1;
	pack->GPS_NEMA_PGRMT.tail[1] = NEMA_TAIL_STANDAD_2;

	return pack;
}


///////////////////////////////////////////////////////////////////
// 函数名：	DecodeNEMA_PGRMV
// 功  能：	解码NEMA的PGRMV协议数据
// 参  数：	
// 返回值：	GPSPack*--解析后的协议数据包
// 备  注：	高明公司三维速度信息
///////////////////////////////////////////////////////////////////
GPSPack* CDataFlow::DecodeNEMA_PGRMV()
{
	int total=5;

	// 判断当数据包中的数据项少于协议规定的15项时,返回
	if (m_dataArray.GetSize() < total) return NULL;

	// 定义数据变量
	GPSPack* pack = new GPSPack();
	memset(pack, 0x00, sizeof(GPSPack));

	// 为数据包的包头和包类型赋值
	pack->GPS_NEMA_PGRMV.head = NEMA_HEAD_STANDAD;
	pack->GPS_NEMA_PGRMV.bodyType = NEMATYPE_GARMIN_PGRMV;

	// 定义解析数据时用到的变量	
	int itemCount;		// 当前解析的是第几项
	int itemLen;		// 当前解析项的长度
	int iLen = 0;		// 当前解析项从第几个字符开始读取
	

	//----------------------------------------------------------------------------
	// 三维速度信息
	// $PGRMV,<1>,<2>,<3>*hh<CR><LF>
	// 从第一项依次解析每个数据项
	//----------------------------------------------------------------------------
	for (itemCount = 1; itemCount <total; itemCount++)
	{
		// 设置每项从数据的第一个字符开始处理
		iLen = 0;
		// 并从数组中取出要解析的数据项
		CString* item = m_dataArray.GetAt(itemCount);

		// 开始逐项解析数据项
		switch (itemCount)
		{	
		case 1:
			//------------------------------------------------------------------------------------------------
			// 速度			<1> 东向速度，514.4~514.4米/秒
			CGPSPublic::ConvertToDouble(pack->GPS_NEMA_PGRMV.body.xVolity, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 2:
			//------------------------------------------------------------------------------------------------
			// 速度			<2> 北向速度，514.4~514.4米/秒
			CGPSPublic::ConvertToDouble(pack->GPS_NEMA_PGRMV.body.yVolity, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 3:
			//------------------------------------------------------------------------------------------------
			// 速度			<3> 上向速度，999.9~9999.9米/秒
			CGPSPublic::ConvertToDouble(pack->GPS_NEMA_PGRMV.body.zVolity, *item);
			//------------------------------------------------------------------------------------------------
			break;			
			
		case 4:
			//------------------------------------------------------------------------------------------------
			//hh校验码
			itemLen = 2;			
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_PGRMV.check, 
				item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;
		}		
	}

	// 设置数据包的数据尾和协议校验码开始符
	pack->GPS_NEMA_PGRMV.checkBegin = NEMA_CHECK_STANDAD;
	pack->GPS_NEMA_PGRMV.tail[0] = NEMA_TAIL_STANDAD_1;
	pack->GPS_NEMA_PGRMV.tail[1] = NEMA_TAIL_STANDAD_2;

	return pack;
}

///////////////////////////////////////////////////////////////////
// 函数名：	DecodeNEMA_PGRMB
// 功  能：	解码NEMA的PGRMB协议数据
// 参  数：	
// 返回值：	GPSPack*--解析后的协议数据包
// 备  注：	高明公司信标差分信息
///////////////////////////////////////////////////////////////////
GPSPack* CDataFlow::DecodeNEMA_PGRMB()
{
	int total=11;

	// 判断当数据包中的数据项少于协议规定的15项时,返回
	if (m_dataArray.GetSize() < total) return NULL;

	// 定义数据变量
	GPSPack* pack = new GPSPack();
	memset(pack, 0x00, sizeof(GPSPack));

	// 为数据包的包头和包类型赋值
	pack->GPS_NEMA_PGRMB.head = NEMA_HEAD_STANDAD;
	pack->GPS_NEMA_PGRMB.bodyType = NEMATYPE_GARMIN_PGRMB;

	// 定义解析数据时用到的变量	
	int itemCount;		// 当前解析的是第几项
	int itemLen;		// 当前解析项的长度
	int iLen = 0;		// 当前解析项从第几个字符开始读取
	

	//----------------------------------------------------------------------------
	// 信标差分信息
	// $PGRMB,<1>,<2>,<3>,<4>,<5>,K,<6>,<7>,<8>*hh<CR><LF>
	// 从第一项依次解析每个数据项
	//----------------------------------------------------------------------------
	for (itemCount = 1; itemCount <total; itemCount++)
	{
		// 设置每项从数据的第一个字符开始处理
		iLen = 0;
		// 并从数组中取出要解析的数据项
		CString* item = m_dataArray.GetAt(itemCount);

		// 开始逐项解析数据项
		switch (itemCount)
		{
		case 1:
			//----------------------------------------------------------------------------------------------
			// 频率			<1> 信标站频率（0.0，283.5~325.0kHz，间隔为0.5kHz）	
			CGPSPublic::ConvertToDouble((double&)pack->GPS_NEMA_PGRMB.body.freq, *item);	
			//------------------------------------------------------------------------------------------------
			break;

		case 2:
			//----------------------------------------------------------------------------------------------
			// 比特率		<2> 信标比特率（0，25，50，100或200bps）
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_PGRMB.body.banud, *item);	
			//------------------------------------------------------------------------------------------------
			break;	

		case 3:
			//----------------------------------------------------------------------------------------------
			// SNR			<3> SNR信标信号信噪比（0~31）
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_PGRMB.body.snr, *item);	
			//------------------------------------------------------------------------------------------------
			break;

		case 4:
			//------------------------------------------------------------------------------------------------
			// 数据质量		<4> 信标数据质量（0~100）	
			CGPSPublic::ConvertToInt((int&)pack->GPS_NEMA_PGRMB.body.quality, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 5:
			//------------------------------------------------------------------------------------------------
			// 距离			<5> 与信标站的距离，单位为公里
			CGPSPublic::ConvertToDouble((double&)pack->GPS_NEMA_PGRMB.body.distance, *item);
			//------------------------------------------------------------------------------------------------
			break;

		case 7:
			//------------------------------------------------------------------------------------------------
			// 通讯状态		<6> 信标接收机的通讯状态，0=检查接线，1=无信号，2=正在调谐，3=正在接收，4=正在扫描			
			itemLen = 1;
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_PGRMB.body.commstatu, 
				*item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 8:
			//------------------------------------------------------------------------------------------------
			// 差分源		<7> 差分源，R=RTCM，W=WAAS，N=非差分定位
			itemLen = 1;
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_PGRMB.body.source, 
				*item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;

		case 9:
			//------------------------------------------------------------------------------------------------
			// 差分状态		<8> 差分状态，A=自动，W=仅为WAAS，R=仅为RTCM，N=不接收差分信号
			itemLen = 1;
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_PGRMB.body.statu, 
				*item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;		
			
		case 10:
			//------------------------------------------------------------------------------------------------
			//hh校验码
			itemLen = 2;			
			CGPSPublic::ConvertToChar((char&)pack->GPS_NEMA_PGRMB.check, 
				item->Mid(iLen, itemLen), itemLen);
			//------------------------------------------------------------------------------------------------
			break;
		}		
	}

	// 设置数据包的数据尾和协议校验码开始符
	pack->GPS_NEMA_PGRMB.checkBegin = NEMA_CHECK_STANDAD;
	pack->GPS_NEMA_PGRMB.tail[0] = NEMA_TAIL_STANDAD_1;
	pack->GPS_NEMA_PGRMB.tail[1] = NEMA_TAIL_STANDAD_2;

	return pack;
}
	

///////////////////////////////////////////////////////////////////
// 函数名：	OnDecodeMsg
// 功  能：	解码NEMA协议数据
// 参  数：	DWORD dwEvent--数据包的数据缓冲区指针
//			DWORD dwLen--数据包的数据长度
// 返回值：	
// 备  注：	
//////////////////////////////////////////////////////////////////
void CDataFlow::OnDecodeMsg(DWORD dwData,DWORD dwLen)
{
	// 如果数据长度小于语句最小长度，则返回
	if (dwLen < MAX_NEMA_SENTENCE_MIN_LENGTH)	return;
	if (!dwData) return;

	GPSPack* pack=NULL;		// 解析后的数据包
	
	// 将协议数据放入数组中
	BYTE gramBytes[MAX_NEMA_SENTENCE_MAX_LENGTH+1];
	memset(gramBytes, 0x00, sizeof(gramBytes));
	memcpy((void*)gramBytes, (void*)dwData, dwLen);

	// 判断数据尾是否正确
	if ((gramBytes[dwLen-1] != NEMA_TAIL_STANDAD_2)
		&& (gramBytes[dwLen-2] != NEMA_TAIL_STANDAD_1))
	{
		return;
	}
	
	//--------------------------------------------------------------------
	// 处理NEMA文本格式的数据包
	if (gramBytes[0] == NEMA_HEAD_TEXT)
	{
		CString content;
		content = gramBytes;
		pack = DecodeNEMA_Text(content);
	}
	//---------------------------------------------------------------------
	//---------------------------------------------------------------------
	// 处理NEMA语句
	else if (gramBytes[0] == NEMA_HEAD_STANDAD)
	{
		// 判断逆数第五位是否为校验码，如果正确则将其取出
		if (gramBytes[dwLen-5] != NEMA_CHECK_STANDAD) return;
		CString* packCheck=new CString();
		packCheck->Format("%c%c", gramBytes[dwLen-4], gramBytes[dwLen-3]);

		// 将数据通过,分割成数组
		int check = 0;
		CString m_item;
		m_dataArray.RemoveAll();
		for (DWORD i = 0;i < dwLen-NEMA_TAIL_LENGTH;i++)
		{
			if (gramBytes[i] == NEMA_SPLIT)
			{
				CString* inArray = new CString();
				inArray->Format("%s", m_item);				
				m_item.Empty();
				m_dataArray.Add(inArray);						
			}
			else
			{
				m_item += gramBytes[i];
			}
			
			if ((i < dwLen - MAX_COM_COMMAND_TAIL_LENGTH)
				&& (i >0))
			{
				check ^= gramBytes[i];
			}
		}		

		CString* inLast = new CString();
		inLast->Format("%s", m_item);		
		m_dataArray.Add(inLast);	

		if (m_dataArray.GetSize() < 1) return;	
		
		// 校验数据，判断数据是否正确
		if (!CheckData(packCheck, check))	return;		

		// 将校验码添加到数据数组中
		m_dataArray.Add(packCheck);

		// 取出语句名
		CString type = *(CString*)m_dataArray.GetAt(0);	
		type = type.Mid(1);	

		//-----------------------------------------------------------------
		// 处理标准NEMA语句, 以$GP开头
		if ((gramBytes[1] == NEMA_STANDAD_HEAD_1)
		&& (gramBytes[2] == NEMA_STANDAD_HEAD_2))
		{				
			if (type == NEMA_STANDARD_GPGGA)	//非差分定位
			{
				pack = DecodeNEMA_GPGGA();
			}
			else if (type == NEMA_STANDARD_GPGSA) //当前卫星信息
			{
				pack = DecodeNEMA_GPGSA();
			}
			else if (type == NEMA_STANDARD_GPGSV) //可见卫星信息
			{
				pack = DecodeNEMA_GPGSV();
			}
			else if (type == NEMA_STANDARD_GPRMC) //推荐定位信息
			{
				pack = DecodeNEMA_GPRMC();
			}
			else if (type == NEMA_STANDARD_GPVTG) //地面速度信息
			{
				pack = DecodeNEMA_GPVTG();
			}
			else if (type == NEMA_STANDARD_GPGLL) //定位地理信息
			{
				pack = DecodeNEMA_GPGLL();
			}
			else if (type == NEMA_STANDARD_GPZDA) //时间和日期信息
			{
				pack = DecodeNEMA_GPZDA();
			}
			else if (type == NEMA_STANDARD_GPDTM) //大地坐标系信息
			{
				pack = DecodeNEMA_GPDTM();
			}
		}
		//----------------------------------------------------------------------
		//----------------------------------------------------------------------
		//高明公司的扩展协议
		else if ((gramBytes[1] == NEMA_GARMIN_HEAD_1)
		&& (gramBytes[2] == NEMA_GARMIN_HEAD_2)
		&& (gramBytes[3] == NEMA_GARMIN_HEAD_3)
		&& (gramBytes[4] == NEMA_GARMIN_HEAD_4))
		{
			if (type == NEMA_USER_GARMIN_PGRME) //估计误差信息
			{
				pack = DecodeNEMA_PGRME();
			}
			else if (type == NEMA_USER_GARMIN_PGRMF) //GPS定位信息
			{
				pack = DecodeNEMA_PGRMF();
			}
			else if (type == NEMA_USER_GARMIN_PGRMM) //坐标系统信息
			{
				pack = DecodeNEMA_PGRMM();
			}
			else if (type == NEMA_USER_GARMIN_PGRMT) //工作状态信息
			{
				pack = DecodeNEMA_PGRMT();
			}
			else if (type == NEMA_USER_GARMIN_PGRMV) //三维速度信息
			{
				pack = DecodeNEMA_PGRMV();
			}
			else if (type == NEMA_USER_GARMIN_PGRMB) //信标差分信息
			{
				pack = DecodeNEMA_PGRMB();
			}
		}
		//----------------------------------------------------------------------		
	}

	// 如果正确解析了数据，发送消息给框架，做处理，比如，记录、在地图上显示等等。
	if (pack != NULL)
	{
		::SendMessage(AfxGetApp()->GetMainWnd()->m_hWnd, WM_DECODED_NEMA_SENTENCE, (WPARAM)&m_Com, (LPARAM)pack);
	}
	//---------------------------------------------------------------------------
}

void CDataFlow::OnResponseMsg(DWORD wp,DWORD lp)
{
	return;
}


void CDataFlow::InitVariable()
{
	m_Com = "";
	m_dwToMeMsg=WM_COM_TO_DATA_FLOW;

	m_dwDataGramTail=0;
	m_dwDataGramHead=0;
	m_dwDataGramLen = 0;
	m_Data.RemoveAll();

	m_dwComEvent=0;		

	m_pReceEdit=NULL;
	m_pSendEdit=NULL;		
}

///////////////////////////////////////////////////////////////////
// 函数名：	CheckData
// 功  能：	判断校验码是否正确
// 参  数：	CString *check1--标准校验码
//			int check2--计算后的校验码 
// 返回值：	BOOL--校验码是否正确
// 备  注：	高明公司坐标系统信息
///////////////////////////////////////////////////////////////////
BOOL CDataFlow::CheckData(CString *check1, int check2)
{
	char c2=check2 & 0x0f; 
	char c1=(check2 >> 4) & 0x0f; 
	if (c1 < 10) c1+= '0'; else c1 += 'A' - 10; 
	if (c2 < 10) c2+= '0'; else c2 += 'A' - 10; 

	if ((c1 == check1->GetAt(0))
		&& (c2 == check1->GetAt(1)))
	{
		return TRUE;
	}

	return FALSE;
}
