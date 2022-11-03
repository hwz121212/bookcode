// novelDoc.cpp : implementation of the CNovelDoc class
//

#include "stdafx.h"
#include "novel.h"

#include "novelDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNovelDoc

IMPLEMENT_DYNCREATE(CNovelDoc, CDocument)

BEGIN_MESSAGE_MAP(CNovelDoc, CDocument)
	//{{AFX_MSG_MAP(CNovelDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNovelDoc construction/destruction

CNovelDoc::CNovelDoc()
{
	// TODO: add one-time construction code here

}

CNovelDoc::~CNovelDoc()
{
}

BOOL CNovelDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CNovelDoc serialization

void CNovelDoc::Serialize(CArchive& ar)
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
// CNovelDoc diagnostics

#ifdef _DEBUG
void CNovelDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNovelDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNovelDoc commands
