// ex24cDoc.cpp : implementation of the CEx24cDoc class
//

#include "stdafx.h"
#include "ex24c.h"

#include "ex24cDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx24cDoc

IMPLEMENT_DYNCREATE(CEx24cDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx24cDoc, CDocument)
	//{{AFX_MSG_MAP(CEx24cDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx24cDoc construction/destruction

CEx24cDoc::CEx24cDoc()
{
	// TODO: add one-time construction code here

}

CEx24cDoc::~CEx24cDoc()
{
}

BOOL CEx24cDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx24cDoc serialization

void CEx24cDoc::Serialize(CArchive& ar)
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
// CEx24cDoc diagnostics

#ifdef _DEBUG
void CEx24cDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx24cDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx24cDoc commands
