// DrawBottunDoc.cpp : implementation of the CDrawBottunDoc class
//

#include "stdafx.h"
#include "DrawBottun.h"

#include "DrawBottunDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawBottunDoc

IMPLEMENT_DYNCREATE(CDrawBottunDoc, CDocument)

BEGIN_MESSAGE_MAP(CDrawBottunDoc, CDocument)
	//{{AFX_MSG_MAP(CDrawBottunDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawBottunDoc construction/destruction

CDrawBottunDoc::CDrawBottunDoc()
{
	// TODO: add one-time construction code here

}

CDrawBottunDoc::~CDrawBottunDoc()
{
}

BOOL CDrawBottunDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDrawBottunDoc serialization

void CDrawBottunDoc::Serialize(CArchive& ar)
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
// CDrawBottunDoc diagnostics

#ifdef _DEBUG
void CDrawBottunDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDrawBottunDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawBottunDoc commands
