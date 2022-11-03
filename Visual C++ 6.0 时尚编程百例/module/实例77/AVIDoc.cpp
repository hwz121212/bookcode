// AVIDoc.cpp : implementation of the CAVIDoc class
//

#include "stdafx.h"
#include "AVI.h"

#include "AVIDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAVIDoc

IMPLEMENT_DYNCREATE(CAVIDoc, CDocument)

BEGIN_MESSAGE_MAP(CAVIDoc, CDocument)
	//{{AFX_MSG_MAP(CAVIDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAVIDoc construction/destruction

CAVIDoc::CAVIDoc()
{
	// TODO: add one-time construction code here

}

CAVIDoc::~CAVIDoc()
{
}

BOOL CAVIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CAVIDoc serialization

void CAVIDoc::Serialize(CArchive& ar)
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
// CAVIDoc diagnostics

#ifdef _DEBUG
void CAVIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAVIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAVIDoc commands
