// ex35cDoc.cpp : implementation of the CEx35cDoc class
//

#include "stdafx.h"
#include "ex35c.h"

#include "ex35cDoc.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx35cDoc

IMPLEMENT_DYNCREATE(CEx35cDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CEx35cDoc, CRichEditDoc)
	//{{AFX_MSG_MAP(CEx35cDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI(ID_OLE_VERB_FIRST, CRichEditDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx35cDoc construction/destruction

CEx35cDoc::CEx35cDoc()
{
	// TODO: add one-time construction code here

}

CEx35cDoc::~CEx35cDoc()
{
}

BOOL CEx35cDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

CRichEditCntrItem* CEx35cDoc::CreateClientItem(REOBJECT* preo) const
{
	// cast away constness of this
	return new CEx35cCntrItem(preo, (CEx35cDoc*) this);
}

/////////////////////////////////////////////////////////////////////////////
// CEx35cDoc serialization

void CEx35cDoc::Serialize(CArchive& ar)
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
// CEx35cDoc diagnostics

#ifdef _DEBUG
void CEx35cDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CEx35cDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx35cDoc commands

BOOL CEx35cDoc::SaveModified() 
{
	return TRUE;
}
