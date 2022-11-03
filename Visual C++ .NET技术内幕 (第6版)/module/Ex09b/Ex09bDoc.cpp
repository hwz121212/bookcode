// Ex09bDoc.cpp : implementation of the CEx09bDoc class
//

#include "stdafx.h"
#include "Ex09b.h"

#include "Ex09bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx09bDoc

IMPLEMENT_DYNCREATE(CEx09bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx09bDoc, CDocument)
END_MESSAGE_MAP()


// CEx09bDoc construction/destruction

CEx09bDoc::CEx09bDoc()
{
	// TODO: add one-time construction code here

}

CEx09bDoc::~CEx09bDoc()
{
}

BOOL CEx09bDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx09bDoc serialization

void CEx09bDoc::Serialize(CArchive& ar)
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


// CEx09bDoc diagnostics

#ifdef _DEBUG
void CEx09bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx09bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx09bDoc commands
