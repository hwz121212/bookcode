// Font1Doc.cpp : implementation of the CFont1Doc class
//

#include "stdafx.h"
#include "Font1.h"

#include "Font1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFont1Doc

IMPLEMENT_DYNCREATE(CFont1Doc, CDocument)

BEGIN_MESSAGE_MAP(CFont1Doc, CDocument)
	//{{AFX_MSG_MAP(CFont1Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFont1Doc construction/destruction

CFont1Doc::CFont1Doc()
{
	// TODO: add one-time construction code here

}

CFont1Doc::~CFont1Doc()
{
}

BOOL CFont1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFont1Doc serialization

void CFont1Doc::Serialize(CArchive& ar)
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
// CFont1Doc diagnostics

#ifdef _DEBUG
void CFont1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFont1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFont1Doc commands
