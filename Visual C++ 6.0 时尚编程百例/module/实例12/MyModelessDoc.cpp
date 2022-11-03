// MyModelessDoc.cpp : implementation of the CMyModelessDoc class
//

#include "stdafx.h"
#include "MyModeless.h"

#include "MyModelessDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyModelessDoc

IMPLEMENT_DYNCREATE(CMyModelessDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyModelessDoc, CDocument)
	//{{AFX_MSG_MAP(CMyModelessDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyModelessDoc construction/destruction

CMyModelessDoc::CMyModelessDoc()
{
	// TODO: add one-time construction code here

}

CMyModelessDoc::~CMyModelessDoc()
{
}

BOOL CMyModelessDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyModelessDoc serialization

void CMyModelessDoc::Serialize(CArchive& ar)
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
// CMyModelessDoc diagnostics

#ifdef _DEBUG
void CMyModelessDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyModelessDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyModelessDoc commands
