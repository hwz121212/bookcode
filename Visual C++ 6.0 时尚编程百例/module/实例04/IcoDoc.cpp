// IcoDoc.cpp : implementation of the CIcoDoc class
//

#include "stdafx.h"
#include "Ico.h"

#include "IcoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIcoDoc

IMPLEMENT_DYNCREATE(CIcoDoc, CDocument)

BEGIN_MESSAGE_MAP(CIcoDoc, CDocument)
	//{{AFX_MSG_MAP(CIcoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIcoDoc construction/destruction

CIcoDoc::CIcoDoc()
{
	// TODO: add one-time construction code here

}

CIcoDoc::~CIcoDoc()
{
}

BOOL CIcoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CIcoDoc serialization

void CIcoDoc::Serialize(CArchive& ar)
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
// CIcoDoc diagnostics

#ifdef _DEBUG
void CIcoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CIcoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIcoDoc commands
