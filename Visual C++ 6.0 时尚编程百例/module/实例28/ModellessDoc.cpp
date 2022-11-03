// ModellessDoc.cpp : implementation of the CModellessDoc class
//

#include "stdafx.h"
#include "Modelless.h"

#include "ModellessDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModellessDoc

IMPLEMENT_DYNCREATE(CModellessDoc, CDocument)

BEGIN_MESSAGE_MAP(CModellessDoc, CDocument)
	//{{AFX_MSG_MAP(CModellessDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModellessDoc construction/destruction

CModellessDoc::CModellessDoc()
{
	// TODO: add one-time construction code here

}

CModellessDoc::~CModellessDoc()
{
}

BOOL CModellessDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CModellessDoc serialization

void CModellessDoc::Serialize(CArchive& ar)
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
// CModellessDoc diagnostics

#ifdef _DEBUG
void CModellessDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CModellessDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CModellessDoc commands
