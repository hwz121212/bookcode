// ex37aDoc.cpp : implementation of the CEx37aDoc class
//

#include "stdafx.h"
#include "ex37a.h"

#include "ex37aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx37aDoc

IMPLEMENT_DYNCREATE(CEx37aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx37aDoc, CDocument)
	//{{AFX_MSG_MAP(CEx37aDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx37aDoc construction/destruction

CEx37aDoc::CEx37aDoc()
{
	// TODO: add one-time construction code here

}

CEx37aDoc::~CEx37aDoc()
{
}

BOOL CEx37aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx37aDoc serialization

void CEx37aDoc::Serialize(CArchive& ar)
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
// CEx37aDoc diagnostics

#ifdef _DEBUG
void CEx37aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx37aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx37aDoc commands
