// Ex21a.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Ex21a.h"
#include "Ex21aDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx21aApp

BEGIN_MESSAGE_MAP(CEx21aApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CEx21aApp construction

CEx21aApp::CEx21aApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CEx21aApp object

CEx21aApp theApp;


// CEx21aApp initialization

BOOL CEx21aApp::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();


	CEx21aDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
