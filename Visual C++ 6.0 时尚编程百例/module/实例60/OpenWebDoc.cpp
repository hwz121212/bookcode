// OpenWebDoc.cpp : implementation of the COpenWebDoc class
//

#include "stdafx.h"
#include "OpenWeb.h"

#include "OpenWebDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenWebDoc

IMPLEMENT_DYNCREATE(COpenWebDoc, CDocument)

BEGIN_MESSAGE_MAP(COpenWebDoc, CDocument)
	//{{AFX_MSG_MAP(COpenWebDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenWebDoc construction/destruction

COpenWebDoc::COpenWebDoc()
{
	// TODO: add one-time construction code here

}

COpenWebDoc::~COpenWebDoc()
{
}

BOOL COpenWebDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COpenWebDoc serialization

void COpenWebDoc::Serialize(CArchive& ar)
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
// COpenWebDoc diagnostics

#ifdef _DEBUG
void COpenWebDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COpenWebDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COpenWebDoc commands
