// ex25cDoc.cpp : implementation of the CEx25cDoc class
//

#include "stdafx.h"
#include "ex25c.h"

#include "Alarm.h"
#include "ex25cDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx25cDoc

IMPLEMENT_DYNCREATE(CEx25cDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx25cDoc, CDocument)
	//{{AFX_MSG_MAP(CEx25cDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CEx25cDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CEx25cDoc)
	DISP_PROPERTY_NOTIFY(CEx25cDoc, "Time", m_time, OnTimeChanged, VT_DATE)
	DISP_FUNCTION(CEx25cDoc, "ShowWin", ShowWin, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CEx25cDoc, "CreateAlarm", CreateAlarm, VT_DISPATCH, VTS_DATE)
	DISP_FUNCTION(CEx25cDoc, "RefreshWin", Refresh, VT_EMPTY, VTS_NONE)
	DISP_PROPERTY_PARAM(CEx25cDoc, "Figure", GetFigure, SetFigure, VT_VARIANT, VTS_I2)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IEx25c to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {A9515B02-5B85-11D0-848F-00400526305B}
static const IID IID_IEx25c =
{ 0xa9515b02, 0x5b85, 0x11d0, { 0x84, 0x8f, 0x0, 0x40, 0x5, 0x26, 0x30, 0x5b } };

BEGIN_INTERFACE_MAP(CEx25cDoc, CDocument)
	INTERFACE_PART(CEx25cDoc, IID_IEx25c, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx25cDoc construction/destruction

CEx25cDoc::CEx25cDoc()
{
	// TODO: add one-time construction code here

	TRACE("Entering CEx25cDoc ctor\n");
	m_time = COleDateTime(0, 0, 0, 5, 10, 15);
	// bogus initial values
	m_strFigure[0] = "XII"; m_strFigure[1] = "III";
	m_strFigure[2] = "VI"; m_strFigure[3] = "IX";
	m_pAlarm = NULL;

	EnableAutomation();

	AfxOleLockApp();
}

CEx25cDoc::~CEx25cDoc()
{
	AfxOleUnlockApp();
}

BOOL CEx25cDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx25cDoc serialization

void CEx25cDoc::Serialize(CArchive& ar)
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

/////////////////////////////////////////////////////////////////////////////
// CEx25cDoc diagnostics

#ifdef _DEBUG
void CEx25cDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx25cDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx25cDoc commands

void CEx25cDoc::OnTimeChanged() 
{
	// TODO: Add notification handler code

}

VARIANT CEx25cDoc::GetFigure(short n) 
{
	TRACE("Entering CEx25cDoc::GetFigure -- n = %d m_strFigure[n] = %s\n",
           n, m_strFigure[n]);
	return COleVariant(m_strFigure[n]).Detach();
}

void CEx25cDoc::SetFigure(short n, const VARIANT FAR& newValue) 
{
	TRACE("Entering CEx25cDoc::SetFigure -- n = %d, vt = %d\n", n, 
		   newValue.vt);
	COleVariant vaTemp;
	vaTemp.ChangeType(VT_BSTR, (COleVariant*) &newValue);
	m_strFigure[n] = vaTemp.bstrVal; // converts double-to-single
}

void CEx25cDoc::ShowWin() 
{
	TRACE("Entering CEx25cDoc::ShowWin\n");
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

LPDISPATCH CEx25cDoc::CreateAlarm(DATE time) 
{
	TRACE("Entering CEx25cDoc::CreateAlarm, time = %f\n", time);
	// OLE deletes any prior CAlarm object
	m_pAlarm = new CAlarm(time);
	return m_pAlarm->GetIDispatch(FALSE);   // no AddRef here
}

void CEx25cDoc::Refresh() 
{
	TRACE("Entering CEx25cDoc::Refresh\n");
	UpdateAllViews(NULL);  // invalidates the one-and-only view
//	AfxGetApp()->m_pMainWnd->BringWindowToTop();
}

BOOL CEx25cDoc::SaveModified() 
{
	return TRUE;
}
