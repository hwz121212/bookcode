// ReceiveInforView.cpp : implementation file
//

#include "stdafx.h"
#include "GpsServer.h"
#include "ViewNemaData.h"
#include "GPSPublic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewNemaData

IMPLEMENT_DYNCREATE(CViewNemaData, CViewBase)

CViewNemaData::CViewNemaData()
{
	InitColumns();
}

CViewNemaData::~CViewNemaData()
{
}


BEGIN_MESSAGE_MAP(CViewNemaData, CViewBase)
	//{{AFX_MSG_MAP(CViewNemaData)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CViewNemaData diagnostics

#ifdef _DEBUG

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewNemaData message handlers
void CViewNemaData::InitColumns()
{
	_gColText.Add(IDS_COL_NEMA_1);
	_gColText.Add(IDS_COL_NEMA_2);
	_gColText.Add(IDS_COL_NEMA_3);	

	_gColWidth.Add(50);
	_gColWidth.Add(75);
	_gColWidth.Add(400);
}

void CViewNemaData::InsertNema(CString source, GPSPack *pack)
{
	// 获取当前列表框中的记录数目，如果超过定义的日志条数,则将列表框中的日志删除
	if ((GetListCtrl().GetItemCount()) > VIEW_LOG_COUNT) 
	{
		ClearLogs();
	}

	//id
	CString sid="";
	sid.Format("%d",(GetListCtrl().GetItemCount()+1));

	CString content="";
	CString temp = "";
	CString temp1 = "";
	int i = 0;
	switch(pack->GPS_NEMA_TEXT.bodyType)
	{
		case NEMATYPE_STANDARD_GPGSA://当前卫星信息
			for (i = 0; i < MAX_SATE_TOTAL;i++)
			{
				if (pack->GPS_NEMA_GPGSA.body.prn[i] != 0)
				{
					temp1.Format("卫星%d,", pack->GPS_NEMA_GPGSA.body.prn[i]);
					temp += temp1;					
				}
			}
			content.Format("模式=%s----定位类型=%s----PRN=%s----PDOP=%f----\
				HDOP=%f----VDOP=%f",
				CGPSPublic::GetGPSMode(pack->GPS_NEMA_GPGSA.body.gpsmode),		
				CGPSPublic::GetPosType(pack->GPS_NEMA_GPGSA.body.postype, 1) ,
				temp,
				pack->GPS_NEMA_GPGSA.body.pdop,
				pack->GPS_NEMA_GPGSA.body.hdop,
				pack->GPS_NEMA_GPGSA.body.vdop);
			break;
		
		case NEMATYPE_STANDARD_GPGSV://可见卫星信息
			for (i = 0; i < MAX_SATE_ONE_TOTAL;i++)
			{
				if (pack->GPS_NEMA_GPGSA.body.prn[i] != 0)
				{
					temp1.Format("----PRN码=%d,卫星仰角=%d,卫星方位角=%d,信噪比=%d", 
						pack->GPS_NEMA_GPGSV.body.prn[i],
						pack->GPS_NEMA_GPGSV.body.yj[i],
						pack->GPS_NEMA_GPGSV.body.fwj[i],
						pack->GPS_NEMA_GPGSV.body.xzb[i]);
					temp += temp1;				
				}
			}
			content.Format("总数=%d----编号=%d----可见=%d----%s",
				pack->GPS_NEMA_GPGSV.body.total ,		
				pack->GPS_NEMA_GPGSV.body.no ,
				pack->GPS_NEMA_GPGSV.body.validsate, temp);
			break;

		case NEMATYPE_STANDARD_GPVTG://地面速度信息
			content.Format("真北航向=%d----磁北航向=%d----地面速率(节)=%f----地面速率(公里/小时)=%f----\
				模式指示=%s",
				pack->GPS_NEMA_GPVTG.body.directtn ,		
				pack->GPS_NEMA_GPVTG.body.directcn ,
				pack->GPS_NEMA_GPVTG.body.volityj,
				pack->GPS_NEMA_GPVTG.body.volitykm,
				CGPSPublic::GetMode(pack->GPS_NEMA_GPVTG.body.mode));
			break;

		case NEMATYPE_STANDARD_GPDTM://大地坐标系信息
			content.Format("本地坐标系代码=%s----坐标系子代码=%s\
			----%s纬度偏移量=%f----%s经度偏移量=%f----高度偏移量=%f----坐标系代码=%s",
				pack->GPS_NEMA_GPDTM.body.localdatum ,		
				pack->GPS_NEMA_GPDTM.body.subdatum,
				CGPSPublic::GetLatitudeType(pack->GPS_NEMA_GPDTM.body.latitudetype),
				pack->GPS_NEMA_GPDTM.body.latitudeoffset,
				CGPSPublic::GetLongitudeType(pack->GPS_NEMA_GPDTM.body.longitudetype),
				pack->GPS_NEMA_GPDTM.body.longitudeoffset,
				pack->GPS_NEMA_GPDTM.body.alitudeoffset,
				pack->GPS_NEMA_GPDTM.body.datum);
			break;		

		case NEMATYPE_GARMIN_PGRME://估计误差信息
			content.Format("水平估计误差=%f----垂直估计误差=%f----位置估计误差=%f",
				pack->GPS_NEMA_PGRME.body.hpe ,		
				pack->GPS_NEMA_PGRME.body.vpe,			
				pack->GPS_NEMA_PGRME.body.epe);
			break;

		case NEMATYPE_GARMIN_PGRMM://坐标系统信息,该信息在与MapSource进行实时连接的时候使用。
			content.Format("坐标系名称=%s(与MapSource进行实时连接的时候使用)",
			pack->GPS_NEMA_PGRMM.body.datum );
			break;

		case NEMATYPE_GARMIN_PGRMT://工作状态信息
			content.Format("版本=%s----ROM校验测试=%s\
				----接收机不连续故障=%s-----存储的数据=%s\
				----时钟的信息=%s----振荡器不连续漂移=%s\
				----数据不连续采集=%s----GPS接收机温度=%f\
				----GPS接收机配置数据=%s",
				pack->GPS_NEMA_PGRMT.body.version ,		
				CGPSPublic::GetFaultStatu(pack->GPS_NEMA_PGRMT.body.romcheck),
				CGPSPublic::GetFaultStatu(pack->GPS_NEMA_PGRMT.body.fault),
				CGPSPublic::GetSaveStatu(pack->GPS_NEMA_PGRMT.body.storedata),
				CGPSPublic::GetSaveStatu(pack->GPS_NEMA_PGRMT.body.clock),
				CGPSPublic::GetOffsetStatu(pack->GPS_NEMA_PGRMT.body.piaoyi),
				CGPSPublic::GetCollectStatu(pack->GPS_NEMA_PGRMT.body.datacollect),
				pack->GPS_NEMA_PGRMT.body.temperature,
				CGPSPublic::GetSaveStatu(pack->GPS_NEMA_PGRMT.body.configdata));
			break;

		case NEMATYPE_GARMIN_PGRMB://信标差分信息
			content.Format("信标站频率=%f----信标比特率=%d\
			----SNR信噪比=%d----信标数据质量=%d----距离=%f----通讯状态=%s\
			----差分源=%s----差分状态=%s",
				pack->GPS_NEMA_PGRMB.body.freq , pack->GPS_NEMA_PGRMB.body.banud,
				pack->GPS_NEMA_PGRMB.body.snr, pack->GPS_NEMA_PGRMB.body.quality,
				pack->GPS_NEMA_PGRMB.body.distance,
				CGPSPublic::GetCommStatu(pack->GPS_NEMA_PGRMB.body.commstatu),
				CGPSPublic::GetDiffSource(pack->GPS_NEMA_PGRMB.body.source),
				CGPSPublic::GetDiffStatu(pack->GPS_NEMA_PGRMB.body.statu));
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
		GetListCtrl().SetItemText(0, 2, content);		
	}
}
