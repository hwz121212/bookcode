// MyDialogDoc.cpp : implementation of the CMyDialogDoc class
//

#include "stdafx.h"
#include "MyDialog.h"

#include "MyDialogDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDialogDoc

IMPLEMENT_DYNCREATE(CMyDialogDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyDialogDoc, CDocument)
	//{{AFX_MSG_MAP(CMyDialogDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDialogDoc construction/destruction

CMyDialogDoc::CMyDialogDoc()
{
	// TODO: add one-time construction code here

}

CMyDialogDoc::~CMyDialogDoc()
{
}

BOOL CMyDialogDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyDialogDoc serialization

void CMyDialogDoc::Serialize(CArchive& ar)
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
// CMyDialogDoc diagnostics

#ifdef _DEBUG
void CMyDialogDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyDialogDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyDialogDoc commands
