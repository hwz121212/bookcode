// ex12cDoc.cpp : implementation of the CEx12cDoc class
//

#include "stdafx.h"
#include "ex12c.h"

#include "ex12cDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx12cDoc

IMPLEMENT_DYNCREATE(CEx12cDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx12cDoc, CDocument)
	//{{AFX_MSG_MAP(CEx12cDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx12cDoc construction/destruction

CEx12cDoc::CEx12cDoc()
{
	// TODO: add one-time construction code here

}

CEx12cDoc::~CEx12cDoc()
{
}

BOOL CEx12cDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx12cDoc serialization

void CEx12cDoc::Serialize(CArchive& ar)
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
// CEx12cDoc diagnostics

#ifdef _DEBUG
void CEx12cDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx12cDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx12cDoc commands
