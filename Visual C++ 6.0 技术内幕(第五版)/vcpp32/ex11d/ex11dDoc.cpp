// ex11dDoc.cpp : implementation of the CEx11dDoc class
//

#include "stdafx.h"
#include "ex11d.h"

#include "ex11dDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx11dDoc

IMPLEMENT_DYNCREATE(CEx11dDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx11dDoc, CDocument)
	//{{AFX_MSG_MAP(CEx11dDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx11dDoc construction/destruction

CEx11dDoc::CEx11dDoc()
{
	// TODO: add one-time construction code here

}

CEx11dDoc::~CEx11dDoc()
{
}

BOOL CEx11dDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx11dDoc serialization

void CEx11dDoc::Serialize(CArchive& ar)
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
// CEx11dDoc diagnostics

#ifdef _DEBUG
void CEx11dDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx11dDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx11dDoc commands
