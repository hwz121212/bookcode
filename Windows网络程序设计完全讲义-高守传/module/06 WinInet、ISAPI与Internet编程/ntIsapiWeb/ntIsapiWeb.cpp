// NTISAPIWEB.CPP - Implementation file for your Internet Server
//    ntIsapiWeb Extension

#include "stdafx.h"
#include "ntIsapiWeb.h"


///////////////////////////////////////////////////////////////////////
// command-parsing map

BEGIN_PARSE_MAP(CNtIsapiWebExtension, CHttpServer)
	// TODO: insert your ON_PARSE_COMMAND() and 
	// ON_PARSE_COMMAND_PARAMS() here to hook up your commands.
	// For example:
	//定义输入函数及其参数类型 
    ON_PARSE_COMMAND(Test, CNtIsapiWebExtension, ITS_R8 ITS_R8 ITS_PSTR) 
    //定义函数的具体参数名称 
    ON_PARSE_COMMAND_PARAMS("m_Height m_Weight m_Sex") 
    //没有提交操作时的缺省函数（显示表单）
	ON_PARSE_COMMAND(Default, CNtIsapiWebExtension, ITS_EMPTY)
	DEFAULT_PARSE_COMMAND(Default, CNtIsapiWebExtension)
END_PARSE_MAP(CNtIsapiWebExtension)


///////////////////////////////////////////////////////////////////////
// The one and only CNtIsapiWebExtension object

CNtIsapiWebExtension theExtension;


///////////////////////////////////////////////////////////////////////
// CNtIsapiWebExtension implementation

CNtIsapiWebExtension::CNtIsapiWebExtension()
{
}

CNtIsapiWebExtension::~CNtIsapiWebExtension()
{
}

BOOL CNtIsapiWebExtension::GetExtensionVersion(HSE_VERSION_INFO* pVer)
{
	// Call default implementation for initialization
	CHttpServer::GetExtensionVersion(pVer);

	// Load description string
	TCHAR sz[HSE_MAX_EXT_DLL_NAME_LEN+1];
	ISAPIVERIFY(::LoadString(AfxGetResourceHandle(),
			IDS_SERVER, sz, HSE_MAX_EXT_DLL_NAME_LEN));
	_tcscpy(pVer->lpszExtensionDesc, sz);
	return TRUE;
}

BOOL CNtIsapiWebExtension::TerminateExtension(DWORD dwFlags)
{
	// extension is being terminated
	//TODO: Clean up any per-instance resources
	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// CNtIsapiWebExtension command handlers

void CNtIsapiWebExtension::Default(CHttpServerContext* pCtxt)
{
	StartContent(pCtxt);
	WriteTitle(pCtxt);
	//The next six lines print the default calc form. 
    //For this form to work correctly the action must contain the "Calc" 
    //command, and the method must be POST. 
    *pCtxt << _T("<H4>用户体形测试</H4><BR>");
	//按照html语句的格式定制表单
    *pCtxt << _T("<FORM ACTION=\"ntIsapiWeb.dll?Test\" METHOD=POST>");
	*pCtxt << _T("<H5>请输入用户身高（cm）</H5>");
    *pCtxt << _T("<INPUT NAME=\"m_Height\" SIZE=5 ><BR><BR>"); 
	*pCtxt << _T("<H5>请输入用户体重（kg）</H5>");
    *pCtxt << _T("<INPUT NAME=\"m_Weight\" SIZE=5 ><BR><BR>"); 
	*pCtxt << _T("<H5>用户性别</H5>");
	*pCtxt << _T("<SELECT NAME=\"m_Sex\" ><OPTION value=1>男 <OPTION value=2>女</SELECT><BR><BR>"); 
    *pCtxt << _T("<INPUT TYPE=SUBMIT VALUE=测试体形></FORM>"); 
    //Print < /HTML > < /BODY > tags. 
	EndContent(pCtxt);
}

void CNtIsapiWebExtension::Test(CHttpServerContext* pCtxt, double m_Height, double m_Weight, LPTSTR m_Sex)
 { 
    //Prints the < HTML > < BODY > tags. 
    StartContent(pCtxt); 
    //Prints the title. 
    WriteTitle(pCtxt); 
	*pCtxt << _T("<BR><BR<H3>测试结果如下：</H3><BR><BR>"); 
	//确定性别
    switch (m_Sex[0]) 
    { 
    //加法运算
    case '1' : 
		{
			if(m_Weight>=((m_Height-100)*1.2))
			{
				//显示结果
				*pCtxt << _T("<H3>你的体重严重超重!</H3><BR>"); 
			}
			else if(m_Weight>=((m_Height-100)*1.05))
			{
				//显示结果
				*pCtxt << _T("<H3>你的体重超重!</H3><BR>"); 
			}
			else if(m_Weight>=((m_Height-100)*0.9))
			{
				//显示结果
				*pCtxt << _T("<H3>你的体重正常!</H3><BR>"); 
			}
			else
			{
				//显示结果
				*pCtxt << _T("<H3>你的体重偏轻!</H3><BR>"); 
			}
		}
		break;
	case '2' : 
		{
			if(m_Weight>=((m_Height-105)*1.2))
			{
				//显示结果
				*pCtxt << _T("<H3>你的体重严重超重!</H3><BR>"); 
			}
			else if(m_Weight>=((m_Height-105)*1.05))
			{
				//显示结果
				*pCtxt << _T("<H3>你的体重超重!</H3><BR>"); 
			}
			else if(m_Weight>=((m_Height-105)*0.9))
			{
				//显示结果
				*pCtxt << _T("<H3>你的体重正常!</H3><BR>"); 
			}
			else
			{
				//显示结果
				*pCtxt << _T("<H3>你的体重偏轻!</H3><BR>"); 
			}
		}
		break;
    } 
    //Print < /HTML > < /BODY > tags. 
    EndContent(pCtxt); 
 }

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CNtIsapiWebExtension, CHttpServer)
	//{{AFX_MSG_MAP(CNtIsapiWebExtension)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0



///////////////////////////////////////////////////////////////////////
// If your extension will not use MFC, you'll need this code to make
// sure the extension objects can find the resource handle for the
// module.  If you convert your extension to not be dependent on MFC,
// remove the comments arounn the following AfxGetResourceHandle()
// and DllMain() functions, as well as the g_hInstance global.

/****

static HINSTANCE g_hInstance;

HINSTANCE AFXISAPI AfxGetResourceHandle()
{
	return g_hInstance;
}

BOOL WINAPI DllMain(HINSTANCE hInst, ULONG ulReason,
					LPVOID lpReserved)
{
	if (ulReason == DLL_PROCESS_ATTACH)
	{
		g_hInstance = hInst;
	}

	return TRUE;
}

****/
