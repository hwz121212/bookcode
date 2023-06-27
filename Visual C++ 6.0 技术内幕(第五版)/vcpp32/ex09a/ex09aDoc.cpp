// ex09aDoc.cpp : implementation of the CEx09aDoc class
//

#include "stdafx.h"
#include "ex09a.h"

#include "ex09aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx09aDoc

IMPLEMENT_DYNCREATE(CEx09aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx09aDoc, CDocument)
	//{{AFX_MSG_MAP(CEx09aDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx09aDoc construction/destruction

CEx09aDoc::CEx09aDoc()
{
	// TODO: add one-time construction code here

}

CEx09aDoc::~CEx09aDoc()
{
}

BOOL CEx09aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx09aDoc serialization

void CEx09aDoc::Serialize(CArchive& ar)
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
// CEx09aDoc diagnostics

#ifdef _DEBUG
void CEx09aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx09aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx09aDoc commands
