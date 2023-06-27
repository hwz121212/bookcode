// ex14bDoc.cpp : implementation of the CEx14bDoc class
//

#include "stdafx.h"
#include "ex14b.h"

#include "ex14bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx14bDoc

IMPLEMENT_DYNCREATE(CEx14bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx14bDoc, CDocument)
	//{{AFX_MSG_MAP(CEx14bDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx14bDoc construction/destruction

CEx14bDoc::CEx14bDoc()
{
	// TODO: add one-time construction code here

}

CEx14bDoc::~CEx14bDoc()
{
}

BOOL CEx14bDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx14bDoc serialization

void CEx14bDoc::Serialize(CArchive& ar)
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
// CEx14bDoc diagnostics

#ifdef _DEBUG
void CEx14bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx14bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx14bDoc commands
