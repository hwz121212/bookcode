
#define MAP_TEMPLATE_PATH					_T("Map51POI.html")			//地图模板文件名
/*通用常量定义*/
#define MAX_SQL_LENGTH						512			//SQL 语句的最大的长度
#define MAX_COM_OUT_LENGTH					1024		//串口发送的最大数据长度
#define MAX_COM_IN_LENGTH					1024		//串口接收缓冲区大小
#define MAX_COM_COMMAND_LENGTH				1024		//串口命令大小
#define MAX_COM_COMMAND_TAIL_LENGTH			5			//串口命令尾的长度
#define MAX_NEMA_SENTENCE_MAX_LENGTH		1024		//NEMA语句的最大长度
#define MAX_NEMA_SENTENCE_MIN_LENGTH		6 		    //NEMA语句的最小长度
#define MAX_COM_VIEW_LENGTH					10000		//串口视图长度


#define	MAX_SATE_TOTAL						12			//卫星总数
#define	MAX_SATE_ONE_TOTAL					4			//每条语句中包含的卫星数目

#define NEMA_TEXT_LENGTH					57			//NEMA的文本格式的长度
#define NEMA_COUNT							15			//NEMA的语句条数


#define	VIEW_LOG_COUNT						70			//定义日志列表框中最多的日志条数
#define	LOG_LEVEL_PROMPT					_T("提示")	//提示级别日志
#define	LOG_LEVEL_INFO						_T("信息")	//信息级别日志
#define	LOG_LEVEL_WARN						_T("警告")	//警告级别日志
#define	LOG_LEVEL_ERROR						_T("错误")	//错误级别日志


#define WM_COM_WORK_FLOW_LOG				WM_USER+7801	//串口开关消息
#define WM_COM_TO_DATA_FLOW					WM_USER+7802	//串口数据消息
#define WM_SEND_COM_DATA					WM_USER+7803	//发送串口消息
#define WM_SEND_COM_DATA_RESULT				WM_USER+7804	//发送串口数据消息的结果
#define WM_RECEIVE_COM_DATA					WM_USER+7805	//接收串口数据消息的结果
#define WM_DECODED_NEMA_SENTENCE			WM_USER+7806	//数据解析成功的消息


#define WM_INITCENTER						WM_USER+4704	//初始化串口应用
#define WM_DECODE_MSG						WM_USER+4477	//解码消息
#define	WM_RESPONSE_MSG						WM_USER+3000	//解码后的响应消息


/*默认串口参数配置*/
#define	COM_NAME							_T("COM1")	//默认串口为COM1
#define COM_BAUD_RATE						4800 
#define COM_DATA_BYTE_SIZE					8 
#define COM_PARITY							NOPARITY 
#define COM_STOP_BIT						ONESTOPBIT 


/*定时器定义*/
#define	EVENT_REFRESH_DATETIME				5
#define	EVENT_CHECK_SENDCOMDATA				12
#define	EVENT_INTERVAL_REFRESH_DATETIME		1000
#define	EVENT_INTERVAL_CHECK_SENDCOMDATA	1000



//语句类型
#define NEMA_STANDARD						1		//NEMA0183标准语句
#define NEMA_GARMIN							2		//NEMA0183高明语句
#define NEMA_TEXT							4		//NEMA0183文本语句

//NEMA协议头和尾定义
#define NEMA_HEAD_TEXT						'@'
#define NEMA_HEAD_STANDAD					'$'
#define NEMA_STANDAD_HEAD_1					'G'
#define NEMA_STANDAD_HEAD_2					'P'
#define NEMA_GARMIN_HEAD_1					'P'
#define NEMA_GARMIN_HEAD_2					'G'
#define NEMA_GARMIN_HEAD_3					'R'
#define NEMA_GARMIN_HEAD_4					'M'
#define NEMA_SPLIT							','
#define NEMA_CHECK_STANDAD					'*' 
#define NEMA_TAIL_STANDAD_1					'\x0D'
#define NEMA_TAIL_STANDAD_2					'\x0A'
#define NEMA_TAIL_LENGTH					5


//标准信息类型标识

//NEMA的标准语句
#define			NEMA_STANDARD_GPGGA		"GPGGA"			//GPS定位信息
#define			NEMA_STANDARD_GPGSA		"GPGSA"			//当前卫星信息
#define			NEMA_STANDARD_GPGSV		"GPGSV"			//可见卫星信息
#define			NEMA_STANDARD_GPRMC		"GPRMC"			//推荐定位信息
#define			NEMA_STANDARD_GPVTG		"GPVTG"			//地面速度信息
#define			NEMA_STANDARD_GPGLL		"GPGLL"			//定位地理信息
#define			NEMA_STANDARD_GPZDA		"GPZDA"			//时间和日期信息
#define			NEMA_STANDARD_GPDTM		"GPDTM"			//大地坐标系信息


//用户信息源头
#define NEMA_SOURCE_USER_1					'P'
//高明厂家的代码
#define NEMA_SOURCE_USER_GARMIN				'GRM'


//高明厂家的信息类型标识
#define NEMA_USER_GARMIN_PGRME				"PGRME"		//估计误差信息
#define NEMA_USER_GARMIN_PGRMF				"PGRMF"		//GPS定位信息
#define NEMA_USER_GARMIN_PGRMM				"PGRMM"		//坐标系统信息
#define NEMA_USER_GARMIN_PGRMT				"PGRMT"		//工作状态信息
#define NEMA_USER_GARMIN_PGRMV				"PGRMV"		//三维速度信息
#define NEMA_USER_GARMIN_PGRMB				"PGRMB"		//信标差分信息




//目前解析的NEMA语句
//NEMA的文本格式
enum enumNEMAType
{
	NEMATYPE_TEXT_POS = 0,			//文本格式
	NEMATYPE_STANDARD_GPGGA = 1,	//非差分定位
	NEMATYPE_STANDARD_GPGSA	= 2,	//当前卫星信息
	NEMATYPE_STANDARD_GPGSV	= 3,	//可见卫星信息
	NEMATYPE_STANDARD_GPRMC	= 4,	//推荐定位信息
	NEMATYPE_STANDARD_GPVTG	= 5,	//地面速度信息
	NEMATYPE_STANDARD_GPGLL	= 6,	//定位地理信息
	NEMATYPE_STANDARD_GPZDA	= 7,	//时间和日期信息
	NEMATYPE_STANDARD_GPDTM = 8,	//大地坐标系信息
	NEMATYPE_GARMIN_PGRME	= 9,	//估计误差信息
	NEMATYPE_GARMIN_PGRMF	= 10,	//GPS定位信息
	NEMATYPE_GARMIN_PGRMM	= 11,	//坐标系统信息
	NEMATYPE_GARMIN_PGRMT	= 12,	//工作状态信息
	NEMATYPE_GARMIN_PGRMV	= 13,	//三维速度信息
	NEMATYPE_GARMIN_PGRMB	= 14	//信标差分信息
};			



class CSendObject{
public:
	CSendObject()
	{
		memset(command,0,sizeof(command));
	}
	CString m_Com;
	char command[MAX_COM_COMMAND_LENGTH];
};


struct tagUTC_DATE
{
	int		year;		// 年
	int		month;		// 月
	int		day;			// 日
};		// UTC日期

struct tagUTC_TIME
{
	int		hour;		// 时
	int		minute;		// 分
	int		second;		// 秒
};		// UTC时间



struct	tagLatitude
{
	//char	degree[2];		// 纬度的度部分
	//char	minute[5];		// 纬度的分部分
	double latitude;
};		// 纬度

struct	tagLongitude
{
	//char	degree[3];		// 经度的度部分
	//char	minute[5];		// 经度的分部分
	double longitude;
};		// 经度

struct tagAlitude
{
	double altitude;
};		// 海拔



//NEMA的文本方式的数据体
struct tagBODY_NEMA_TEXT
{
	tagUTC_DATE			date;				//UTC日期
	tagUTC_TIME			time;				//UTC时间
	char				latitudeType;		//纬度半球
	tagLatitude			latitude;			//纬度坐标
	char				longitudeType;		//经度半球
	tagLongitude		longitude;			//经度坐标
	char				gpsStatus;			//定位状态
	double				hdop;				//水平定位误差	
	char				altitudeSymbol;		//高度符号
	tagAlitude			altitude;			//高度
	char				xDirect;			//东/西 速度方向
	double				xVolity;			//东/西速度
	char				yDirect;			//南/北 速度方向
	double				yVolity;			//南/北 速度
	char				zDirect;			//垂直速度方向
	double				zVolity;			//垂直速度		
};	

/*GPS定位信息
$GPGGA,<1>,<2>,<3>,<4>,<5>,<6>,<7>,<8>,<9>,M,<10>,M,<11>,<12>*hh<CR><LF>*/
struct tagBODY_NEMA_GPGGA
{
	tagUTC_TIME			time;				//<1> UTC时间，hhmmss（时分秒）格式
	tagLatitude			latitude;			//<2> 纬度ddmm.mmmm（度分）格式（前面的0也将被传输）
	char				latitudeType;		//<3> 纬度半球N（北半球）或S（南半球）
	tagLongitude		longitude;			//<4> 经度dddmm.mmmm（度分）格式（前面的0也将被传输）
	char				longitudeType;		//<5> 经度半球E（东经）或W（西经）
	char				gpsStatus;			//<6> GPS状态：0=未定位，1=非差分定位，2=差分定位，6=正在估算
	int					sateCount;			//<7> 正在使用解算位置的卫星数量（00~12）（前面的0也将被传输）
	double				hdop;				//<8> HDOP水平精度因子（0.5~99.9）
	tagAlitude			altitude;			//<9> 海拔高度（-9999.9~99999.9）
	double				height;				//<10> 地球椭球面相对大地水准面的高度
	int					diffSecond;			//<11> 差分时间（从最近一次接收到差分信号开始的秒数，如果不是差分定位将为空）
	char				diffStationID[4];	//<12> 差分站ID号0000~1023（前面的0也将被传输，如果不是差分定位将为空）		
};	

/*2、 GPS DOP and Active Satellites（GSA）当前卫星信息
$GPGSA,<1>,<2>,<3>,<3>,<3>,<3>,<3>,<3>,<3>,<3>,<3>,<3>,<3>,<3>,<4>,<5>,<6>*hh<CR><LF>*/
struct tagBODY_NEMA_GPGSA
{
	char				gpsmode;			//<1> 模式，M=手动，A=自动
	char				postype;			//<2> 定位类型，1=没有定位，2=2D定位，3=3D定位
	int					prn[MAX_SATE_TOTAL];			//<3> PRN码（伪随机噪声码），正在用于解算位置的卫星号（01~32，前面的0也将被传输）。
	double				pdop;				//<4> PDOP位置精度因子（0.5~99.9）
	double				hdop;				//<5> HDOP水平精度因子（0.5~99.9）
	double				vdop;				//<6> VDOP垂直精度因子（0.5~99.9）
};
	
/*3、 GPS Satellites in View（GSV）可见卫星信息
$GPGSV,<1>,<2>,<3>,<4>,<5>,<6>,<7>,…<4>,<5>,<6>,<7>*hh<CR><LF>
注：<4>,<5>,<6>,<7>信息将按照每颗卫星进行循环显示，每条GSV语句最多可以显示4颗卫星的信息。其他卫星信息将在下一序列的NMEA0183语句中输出。*/
struct tagBODY_NEMA_GPGSV
{
	int					total;				//<1> GSV语句的总数	
	int					no;					//<2> 本句GSV的编号
	int					validsate;			//<3> 可见卫星的总数（00~12，前面的0也将被传输）
	int					prn[MAX_SATE_ONE_TOTAL];				//<4> PRN码（伪随机噪声码）（01~32，前面的0也将被传输）
	int					yj[MAX_SATE_ONE_TOTAL];				//<5> 卫星仰角（00~90度，前面的0也将被传输）
	int					fwj[MAX_SATE_ONE_TOTAL];				//<6> 卫星方位角（000~359度，前面的0也将被传输）
	int					xzb[MAX_SATE_ONE_TOTAL];				//<7> 信噪比（00~99dB，没有跟踪到卫星时为空，前面的0也将被传输）
};

/*推荐定位信息
$GPRMC,<1>,<2>,<3>,<4>,<5>,<6>,<7>,<8>,<9>,<10>,<11>,<12>*hh<CR><LF>*/
struct tagBODY_NEMA_GPRMC
{
	tagUTC_TIME			time;				//<1> UTC时间，hhmmss（时分秒）格式
	char				posvalid;			//<2> 定位状态，A=有效定位，V=无效定位
	tagLatitude			latitude;			//<3> 纬度ddmm.mmmm（度分）格式（前面的0也将被传输）
	char				latitudeType;		//<4> 纬度半球N（北半球）或S（南半球）
	tagLongitude		longitude;			//<5> 经度dddmm.mmmm（度分）格式（前面的0也将被传输）
	char				longitudeType;		//<6> 经度半球E（东经）或W（西经）
	double				volity;				//<7> 地面速率（000.0~999.9节，前面的0也将被传输）
	double				direct;				//<8> 地面航向（000.0~359.9度，以真北为参考基准，前面的0也将被传输）
	tagUTC_DATE			date;				//<9> UTC日期，ddmmyy（日月年）格式
	double				cpj;				//<10> 磁偏角（000.0~180.0度，前面的0也将被传输）
	char				cpjdirect;			//<11> 磁偏角方向，E（东）或W（西）
	char				mode;				//<12> 模式指示（仅NMEA0183 3.00版本输出，A=自主定位，D=差分，E=估算，N=数据无效）
};

/*地面速度信息
$GPVTG,<1>,T,<2>,M,<3>,N,<4>,K,<5>*hh<CR><LF>*/
struct tagBODY_NEMA_GPVTG
{
	int					directtn;			//<1> 以真北为参考基准的地面航向（000~359度，前面的0也将被传输）
	int					directcn;			//<2> 以磁北为参考基准的地面航向（000~359度，前面的0也将被传输）
	double				volityj;			//<3> 地面速率（000.0~999.9节，前面的0也将被传输）
	double				volitykm;			//<4> 地面速率（0000.0~1851.8公里/小时，前面的0也将被传输）
	char				mode;				//<5> 模式指示（仅NMEA0183 3.00版本输出，A=自主定位，D=差分，E=估算，N=数据无效）
};

/*定位地理信息
$GPGLL,<1>,<2>,<3>,<4>,<5>,<6>,<7>*hh<CR><LF>*/
struct tagBODY_NEMA_GPGLL
{
	tagLatitude			latitude;			//<1> 纬度ddmm.mmmm（度分）格式（前面的0也将被传输）
	char				latitudeType;		//<2> 纬度半球N（北半球）或S（南半球）
	tagLongitude		longitude;			//<3> 经度dddmm.mmmm（度分）格式（前面的0也将被传输）
	char				longitudeType;		//<4> 经度半球E（东经）或W（西经）
	tagUTC_TIME			time;				//<5> UTC时间，hhmmss（时分秒）格式
	char				posvalid;			//<6> 定位状态，A=有效定位，V=无效定位
	char				mode;				//<7> 模式指示（仅NMEA0183 3.00版本输出，A=自主定位，D=差分，E=估算，N=数据无效）
};

/*时间和日期信息
$GPZDA,<1>,<2>,<3>,<4>*hh<CR><LF>*/
struct tagBODY_NEMA_GPZDA
{
	tagUTC_TIME			time;				//<1> UTC时间，hhmmss（时分秒）格式
	tagUTC_DATE			date;				//<2> UTC日期，日   <3> UTC日期，月  <4> UTC日期，年
};

/*大地坐标系信息
$GPDTM,<1>,<2>,<3>,<4>,<5>,<6>,<7>,<8>*hh<CR><LF>*/
struct tagBODY_NEMA_GPDTM
{
	char*				localdatum;			//<1>本地坐标系代码 W84
	char*				subdatum;			//<2>坐标系子代码 空
	double				latitudeoffset;		//<3>纬度偏移量
	char				latitudetype;		//<4>纬度半球N（北半球）或S（南半球）
	double				longitudeoffset;	//<5>经度偏移量
	char				longitudetype;		//<6>经度半球E（东经）或W（西经）
	double				alitudeoffset;		//<7>高度偏移量
	char*				datum;				//<8>坐标系代码 W84
};



//高明公司扩展协议
/*估计误差信息
$PGRME,<1>,M,<2>,M,<3>,M*hh<CR><LF>*/
struct tagBODY_NEMA_PGRME
{
	double				hpe;				//<1> HPE（水平估计误差），0.0~999.9米
	double				vpe;				//<2> VPE（垂直估计误差），0.0~999.9米
	double				epe;				//<3> EPE（位置估计误差），0.0~999.9米
};

/*GPS定位信息
$PGRMF,<1>,<2>,<3>,<4>,<5>,<6>,<7>,<8>,<9>,<10>,<11>,<12>,<13>,<14>,<15>*hh<CR><LF>*/
struct tagBODY_NEMA_PGRMF
{
	int					gpscircle;			//<1> GPS周数（0~1023）
	int					gpssecond;			//<2> GPS秒数（0~604799）
	tagUTC_DATE			date;				//<3> UTC日期，ddmmyy（日月年）格式
	tagUTC_TIME			time;				//<4> UTC时间，hhmmss（时分秒）格式
	double				gpsjump;			//<5> GPS跳秒数
	tagLatitude			latitude;			//<6> 纬度ddmm.mmmm（度分）格式（前面的0也将被传输）
	char				latitudeType;		//<7> 纬度半球N（北半球）或S（南半球）
	tagLongitude		longitude;			//<8> 经度dddmm.mmmm（度分）格式（前面的0也将被传输）
	char				longitudeType;		//<9> 经度半球E（东经）或W（西经）
	char				gpsmode;			//<10> 模式，M=手动，A=自动
	char				postype;			//<11> 定位类型，0=没有定位，1=2D定位，2=3D定位
	int					volity;				//<12> 地面速率（0~1851公里/小时）
	int					direct;				//<13> 地面航向（000~359度，以真北为参考基准）	
	int					pdop;				//<14> PDOP位置精度因子（0~9，四舍五入取整）
	int					tdop;				//<15> TDOP时间精度因子（0~9，四舍五入取整）
};

/*坐标系统信息
$PGRMM,<1>*hh<CR><LF>
注：该信息在与MapSource进行实时连接的时候使用。*/
struct tagBODY_NEMA_PGRMM
{
	char*				datum;				//<1> 当前使用的坐标系名称（数据长度可变，如“WGS 84”）
	int					dwLen;
};


/*工作状态信息
$PGRMT,<1>,<2>,<3>,<4>,<5>,<6>,<7>,<8>,<9>*hh<CR><LF>
注：本语句每分钟发送一次，与所选择的波特率无关。*/
struct tagBODY_NEMA_PGRMT
{
	char*				version;			//<1> 产品型号和软件版本（数据长度可变，如“GPS 15L/15H VER 2.05”）
	int					dwLen;				//<2> ROM校验测试，P=通过，F=失败
	char				romcheck;			//<3> 接收机不连续故障，P=通过，F=失败
	char				fault;				//<4> 存储的数据，R=保持，L=丢失
	char				storedata;			//<5> 时钟的信息，R=保持，L=丢失
	char				clock;				//<6> 振荡器不连续漂移，P=通过，F=检测到过度漂移
	char				piaoyi;				//<7> 数据不连续采集，C=正在采集，如果没有采集则为空
	char				datacollect;		//<8> GPS接收机温度，单位为摄氏度
	double				temperature;		//<9> GPS接收机配置数据，R=保持，L=丢失
	char				configdata;
};

/*三维速度信息
$PGRMV,<1>,<2>,<3>*hh<CR><LF>*/
struct tagBODY_NEMA_PGRMV
{
	double				xVolity;			//<1> 东向速度，514.4~514.4米/秒
	double				yVolity;			//<2> 北向速度，514.4~514.4米/秒
	double				zVolity;			//<3> 上向速度，999.9~9999.9米/秒
};


/*信标差分信息
$PGRMB,<1>,<2>,<3>,<4>,<5>,K,<6>,<7>,<8>*hh<CR><LF>*/
struct tagBODY_NEMA_PGRMB
{
	double				freq;				//<1> 信标站频率（0.0，283.5~325.0kHz，间隔为0.5kHz）
	int					banud;				//<2> 信标比特率（0，25，50，100或200bps）
	int					snr;				//<3> SNR信标信号信噪比（0~31）
	int					quality;			//<4> 信标数据质量（0~100）
	double				distance;			//<5> 与信标站的距离，单位为公里
	char				commstatu;			//<6> 信标接收机的通讯状态，0=检查接线，1=无信号，2=正在调谐，3=正在接收，4=正在扫描
	char				source;				//<7> 差分源，R=RTCM，W=WAAS，N=非差分定位
	char				statu;				//<8> 差分状态，A=自动，W=仅为WAAS，R=仅为RTCM，N=不接收差分信号
};

union GPSPack
{
	//NEMA的文本方式
	struct tagNEMA_TEXT
	{
		char					head;
		char					bodyType;
		tagBODY_NEMA_TEXT		body;		
		char					tail[2];
	}GPS_NEMA_TEXT;


	//GPS定位信息
	struct tagNEMA_GPGGA
	{
		char					head;
		char					bodyType;
		tagBODY_NEMA_GPGGA		body;	
		char					checkBegin;
		char					check[2];
		char					tail[2];
	}GPS_NEMA_GPGGA;

	//当前卫星信息
	struct tagNEMA_GPGSA
	{
		char					head;
		char					bodyType;
		tagBODY_NEMA_GPGSA		body;	
		char					checkBegin;
		char					check[2];
		char					tail[2];
	}GPS_NEMA_GPGSA;

	//可见卫星信息
	struct tagNEMA_GPGSV
	{
		char					head;
		char					bodyType;
		tagBODY_NEMA_GPGSV		body;	
		char					checkBegin;
		char					check[2];
		char					tail[2];
	}GPS_NEMA_GPGSV;

	//推荐定位信息
	struct tagNEMA_GPRMC
	{
		char					head;
		char					bodyType;
		tagBODY_NEMA_GPRMC		body;	
		char					checkBegin;
		char					check[2];
		char					tail[2];
	}GPS_NEMA_GPRMC;

	//地面速度信息
	struct tagNEMA_GPVTG
	{
		char					head;
		char					bodyType;
		tagBODY_NEMA_GPVTG		body;	
		char					checkBegin;
		char					check[2];
		char					tail[2];
	}GPS_NEMA_GPVTG;
	
	//定位地理信息
	struct tagNEMA_GPGLL
	{
		char					head;
		char					bodyType;
		tagBODY_NEMA_GPGLL		body;	
		char					checkBegin;
		char					check[2];
		char					tail[2];
	}GPS_NEMA_GPGLL;
	
	//时间和日期信息
	struct tagNEMA_GPZDA
	{
		char					head;
		char					bodyType;
		tagBODY_NEMA_GPZDA		body;	
		char					checkBegin;
		char					check[2];
		char					tail[2];
	}GPS_NEMA_GPZDA;

	//大地坐标系信息
	struct tagNEMA_GPDTM
	{
		char					head;
		char					bodyType;
		tagBODY_NEMA_GPDTM		body;	
		char					checkBegin;
		char					check[2];
		char					tail[2];
	}GPS_NEMA_GPDTM;


	//高明公司扩展协议

	//估计误差信息
	struct tagNEMA_PGRME
	{
		char					head;
		char					bodyType;
		tagBODY_NEMA_PGRME		body;	
		char					checkBegin;
		char					check[2];
		char					tail[2];
	}GPS_NEMA_PGRME;
	
	//GPS定位信息
	struct tagNEMA_PGRMF
	{
		char					head;
		char					bodyType;
		tagBODY_NEMA_PGRMF		body;	
		char					checkBegin;
		char					check[2];
		char					tail[2];
	}GPS_NEMA_PGRMF;

	//坐标系统信息
	struct tagNEMA_PGRMM
	{
		char					head;
		char					bodyType;
		tagBODY_NEMA_PGRMM		body;	
		char					checkBegin;
		char					check[2];
		char					tail[2];
	}GPS_NEMA_PGRMM;

	//工作状态信息
	struct tagNEMA_PGRMT
	{
		char					head;
		char					bodyType;
		tagBODY_NEMA_PGRMT		body;	
		char					checkBegin;
		char					check[2];
		char					tail[2];
	}GPS_NEMA_PGRMT;
	
	//三维速度信息
	struct tagNEMA_PGRMV
	{
		char					head;
		char					bodyType;
		tagBODY_NEMA_PGRMV		body;	
		char					checkBegin;
		char					check[2];
		char					tail[2];
	}GPS_NEMA_PGRMV;

	//信标差分信息
	struct tagNEMA_PGRMB
	{
		char					head;
		char					bodyType;
		tagBODY_NEMA_PGRMB		body;	
		char					checkBegin;
		char					check[2];
		char					tail[2];
	}GPS_NEMA_PGRMB;
};













