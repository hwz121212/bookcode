// KeyScrollDoc.cpp : implementation of the CKeyScrollDoc class
//

#include "stdafx.h"
#include "KeyScroll.h"

#include "KeyScrollDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKeyScrollDoc

IMPLEMENT_DYNCREATE(CKeyScrollDoc, CDocument)

BEGIN_MESSAGE_MAP(CKeyScrollDoc, CDocument)
	//{{AFX_MSG_MAP(CKeyScrollDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeyScrollDoc construction/destruction

CKeyScrollDoc::CKeyScrollDoc()
{
	// TODO: add one-time construction code here

}

CKeyScrollDoc::~CKeyScrollDoc()
{
}

BOOL CKeyScrollDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CKeyScrollDoc serialization

void CKeyScrollDoc::Serialize(CArchive& ar)
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
// CKeyScrollDoc diagnostics

#ifdef _DEBUG
void CKeyScrollDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CKeyScrollDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CKeyScrollDoc commands
