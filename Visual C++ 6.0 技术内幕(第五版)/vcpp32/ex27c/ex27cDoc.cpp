// ex27cDoc.cpp : implementation of the CEx27cDoc class
//

#include "stdafx.h"
#include "ex27c.h"

#include "ex27cDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx27cDoc

IMPLEMENT_DYNCREATE(CEx27cDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx27cDoc, CDocument)
	//{{AFX_MSG_MAP(CEx27cDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx27cDoc construction/destruction

CEx27cDoc::CEx27cDoc()
{
	// TODO: add one-time construction code here

}

CEx27cDoc::~CEx27cDoc()
{
}

BOOL CEx27cDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx27cDoc serialization

void CEx27cDoc::Serialize(CArchive& ar)
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
// CEx27cDoc diagnostics

#ifdef _DEBUG
void CEx27cDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx27cDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx27cDoc commands
