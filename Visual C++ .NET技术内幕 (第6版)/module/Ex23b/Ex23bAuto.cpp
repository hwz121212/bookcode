// Ex23bAuto.cpp : implementation file
//

#include "stdafx.h"
#include "Ex23b.h"
#include "Ex23bAuto.h"
#include "Promptdlg.h"

// CEx23bAuto

IMPLEMENT_DYNCREATE(CEx23bAuto, CCmdTarget)
CEx23bAuto::CEx23bAuto()
{
	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.

    ::VariantInit(&m_vaTextData); // necessary initialization
    m_lData = 0;
	
	AfxOleLockApp();
}

CEx23bAuto::~CEx23bAuto()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	AfxOleUnlockApp();
}


void CEx23bAuto::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CEx23bAuto, CCmdTarget)
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CEx23bAuto, CCmdTarget)
    DISP_PROPERTY_NOTIFY_ID(CEx23bAuto, "LongData", dispidLongData, m_lData, OnLongDataChanged, VT_I4)
    DISP_PROPERTY_NOTIFY_ID(CEx23bAuto, "TextData", dispidTextData, m_vaTextData, OnTextDataChanged, VT_VARIANT)
    DISP_FUNCTION_ID(CEx23bAuto, "DisplayDialog", dispidDisplayDialog, DisplayDialog, VT_BOOL, VTS_NONE)
END_DISPATCH_MAP()

// Note: we add support for IID_IEx23bAuto to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {125FECB2-734D-49FD-95C7-FE44B77FDE2C}
static const IID IID_IEx23bAuto =
{ 0x125FECB2, 0x734D, 0x49FD, { 0x95, 0xC7, 0xFE, 0x44, 0xB7, 0x7F, 0xDE, 0x2C } };

BEGIN_INTERFACE_MAP(CEx23bAuto, CCmdTarget)
	INTERFACE_PART(CEx23bAuto, IID_IEx23bAuto, Dispatch)
END_INTERFACE_MAP()

// {BAF3D9ED-4518-43CA-B017-2EBA332CB618}
IMPLEMENT_OLECREATE_FLAGS(CEx23bAuto, "Ex23b.Ex23bAuto", afxRegApartmentThreading, 0xbaf3d9ed, 0x4518, 0x43ca, 0xb0, 0x17, 0x2e, 0xba, 0x33, 0x2c, 0xb6, 0x18)


// CEx23bAuto message handlers

void CEx23bAuto::OnLongDataChanged(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    TRACE("CEx23bAuto::OnLongDataChanged\n");
}

void CEx23bAuto::OnTextDataChanged(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    TRACE("CEx23bAuto::OnTextDataChanged\n");
}

VARIANT_BOOL CEx23bAuto::DisplayDialog(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    VARIANT_BOOL bRet;

    TRACE("Entering CEx23bAuto::DisplayDialog %p\n", this);
    bRet = TRUE;
    AfxLockTempMaps();  // See MFC Tech Note #3
    CWnd* pTopWnd = CWnd::FromHandle(::GetTopWindow(NULL));
    try {
        CPromptDlg dlg /*(pTopWnd)*/;
        if (m_vaTextData.vt == VT_BSTR){
            dlg.m_strData = m_vaTextData.bstrVal; // converts 
                                                  //  double-byte
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
