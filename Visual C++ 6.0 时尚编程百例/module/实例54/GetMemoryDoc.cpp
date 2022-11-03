// GetMemoryDoc.cpp : implementation of the CGetMemoryDoc class
//

#include "stdafx.h"
#include "GetMemory.h"

#include "GetMemoryDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGetMemoryDoc

IMPLEMENT_DYNCREATE(CGetMemoryDoc, CDocument)

BEGIN_MESSAGE_MAP(CGetMemoryDoc, CDocument)
	//{{AFX_MSG_MAP(CGetMemoryDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetMemoryDoc construction/destruction

CGetMemoryDoc::CGetMemoryDoc()
{
	// TODO: add one-time construction code here

}

CGetMemoryDoc::~CGetMemoryDoc()
{
}

BOOL CGetMemoryDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGetMemoryDoc serialization

void CGetMemoryDoc::Serialize(CArchive& ar)
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
// CGetMemoryDoc diagnostics

#ifdef _DEBUG
void CGetMemoryDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGetMemoryDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGetMemoryDoc commands
