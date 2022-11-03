// MyPenDoc.cpp : implementation of the CMyPenDoc class
//

#include "stdafx.h"
#include "MyPen.h"

#include "MyPenDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyPenDoc

IMPLEMENT_DYNCREATE(CMyPenDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyPenDoc, CDocument)
	//{{AFX_MSG_MAP(CMyPenDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPenDoc construction/destruction

CMyPenDoc::CMyPenDoc()
{
	// TODO: add one-time construction code here

}

CMyPenDoc::~CMyPenDoc()
{
}

BOOL CMyPenDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyPenDoc serialization

void CMyPenDoc::Serialize(CArchive& ar)
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
// CMyPenDoc diagnostics

#ifdef _DEBUG
void CMyPenDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyPenDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyPenDoc commands
