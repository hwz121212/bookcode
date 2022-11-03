// Ex23dView.cpp : implementation of the CEx23dView class
//

#include "stdafx.h"
#include "Ex23d.h"
#include "alarmdialog.h"
#include "Ex23dDoc.h"
#include "Ex23dView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx23dView

IMPLEMENT_DYNCREATE(CEx23dView, CView)

BEGIN_MESSAGE_MAP(CEx23dView, CView)
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
    ON_COMMAND(ID_EXCELOLE_EXECUTE, OnExceloleExecute)
    ON_UPDATE_COMMAND_UI(ID_EXCELOLE_EXECUTE, OnUpdateExceloleExecute)
    ON_COMMAND(ID_EXCELOLE_LOAD, OnExceloleLoad)
    ON_UPDATE_COMMAND_UI(ID_EXCELOLE_LOAD, OnUpdateExceloleLoad)
    ON_COMMAND(ID_DLLOLE_UNLOAD, OnDlloleUnload)
    ON_UPDATE_COMMAND_UI(ID_DLLOLE_UNLOAD, OnUpdateDlloleUnload)
END_MESSAGE_MAP()

// CEx23dView construction/destruction

CEx23dView::CEx23dView()
{
	// TODO: add construction code here

}

CEx23dView::~CEx23dView()
{
}

BOOL CEx23dView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEx23dView drawing

void CEx23dView::OnDraw(CDC* pDC)
{
    CEx23dDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
	pDC->TextOut(0, 0, "Uses COleDispatchDriver.");
	pDC->TextOut(0, 25, "Run this program from the debugger to see test output.");
	pDC->TextOut(0, 50, "Components must be built and registered prior to loading.");
}


// CEx23dView diagnostics

#ifdef _DEBUG
void CEx23dView::AssertValid() const
{
	CView::AssertValid();
}

void CEx23dView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx23dDoc* CEx23dView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx23dDoc)));
	return (CEx23dDoc*)m_pDocument;
}
#endif //_DEBUG


// CEx23dView message handlers

void CEx23dView::OnBankoleLoad()
{
   if(!m_bank.CreateDispatch("Ex23a.Bank")) {
		AfxMessageBox("Ex23a.Bank component not found");
		return;
   }
}

void CEx23dView::OnUpdateBankoleLoad(CCmdUI *pCmdUI)
{
   pCmdUI->Enable(m_bank.m_lpDispatch == NULL);
}

void CEx23dView::OnBankoleTest()
{
   m_bank.Deposit(20.0);
   m_bank.Withdrawal(15.0);
   TRACE("new balance = %f\n", m_bank.GetBalance());
}

void CEx23dView::OnUpdateBankoleTest(CCmdUI *pCmdUI)
{
   pCmdUI->Enable(m_bank.m_lpDispatch != NULL);
}

void CEx23dView::OnBankoleUnload()
{
   m_bank.ReleaseDispatch();
}

void CEx23dView::OnUpdateBankoleUnload(CCmdUI *pCmdUI)
{
   pCmdUI->Enable(m_bank.m_lpDispatch != NULL);
}

void CEx23dView::OnClockoleCreatealarm()
{
	CAlarmDialog dlg;
	if (dlg.DoModal() == IDOK) {
		COleDateTime dt(2002, 12, 23, dlg.m_nHours, dlg.m_nMinutes, 
			dlg.m_nSeconds);
		LPDISPATCH pAlarm = m_clock.CreateAlarm(dt);
		m_alarm.AttachDispatch(pAlarm);  // releases prior object!
		m_clock.RefreshWin();
	}
}

void CEx23dView::OnUpdateClockoleCreatealarm(CCmdUI *pCmdUI)
{
   pCmdUI->Enable(m_clock.m_lpDispatch != NULL);
}

void CEx23dView::OnClockoleLoad()
{
   if(!m_clock.CreateDispatch("Ex23c.Document")) {
		AfxMessageBox("Ex23c.Document component not found");
		return;
   }
   m_clock.put_Figure(0, COleVariant("XII"));
   m_clock.put_Figure(1, COleVariant("III"));
   m_clock.put_Figure(2, COleVariant("VI"));
   m_clock.put_Figure(3, COleVariant("IX"));
   OnClockoleRefreshtime();
   m_clock.ShowWin();
}

void CEx23dView::OnUpdateClockoleLoad(CCmdUI *pCmdUI)
{
   pCmdUI->Enable(m_clock.m_lpDispatch == NULL);
}

void CEx23dView::OnClockoleRefreshtime()
{
   COleDateTime now = COleDateTime::GetCurrentTime();
   m_clock.SetTime(now);
   m_clock.RefreshWin();
}

void CEx23dView::OnUpdateClockoleRefreshtime(CCmdUI *pCmdUI)
{
   pCmdUI->Enable(m_clock.m_lpDispatch != NULL);
}

void CEx23dView::OnClockoleUnload()
{
   m_clock.ReleaseDispatch();
}

void CEx23dView::OnUpdateClockoleUnload(CCmdUI *pCmdUI)
{
   pCmdUI->Enable(m_clock.m_lpDispatch != NULL);
}

void CEx23dView::OnDlloleGetdata()
{
   m_auto.DisplayDialog();
   COleVariant vaData = m_auto.GetTextData();
   ASSERT(vaData.vt == VT_BSTR);
   CString strTextData(vaData.bstrVal);
   long lData = m_auto.GetLongData();
   TRACE("CEx23dView::OnDlloleGetdata -- long = %ld, text = %s\n",
         lData, strTextData);
}

void CEx23dView::OnUpdateDlloleGetdata(CCmdUI *pCmdUI)
{
   pCmdUI->Enable(m_auto.m_lpDispatch != NULL);
}

void CEx23dView::OnDlloleLoad()
{
   if(!m_auto.CreateDispatch("Ex23b.Ex23bAuto")) {
		AfxMessageBox("Ex23b.Ex23bAuto component not found");
		return;
   }
   COleVariant va("test");
   m_auto.SetTextData(va);  // testing
   m_auto.SetLongData(79);  // testing
	// verify dispatch interface
    // {125FECB2-734D-49FD-95C7-FE44B77FDE2C}
    static const IID IID_IEx23bAuto =
    { 0x125FECB2, 0x734D, 0x49FD, { 0x95, 0xC7, 0xFE, 0x44, 0xB7, 0x7F, 0xDE, 0x2C } };
	LPDISPATCH p;
	HRESULT hr = m_auto.m_lpDispatch->QueryInterface(IID_IEx23bAuto, 
		(void**) &p);
	TRACE("OnDlloleLoad -- QueryInterface result = %x\n", hr);
	p->Release();
}

void CEx23dView::OnUpdateDlloleLoad(CCmdUI *pCmdUI)
{
   pCmdUI->Enable(m_auto.m_lpDispatch == NULL);
}

void CEx23dView::OnExceloleExecute()
{
   LPDISPATCH pRange, pWorkbooks;
    
   CWnd* pWnd = CWnd::FindWindow("XLMAIN", NULL);
   if (pWnd != NULL) {
     TRACE("Excel window found\n");
     pWnd->ShowWindow(SW_SHOWNORMAL);
     pWnd->UpdateWindow();
     pWnd->BringWindowToTop();
   }

   m_app.put_SheetsInNewWorkbook(1);
   
   VERIFY(pWorkbooks = m_app.get_Workbooks());
   m_workbooks.AttachDispatch(pWorkbooks);

   LPDISPATCH pWorkbook = NULL;
   if (m_workbooks.get_Count() == 0) {
      // Add returns a Workbook pointer, but we
      //  don't have a Workbook class
      pWorkbook = m_workbooks.Add(COleVariant((short) 0)); // Save the pointer for
                                     //  later release
   }
   LPDISPATCH pWorksheets = m_app.get_Worksheets();
   ASSERT(pWorksheets != NULL);
   m_worksheets.AttachDispatch(pWorksheets);
   LPDISPATCH pWorksheet = m_worksheets.get_Item(COleVariant((short) 1));

   m_worksheet.AttachDispatch(pWorksheet);
   m_worksheet.Select(COleVariant((short) 0));

   VERIFY(pRange = m_worksheet.get_Range(COleVariant("A1"), COleVariant("A1")));
   m_range[0].AttachDispatch(pRange);

   VERIFY(pRange = m_worksheet.get_Range(COleVariant("A2"), COleVariant("A2")));
   m_range[1].AttachDispatch(pRange);
   
   VERIFY(pRange = m_worksheet.get_Range(COleVariant("A3"), COleVariant("A3")));
   m_range[2].AttachDispatch(pRange);

   VERIFY(pRange = m_worksheet.get_Range(COleVariant("A3"), 
	   COleVariant("C5")));
   m_range[3].AttachDispatch(pRange);

   VERIFY(pRange = m_worksheet.get_Range(COleVariant("A6"), COleVariant("A6")));
   m_range[4].AttachDispatch(pRange);
   
   m_range[4].put_Value(COleVariant(COleDateTime(2002, 4, 24, 15, 47, 8)));
   // retrieve the stored date and print it as a string
   COleVariant vaTimeDate = m_range[4].get_Value();
   TRACE("returned date type = %d\n", vaTimeDate.vt);
   COleVariant vaTemp;
   vaTemp.ChangeType(VT_BSTR, &vaTimeDate);
   CString str(vaTemp.bstrVal);
   TRACE("date = %s\n", (const char*) str);

   m_range[0].put_Value(COleVariant("test string"));
   
   COleVariant vaResult0 = m_range[0].get_Value();
   if (vaResult0.vt == VT_BSTR) {
     CString str(vaResult0.bstrVal);
     TRACE("vaResult0 = %s\n", (const char*) str);
   }

   m_range[1].put_Value(COleVariant(3.14159));
   
   COleVariant vaResult1 = m_range[1].get_Value();
   if (vaResult1.vt == VT_R8) {
     TRACE("vaResult1 = %f\n", vaResult1.dblVal);
   }
   
   m_range[2].put_Formula(COleVariant("=$A2*2.0"));
   
   COleVariant vaResult2 = m_range[2].get_Value();
   if (vaResult2.vt == VT_R8) {
     TRACE("vaResult2 = %f\n", vaResult2.dblVal);
   }

   COleVariant vaResult2a = m_range[2].get_Formula();
   if (vaResult2a.vt == VT_BSTR) {
     CString str(vaResult2a.bstrVal);
     TRACE("vaResult2a = %s\n", (const char*) str);
   }
   
   m_range[3].FillRight();
   m_range[3].FillDown();
   
// cleanup  
    if (pWorkbook != NULL) {
	    pWorkbook->Release();
   }
}

void CEx23dView::OnUpdateExceloleExecute(CCmdUI *pCmdUI)
{
   pCmdUI->Enable(m_app.m_lpDispatch != NULL);
}

void CEx23dView::OnExceloleLoad()
{   // if Excel is already running, attach to it, otherwise start it
   LPDISPATCH pDisp;
   LPUNKNOWN pUnk;
   CLSID clsid;
   TRACE("Entering CEx23dView::OnExcelLoad\n");
   BeginWaitCursor();
   ::CLSIDFromProgID(L"Excel.Application.10", &clsid); // from registry
   if(::GetActiveObject(clsid, NULL, &pUnk) == S_OK) {
      VERIFY(pUnk->QueryInterface(IID_IDispatch,
            (void**) &pDisp) == S_OK);
      m_app.AttachDispatch(pDisp);
      pUnk->Release();
      TRACE(" attach complete\n");
  } 
   else {
	   if(!m_app.CreateDispatch("Excel.Application.10")) {
			AfxMessageBox("Microsoft Excel program not found");
	   }
       TRACE(" create complete\n");
   }
   EndWaitCursor();
}

void CEx23dView::OnUpdateExceloleLoad(CCmdUI *pCmdUI)
{
   pCmdUI->Enable(m_app.m_lpDispatch == NULL);
}

void CEx23dView::OnDlloleUnload()
{
   m_auto.ReleaseDispatch();
}

void CEx23dView::OnUpdateDlloleUnload(CCmdUI *pCmdUI)
{
   pCmdUI->Enable(m_auto.m_lpDispatch != NULL);
}
