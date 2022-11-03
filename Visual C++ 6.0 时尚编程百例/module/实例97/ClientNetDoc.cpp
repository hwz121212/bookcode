// ClientNetDoc.cpp : implementation of the CClientNetDoc class
//

#include "stdafx.h"
#include "ClientNet.h"

#include "ClientNetDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientNetDoc

IMPLEMENT_DYNCREATE(CClientNetDoc, CDocument)

BEGIN_MESSAGE_MAP(CClientNetDoc, CDocument)
	//{{AFX_MSG_MAP(CClientNetDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientNetDoc construction/destruction

CClientNetDoc::CClientNetDoc()
{
	// TODO: add one-time construction code here

}

CClientNetDoc::~CClientNetDoc()
{
}

BOOL CClientNetDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CClientNetDoc serialization

void CClientNetDoc::Serialize(CArchive& ar)
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
// CClientNetDoc diagnostics

#ifdef _DEBUG
void CClientNetDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CClientNetDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CClientNetDoc commands
