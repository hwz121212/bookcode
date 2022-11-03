// ServerNetDoc.cpp : implementation of the CServerNetDoc class
//

#include "stdafx.h"
#include "ServerNet.h"

#include "ServerNetDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerNetDoc

IMPLEMENT_DYNCREATE(CServerNetDoc, CDocument)

BEGIN_MESSAGE_MAP(CServerNetDoc, CDocument)
	//{{AFX_MSG_MAP(CServerNetDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerNetDoc construction/destruction

CServerNetDoc::CServerNetDoc()
{
	// TODO: add one-time construction code here

}

CServerNetDoc::~CServerNetDoc()
{
}

BOOL CServerNetDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CServerNetDoc serialization

void CServerNetDoc::Serialize(CArchive& ar)
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
// CServerNetDoc diagnostics

#ifdef _DEBUG
void CServerNetDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CServerNetDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CServerNetDoc commands
