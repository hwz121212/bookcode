// MyScrollDoc.cpp : implementation of the CMyScrollDoc class
//

#include "stdafx.h"
#include "MyScroll.h"

#include "MyScrollDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyScrollDoc

IMPLEMENT_DYNCREATE(CMyScrollDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyScrollDoc, CDocument)
	//{{AFX_MSG_MAP(CMyScrollDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyScrollDoc construction/destruction

CMyScrollDoc::CMyScrollDoc()
{
	// TODO: add one-time construction code here

}

CMyScrollDoc::~CMyScrollDoc()
{
}

BOOL CMyScrollDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyScrollDoc serialization

void CMyScrollDoc::Serialize(CArchive& ar)
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
// CMyScrollDoc diagnostics

#ifdef _DEBUG
void CMyScrollDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyScrollDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyScrollDoc commands
