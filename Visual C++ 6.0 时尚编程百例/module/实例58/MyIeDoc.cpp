// MyIeDoc.cpp : implementation of the CMyIeDoc class
//

#include "stdafx.h"
#include "MyIe.h"

#include "MyIeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyIeDoc

IMPLEMENT_DYNCREATE(CMyIeDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyIeDoc, CDocument)
	//{{AFX_MSG_MAP(CMyIeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyIeDoc construction/destruction

CMyIeDoc::CMyIeDoc()
{
	// TODO: add one-time construction code here

}

CMyIeDoc::~CMyIeDoc()
{
}

BOOL CMyIeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyIeDoc serialization

void CMyIeDoc::Serialize(CArchive& ar)
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
// CMyIeDoc diagnostics

#ifdef _DEBUG
void CMyIeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyIeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyIeDoc commands
