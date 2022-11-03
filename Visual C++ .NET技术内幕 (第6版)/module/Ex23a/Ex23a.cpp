// Ex23a.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Ex23a.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx23aApp

BEGIN_MESSAGE_MAP(CEx23aApp, CWinApp)
END_MESSAGE_MAP()


// CEx23aApp construction

CEx23aApp::CEx23aApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CEx23aApp object

CEx23aApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x60BCA7D2, 0x14D1, 0x4832, { 0xA2, 0x78, 0x50, 0x67, 0xC, 0xD9, 0x97, 0x5E } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// CEx23aApp initialization

BOOL CEx23aApp::InitInstance()
{
	CWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	// Parse command line for automation or reg/unreg switches.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// App was launched with /Embedding or /Automation switch.
	// Run app as automation server.
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Register class factories via CoRegisterClassObject().
		COleTemplateServer::RegisterAll();
        return TRUE;
	}
	// App was launched with /Unregserver or /Unregister switch.  Remove
	// entries from the registry.
	else if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
	{
		COleObjectFactory::UpdateRegistryAll(FALSE);
		AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor);
		return FALSE;
	}
	// App was launched standalone or with other switches (e.g. /Register
	// or /Regserver).  Update registry entries, including typelibrary.
	else
	{
		COleObjectFactory::UpdateRegistryAll();
		AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid);
		if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppRegister)
			return FALSE;
	}

	return FALSE;
}
