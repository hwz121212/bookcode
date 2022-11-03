// MyDialogBarDoc.cpp : implementation of the CMyDialogBarDoc class
//

#include "stdafx.h"
#include "MyDialogBar.h"

#include "MyDialogBarDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDialogBarDoc

IMPLEMENT_DYNCREATE(CMyDialogBarDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyDialogBarDoc, CDocument)
	//{{AFX_MSG_MAP(CMyDialogBarDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDialogBarDoc construction/destruction

CMyDialogBarDoc::CMyDialogBarDoc()
{
	// TODO: add one-time construction code here

}

CMyDialogBarDoc::~CMyDialogBarDoc()
{
}

BOOL CMyDialogBarDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyDialogBarDoc serialization

void CMyDialogBarDoc::Serialize(CArchive& ar)
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
// CMyDialogBarDoc diagnostics

#ifdef _DEBUG
void CMyDialogBarDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyDialogBarDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyDialogBarDoc commands
