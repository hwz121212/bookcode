// MyRectDoc.cpp : implementation of the CMyRectDoc class
//

#include "stdafx.h"
#include "MyRect.h"

#include "MyRectDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyRectDoc

IMPLEMENT_DYNCREATE(CMyRectDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyRectDoc, CDocument)
	//{{AFX_MSG_MAP(CMyRectDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyRectDoc construction/destruction

CMyRectDoc::CMyRectDoc()
{
	// TODO: add one-time construction code here

}

CMyRectDoc::~CMyRectDoc()
{
}

BOOL CMyRectDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyRectDoc serialization

void CMyRectDoc::Serialize(CArchive& ar)
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
// CMyRectDoc diagnostics

#ifdef _DEBUG
void CMyRectDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyRectDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyRectDoc commands
