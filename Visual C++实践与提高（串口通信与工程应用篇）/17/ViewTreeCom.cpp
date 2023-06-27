// ViewTreeGis.cpp : implementation file
//

#include "stdafx.h"
#include "GpsServer.h"
#include "ViewTreeCom.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTreeCom

IMPLEMENT_DYNCREATE(CViewTreeCom, CTreeView)

CViewTreeCom::CViewTreeCom()
{
}

CViewTreeCom::~CViewTreeCom()
{
}


BEGIN_MESSAGE_MAP(CViewTreeCom, CTreeView)
	//{{AFX_MSG_MAP(CViewTreeCom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTreeCom drawing

void CViewTreeCom::OnDraw(CDC* pDC)
{
	Invalidate();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CViewTreeCom diagnostics

#ifdef _DEBUG
void CViewTreeCom::AssertValid() const
{
	CTreeView::AssertValid();
}

void CViewTreeCom::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewTreeCom message handlers

void CViewTreeCom::InsertCom(CComWorkFlow *obj)
{
	HTREEITEM htm;
	int count=GetTreeCtrl().GetCount();
	CString tmp;
	CString cmp;
	htm=GetTreeCtrl().GetRootItem();
	cmp=GetTreeCtrl().GetItemText(htm);
	for (int i=0; i<count; i++)
	{		
		if (cmp==obj->m_Com)
		{		
			htm = GetTreeCtrl().GetChildItem(htm);
			GetTreeCtrl().SetItemText(htm, obj->m_Com);
			
			tmp.Format("波特率:%d",obj->m_dcb.BaudRate);
			htm=GetTreeCtrl().GetNextSiblingItem(htm);
			GetTreeCtrl().SetItemText(htm, tmp);

			tmp.Format("数据位:%d", obj->m_dcb.ByteSize);
			htm=GetTreeCtrl().GetNextSiblingItem(htm);
			GetTreeCtrl().SetItemText(htm, tmp);

			tmp.Format("奇偶校验:%d", obj->m_dcb.Parity);
			htm=GetTreeCtrl().GetNextSiblingItem(htm);
			GetTreeCtrl().SetItemText(htm, tmp);

			tmp.Format("停止位:%d", obj->m_dcb.StopBits);
			htm=GetTreeCtrl().GetNextSiblingItem(htm);
			GetTreeCtrl().SetItemText(htm, tmp);			

			return;
		}
		htm=GetTreeCtrl().GetNextSiblingItem(htm);
		cmp=GetTreeCtrl().GetItemText(htm);
	}	
	htm = GetTreeCtrl().InsertItem(obj->m_Com);
	
	tmp.Format("波特率:%d",obj->m_dcb.BaudRate);
	GetTreeCtrl().InsertItem(tmp, htm);

    tmp.Format("数据位:%d", obj->m_dcb.ByteSize);
	GetTreeCtrl().InsertItem(tmp, htm);
	
	tmp.Format("奇偶校验:%d", obj->m_dcb.Parity);
	GetTreeCtrl().InsertItem(tmp, htm);

	tmp.Format("停止位:%d", obj->m_dcb.StopBits);
	GetTreeCtrl().InsertItem(tmp, htm);
}

void CViewTreeCom::DeleteCom(CComWorkFlow *obj)
{
	HTREEITEM htm;
	int count=GetTreeCtrl().GetCount();
	CString tmp;	
	CString cmp;
	htm=GetTreeCtrl().GetRootItem();
	cmp=GetTreeCtrl().GetItemText(htm);
	for (int i=0;i<count;i++)
	{		
		if (cmp == obj->m_Com)
		{
			GetTreeCtrl().DeleteItem(htm);			
			return;
		}
		htm=GetTreeCtrl().GetNextSiblingItem(htm);
		cmp=GetTreeCtrl().GetItemText(htm);
	}	
}



BOOL CViewTreeCom::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CTreeView::PreCreateWindow(cs);
}

void CViewTreeCom::OnInitialUpdate() 
{
	CTreeView::OnInitialUpdate();
	GetTreeCtrl().ModifyStyle(0,TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS);
	
	
	// TODO: Add your specialized code here and/or call the base class
	
	//AddExStyle(TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS|TVS_SHOWSELALWAYS);
}


