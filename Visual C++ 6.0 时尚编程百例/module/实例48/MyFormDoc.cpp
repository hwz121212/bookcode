// MyFormDoc.cpp : implementation of the CMyFormDoc class
//

#include "stdafx.h"
#include "MyForm.h"

#include "MyFormDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFormDoc

IMPLEMENT_DYNCREATE(CMyFormDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyFormDoc, CDocument)
	//{{AFX_MSG_MAP(CMyFormDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyFormDoc construction/destruction

CMyFormDoc::CMyFormDoc()
{
	// TODO: add one-time construction code here

}

CMyFormDoc::~CMyFormDoc()
{
}

BOOL CMyFormDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyFormDoc serialization

void CMyFormDoc::Serialize(CArchive& ar)
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
// CMyFormDoc diagnostics

#ifdef _DEBUG
void CMyFormDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyFormDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyFormDoc commands
