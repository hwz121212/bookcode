// Bank.cpp : implementation file
//

#include "stdafx.h"
#include "Ex23a.h"
#include "Bank.h"


// CBank

IMPLEMENT_DYNCREATE(CBank, CCmdTarget)
CBank::CBank()
{
	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	
	AfxOleLockApp();

    m_dBalance = 0.0;
}

CBank::~CBank()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	AfxOleUnlockApp();
}


void CBank::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CBank, CCmdTarget)
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CBank, CCmdTarget)
    DISP_FUNCTION_ID(CBank, "Withdrawal", dispidWithdrawal, Withdrawal, VT_R8, VTS_R8)
    DISP_FUNCTION_ID(CBank, "Deposit", dispidDeposit, Deposit, VT_EMPTY, VTS_R8)
    DISP_PROPERTY_EX_ID(CBank, "Balance", dispidBalance, GetBalance, SetBalance, VT_R8)
END_DISPATCH_MAP()

// Note: we add support for IID_IBank to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {8BAD2B0C-62CC-4952-811C-C736DA06858E}
static const IID IID_IBank =
{ 0x8BAD2B0C, 0x62CC, 0x4952, { 0x81, 0x1C, 0xC7, 0x36, 0xDA, 0x6, 0x85, 0x8E } };

BEGIN_INTERFACE_MAP(CBank, CCmdTarget)
	INTERFACE_PART(CBank, IID_IBank, Dispatch)
END_INTERFACE_MAP()

// {3EC6FA59-9F9F-4619-9F62-BA5FE37176F0}
IMPLEMENT_OLECREATE_FLAGS(CBank, "Ex23a.Bank", 
	afxRegApartmentThreading, 0x3ec6fa59, 0x9f9f, 
    0x4619, 0x9f, 0x62, 0xba, 0x5f, 0xe3, 0x71, 
    0x76, 0xf0)

// CBank message handlers

DOUBLE CBank::Withdrawal(DOUBLE dAmount)
{
    AFX_MANAGE_STATE(AfxGetAppModuleState());

    if (dAmount < 0.0) {
        return 0.0;
    }
    if (dAmount <= m_dBalance) {
        m_dBalance -= dAmount;
         return dAmount;
    }
    double dTemp = m_dBalance;
    m_dBalance = 0.0;
    return dTemp;
}

void CBank::Deposit(DOUBLE dAmount)
{
    AFX_MANAGE_STATE(AfxGetAppModuleState());

    if (dAmount < 0.0) {
        return;
    }
    m_dBalance += dAmount;
}

DOUBLE CBank::GetBalance(void)
{
    AFX_MANAGE_STATE(AfxGetAppModuleState());

    return m_dBalance;
}

void CBank::SetBalance(DOUBLE newVal)
{
    AFX_MANAGE_STATE(AfxGetAppModuleState());

    TRACE("Sorry, Dave, I can’t do that!\n");
}
