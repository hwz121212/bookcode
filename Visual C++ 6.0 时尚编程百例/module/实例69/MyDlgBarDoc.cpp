// MyDlgBarDoc.cpp : implementation of the CMyDlgBarDoc class
//

#include "stdafx.h"
#include "MyDlgBar.h"

#include "MyDlgBarDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDlgBarDoc

IMPLEMENT_DYNCREATE(CMyDlgBarDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyDlgBarDoc, CDocument)
	//{{AFX_MSG_MAP(CMyDlgBarDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlgBarDoc construction/destruction

CMyDlgBarDoc::CMyDlgBarDoc()
{
	// TODO: add one-time construction code here

}

CMyDlgBarDoc::~CMyDlgBarDoc()
{
}

BOOL CMyDlgBarDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyDlgBarDoc serialization

void CMyDlgBarDoc::Serialize(CArchive& ar)
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
// CMyDlgBarDoc diagnostics

#ifdef _DEBUG
void CMyDlgBarDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyDlgBarDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyDlgBarDoc commands
