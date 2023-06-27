// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "usespaceshipsvr.h"
#include "DlgProxy.h"
#include "usespaceshipsvrDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUsespaceshipsvrDlgAutoProxy

IMPLEMENT_DYNCREATE(CUsespaceshipsvrDlgAutoProxy, CCmdTarget)

CUsespaceshipsvrDlgAutoProxy::CUsespaceshipsvrDlgAutoProxy()
{
	EnableAutomation();
	
	// To keep the application running as long as an automation 
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT (AfxGetApp()->m_pMainWnd != NULL);
	ASSERT_VALID (AfxGetApp()->m_pMainWnd);
	ASSERT_KINDOF(CUsespaceshipsvrDlg, AfxGetApp()->m_pMainWnd);
	m_pDialog = (CUsespaceshipsvrDlg*) AfxGetApp()->m_pMainWnd;
	m_pDialog->m_pAutoProxy = this;
}

CUsespaceshipsvrDlgAutoProxy::~CUsespaceshipsvrDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CUsespaceshipsvrDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CUsespaceshipsvrDlgAutoProxy, CCmdTarget)
	//{{AFX_MSG_MAP(CUsespaceshipsvrDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CUsespaceshipsvrDlgAutoProxy, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CUsespaceshipsvrDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IUsespaceshipsvr to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {FACE88F9-06C8-11D2-B77D-0060081EE21C}
static const IID IID_IUsespaceshipsvr =
{ 0xface88f9, 0x6c8, 0x11d2, { 0xb7, 0x7d, 0x0, 0x60, 0x8, 0x1e, 0xe2, 0x1c } };

BEGIN_INTERFACE_MAP(CUsespaceshipsvrDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CUsespaceshipsvrDlgAutoProxy, IID_IUsespaceshipsvr, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {FACE88F7-06C8-11D2-B77D-0060081EE21C}
IMPLEMENT_OLECREATE2(CUsespaceshipsvrDlgAutoProxy, "Usespaceshipsvr.Application", 0xface88f7, 0x6c8, 0x11d2, 0xb7, 0x7d, 0x0, 0x60, 0x8, 0x1e, 0xe2, 0x1c)

/////////////////////////////////////////////////////////////////////////////
// CUsespaceshipsvrDlgAutoProxy message handlers
