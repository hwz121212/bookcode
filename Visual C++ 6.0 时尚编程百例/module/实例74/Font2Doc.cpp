// Font2Doc.cpp : implementation of the CFont2Doc class
//

#include "stdafx.h"
#include "Font2.h"

#include "Font2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFont2Doc

IMPLEMENT_DYNCREATE(CFont2Doc, CDocument)

BEGIN_MESSAGE_MAP(CFont2Doc, CDocument)
	//{{AFX_MSG_MAP(CFont2Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFont2Doc construction/destruction

CFont2Doc::CFont2Doc()
{
	// TODO: add one-time construction code here

}

CFont2Doc::~CFont2Doc()
{
}

BOOL CFont2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFont2Doc serialization

void CFont2Doc::Serialize(CArchive& ar)
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
// CFont2Doc diagnostics

#ifdef _DEBUG
void CFont2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFont2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFont2Doc commands
