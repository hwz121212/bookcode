// ex22bDoc.cpp : implementation of the CEx22bDoc class
//

#include "stdafx.h"
#include "ex22b.h"

#include "ex22bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx22bDoc

IMPLEMENT_DYNCREATE(CEx22bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx22bDoc, CDocument)
	//{{AFX_MSG_MAP(CEx22bDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx22bDoc construction/destruction

CEx22bDoc::CEx22bDoc()
{
	// TODO: add one-time construction code here

}

CEx22bDoc::~CEx22bDoc()
{
}

BOOL CEx22bDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx22bDoc serialization

void CEx22bDoc::Serialize(CArchive& ar)
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
// CEx22bDoc diagnostics

#ifdef _DEBUG
void CEx22bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx22bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx22bDoc commands
