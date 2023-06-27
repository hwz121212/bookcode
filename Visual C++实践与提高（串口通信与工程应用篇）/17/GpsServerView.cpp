// GpsServerView.cpp : implementation of the CGpsServerView class
//

#include "stdafx.h"
#include "GpsServer.h"
#include "GpsServerDoc.h"
#include "GpsServerView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGpsServerView
IMPLEMENT_DYNCREATE(CGpsServerView, CHtmlView)

BEGIN_MESSAGE_MAP(CGpsServerView, CHtmlView)
	//{{AFX_MSG_MAP(CGpsServerView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CGpsServerView construction/destruction

CGpsServerView::CGpsServerView()   	
{	
	// TODO: add construction code here
}

CGpsServerView::~CGpsServerView()
{
}

CMainFrame* CGpsServerView::GetMainFrame()
{
	return (CMainFrame*)AfxGetApp()->GetMainWnd();
}


/////////////////////////////////////////////////////////////////////////////
// CGpsServerView drawing

void CGpsServerView::OnDraw(CDC* pDC)
{
	CGpsServerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here	

}

/////////////////////////////////////////////////////////////////////////////
// CGpsServerView printing

/////////////////////////////////////////////////////////////////////////////
// CGpsServerView diagnostics

#ifdef _DEBUG
void CGpsServerView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CGpsServerView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CGpsServerDoc* CGpsServerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGpsServerDoc)));
	return (CGpsServerDoc*)m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGpsServerView message handlers

void CGpsServerView::OnInitialUpdate() 
{
	CHtmlView::OnInitialUpdate();

	CMainFrame* pFrame =  GetMainFrame();
	if (pFrame != NULL)	
		pFrame->SetView(this);

	// TODO: This code navigates to a popular spot on the web.
	//  change the code to go where you'd like.
	InitMap();
}

int CGpsServerView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CHtmlView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CMainFrame* pFrame =  GetMainFrame();
	if (pFrame != NULL)	
		pFrame->SetView(this);

	return 0;
}


void CGpsServerView::DrawPositionOnMap(GPSPack *pack)
{	
	if (pack == NULL) return;

	double x;
	double y;
	CString name;

	switch(pack->GPS_NEMA_TEXT.bodyType)
	{
	case NEMATYPE_TEXT_POS:
		x = pack->GPS_NEMA_TEXT.body.longitude.longitude*100000;
		y = pack->GPS_NEMA_TEXT.body.latitude.latitude*100000;
		name = "(GPS_NEMA_TEXT)这是我的测试位置!!!";	
		ShowPoint(x, y, name);
		break;

	case NEMATYPE_STANDARD_GPGGA:
		x = pack->GPS_NEMA_GPGGA.body.longitude.longitude*100000;
		y = pack->GPS_NEMA_GPGGA.body.latitude.latitude*100000;
		name = "(GPS_NEMA_GPGGA)这是我的测试位置!!!";
		ShowPoint(x, y, name);
		break;

	case NEMATYPE_STANDARD_GPRMC:
		x = pack->GPS_NEMA_GPRMC.body.longitude.longitude*100000;
		y = pack->GPS_NEMA_GPRMC.body.latitude.latitude*100000;
		name = "(GPS_NEMA_GPRMC)这是我的测试位置!!!";
		ShowPoint(x, y, name);
		break;

	case NEMATYPE_STANDARD_GPGLL:
		x = pack->GPS_NEMA_GPGLL.body.longitude.longitude*100000;
		y = pack->GPS_NEMA_GPGLL.body.latitude.latitude*100000;
		name = "(GPS_NEMA_GPGLL)这是我的测试位置!!!";
		ShowPoint(x, y, name);
		break;

	case NEMATYPE_GARMIN_PGRMF:
		x = pack->GPS_NEMA_PGRMF.body.longitude.longitude*100000;
		y = pack->GPS_NEMA_PGRMF.body.latitude.latitude*100000;
		name = "(GPS_NEMA_PGRMF)这是我的测试位置!!!";
		ShowPoint(x, y, name);
		break;
	}	
}

///////////////////////////////////////////////////////////////////
// 函数名：	ShowPoint
// 功  能：	显示定位点
// 参  数：	double x--显示的经度
//			double y--显示的纬度
//			CString name--显示的名称
// 返回值：	
///////////////////////////////////////////////////////////////////
void CGpsServerView::ShowPoint(double x, double y, CString name)
{
	CString js;	
	js.Format(_T("showpoint(%f, %f, \"%s\");"), x, y, name);
	ExecJavaScript(js);
}

///////////////////////////////////////////////////////////////////
// 函数名：	ExecJavaScript
// 功  能：	执行JavaScript脚本函数
// 参  数：	CString js--要执行的脚本
// 返回值：	
///////////////////////////////////////////////////////////////////
void CGpsServerView::ExecJavaScript(CString js)
{
	//获取HTML文档
	CComQIPtr<IHTMLDocument2> pDoc = (IHTMLDocument2*)GetHtmlDocument();
	if (pDoc == NULL) return;

	//获取HTML窗体
	CComQIPtr<IHTMLWindow2> pWin;
	pDoc->get_parentWindow(&pWin);
	if (pWin == NULL) return;

	//执行JavaScript脚本
	CComBSTR bstrJS = js.AllocSysString();
	CComBSTR bstrLanguage = SysAllocString(L"javascript");
	VARIANT varResult;
	pWin->execScript(bstrJS, bstrLanguage, &varResult);

	return;
}

void CGpsServerView::InitMap()
{	
	//读取当前应用程序的完整路径
	char szCurDir[MAX_PATH];
	memset(szCurDir, 0x00, sizeof(szCurDir));
	DWORD length=sizeof(szCurDir);  
	GetModuleFileName(NULL, szCurDir, length);
	
	//将应用程序名称去掉，得到当前运行程序的目录
	CString app;
	app.Format("%s", szCurDir);
	int end = app.ReverseFind('\\');
	app = app.Left(end);

	//找到当前路径下的地图信息点模板文件名
	CString sPath;
	sPath.Format(_T("%s\\%s"), app, MAP_TEMPLATE_PATH);	

	//浏览地图页面。
	Navigate2(_T(sPath),NULL,NULL);
}





