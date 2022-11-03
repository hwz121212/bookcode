// MySerializeDoc.cpp : implementation of the CMySerializeDoc class
//

#include "stdafx.h"
#include "MySerialize.h"

#include "MySerializeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySerializeDoc

IMPLEMENT_DYNCREATE(CMySerializeDoc, CDocument)

BEGIN_MESSAGE_MAP(CMySerializeDoc, CDocument)
	//{{AFX_MSG_MAP(CMySerializeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySerializeDoc construction/destruction

CMySerializeDoc::CMySerializeDoc()
{
	// TODO: add one-time construction code here
   
}

CMySerializeDoc::~CMySerializeDoc()
{
}

BOOL CMySerializeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMySerializeDoc serialization

void CMySerializeDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar<<StrName;
		// TODO: add storing code here
	}
	else
	{   
		ar>>StrName;
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMySerializeDoc diagnostics

#ifdef _DEBUG
void CMySerializeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMySerializeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMySerializeDoc commands
