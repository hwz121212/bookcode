// Ex25bAuto.cpp : implementation file
//

#include "stdafx.h"
#include "ex25b.h"
#include "Ex25bAuto.h"
#include "Promptdl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx25bAuto

IMPLEMENT_DYNCREATE(CEx25bAuto, CCmdTarget)

CEx25bAuto::CEx25bAuto()
{
	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.

    ::VariantInit(&m_vaTextData); // necessary initialization
    m_lData = 0;
	
	AfxOleLockApp();
}

CEx25bAuto::~CEx25bAuto()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	AfxOleUnlockApp();
}


void CEx25bAuto::OnFinalRelease()
{
	// When the last reference for an automation object is released,
	//  OnFinalRelease is called.  The base class will automatically
	//  delete the object.  Add additional cleanup required for your
	//  object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CEx25bAuto, CCmdTarget)
	//{{AFX_MSG_MAP(CEx25bAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CEx25bAuto, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CEx25bAuto)
	DISP_PROPERTY_NOTIFY(CEx25bAuto, "LongData", m_lData, OnLongDataChanged, VT_I4)
	DISP_PROPERTY_NOTIFY(CEx25bAuto, "TextData", m_vaTextData, OnTextDataChanged, VT_VARIANT)
	DISP_FUNCTION(CEx25bAuto, "DisplayDialog", DisplayDialog, VT_BOOL, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IEx25bAuto to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {A9515AD7-5B85-11D0-848F-00400526305B}
static const IID IID_IEx25bAuto =
{ 0xa9515ad7, 0x5b85, 0x11d0, { 0x84, 0x8f, 0x0, 0x40, 0x5, 0x26, 0x30, 
    0x5b } };

BEGIN_INTERFACE_MAP(CEx25bAuto, CCmdTarget)
	INTERFACE_PART(CEx25bAuto, IID_IEx25bAuto, Dispatch)
END_INTERFACE_MAP()

// {A9515AD8-5B85-11D0-848F-00400526305B}
IMPLEMENT_OLECREATE(CEx25bAuto, "ex25b.Auto", 0xa9515ad8, 0x5b85, 
    0x11d0, 0x84, 0x8f, 0x0, 0x40, 0x5, 0x26, 0x30, 0x5b)

/////////////////////////////////////////////////////////////////////////////
// CEx25bAuto message handlers

void CEx25bAuto::OnLongDataChanged() 
{
    TRACE("CEx25bAuto::OnLongDataChanged\n");
}

void CEx25bAuto::OnTextDataChanged() 
{
    TRACE("CEx25bAuto::OnTextDataChanged\n");
}

BOOL CEx25bAuto::DisplayDialog() 
{
    TRACE("Entering CEx25bAuto::DisplayDialog %p\n", this);
    BOOL bRet = TRUE;
    AfxLockTempMaps();  // See MFC Tech Note #3
    CWnd* pTopWnd = CWnd::FromHandle(::GetTopWindow(NULL));
    try {
      CPromptDlg dlg(pTopWnd);
      if (m_vaTextData.vt == VT_BSTR){
        dlg.m_strData = m_vaTextData.bstrVal; // converts double-byte
                                              //  character to
		                                      //  single-byte 
		                                      //  character                                                                                                                      
      }
      dlg.m_lData = m_lData;
      if (dlg.DoModal() == IDOK) {
        m_vaTextData = COleVariant(dlg.m_strData).Detach();
        m_lData = dlg.m_lData;
        bRet = TRUE;
      }
      else {
        bRet =  FALSE;
      }
    }
    catch (CException* pe) {
      TRACE("Exception: failure to display dialog\n");
      bRet =  FALSE;
	  pe->Delete();
    }
    AfxUnlockTempMaps();
    return bRet;
}
