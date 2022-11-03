// Ex23eView.cpp : implementation of the CEx23eView class
//

#include "stdafx.h"
#include "Ex23e.h"

#include "Ex23eDoc.h"
#include "Ex23eView.h"

#include "alarm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx23eView

IMPLEMENT_DYNCREATE(CEx23eView, CView)

BEGIN_MESSAGE_MAP(CEx23eView, CView)
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
END_MESSAGE_MAP()

// CEx23eView construction/destruction

CEx23eView::CEx23eView()
{
	// TODO: add construction code here

}

CEx23eView::~CEx23eView()
{
}

BOOL CEx23eView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEx23eView drawing

void CEx23eView::OnDraw(CDC* /*pDC*/)
{
	CEx23eDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


// CEx23eView diagnostics

#ifdef _DEBUG
void CEx23eView::AssertValid() const
{
	CView::AssertValid();
}

void CEx23eView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx23eDoc* CEx23eView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx23eDoc)));
	return (CEx23eDoc*)m_pDocument;
}
#endif //_DEBUG


// CEx23eView message handlers

void CEx23eView::OnBankoleLoad()
{
    if(m_bank.CreateInstance(__uuidof(Bank)) != S_OK) {
        AfxMessageBox("Bank component not found");
        return;
    }
}

void CEx23eView::OnUpdateBankoleLoad(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(m_bank.GetInterfacePtr() == NULL);
}

void CEx23eView::OnBankoleTest()
{
    try {
        m_bank->Deposit(20.0);
        m_bank->Withdrawal(15.0);
        TRACE("new balance = %f\n", m_bank->GetBalance());
    } catch(_com_error& e) {
        AfxMessageBox(e.ErrorMessage());
    }

}

void CEx23eView::OnUpdateBankoleTest(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(m_bank.GetInterfacePtr() != NULL);
}

void CEx23eView::OnBankoleUnload()
{
    m_bank.Release();
}

void CEx23eView::OnUpdateBankoleUnload(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(m_bank.GetInterfacePtr() != NULL);
}

void CEx23eView::OnClockoleCreatealarm()
{
    CAlarmDlg dlg;
    try {
        if (dlg.DoModal() == IDOK) {
            COleDateTime dt(2001, 12, 23, dlg.m_nHours, dlg.m_nMinutes, 
                dlg.m_nSeconds);
            LPDISPATCH pAlarm = m_clock->CreateAlarm(dt);
            m_alarm.Attach((IAlarm*) pAlarm);  // releases prior object!
            m_clock->RefreshWin();
        }
    } catch(_com_error& e) {
        AfxMessageBox(e.ErrorMessage());
    }
}

void CEx23eView::OnUpdateClockoleCreatealarm(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(m_clock.GetInterfacePtr() != NULL);
}

void CEx23eView::OnClockoleLoad()
{
    if(m_clock.CreateInstance(__uuidof(CEx23cDoc)) != S_OK) {
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

void CEx23eView::OnUpdateClockoleLoad(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(m_clock.GetInterfacePtr() == NULL);
}

void CEx23eView::OnClockoleRefreshtime()
{
    COleDateTime now = COleDateTime::GetCurrentTime();
    try {
        m_clock->PutTime(now);
        m_clock->RefreshWin();
    } catch(_com_error& e) {
        AfxMessageBox(e.ErrorMessage());
    }
}

void CEx23eView::OnUpdateClockoleRefreshtime(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(m_clock.GetInterfacePtr() != NULL);
}

void CEx23eView::OnClockoleUnload()
{
    m_clock.Release();
}

void CEx23eView::OnUpdateClockoleUnload(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(m_clock.GetInterfacePtr() != NULL);
}

void CEx23eView::OnDlloleGetdata()
{
    try {
        m_auto->DisplayDialog();
        COleVariant vaData = m_auto->GetTextData();
        ASSERT(vaData.vt == VT_BSTR);
        CString strTextData(vaData.bstrVal);
        long lData = m_auto->GetLongData();
        TRACE("CEx23dView::OnDlloleGetdata—long = %ld, text = %s\n",
              lData, strTextData);
    } catch(_com_error& e) {
        AfxMessageBox(e.ErrorMessage());
    }
}

void CEx23eView::OnUpdateDlloleGetdata(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(m_auto.GetInterfacePtr() != NULL);
}

void CEx23eView::OnDlloleLoad()
{
    if(m_auto.CreateInstance(__uuidof(Ex23bAuto)) != S_OK) {
        AfxMessageBox("Ex23bAuto component not found");
        return;
    }
    IEx23bAuto* pEx23bAuto = 0;
    m_auto.QueryInterface(__uuidof(IEx23bAuto), (void**)&pEx23bAuto);
    if(pEx23bAuto) {
        pEx23bAuto->PutLongData(42);
        pEx23bAuto->Release();
    }
}

void CEx23eView::OnUpdateDlloleLoad(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(m_auto.GetInterfacePtr() == NULL);
}

void CEx23eView::OnDlloleUnload()
{
    m_auto.Release();
}

void CEx23eView::OnUpdateDlloleUnload(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(m_auto.GetInterfacePtr() != NULL);
}

