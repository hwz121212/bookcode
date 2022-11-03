// StatusDoc.cpp : implementation of the CStatusDoc class
//

#include "stdafx.h"
#include "Status.h"

#include "StatusDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatusDoc

IMPLEMENT_DYNCREATE(CStatusDoc, CDocument)

BEGIN_MESSAGE_MAP(CStatusDoc, CDocument)
	//{{AFX_MSG_MAP(CStatusDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusDoc construction/destruction

CStatusDoc::CStatusDoc()
{
	// TODO: add one-time construction code here

}

CStatusDoc::~CStatusDoc()
{
}

BOOL CStatusDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CStatusDoc serialization

void CStatusDoc::Serialize(CArchive& ar)
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
// CStatusDoc diagnostics

#ifdef _DEBUG
void CStatusDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStatusDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStatusDoc commands
