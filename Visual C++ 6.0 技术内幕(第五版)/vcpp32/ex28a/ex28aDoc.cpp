// ex28aDoc.cpp : implementation of the CEx28aDoc class
//

#include "stdafx.h"
#include "ex28a.h"

#include "ex28aDoc.h"
#include "SrvrItem.h"
#include "TextDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx28aDoc

IMPLEMENT_DYNCREATE(CEx28aDoc, COleServerDoc)

BEGIN_MESSAGE_MAP(CEx28aDoc, COleServerDoc)
	//{{AFX_MSG_MAP(CEx28aDoc)
	ON_COMMAND(ID_MODIFY, OnModify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx28aDoc construction/destruction

CEx28aDoc::CEx28aDoc()
{
	// Use OLE compound files
	EnableCompoundFile();

	// TODO: add one-time construction code here

}

CEx28aDoc::~CEx28aDoc()
{
}

BOOL CEx28aDoc::OnNewDocument()
{
	if (!COleServerDoc::OnNewDocument())
		return FALSE;

	m_strText = "Initial default text";

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEx28aDoc server implementation

COleServerItem* CEx28aDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem is called by the framework to get the COleServerItem
	//  that is associated with the document.  It is only called when necessary.

	CEx28aSrvrItem* pItem = new CEx28aSrvrItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}



/////////////////////////////////////////////////////////////////////////////
// CEx28aDoc serialization

void CEx28aDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
        ar << m_strText;
	}
	else
	{
        ar >> m_strText;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CEx28aDoc diagnostics

#ifdef _DEBUG
void CEx28aDoc::AssertValid() const
{
	COleServerDoc::AssertValid();
}

void CEx28aDoc::Dump(CDumpContext& dc) const
{
	COleServerDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx28aDoc commands

void CEx28aDoc::OnModify() 
{
    CTextDialog dlg;
    dlg.m_strText = m_strText;
    if (dlg.DoModal() == IDOK) {
        m_strText = dlg.m_strText;
        UpdateAllViews(NULL); // Trigger CEx28aView::OnDraw
        UpdateAllItems(NULL); // Trigger CEx28aSrvrItem::OnDraw
        SetModifiedFlag();
    }
	
}
