// ViewBase.cpp : implementation file
//

#include "stdafx.h"
#include "GpsServer.h"
#include "ViewBase.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewBase

IMPLEMENT_DYNCREATE(CViewBase, CListView)

CViewBase::CViewBase()
{
	InitColumns();
}

CViewBase::~CViewBase()
{
}


BEGIN_MESSAGE_MAP(CViewBase, CListView)
	//{{AFX_MSG_MAP(CViewBase)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewBase drawing

void CViewBase::OnDraw(CDC* pDC)
{
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CViewLog diagnostics

#ifdef _DEBUG
void CViewBase::AssertValid() const
{
	CListView::AssertValid();
}

void CViewBase::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewBase message handlers

void CViewBase::AddExStyle(DWORD dwExStyle)
{
	DWORD dwStyle=::SendMessage(GetListCtrl().m_hWnd,LVM_GETEXTENDEDLISTVIEWSTYLE,0,0);

	//set new style
	dwStyle |= dwExStyle;

	//set current style
	::SendMessage(GetListCtrl().m_hWnd,LVM_SETEXTENDEDLISTVIEWSTYLE,0,dwStyle);
}

void CViewBase::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	GetListCtrl().ModifyStyleEx(0,WS_EX_CLIENTEDGE);
	AddExStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	//SetColumns(sizeof(_gColText)/sizeof(int),_gColWidth,_gColText);
	SetColumns(_gColText.GetSize(),(int*)(_gColWidth.GetData()),(int*)_gColText.GetData());	
}

BOOL CViewBase::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style |=LVS_REPORT;
	return CListView::PreCreateWindow(cs);
}



void CViewBase::SetColumns(int nCols, int *nWidth, int *pCol)
{
	ASSERT(nCols);
	ASSERT(nWidth);
	ASSERT(pCol);

	//insert columns	
	CString tempstr;
	LV_COLUMN lvc;
	lvc.mask=LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	for (int i=0; i < nCols;i++)
	{
		lvc.iSubItem=i;
		tempstr.LoadString(pCol[i]);
		lvc.pszText = (char*)(LPCTSTR)tempstr;
		lvc.cx = nWidth[i];
		lvc.fmt = LVCFMT_LEFT;
		GetListCtrl().InsertColumn(i,&lvc);
	}
}

void CViewBase::SetLVCheck(WPARAM ItemIndex, BOOL bCheck)
{
	LV_ITEM lvItem;
	lvItem.stateMask = LVIS_STATEIMAGEMASK;
	lvItem.state = UINT((int(bCheck) + 1) << 12);
	::SendMessage (GetListCtrl().m_hWnd, LVM_SETITEMSTATE, (WPARAM)ItemIndex,
		(LPARAM)(LV_ITEM FAR*)&lvItem);
}



void CViewBase::ClearLogs()
{
	GetListCtrl().DeleteAllItems();
}



void CViewBase::InitColumns()
{

}
