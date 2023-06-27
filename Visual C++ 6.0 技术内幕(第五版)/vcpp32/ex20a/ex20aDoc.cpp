// ex20aDoc.cpp : implementation of the CEx20aDoc class
//

#include "stdafx.h"
#include "ex20a.h"

#include "ex20aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx20aDoc

IMPLEMENT_DYNCREATE(CEx20aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx20aDoc, CDocument)
	//{{AFX_MSG_MAP(CEx20aDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx20aDoc construction/destruction

CEx20aDoc::CEx20aDoc()
{
	// TODO: add one-time construction code here

}

CEx20aDoc::~CEx20aDoc()
{
}

BOOL CEx20aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx20aDoc serialization

void CEx20aDoc::Serialize(CArchive& ar)
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
// CEx20aDoc diagnostics

#ifdef _DEBUG
void CEx20aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx20aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx20aDoc commands
