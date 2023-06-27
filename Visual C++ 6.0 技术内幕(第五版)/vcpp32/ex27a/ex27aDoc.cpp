// ex27aDoc.cpp : implementation of the CEx27aDoc class
//

#include "stdafx.h"
#include "ex27a.h"

#include "ex27aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx27aDoc

IMPLEMENT_DYNCREATE(CEx27aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx27aDoc, CDocument)
	//{{AFX_MSG_MAP(CEx27aDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx27aDoc construction/destruction

CEx27aDoc::CEx27aDoc()
{
	// TODO: add one-time construction code here

}

CEx27aDoc::~CEx27aDoc()
{
}

BOOL CEx27aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx27aDoc serialization

void CEx27aDoc::Serialize(CArchive& ar)
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
// CEx27aDoc diagnostics

#ifdef _DEBUG
void CEx27aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx27aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx27aDoc commands
