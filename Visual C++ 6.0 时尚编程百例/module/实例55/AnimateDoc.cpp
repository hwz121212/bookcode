// AnimateDoc.cpp : implementation of the CAnimateDoc class
//

#include "stdafx.h"
#include "Animate.h"

#include "AnimateDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimateDoc

IMPLEMENT_DYNCREATE(CAnimateDoc, CDocument)

BEGIN_MESSAGE_MAP(CAnimateDoc, CDocument)
	//{{AFX_MSG_MAP(CAnimateDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimateDoc construction/destruction

CAnimateDoc::CAnimateDoc()
{
	// TODO: add one-time construction code here

}

CAnimateDoc::~CAnimateDoc()
{
}

BOOL CAnimateDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CAnimateDoc serialization

void CAnimateDoc::Serialize(CArchive& ar)
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
// CAnimateDoc diagnostics

#ifdef _DEBUG
void CAnimateDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAnimateDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAnimateDoc commands
