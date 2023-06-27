// ex36bDoc.cpp : implementation of the CEx36bDoc class
//

#include "stdafx.h"
#include "ex36b.h"

#include "ex36bDoc.h"
#include "CntrItem.h"
#include "SrvrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx36bDoc

IMPLEMENT_DYNCREATE(CEx36bDoc, COleServerDoc)

BEGIN_MESSAGE_MAP(CEx36bDoc, COleServerDoc)
	//{{AFX_MSG_MAP(CEx36bDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, COleServerDoc::OnUpdatePasteMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, COleServerDoc::OnUpdatePasteLinkMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_CONVERT, COleServerDoc::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_OLE_EDIT_CONVERT, COleServerDoc::OnEditConvert)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, COleServerDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, COleServerDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI(ID_OLE_VERB_FIRST, COleServerDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx36bDoc construction/destruction

CEx36bDoc::CEx36bDoc()
{
	// Use OLE compound files
	EnableCompoundFile();

	m_nPeriod = 12; // should initialize this some other way
}

CEx36bDoc::~CEx36bDoc()
{
}

BOOL CEx36bDoc::OnNewDocument()
{
	if (!COleServerDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEx36bDoc server implementation

COleServerItem* CEx36bDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem is called by the framework to get the COleServerItem
	//  that is associated with the document.  It is only called when necessary.

	CEx36bSrvrItem* pItem = new CEx36bSrvrItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}

CDocObjectServer* CEx36bDoc::GetDocObjectServer(LPOLEDOCUMENTSITE pSite)
{
	return new CDocObjectServer(this, pSite);
}

/////////////////////////////////////////////////////////////////////////////
// CEx36bDoc serialization

void CEx36bDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())	{
		ar << m_nPeriod;
	}
	else {
		ar >> m_nPeriod;
	}

	// Calling the base class COleServerDoc enables serialization
	//  of the container document's COleClientItem objects.
	COleServerDoc::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CEx36bDoc diagnostics

#ifdef _DEBUG
void CEx36bDoc::AssertValid() const
{
	COleServerDoc::AssertValid();
}

void CEx36bDoc::Dump(CDumpContext& dc) const
{
	COleServerDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx36bDoc commands
