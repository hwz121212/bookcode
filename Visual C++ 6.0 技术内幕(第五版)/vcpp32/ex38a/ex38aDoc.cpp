// ex38aDoc.cpp : implementation of the CEx38aDoc class
//

#include "stdafx.h"
#include "ex38a.h"

#include "ex38aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx38aDoc

IMPLEMENT_DYNCREATE(CEx38aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx38aDoc, CDocument)
	//{{AFX_MSG_MAP(CEx38aDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx38aDoc construction/destruction

CEx38aDoc::CEx38aDoc()
{
	// TODO: add one-time construction code here

}

CEx38aDoc::~CEx38aDoc()
{
}

BOOL CEx38aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx38aDoc serialization

void CEx38aDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CEx38aDoc diagnostics

#ifdef _DEBUG
void CEx38aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx38aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx38aDoc commands
