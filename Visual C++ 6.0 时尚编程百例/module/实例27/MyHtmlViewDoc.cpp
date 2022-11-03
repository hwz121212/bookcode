// MyHtmlViewDoc.cpp : implementation of the CMyHtmlViewDoc class
//

#include "stdafx.h"
#include "MyHtmlView.h"

#include "MyHtmlViewDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyHtmlViewDoc

IMPLEMENT_DYNCREATE(CMyHtmlViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyHtmlViewDoc, CDocument)
	//{{AFX_MSG_MAP(CMyHtmlViewDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyHtmlViewDoc construction/destruction

CMyHtmlViewDoc::CMyHtmlViewDoc()
{
	// TODO: add one-time construction code here

}

CMyHtmlViewDoc::~CMyHtmlViewDoc()
{
}

BOOL CMyHtmlViewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyHtmlViewDoc serialization

void CMyHtmlViewDoc::Serialize(CArchive& ar)
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
// CMyHtmlViewDoc diagnostics

#ifdef _DEBUG
void CMyHtmlViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyHtmlViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyHtmlViewDoc commands
