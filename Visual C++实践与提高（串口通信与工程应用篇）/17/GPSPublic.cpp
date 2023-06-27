// GPSPublic.cpp : implementation file
//

#include "stdafx.h"
#include "gpsserver.h"
#include "GPSPublic.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGPSPublic

CGPSPublic::CGPSPublic()
{
}

CGPSPublic::~CGPSPublic()
{
}


BEGIN_MESSAGE_MAP(CGPSPublic, CWnd)
	//{{AFX_MSG_MAP(CGPSPublic)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGPSPublic message handlers

CString CGPSPublic::GetDirectXType(char type)
{
	CString result;
	switch (type)
	{
	case 'E':
		result = "向东";
		break;
	case 'W':
		result = "向西";
		break;
	default:
		result = "未知";
		break;
	}
	return result;
}

CString CGPSPublic::GetDirectYType(char type)
{
	CString result;
	switch (type)
	{
	case 'N':
		result = "向北";
		break;
	case 'S':
		result = "向南";
		break;
	default:
		result = "未知";
		break;
	}
	return result;
}

CString CGPSPublic::GetDirectZType(char type)
{
	CString result;
	switch (type)
	{
	case 'D':
		result = "向下";
		break;
	case 'U':
		result = "向上";
		break;
	default:
		result = "未知";
		break;
	}
	return result;
}

CString CGPSPublic::GetLatitudeType(char type)
{
	CString result;
	switch (type)
	{
	case 'N':
		result = "北纬";
		break;
	case 'S':
		result = "南纬";
		break;
	default:
		result = "未知";
		break;
	}
	return result;
}

CString CGPSPublic::GetLongitudeType(char type)
{
	CString result;
	switch (type)
	{
	case 'E':
		result = "东经";
		break;
	case 'W':
		result = "西经";
		break;
	default:
		result = "未知";
		break;
	}
	return result;
}


CString CGPSPublic::GetMode(char type)
{
	CString result;
	switch (type)
	{
	case 'A':
		result = "自主定位";
		break;
	case 'D':
		result = "差分";
		break;
	case 'E':
		result = "估算D";
		break;
	case 'N':
		result = "数据无效";
		break;
	default:
		result = "未知";
		break;
	}
	return result;
}
		
CString CGPSPublic::GetCommStatu(char type)
{
	CString result;
	switch (type)
	{
	case '0':
		result = "检查接线";
		break;
	case '1':
		result = "无信号";
		break;
	case '2':
		result = "正在调谐";
		break;	
	case '3':
		result = "正在接收";
		break;
	case '4':
		result = "正在扫描";
		break;
	default:
		result = "未知";
		break;
	}
	return result;
}

CString CGPSPublic::GetFaultStatu(char type)
{
	CString result;
	switch (type)
	{
	case 'P':
		result = "通过";
		break;
	case 'F':
		result = "失败";
		break;
	default:
		result = "未知";
		break;
	}
	return result;
}

CString CGPSPublic::GetSaveStatu(char type)
{
	CString result;
	switch (type)
	{
	case 'R':
		result = "保持";
		break;
	case 'L':
		result = "丢失";
		break;
	default:
		result = "未知";
		break;
	}
	return result;
}

CString CGPSPublic::GetOffsetStatu(char type)
{
	CString result;
	switch (type)
	{
	case 'P':
		result = "通过";
		break;
	case 'F':
		result = "检测到过度漂移";
		break;
	default:
		result = "未知";
		break;
	}
	return result;
}

CString CGPSPublic::GetCollectStatu(char type)
{
	CString result;
	switch (type)
	{
	case 'C':
		result = "正在采集";
		break;
	default:
		result = "没有采集";
		break;
	}
	return result;
}	
		
CString CGPSPublic::GetDiffSource(char type)
{
	CString result;
	switch (type)
	{
	case 'W':
		result = "WAAS";
		break;
	case 'R':
		result = "RTCM";
		break;
	case 'N':
		result = "非差分定位";
		break;	
	default:
		result = "未知";
		break;
	}
	return result;
}

CString CGPSPublic::GetDiffStatu(char type)
{
	CString result;
	switch (type)
	{
	case 'A':
		result = "自动";
		break;
	case 'W':
		result = "仅为WAAS";
		break;
	case 'R':
		result = "RTCM";
		break;
	case 'N':
		result = "不接收差分信号";
		break;	
	default:
		result = "未知";
		break;
	}
	return result;
}

CString CGPSPublic::GetGPSMode(char type)
{
	CString result;
	switch (type)
	{
	case 'A':
		result = "自动";
		break;
	case 'M':
		result = "手动";
		break;
	default:
		result = "未知";
		break;
	}
	return result;
}


CString CGPSPublic::GetGPSValid(char type)
{
	CString result;
	switch (type)
	{
	case 'A':
		result = "有效定位";
		break;
	case 'V':
		result = "无效定位";
		break;
	default:
		result = "未知";
		break;
	}
	return result;
}

CString CGPSPublic::GetGPSStatu(char type)
{
	CString result;
	switch (type)
	{
	case '0':
		result = "未定位";
		break;
	case '1':
		result = "非差分定位";
		break;
	case '2':
		result = "差分定位";
		break;
	case '6':
		result = "正在估算";
		break;	
	default:
		result = "未知";
		break;
	}
	return result;
}


CString CGPSPublic::GetPosType(char type, int stardand)
{
	CString result;

	// 如果是标准的NEMA语句则
	if (stardand == 1)
	{
		switch (type)
		{
		case '1':
			result = "没有定位";
			break;
		case '2':
			result = "2D定位";
			break;
		case '3':
			result = "3D定位";
			break;	
		default:
			result = "未知";
			break;
		}
	}
	// 如果是GARMIN公司的则
	else
	{
		switch (type)
		{
		case '0':
			result = "没有定位";
			break;
		case '1':
			result = "2D定位";
			break;
		case '2':
			result = "3D定位";
			break;	
		default:
			result = "未知";
			break;
		}
	}
	return result;
}

CString CGPSPublic::GetTextPosStatu(char type)
{
	CString result;
	switch (type)
	{
	case 'd':
		result = "2维差分定位";
		break;
	case 'D':
		result = "3维差分定位";
		break;
	case 'g':
		result = "2维定位";
		break;
	case 'G':
		result = "3维定位";
		break;
	case 'S':
		result = "模拟状态";
		break;
	case '_':
		result = "无效";
		break;
	default:
		result = "未知";
		break;
	}
	return result;
}

void CGPSPublic::ConvertToLongitude(double& longitude, CString inStr)
{
	if (inStr.GetLength() < 8)
	{
		return;
	}

	int degree = atoi((const char*)inStr.Mid(0, 3));
	CString minute;
	minute = inStr.Mid(3, 5);
	minute.Insert(2, '.');
	double dminute = atof((const char*)minute);
	longitude = degree + dminute/60;
}

void CGPSPublic::ConvertToLongitudeHavePoint(double& longitude, CString inStr)
{
	if (inStr.GetLength() < 8)
	{
		return;
	}

	int degree = atoi((const char*)inStr.Mid(0, 3));
	CString minute;
	minute = inStr.Mid(3, 5);	
	double dminute = atof((const char*)minute);
	longitude = degree + dminute/60;
}

void CGPSPublic::ConvertToLatitude(double& latitude, CString inStr)
{
	if (inStr.GetLength() < 7)
	{
		return;
	}

	int degree = atoi((const char*)inStr.Mid(0, 2));
	CString minute;
	minute = inStr.Mid(2, 5);
	minute.Insert(2, '.');
	double dminute = atof((const char*)minute);
	latitude = degree + dminute/60;
}

void CGPSPublic::ConvertToLatitudeHavePoint(double& latitude, CString inStr)
{
	if (inStr.GetLength() < 2)
	{
		return;
	}

	int degree = atoi((const char*)inStr.Mid(0, 2));
	CString minute;
	minute = inStr.Mid(2, 5);
	double dminute = atof((const char*)minute);
	latitude = degree + dminute/60;
}

void CGPSPublic::ConvertToDouble(double& value, CString inStr)
{
	value = atof((const char*)inStr);
}

void CGPSPublic::ConvertToInt(int& value, CString inStr)
{
	value = atoi((const char*)inStr);
}

void CGPSPublic::ConvertToDoubleAddPoint(double& value, CString inStr, int pos)
{	
	inStr.Insert(pos, '.');
	value = atof((const char*)inStr);
}

void CGPSPublic::ConvertToChar(char& value, CString inStr, int length)
{
	memcpy((void*)&value, (const void*)inStr, length);	
}
