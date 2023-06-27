// ex38bDoc.cpp : implementation of the CEx38bDoc class
//

#include "stdafx.h"
#include "ex38b.h"

#include "ex38bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx38bDoc

IMPLEMENT_DYNCREATE(CEx38bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx38bDoc, CDocument)
	//{{AFX_MSG_MAP(CEx38bDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx38bDoc construction/destruction

CEx38bDoc::CEx38bDoc()
{
	// TODO: add one-time construction code here

}

CEx38bDoc::~CEx38bDoc()
{
}

BOOL CEx38bDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx38bDoc serialization

void CEx38bDoc::Serialize(CArchive& ar)
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
// CEx38bDoc diagnostics

#ifdef _DEBUG
void CEx38bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx38bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx38bDoc commands
