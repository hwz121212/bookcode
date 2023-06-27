// ex36aDoc.cpp : implementation of the CEx36aDoc class
//

#include "stdafx.h"
#include "ex36a.h"

#include "ex36aDoc.h"
#include "CntrItem.h"
#include "SrvrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx36aDoc

IMPLEMENT_DYNCREATE(CEx36aDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CEx36aDoc, CRichEditDoc)
	//{{AFX_MSG_MAP(CEx36aDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI(ID_OLE_VERB_FIRST, CRichEditDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx36aDoc construction/destruction

CEx36aDoc::CEx36aDoc()
{
	// Use OLE compound files
	EnableCompoundFile();

	// TODO: add one-time construction code here

}

CEx36aDoc::~CEx36aDoc()
{
}

BOOL CEx36aDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

CRichEditCntrItem* CEx36aDoc::CreateClientItem(REOBJECT* preo) const
{
	// cast away constness of this
	return new CEx36aCntrItem(preo, (CEx36aDoc*) this);
}

/////////////////////////////////////////////////////////////////////////////
// CEx36aDoc server implementation

COleServerItem* CEx36aDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem is called by the framework to get the COleServerItem
	//  that is associated with the document.  It is only called when necessary.

	CEx36aSrvrItem* pItem = new CEx36aSrvrItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}

CDocObjectServer* CEx36aDoc::GetDocObjectServer(LPOLEDOCUMENTSITE pSite)
{
	return new CDocObjectServer(this, pSite);
}

/////////////////////////////////////////////////////////////////////////////
// CEx36aDoc serialization

void CEx36aDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class CRichEditDoc enables serialization
	//  of the container document's COleClientItem objects.
	CRichEditDoc::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CEx36aDoc diagnostics

#ifdef _DEBUG
void CEx36aDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CEx36aDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx36aDoc commands
