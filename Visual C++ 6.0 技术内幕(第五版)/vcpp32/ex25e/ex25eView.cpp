// ex25eView.cpp : implementation of the CEx25eView class
//

#include "stdafx.h"
#include "ex25e.h"

#include "ex25eDoc.h"
#include "ex25eView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx25eView

IMPLEMENT_DYNCREATE(CEx25eView, CView)

BEGIN_MESSAGE_MAP(CEx25eView, CView)
	//{{AFX_MSG_MAP(CEx25eView)
	ON_COMMAND(ID_BANKOLE_LOAD, OnBankoleLoad)
	ON_UPDATE_COMMAND_UI(ID_BANKOLE_LOAD, OnUpdateBankoleLoad)
	ON_COMMAND(ID_BANKOLE_TEST, OnBankoleTest)
	ON_UPDATE_COMMAND_UI(ID_BANKOLE_TEST, OnUpdateBankoleTest)
	ON_COMMAND(ID_BANKOLE_UNLOAD, OnBankoleUnload)
	ON_UPDATE_COMMAND_UI(ID_BANKOLE_UNLOAD, OnUpdateBankoleUnload)
	ON_COMMAND(ID_CLOCKOLE_CREATEALARM, OnClockoleCreatealarm)
	ON_UPDATE_COMMAND_UI(ID_CLOCKOLE_CREATEALARM, OnUpdateClockoleCreatealarm)
	ON_COMMAND(ID_CLOCKOLE_LOAD, OnClockoleLoad)
	ON_UPDATE_COMMAND_UI(ID_CLOCKOLE_LOAD, OnUpdateClockoleLoad)
	ON_COMMAND(ID_CLOCKOLE_REFRESHTIME, OnClockoleRefreshtime)
	ON_UPDATE_COMMAND_UI(ID_CLOCKOLE_REFRESHTIME, OnUpdateClockoleRefreshtime)
	ON_COMMAND(ID_CLOCKOLE_UNLOAD, OnClockoleUnload)
	ON_UPDATE_COMMAND_UI(ID_CLOCKOLE_UNLOAD, OnUpdateClockoleUnload)
	ON_COMMAND(ID_DLLOLE_GETDATA, OnDlloleGetdata)
	ON_UPDATE_COMMAND_UI(ID_DLLOLE_GETDATA, OnUpdateDlloleGetdata)
	ON_COMMAND(ID_DLLOLE_LOAD, OnDlloleLoad)
	ON_UPDATE_COMMAND_UI(ID_DLLOLE_LOAD, OnUpdateDlloleLoad)
	ON_COMMAND(ID_DLLOLE_UNLOAD, OnDlloleUnload)
	ON_UPDATE_COMMAND_UI(ID_DLLOLE_UNLOAD, OnUpdateDlloleUnload)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx25eView construction/destruction

CEx25eView::CEx25eView()
{
	// TODO: add construction code here

}

CEx25eView::~CEx25eView()
{
}

BOOL CEx25eView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx25eView drawing

void CEx25eView::OnDraw(CDC* pDC)
{
	CEx25eDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDC->TextOut(0, 0, "Uses #import.");
	pDC->TextOut(0, 25, "Run this program from the debugger to see test output.");
	pDC->TextOut(0, 50, "Components must be built and registered prior to loading.");
}

/////////////////////////////////////////////////////////////////////////////
// CEx25eView diagnostics

#ifdef _DEBUG
void CEx25eView::AssertValid() const
{
	CView::AssertValid();
}

void CEx25eView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx25eDoc* CEx25eView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx25eDoc)));
	return (CEx25eDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx25eView message handlers

void CEx25eView::OnBankoleLoad() 
{
	if(m_bank.CreateInstance(__uuidof(Bank)) != S_OK) {
		AfxMessageBox("Bank component not found");
		return;
    }
}

void CEx25eView::OnUpdateBankoleLoad(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bank.GetInterfacePtr() == NULL);
}

void CEx25eView::OnBankoleTest() 
{
	try {
	   m_bank->Deposit(20.0);
	   m_bank->Withdrawal(15.0);
	   TRACE("new balance = %f\n", m_bank->GetBalance());
    } catch(_com_error& e) {
		AfxMessageBox(e.ErrorMessage());
    }
}

void CEx25eView::OnUpdateBankoleTest(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bank.GetInterfacePtr() != NULL);
}

void CEx25eView::OnBankoleUnload() 
{
	m_bank.Release();
}

void CEx25eView::OnUpdateBankoleUnload(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bank.GetInterfacePtr() != NULL);
}

void CEx25eView::OnClockoleCreatealarm() 
{
	CAlarmDialog dlg;
	try {
		if (dlg.DoModal() == IDOK) {
			COleDateTime dt(1995, 12, 23, dlg.m_nHours, dlg.m_nMinutes, 
				dlg.m_nSeconds);
			LPDISPATCH pAlarm = m_clock->CreateAlarm(dt);
			m_alarm.Attach((IAlarm*) pAlarm);  // releases prior object!
			m_clock->RefreshWin();
		}
    } catch(_com_error& e) {
		AfxMessageBox(e.ErrorMessage());
    }
}

void CEx25eView::OnUpdateClockoleCreatealarm(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_clock.GetInterfacePtr() != NULL);
}

void CEx25eView::OnClockoleLoad() 
{
   if(m_clock.CreateInstance(__uuidof(Document)) != S_OK) {
		AfxMessageBox("Clock component not found");
		return;
   }
   try {
	   m_clock->PutFigure(0, COleVariant("XII"));
	   m_clock->PutFigure(1, COleVariant("III"));
	   m_clock->PutFigure(2, COleVariant("VI"));
	   m_clock->PutFigure(3, COleVariant("IX"));
	   OnClockoleRefreshtime();
	   m_clock->ShowWin();
    } catch(_com_error& e) {
		AfxMessageBox(e.ErrorMessage());
    }
}

void CEx25eView::OnUpdateClockoleLoad(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_clock.GetInterfacePtr() == NULL);
}

void CEx25eView::OnClockoleRefreshtime() 
{
   COleDateTime now = COleDateTime::GetCurrentTime();
	try {
	   m_clock->PutTime(now);
	   m_clock->RefreshWin();
    } catch(_com_error& e) {
		AfxMessageBox(e.ErrorMessage());
    }
}

void CEx25eView::OnUpdateClockoleRefreshtime(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_clock.GetInterfacePtr() != NULL);
}

void CEx25eView::OnClockoleUnload() 
{
	m_clock.Release();
}

void CEx25eView::OnUpdateClockoleUnload(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_clock.GetInterfacePtr() != NULL);
}

void CEx25eView::OnDlloleGetdata() 
{
	try {
	   m_auto->DisplayDialog();
	   COleVariant vaData = m_auto->GetTextData();
	   ASSERT(vaData.vt == VT_BSTR);
	   CString strTextData = vaData.bstrVal;
	   long lData = m_auto->GetLongData();
	   TRACE("CEx25dView::OnDlloleGetdata -- long = %ld, text = %s\n",
			 lData, strTextData);
    } catch(_com_error& e) {
		AfxMessageBox(e.ErrorMessage());
    }
}

void CEx25eView::OnUpdateDlloleGetdata(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_auto.GetInterfacePtr() != NULL);
}

void CEx25eView::OnDlloleLoad() 
{
	if(m_auto.CreateInstance(__uuidof(Ex25bAuto)) != S_OK) {
		AfxMessageBox("Ex25bAuto component not found");
		return;
   }
}

void CEx25eView::OnUpdateDlloleLoad(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_auto.GetInterfacePtr() == NULL);
}

void CEx25eView::OnDlloleUnload() 
{
	m_auto.Release();
}

void CEx25eView::OnUpdateDlloleUnload(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_auto.GetInterfacePtr() != NULL);
}
