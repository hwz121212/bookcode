// ex35cView.cpp : implementation of the CEx35cView class
//

#include "stdafx.h"
#include "ex35c.h"

#include "ex35cDoc.h"
#include "CntrItem.h"
#include "ex35cView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx35cView

IMPLEMENT_DYNCREATE(CEx35cView, CRichEditView)

BEGIN_MESSAGE_MAP(CEx35cView, CRichEditView)
	//{{AFX_MSG_MAP(CEx35cView)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, OnUpdateEditClearAll)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRichEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx35cView construction/destruction

CEx35cView::CEx35cView()
{
	// TODO: add construction code here

}

CEx35cView::~CEx35cView()
{
}

BOOL CEx35cView::PreCreateWindow(CREATESTRUCT& cs)
{
	
	BOOL bPreCreated = CRichEditView::PreCreateWindow(cs);
	cs.style |= ES_READONLY;
	return bPreCreated;
}

void CEx35cView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();

	// Set the printing margins (720 twips = 1/2 inch).
	SetMargins(CRect(720, 720, 720, 720));
}

/////////////////////////////////////////////////////////////////////////////
// CEx35cView printing

BOOL CEx35cView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}


void CEx35cView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
   CRichEditView::OnDestroy();
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
}


/////////////////////////////////////////////////////////////////////////////
// CEx35cView diagnostics

#ifdef _DEBUG
void CEx35cView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CEx35cView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CEx35cDoc* CEx35cView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx35cDoc)));
	return (CEx35cDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx35cView message handlers
void CEx35cView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	TRACE("CEx35cView::OnRButtonDown\n");
	CMenu menu;
	menu.LoadMenu(IDR_MENUCONTEXT);
	ClientToScreen(&point);
	menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		point.x, point.y, this);
}

void CEx35cView::OnEditClearAll() 
{
	CRichEditCtrl& re = GetRichEditCtrl();
	re.SetSel(0, -1);
	// won't let us clear unless we reset readonly flag
	re.SetOptions(ECOOP_XOR, ECO_READONLY);
	re.Clear();
	re.SetOptions(ECOOP_SET, ECO_READONLY);
}

void CEx35cView::OnUpdateEditClearAll(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetRichEditCtrl().GetTextLength() > 0);
}
