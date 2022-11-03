// Ex23cDoc.cpp : implementation of the CEx23cDoc class
//

#include "stdafx.h"
#include "Ex23c.h"

#include "Alarm.h"
#include "Ex23cDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx23cDoc

IMPLEMENT_DYNCREATE(CEx23cDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx23cDoc, CDocument)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CEx23cDoc, CDocument)
    DISP_PROPERTY_NOTIFY_ID(CEx23cDoc, "Time", dispidTime, m_time, OnTimeChanged, VT_DATE)
    DISP_FUNCTION_ID(CEx23cDoc, "ShowWin", dispidShowWin, ShowWin, VT_EMPTY, VTS_NONE)
    DISP_FUNCTION_ID(CEx23cDoc, "CreateAlarm", dispidCreateAlarm, CreateAlarm, VT_DISPATCH, VTS_DATE)
    DISP_FUNCTION_ID(CEx23cDoc, "RefreshWin", dispidRefreshWin, RefreshWin, VT_EMPTY, VTS_NONE)
    DISP_PROPERTY_PARAM_ID(CEx23cDoc, "Figure", dispidFigure, GetFigure, SetFigure, VT_VARIANT, VTS_I2)
END_DISPATCH_MAP()

// Note: we add support for IID_IEx23c to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {74084826-F896-446F-8414-3FF2BB911A63}
static const IID IID_IEx23c =
{ 0x74084826, 0xF896, 0x446F, { 0x84, 0x14, 0x3F, 0xF2, 0xBB, 0x91, 0x1A, 0x63 } };

BEGIN_INTERFACE_MAP(CEx23cDoc, CDocument)
	INTERFACE_PART(CEx23cDoc, IID_IEx23c, Dispatch)
END_INTERFACE_MAP()


// CEx23cDoc construction/destruction

CEx23cDoc::CEx23cDoc()
{
	// TODO: add one-time construction code here

	TRACE("Entering CEx23cDoc ctor\n");
	m_time = COleDateTime(0, 0, 0, 5, 10, 15);
	// bogus initial values
	m_strFigure[0] = "XII"; m_strFigure[1] = "III";
	m_strFigure[2] = "VI"; m_strFigure[3] = "IX";
	m_pAlarm = NULL;

	EnableAutomation();

	AfxOleLockApp();
}

CEx23cDoc::~CEx23cDoc()
{
	AfxOleUnlockApp();
}

BOOL CEx23cDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx23cDoc serialization

void CEx23cDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CEx23cDoc diagnostics

#ifdef _DEBUG
void CEx23cDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx23cDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx23cDoc commands

void CEx23cDoc::OnTimeChanged(void)
{
    AFX_MANAGE_STATE(AfxGetAppModuleState());

    // TODO: Add your property handler code here

    SetModifiedFlag();
}

void CEx23cDoc::ShowWin(void)
{
    AFX_MANAGE_STATE(AfxGetAppModuleState());
	TRACE("Entering CEx23cDoc::ShowWin\n");
	CRect rectWindow;
	CWnd* pFrm = AfxGetApp()->m_pMainWnd;
	pFrm->GetWindowRect(rectWindow);
	WINDOWPLACEMENT wndpl;
	wndpl.length = sizeof(WINDOWPLACEMENT);
	wndpl.showCmd = SW_SHOWNORMAL;
	wndpl.rcNormalPosition.left = rectWindow.left;
	wndpl.rcNormalPosition.top = rectWindow.top;
	wndpl.rcNormalPosition.right = rectWindow.left + 150;
	wndpl.rcNormalPosition.bottom = rectWindow.top + 150;
	pFrm->SetWindowPlacement(&wndpl);
	pFrm->ShowWindow(AfxGetApp()->m_nCmdShow);
	pFrm->UpdateWindow();
	pFrm->BringWindowToTop();
}

IDispatch* CEx23cDoc::CreateAlarm(DATE time)
{
    AFX_MANAGE_STATE(AfxGetAppModuleState());

	TRACE("Entering CEx23cDoc::CreateAlarm, time = %f\n", time);
	// OLE deletes any prior CAlarm object
	m_pAlarm = new CAlarm(time);
	return m_pAlarm->GetIDispatch(FALSE);   // no AddRef here
}

void CEx23cDoc::RefreshWin(void)
{
    AFX_MANAGE_STATE(AfxGetAppModuleState());
	TRACE("Entering CEx23cDoc::Refresh\n");
	UpdateAllViews(NULL);  // invalidates the one-and-only view

}

VARIANT CEx23cDoc::GetFigure(SHORT n)
{
    AFX_MANAGE_STATE(AfxGetAppModuleState());

	TRACE("Entering CEx23cDoc::GetFigure -- n = %d m_strFigure[n] = %s\n",
           n, m_strFigure[n]);
	return COleVariant(m_strFigure[n]).Detach();
}

void CEx23cDoc::SetFigure(SHORT n, VARIANT FAR& newVal)
{
    AFX_MANAGE_STATE(AfxGetAppModuleState());

	TRACE("Entering CEx23cDoc::SetFigure -- n = %d, vt = %d\n", n, 
		   newVal.vt);
	COleVariant vaTemp;
	vaTemp.ChangeType(VT_BSTR, (COleVariant*) &newVal);
	m_strFigure[n] = vaTemp.bstrVal; // converts double-to-single

    SetModifiedFlag();
}
