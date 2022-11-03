// MyFileDoc.cpp : implementation of the CMyFileDoc class
//

#include "stdafx.h"
#include "MyFile.h"

#include "MyFileDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFileDoc

IMPLEMENT_DYNCREATE(CMyFileDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyFileDoc, CDocument)
	//{{AFX_MSG_MAP(CMyFileDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyFileDoc construction/destruction

CMyFileDoc::CMyFileDoc()
{
	// TODO: add one-time construction code here

}

CMyFileDoc::~CMyFileDoc()
{
}

BOOL CMyFileDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyFileDoc serialization

void CMyFileDoc::Serialize(CArchive& ar)
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
// CMyFileDoc diagnostics

#ifdef _DEBUG
void CMyFileDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyFileDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyFileDoc commands
