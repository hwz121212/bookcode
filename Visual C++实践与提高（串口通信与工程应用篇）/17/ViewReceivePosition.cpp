// ReceiveInforView.cpp : implementation file
//

#include "stdafx.h"
#include "GpsServer.h"
#include "ViewReceivePosition.h"
#include "GPSPublic.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewReceivePosition

IMPLEMENT_DYNCREATE(CViewReceivePosition, CViewBase)

CViewReceivePosition::CViewReceivePosition()
{
	InitColumns();
}

CViewReceivePosition::~CViewReceivePosition()
{
}


BEGIN_MESSAGE_MAP(CViewReceivePosition, CViewBase)
	//{{AFX_MSG_MAP(CViewReceivePosition)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CViewReceivePosition diagnostics

#ifdef _DEBUG

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewReceivePosition message handlers
void CViewReceivePosition::InitColumns()
{
	_gColText.Add(IDS_COL_POSITION_1);
	_gColText.Add(IDS_COL_POSITION_2);
	_gColText.Add(IDS_COL_POSITION_3);
	_gColText.Add(IDS_COL_POSITION_4);
	_gColText.Add(IDS_COL_POSITION_5);
	_gColText.Add(IDS_COL_POSITION_6);
	_gColText.Add(IDS_COL_POSITION_7);
	_gColText.Add(IDS_COL_POSITION_8);
	_gColText.Add(IDS_COL_POSITION_9);
	_gColText.Add(IDS_COL_POSITION_10);
	_gColText.Add(IDS_COL_POSITION_11);
	_gColText.Add(IDS_COL_POSITION_12);

	_gColWidth.Add(50);
	_gColWidth.Add(50);
	_gColWidth.Add(150);
	_gColWidth.Add(100);
	_gColWidth.Add(90);
	_gColWidth.Add(90);
	_gColWidth.Add(90);
	_gColWidth.Add(90);
	_gColWidth.Add(90);
	_gColWidth.Add(90);
	_gColWidth.Add(90);
	_gColWidth.Add(90);
}

void CViewReceivePosition::InsertPosition(CString source, GPSPack *pack)
{
	//编号     串口    时间     经度 纬度 海拔 定位状态 水平精度  x速度 y速度
	// z速度  

	// 获取当前列表框中的记录数目，如果超过定义的日志条数,则将列表框中的日志删除
	if ((GetListCtrl().GetItemCount()) > VIEW_LOG_COUNT) 
	{
		ClearLogs();
	}

	//id
	CString sid="";
	sid.Format("%d",(GetListCtrl().GetItemCount()+1));
	//time
	CString tt;	
	CString longitude;
	CString latitude;
	CString altitude;
	CString status;
	CString hdop;
	CString xVolity;
	CString yVolity;
	CString zVolity;
	CString other;

	switch(pack->GPS_NEMA_TEXT.bodyType)
	{
	case NEMATYPE_TEXT_POS:
		tt.Format("%04d-%02d-%02d  %02d:%02d:%02d",
			pack->GPS_NEMA_TEXT.body.date.year,		
			pack->GPS_NEMA_TEXT.body.date.month,
			pack->GPS_NEMA_TEXT.body.date.day,
			pack->GPS_NEMA_TEXT.body.time.hour,
			pack->GPS_NEMA_TEXT.body.time.minute,
			pack->GPS_NEMA_TEXT.body.time.second);

		longitude.Format("%s%f", 
			CGPSPublic::GetLongitudeType(pack->GPS_NEMA_TEXT.body.longitudeType),
			pack->GPS_NEMA_TEXT.body.longitude);

		latitude.Format("%s%f", 
			CGPSPublic::GetLatitudeType(pack->GPS_NEMA_TEXT.body.latitudeType),
			pack->GPS_NEMA_TEXT.body.latitude);

		altitude.Format("%c%f", 
			pack->GPS_NEMA_TEXT.body.altitudeSymbol,
			pack->GPS_NEMA_TEXT.body.altitude);

		status.Format("%s", 
			CGPSPublic::GetTextPosStatu(pack->GPS_NEMA_TEXT.body.gpsStatus));

		hdop.Format("%f", 
			pack->GPS_NEMA_TEXT.body.hdop);

		xVolity.Format("%s%f", 
			CGPSPublic::GetDirectXType(pack->GPS_NEMA_TEXT.body.xDirect),
			pack->GPS_NEMA_TEXT.body.xVolity);

		yVolity.Format("%s%f", 
			CGPSPublic::GetDirectYType(pack->GPS_NEMA_TEXT.body.yDirect),
			pack->GPS_NEMA_TEXT.body.yVolity);

		zVolity.Format("%s%f", 
			CGPSPublic::GetDirectZType(pack->GPS_NEMA_TEXT.body.zDirect),
			pack->GPS_NEMA_TEXT.body.zVolity);

		other = "";
		break;

	case NEMATYPE_STANDARD_GPGGA:
		tt.Format("%02d:%02d:%02d",		
			pack->GPS_NEMA_GPGGA.body.time.hour,
			pack->GPS_NEMA_GPGGA.body.time.minute,
			pack->GPS_NEMA_GPGGA.body.time.second);

		longitude.Format("%s%f", 
			CGPSPublic::GetLongitudeType(pack->GPS_NEMA_GPGGA.body.longitudeType),
			pack->GPS_NEMA_GPGGA.body.longitude);

		latitude.Format("%s%f", 
			CGPSPublic::GetLatitudeType(pack->GPS_NEMA_GPGGA.body.latitudeType),
			pack->GPS_NEMA_GPGGA.body.latitude);

		altitude.Format("%f--%f", pack->GPS_NEMA_GPGGA.body.altitude,
			pack->GPS_NEMA_GPGGA.body.height);

		status.Format("%s", 
			CGPSPublic::GetGPSStatu(pack->GPS_NEMA_GPGGA.body.gpsStatus));

		hdop.Format("%f", 
			pack->GPS_NEMA_GPGGA.body.hdop);

		other.Format("卫星数目%d---差分时间%d---差分站%s", 
			pack->GPS_NEMA_GPGGA.body.sateCount, 
			pack->GPS_NEMA_GPGGA.body.diffSecond,
			pack->GPS_NEMA_GPGGA.body.diffStationID);
		break;

	case NEMATYPE_STANDARD_GPRMC:
		tt.Format("%04d-%02d-%02d  %02d:%02d:%02d",
			pack->GPS_NEMA_GPRMC.body.date.year,		
			pack->GPS_NEMA_GPRMC.body.date.month,
			pack->GPS_NEMA_GPRMC.body.date.day,
			pack->GPS_NEMA_GPRMC.body.time.hour,
			pack->GPS_NEMA_GPRMC.body.time.minute,
			pack->GPS_NEMA_GPRMC.body.time.second);

		longitude.Format("%s%f", 
			CGPSPublic::GetLongitudeType(pack->GPS_NEMA_GPRMC.body.longitudeType),
			pack->GPS_NEMA_GPRMC.body.longitude);

		latitude.Format("%s%f", 
			CGPSPublic::GetLatitudeType(pack->GPS_NEMA_GPRMC.body.latitudeType),
			pack->GPS_NEMA_GPRMC.body.latitude);

		altitude="";

		status.Format("%s", 
			CGPSPublic::GetGPSValid(pack->GPS_NEMA_GPRMC.body.posvalid));

		hdop="";

		xVolity.Format("方向=%f----速度=%f", 
			pack->GPS_NEMA_GPRMC.body.direct,
			pack->GPS_NEMA_GPRMC.body.volity);

		yVolity="";

		zVolity="";

		other.Format("磁偏角=%f---磁偏角方向=%s---模式=%s", 
			pack->GPS_NEMA_GPRMC.body.cpj,
			CGPSPublic::GetDirectXType(pack->GPS_NEMA_GPRMC.body.cpjdirect),
			CGPSPublic::GetMode(pack->GPS_NEMA_GPRMC.body.mode));
		break;

	case NEMATYPE_GARMIN_PGRMF:
		tt.Format("%04d-%02d-%02d  %02d:%02d:%02d",
			pack->GPS_NEMA_PGRMF.body.date.year,		
			pack->GPS_NEMA_PGRMF.body.date.month,
			pack->GPS_NEMA_PGRMF.body.date.day,
			pack->GPS_NEMA_PGRMF.body.time.hour,
			pack->GPS_NEMA_PGRMF.body.time.minute,
			pack->GPS_NEMA_PGRMF.body.time.second);

		longitude.Format("%s%f", 
			CGPSPublic::GetLongitudeType(pack->GPS_NEMA_PGRMF.body.longitudeType),
			pack->GPS_NEMA_PGRMF.body.longitude);

		latitude.Format("%s%f", 
			CGPSPublic::GetLatitudeType(pack->GPS_NEMA_PGRMF.body.latitudeType),
			pack->GPS_NEMA_PGRMF.body.latitude);

		altitude = "";

		status.Format("%s", 
			CGPSPublic::GetGPSMode(pack->GPS_NEMA_PGRMF.body.gpsmode));

		hdop.Format("PDOP=%d---TDOP=%d", 
			pack->GPS_NEMA_PGRMF.body.pdop, pack->GPS_NEMA_PGRMF.body.tdop);

		xVolity.Format("航向=%d----速度=%d", 
			pack->GPS_NEMA_PGRMF.body.direct,
			pack->GPS_NEMA_PGRMF.body.volity);

		yVolity="";

		zVolity="";

		other.Format("GPS周数=%d---GPS秒数=%d---GPS跳秒数=%d---模式=%s", 
			pack->GPS_NEMA_PGRMF.body.gpscircle, pack->GPS_NEMA_PGRMF.body.gpssecond,
			pack->GPS_NEMA_PGRMF.body.gpsjump,
			CGPSPublic::GetPosType(pack->GPS_NEMA_PGRMF.body.postype, 0));
		break;

	case NEMATYPE_STANDARD_GPGLL:		//定位地理信息
		tt.Format("%02d:%02d:%02d",
			pack->GPS_NEMA_GPGLL.body.time.hour,
			pack->GPS_NEMA_GPGLL.body.time.minute,
			pack->GPS_NEMA_GPGLL.body.time.second);

		longitude.Format("%s%f", 
			CGPSPublic::GetLongitudeType(pack->GPS_NEMA_GPGLL.body.longitudeType),
			pack->GPS_NEMA_GPGLL.body.longitude);

		latitude.Format("%s%f", 
			CGPSPublic::GetLatitudeType(pack->GPS_NEMA_GPGLL.body.latitudeType),
			pack->GPS_NEMA_GPGLL.body.latitude);

		altitude = "";	

		status.Format("%s", 
			CGPSPublic::GetGPSValid(pack->GPS_NEMA_GPGLL.body.posvalid));

		hdop="";
		xVolity="";
		yVolity="";
		zVolity="";

		other.Format("模式=%s",
			CGPSPublic::GetMode(pack->GPS_NEMA_GPGLL.body.mode));		
		break;

	case NEMATYPE_STANDARD_GPZDA:	//时间和日期信息
		tt.Format("%04d-%02d-%02d  %02d:%02d:%02d",
			pack->GPS_NEMA_GPZDA.body.date.year,		
			pack->GPS_NEMA_GPZDA.body.date.month,
			pack->GPS_NEMA_GPZDA.body.date.day,
			pack->GPS_NEMA_GPZDA.body.time.hour,
			pack->GPS_NEMA_GPZDA.body.time.minute,
			pack->GPS_NEMA_GPZDA.body.time.second);

		longitude = "";
		latitude = "";
		altitude = "";
		status = "";
		hdop = "";
		xVolity = "";
		yVolity = "";
		zVolity = "";
		other = "";
		break;

	case NEMATYPE_GARMIN_PGRMV://三维速度信息
		tt = "";
		longitude = "";
		latitude = "";
		altitude = "";
		status = "";
		hdop = "";
		other = "";

		xVolity.Format("东向速度%f",
			pack->GPS_NEMA_PGRMV.body.xVolity);

		yVolity.Format("北向速度%f", 
			pack->GPS_NEMA_PGRMV.body.yVolity);

		zVolity.Format("上向速度%f",
			pack->GPS_NEMA_PGRMV.body.zVolity);		

			break;
	}

	LV_ITEM	lvItem;
	lvItem.mask = LVIF_TEXT | LVIF_STATE;
	lvItem.iItem = 0;
	lvItem.iSubItem = 0;
	lvItem.iImage = 0;
	lvItem.stateMask = LVIS_STATEIMAGEMASK;
	lvItem.state = INDEXTOSTATEIMAGEMASK(1);	
	lvItem.pszText = (char*)(LPCTSTR)(sid);	
	int result = GetListCtrl().InsertItem(&lvItem);
	if (result != -1)
	{		
		GetListCtrl().SetItemText(0, 1, source);
		GetListCtrl().SetItemText(0, 2, tt);
		GetListCtrl().SetItemText(0, 3, longitude);
		GetListCtrl().SetItemText(0, 4, latitude);
		GetListCtrl().SetItemText(0, 5, altitude);
		GetListCtrl().SetItemText(0, 6, status);
		GetListCtrl().SetItemText(0, 7, hdop);
		GetListCtrl().SetItemText(0, 8, xVolity);
		GetListCtrl().SetItemText(0, 9, yVolity);
		GetListCtrl().SetItemText(0, 10, zVolity);	
		GetListCtrl().SetItemText(0, 11, other);
	}
}
