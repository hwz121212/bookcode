// ex36bView.cpp : implementation of the CEx36bView class
//

#include "stdafx.h"
#include "ex36b.h"

#include "ex36bDoc.h"
#include "CntrItem.h"
#include "ex36bView.h"
#include "AddrDialog.h"
#include "PostThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx36bView

IMPLEMENT_DYNCREATE(CEx36bView, CValidForm)

BEGIN_MESSAGE_MAP(CEx36bView, CValidForm)
	//{{AFX_MSG_MAP(CEx36bView)
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_OLE_INSERT_NEW, OnInsertObject)
	ON_COMMAND(ID_CANCEL_EDIT_CNTR, OnCancelEditCntr)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_BN_CLICKED(IDC_SUBMIT, OnSubmit)
	ON_BN_CLICKED(IDCANCEL, OnCancel)
	ON_COMMAND(ID_SERVER_ADDRESS, OnServerAddress)
	ON_MESSAGE(WM_POSTCOMPLETE, OnPostComplete)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CValidForm::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CValidForm::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CValidForm::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx36bView construction/destruction

CEx36bView::CEx36bView()
	: CValidForm(CEx36bView::IDD)
{
	//{{AFX_DATA_INIT(CEx36bView)
	m_dHours = 0.0;
	m_strEmployee = _T("");
	m_nJob = 0;
	m_nPeriod = 0;
	//}}AFX_DATA_INIT
	m_pSelection = NULL;
	// TODO: add construction code here

}

CEx36bView::~CEx36bView()
{
}

void CEx36bView::DoDataExchange(CDataExchange* pDX)
{
	CValidForm::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_EMPLOYEE, m_strEmployee);
	DDV_MaxChars(pDX, m_strEmployee, 10);
	if(pDX->m_bSaveAndValidate && m_strEmployee.IsEmpty()) {
		AfxMessageBox("Must supply an employee name");
		pDX->Fail();
	}
	//{{AFX_DATA_MAP(CEx36bView)
	DDX_Text(pDX, IDC_HOURS, m_dHours);
	DDV_MinMaxDouble(pDX, m_dHours, 0.1, 100.);
	DDX_Text(pDX, IDC_JOB, m_nJob);
	DDV_MinMaxInt(pDX, m_nJob, 1, 20);
	DDX_Text(pDX, IDC_PERIOD, m_nPeriod);
	//}}AFX_DATA_MAP
}

BOOL CEx36bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CValidForm::PreCreateWindow(cs);
}

void CEx36bView::OnInitialUpdate()
{
	CEx36bDoc* pDoc = GetDocument();
	m_nPeriod = pDoc->m_nPeriod;
	UpdateData(FALSE);

	// TODO: remove this code when final selection model code is written
	m_pSelection = NULL;    // initialize selection

}

/////////////////////////////////////////////////////////////////////////////
// CEx36bView printing

BOOL CEx36bView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx36bView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx36bView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CEx36bView::OnPrint(CDC* pDC, CPrintInfo*)
{
	// TODO: add code to print the controls
}

/////////////////////////////////////////////////////////////////////////////
// OLE Client support and commands

BOOL CEx36bView::IsSelected(const CObject* pDocItem) const
{
	// The implementation below is adequate if your selection consists of
	//  only CEx36bCntrItem objects.  To handle different selection
	//  mechanisms, the implementation here should be replaced.

	// TODO: implement this function that tests for a selected OLE client item

	return pDocItem == m_pSelection;
}

void CEx36bView::OnInsertObject()
{
	// Invoke the standard Insert Object dialog box to obtain information
	//  for new CEx36bCntrItem object.
	COleInsertDialog dlg;
	if (dlg.DoModal() != IDOK)
		return;

	BeginWaitCursor();

	CEx36bCntrItem* pItem = NULL;
	TRY
	{
		// Create new item connected to this document.
		CEx36bDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pItem = new CEx36bCntrItem(pDoc);
		ASSERT_VALID(pItem);

		// Initialize the item from the dialog data.
		if (!dlg.CreateItem(pItem))
			AfxThrowMemoryException();  // any exception will do
		ASSERT_VALID(pItem);

		// If item created from class list (not from file) then launch
		//  the server to edit the item.
		if (dlg.GetSelectionType() == COleInsertDialog::createNewItem)
			pItem->DoVerb(OLEIVERB_SHOW, this);

		ASSERT_VALID(pItem);

		// As an arbitrary user interface design, this sets the selection
		//  to the last item inserted.

		// TODO: reimplement selection as appropriate for your application

		m_pSelection = pItem;   // set selection to last inserted item
		pDoc->UpdateAllViews(NULL);
	}
	CATCH(CException, e)
	{
		if (pItem != NULL)
		{
			ASSERT_VALID(pItem);
			pItem->Delete();
		}
		AfxMessageBox(IDP_FAILED_TO_CREATE);
	}
	END_CATCH

	EndWaitCursor();
}

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the container (not the server) causes the deactivation.
void CEx36bView::OnCancelEditCntr()
{
	// Close any in-place active item on this view.
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
	{
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
}

// Special handling of OnSetFocus and OnSize are required for a container
//  when an object is being edited in-place.
void CEx36bView::OnSetFocus(CWnd* pOldWnd)
{
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetItemState() == COleClientItem::activeUIState)
	{
		// need to set focus to this item if it is in the same view
		CWnd* pWnd = pActiveItem->GetInPlaceWindow();
		if (pWnd != NULL)
		{
			pWnd->SetFocus();   // don't call the base class
			return;
		}
	}

	CValidForm::OnSetFocus(pOldWnd);
}

void CEx36bView::OnSize(UINT nType, int cx, int cy)
{
	CValidForm::OnSize(nType, cx, cy);
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
		pActiveItem->SetItemRects();
}

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void CEx36bView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CEx36bView diagnostics

#ifdef _DEBUG
void CEx36bView::AssertValid() const
{
	CValidForm::AssertValid();
}

void CEx36bView::Dump(CDumpContext& dc) const
{
	CValidForm::Dump(dc);
}

CEx36bDoc* CEx36bView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx36bDoc)));
	return (CEx36bDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx36bView message handlers

void CEx36bView::OnCancel() 
{
	CEx36bDoc* pDoc = GetDocument();
	m_dHours = 0;
	m_strEmployee = "";
	m_nJob = 0;
	m_nPeriod = pDoc->m_nPeriod;
	UpdateData(FALSE);
}

void CEx36bView::OnSubmit() 
{
	if(UpdateData(TRUE) == TRUE) {
		GetDlgItem(IDC_SUBMIT)->EnableWindow(FALSE);
		CString strHours, strJob, strPeriod;
		strPeriod.Format("%d", m_nPeriod);
		strHours.Format("%3.2f", m_dHours);
		strJob.Format("%d", m_nJob);
		g_strParameters = "Period=" + strPeriod + "&Employee=" + m_strEmployee + "&Hours=" +
						strHours + "&Job=" + strJob + "\r\n";
		TRACE("parameter string = %s", g_strParameters);
		AfxBeginThread(PostThreadProc, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
	}
}

// overridden CValidForm function
void CEx36bView::ValidateDlgItem(CDataExchange* pDX, UINT uID)
{
	ASSERT(this);
	TRACE("CEx36bView::ValidateDlgItem\n");
	switch (uID) {
	case IDC_EMPLOYEE:
		DDX_CBString(pDX, IDC_EMPLOYEE, m_strEmployee);
		// need custom DDV for empty string
		DDV_MaxChars(pDX, m_strEmployee, 10);
		if(m_strEmployee.IsEmpty()) {
			AfxMessageBox("Must supply an employee name");
			pDX->Fail();
		}
		break;
	case IDC_HOURS:
		DDX_Text(pDX, IDC_HOURS, m_dHours);
		DDV_MinMaxDouble(pDX, m_dHours, 0.1, 100.);
		break;
	case IDC_JOB:
		DDX_Text(pDX, IDC_JOB, m_nJob);
		DDV_MinMaxInt(pDX, m_nJob, 1, 20);
		break;
	default:
		break;
	}
	return;
}

void CEx36bView::OnServerAddress() 
{
	CAddrDialog dlg;
	dlg.m_strServerName = g_strServerName;
	dlg.m_strFile = g_strFile;
	if(dlg.DoModal() == IDOK) {
		g_strFile = dlg.m_strFile;
		g_strServerName = dlg.m_strServerName; 
	}
}

// thread sends this message when it's done wParam = 1 for success
LONG CEx36bView::OnPostComplete(UINT wParam, LONG lParam)
{
	TRACE("CEx36bView::OnPostComplete - %d\n", wParam);
	if(wParam == 0) {
		AfxMessageBox("Server did not accept the transaction");
	}
	else OnCancel();
	GetDlgItem(IDC_SUBMIT)->EnableWindow(TRUE);
	return 0;
}
