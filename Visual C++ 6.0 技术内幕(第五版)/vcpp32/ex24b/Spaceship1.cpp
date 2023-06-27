// Spaceship1.cpp : implementation file
//

#include "stdafx.h"
#include "ex24b.h"
#include "Spaceship1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpaceship

IMPLEMENT_DYNCREATE(CSpaceship, CCmdTarget)

CSpaceship::CSpaceship()
{
	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	
	AfxOleLockApp();
}

CSpaceship::~CSpaceship()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	AfxOleUnlockApp();
}


void CSpaceship::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CSpaceship, CCmdTarget)
	//{{AFX_MSG_MAP(CSpaceship)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CSpaceship, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CSpaceship)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ISpaceship to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {9D4F0917-EA79-11D1-B30A-0080C7360DC1}
static const IID IID_ISpaceship =
{ 0x9d4f0917, 0xea79, 0x11d1, { 0xb3, 0xa, 0x0, 0x80, 0xc7, 0x36, 0xd, 0xc1 } };

BEGIN_INTERFACE_MAP(CSpaceship, CCmdTarget)
	INTERFACE_PART(CSpaceship, IID_ISpaceship, Dispatch)
END_INTERFACE_MAP()

// {9D4F0918-EA79-11D1-B30A-0080C7360DC1}
IMPLEMENT_OLECREATE(CSpaceship, "ex24b.Spaceship", 0x9d4f0918, 0xea79, 0x11d1, 0xb3, 0xa, 0x0, 0x80, 0xc7, 0x36, 0xd, 0xc1)

/////////////////////////////////////////////////////////////////////////////
// CSpaceship message handlers
