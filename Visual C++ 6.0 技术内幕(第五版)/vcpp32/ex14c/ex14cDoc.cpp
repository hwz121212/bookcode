// ex14cDoc.cpp : implementation of the CEx14cDoc class
//

#include "stdafx.h"
#include "ex14c.h"

#include "ex14cDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx14cDoc

IMPLEMENT_DYNCREATE(CEx14cDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx14cDoc, CDocument)
	//{{AFX_MSG_MAP(CEx14cDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx14cDoc construction/destruction

CEx14cDoc::CEx14cDoc()
{
	// TODO: add one-time construction code here

}

CEx14cDoc::~CEx14cDoc()
{
}

BOOL CEx14cDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx14cDoc serialization

void CEx14cDoc::Serialize(CArchive& ar)
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
// CEx14cDoc diagnostics

#ifdef _DEBUG
void CEx14cDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx14cDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx14cDoc commands
