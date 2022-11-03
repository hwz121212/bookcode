// MouseClickDoc.cpp : implementation of the CMouseClickDoc class
//

#include "stdafx.h"
#include "MouseClick.h"

#include "MouseClickDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMouseClickDoc

IMPLEMENT_DYNCREATE(CMouseClickDoc, CDocument)

BEGIN_MESSAGE_MAP(CMouseClickDoc, CDocument)
	//{{AFX_MSG_MAP(CMouseClickDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMouseClickDoc construction/destruction

CMouseClickDoc::CMouseClickDoc()
{
	// TODO: add one-time construction code here

}

CMouseClickDoc::~CMouseClickDoc()
{
}

BOOL CMouseClickDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMouseClickDoc serialization

void CMouseClickDoc::Serialize(CArchive& ar)
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
// CMouseClickDoc diagnostics

#ifdef _DEBUG
void CMouseClickDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMouseClickDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMouseClickDoc commands
